#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
// 그래프의 인접 리스트
vector<vector<int>> adj;
// 두 시간대 a, b 가 서로 겹치지 않는지 확인
bool disjoint(const pair<int, int>& a, const pair<int, int>& b) {
	return a.second <= b.first || b.second <= a.first;
}
// meetings[]: 각 팀이 하고 싶어하는 회의 시간 목록
//  => 2-SAT문제를 위한 함의 그래프 생성
// i번 팀은 meetings[i*2] 또는 meetings[i*2+1]중 하나는 회의를 해야 함
void makeGraph(const vector<pair<int, int>>& meetings) {
	int vars = meetings.size();
	// 그래프는 각 변수마다 두 개의 정점을 가짐
	adj.clear(); adj.resize(vars * 2);
	// 두개의 회의중 하나는 반드시 해야한다.
	for (int i = 0; i < vars; i += 2) {
		// (i || j)절 추가
		int j = i + 1;
		adj[i * 2 + 1].push_back(j * 2); // ~i => j
		adj[j * 2 + 1].push_back(i * 2); // ~j => i
	}
	// 회의를 하나 했으면 남은 회의는 반드시 안해야한다.
	for (int i = 0; i < vars; i += 2) {
		// (!i || !j)절 추가
		int j = i + 1;
		adj[i * 2].push_back(j * 2 + 1); // i => ~j
		adj[j * 2].push_back(i * 2 + 1); // j => ~i
	}
	for (int i = 0; i < vars; i++) 
		for (int j = 0; j < i; j++) {
			// i번 회의와 j번 회의가 서로 겹치 경우
			if (!disjoint(meetings[i], meetings[j])) {
				// (~j || ~i)절 추가
				adj[i * 2].push_back(j * 2 + 1); // i => ~j
				adj[j * 2].push_back(i * 2 + 1); // j => ~i
			}
		}
}
// 각 정점의 (강결합)컴포넌트 번호, 0부터 시작
vector<int> sccId;
// 각 정점의 발견 순서
vector<int> discovered;
// 정점의 번호를 담는 스택
stack<int> st;
// 컴포넌트 번호 카운터, 정점 발견순서 카운터
int sccCounter, vertexCounter;
// here를 루트로 하는 서브트리에서 역방향, 교차간선을 통해 갈 수 있는 최소 정점 반환
int scc(int here) {
	int ret = discovered[here] = vertexCounter++;
	// here를 스택에 넣는다. here의 자손들은 here위로 들어감
	st.push(here);
	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];
		// (here, there)가 트린 간선
		if (discovered[there] == -1)
			ret = min(ret, scc(there));
		// there가 무시해야하는 교차간선이 아니거나, 역방향 간선이라면
		else if (sccId[there] == -1)
			ret = min(ret, discovered[there]);
	}
	// here에서 부모로 올라가는 간선을 끊어야 할지 확인
	if (ret == discovered[here]) {
		// here를 루트로 하는 서브트리에 있는 정점들을 하나의 컴포넌트로 묶기
		while (true) {
			int t = st.top();
			st.pop();
			sccId[t] = sccCounter;
			if (t == here)break;
		}
		sccCounter++;
	}
	return ret;
}
// scc알고리즘 실행
vector<int> tarjanSCC() {
	// 배열들 초기화
	sccId = discovered = vector<int>(adj.size(), - 1);
	// 카운터 초기화
	sccCounter = vertexCounter = 0;
	// 방문하지 않은 모든 정점에서 scc()호출
	for (int i = 0; i < adj.size(); i++)
		if (discovered[i] == -1)
			scc(i);
	return sccId;
}
// adj에 함의 그래프의 인접 리스트 표현이 주어질때, 2-SAT 문제의 답을 반환
vector<int> solve2SAT() {
	int n = adj.size() / 2; // 회의 개수
	// 함의 그래프의 정점들을 강결합 요소별로 묶기
	vector<int> label = tarjanSCC();
	// 하나의 회의를 나타내는 두 정점이 같은 컴포넌트에 속하면 답이 없음
	for (int i = 0; i < n * 2; i += 2) {
		if (label[i] == label[i + 1])
			return vector<int>();
	}
	// SAT문제를 해결 가능하므로 답을 생성
	vector<int> value( n, -1);
	// tarjan알고리즘에서 scc번호는 위상 정렬의 역순
	// 위상 정렬 순서로 재정렬
	vector<pair<int, int>> order;
	for (int i = 0; i < 2 * n; i++)
		order.push_back(make_pair(-label[i], i));
	sort(order.begin(), order.end());
	// 각 정점에 값을 배정
	for (int i = 0; i < 2 * n; i++) {
		int vertex = order[i].second;
		int variable = vertex / 2, isTrue = vertex % 2 == 0;
		if (value[variable] != -1)continue;
		// !A가 A보다 먼저 나왔으면 A는 참
		// A가 !A보다 먼저 나왔으면 A는 거짓
		value[variable] = !isTrue;
	}
	return value;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int meetingNum;
		vector<pair<int, int>>meetings;
		cin >> meetingNum;
		for (int i = 0; i < meetingNum; i++) {
			int start1, end1, start2, end2;
			cin >> start1 >> end1;
			cin >> start2 >> end2;
			meetings.push_back(make_pair(start1, end1));
			meetings.push_back(make_pair(start2, end2));
		}
		makeGraph(meetings);
		vector<int> result = solve2SAT();
		if (result.size() == 0) {
			cout << "IMPOSSIBLE" << endl;
		}
		else {
			cout << "POSSIBLE" << endl;
			for (int i = 0; i < result.size(); i++) {
				if (result[i] == 1)
					cout << meetings[i].first << ' ' << meetings[i].second << endl;
			}
		}
	}
}
