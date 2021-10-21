#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
// 그래프의 인접 행렬 표현. adj[i][j]=i와 j사이의 간선의 수
vector<vector<int>> adj;
// graph[i][j] = i로 시작해서 j로 끝나는 단어의 목록
vector<string>graph[26][26];
// indegree[i]=i로 시작하는 단어의 수
// outdegree[i]=i로 끝나는 단어의 수
vector<int> indegree, outdegree;
void makeGraph(const vector<string>& words) {
	// 전역변수 초기화
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			graph[i][j].clear();
	adj = vector<vector<int>>(26, vector<int>(26, 0));
	indegree = outdegree = vector<int>(26, 0);
	// 주어진 단어들을 그래프에 추가
	for (int i = 0; i < words.size(); i++) {
		int a = words[i][0] - 'a';
		int b = words[i][words[i].length() - 1] - 'a';
		graph[a][b].push_back(words[i]);
		adj[a][b]++;
		outdegree[a]++;
		indegree[b]++;
	}
}
// 유향 그래프의 인접 행렬 adj가 주어질 때 오일러 서킷 혹은 트레일 계산
void getEulerCircuit(int here, vector<int>& circuit) {
	for (int there = 0; there < adj.size(); there++) 
		while (adj[here][there] > 0) {
			adj[here][there]--;
			getEulerCircuit(there, circuit);
		}
	// push를 마지막에 함으로써 한 정점에 나가는 간선이 여러개여도
	// 방문 순서가 꼬이지 않게 circuit을 거꾸로 구성
	circuit.push_back(here);
}
// 현재 그래프의 오일러 트레일이나 서킷을 반환
vector<int> getEulerTrailOrCircuit() {
	vector<int> circuit;
	// 그래프의 형태가 트레일이면 시작점에서 순환 시작
	for(int i=0; i<26; i++)
		if (outdegree[i] == indegree[i] + 1) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	// 트레일이 아니면 서킷이니, 아무 정점에서나 시작
	for(int i=0; i<26; i++)
		if (outdegree[i]) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	// 모두 실패한경우 빈 배열 반환
	return circuit;
}
// 현재 그래프의 오일러 서킷/트레일 존재 여부를 확인
bool checkEuler() {
	// 트레일의 경우 시작점과 끝점이 하나씩인지 체크
	int plus1 = 0, minus1 = 0;
	for (int i = 0; i < 26; i++) {
		// 각 정점의 차수 계산
		int delta = outdegree[i] - indegree[i];
		if (delta < -1 || 1 < delta) return false;
		if (delta == 1)plus1++;
		if (delta == -1)minus1++;
	}
	return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}
string solve(const vector<string>& words) {
	makeGraph(words);
	if (!checkEuler())return "IMPOSSIBLE";
	// 오일러 서킷이나 경로 탐색
	vector<int> circuit = getEulerTrailOrCircuit();
	// 모든 간선을 다 들렸으면, 방문한 정점의 수가 모든 간선의 수보다 1많아야 된다.
	if (circuit.size() != words.size() + 1) return "IMPOSSIBLE";
	// 거꾸로 circuit채운거 다시 뒤집기
	reverse(circuit.begin(), circuit.end());
	string ret;
	for (int i = 1; i < circuit.size(); i++) {
		int a = circuit[i - 1], b = circuit[i];
		if (ret.size())ret += " ";
		ret += graph[a][b].back();
		graph[a][b].pop_back();
	}
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int wordNum;
		vector<string> words;
		string str;
		cin >> wordNum;
		for (int i = 0; i < wordNum; i++) {
			cin >> str;
			words.push_back(str);
		}
		cout << solve(words) << endl;
	}
}
