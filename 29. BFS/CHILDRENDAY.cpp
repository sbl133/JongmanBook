#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
int n, m;
// here에서 edge를 통하면 나오는 정점
int append(int here, int edge, int mod) {
	int there = here * 10 + edge;
	if (there >= mod)return mod + there % mod;
	return there;
}
// C mod n == m인 최소 C 찾기
string gifts(string digits) {
	// 간선의 번호를 오름차순으로 정렬하면 장난감이 가장 적은순으로 경로 탐색 가능
	sort(digits.begin(), digits.end());
	// parent[i] = i의 부모, choice[i] = parent[i]에서 i로 연결된 간선의 번호
	vector<int> parent(2 * n, -1), choice(2 * n, -1);
	queue<int> q;
	// n+m미만이고 나머지가 0인 경우(맨 처음 경우)
	parent[0] = 0;
	q.push(0);
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		for (int i = 0; i < digits.size(); i++) {
			int there = append(here, digits[i] - '0', n);
			// there이 될수 있는 가장 빠른(장난감 수가 제일 적은) 경우 하나만 고려해도 됨
			if (parent[there] == -1) {
				parent[there] = here;
				choice[there] = digits[i] - '0';
				q.push(there);
			}
		}
	}
	// 장난감 갯수가 n+m이상이고 나머지가 m인 경우가 없음
	if (parent[n + m] == -1)return "IMPOSSIBLE";
	// 부모로 가는 연결을 따라가면서 C를 계산
	string ret;
	int here = n + m;
	while (parent[here] != here) {
		ret += char('0' + choice[here]);
		here = parent[here];
	}
	reverse(ret.begin(), ret.end());
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		string str;
		cin >> str >> n >> m;
		cout << gifts(str) << endl;
	}
}
