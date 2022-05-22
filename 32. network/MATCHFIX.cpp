#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int MAX_V = 200;
const int INF = 987654321;
// 노드의 개수
int V;
// capacity: 보낼 수 있는 용량, flow: 흘러가는 유량
int capacity[MAX_V][MAX_V];
int flow[MAX_V][MAX_V];
// 최대 유량 계산
int networkFlow(int source, int sink) {
	// flow를 0으로 초기화
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	while (true) {
		// 너비 우선 탐색으로 증가 경로 찾기
		vector<int> parent(MAX_V, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front(); q.pop();
			for (int there = 0; there < V; there++) {
				// 잔여 용량이 남아있는 간선을 따라 탐색. 단, 이미 지난 노드를 다시 확인 할 필요X
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
			}
		}
		// 증가 경로가 없으면 종료
		if (parent[sink] == -1)
			break;
		// 증가 경로를 통해 유량을 얼마나 보낼지 계산
		int amount = INF;
		for(int p = sink; p!=source; p = parent[p])
			amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);
		// 유량 갱신
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}
	return totalFlow;
}
int n, m;
int wins[20], match[200][2];
// source(0번선수)가 총 totalWins번 승해서 우승할 수 있는지 계산
bool canWinWith(int totalWins) {
	// 이미 totalWins번 이상 이긴 선수가 있는경우
	if (*max_element(wins + 1, wins + n) >= totalWins)
		return false;
	// source는 0번 sink는 1번
	V = 2 + m + n;
	memset(capacity, 0, sizeof(capacity));
	for (int i = 0; i < m; i++) {
		// 소스에서 각 경기로 가는 간선
		capacity[0][2 + i] = 1;
		// 각 경기에서 두 선수로 가는 간선
		capacity[2 + i][2 + m + match[i][0]] = 1;
		capacity[2 + i][2 + m + match[i][1]] = 1;
	}
	// 각 선수에서 sink로, 가능한 최대 승수를 용량으로 하는 간선
	for (int i = 0; i < n; i++) {
		int maxWin = (i == 0 ? totalWins : totalWins - 1);
		capacity[2 + m + i][1] = maxWin - wins[i];
	}
	// 이때 모든 경기에 승자를 지정할 수 있는가?
	return networkFlow(0, 1) == m;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		// 남은 경기 수 중 0번 선수가 참여하는 경기의 수
		int matches = 0;
		cin >> n >> m;
		for (int i = 0; i < n; i++) 
			cin >> wins[i];
		for (int i = 0; i < m; i++) {
			cin >> match[i][0];
			cin >> match[i][1];
			if (match[i][0] == 0 || match[i][1] == 0)
				matches++;
		}
		int totalWins;
		for (totalWins = wins[0]; totalWins <= wins[0] + matches; totalWins++) {
			if (canWinWith(totalWins)) {
				cout << totalWins << endl;
				break;
			}
		}
		if (totalWins == wins[0] + matches + 1)
			cout << -1 << endl;
	}
}
