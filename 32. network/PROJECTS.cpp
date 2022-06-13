#include<vector>
#include<iostream>
#include<queue>
#include<numeric>
#include<cstring>
using namespace std;
const int INF = 987654321;
int V;
// capacity[u][v] = u에서 v로 보낼 수 있는 용량
// flow[u][v] = u에서 v로 흘러가는 유량 (반대 방향인 경우 음수)
int capacity[210][210], flow[210][210];
// flow[][]를 계산하고 총 유량 반환
int networkFlow(int source, int sink) {
	// flow를 0으로 초기화
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	while (true) {
		// 너비 우선 탐색으로 증가 경로를 찾는다.
		vector<int> parent(V, -1);
		queue<int> q;
		q.push(source);
		// 유량이 흐르는 방향을 역추적 하기위한 parent
		parent[source] = source;
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front(); q.pop();
			for (int there = 0; there < V; there++)
				// 잔여 용량이 남아있는 간선을 따라 탐색
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
		}
		// 증가 경로가 없으면 종료
		if (parent[sink] == -1)break;
		// 증가 경로를 통해 유량을 얼마나 보낼지 결정
		int amount = INF;
		for (int p = sink; p != source; p = parent[p])
			amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);
		// 증가 경로를 토해 유량을 보냄
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}
	return totalFlow;
}
int n, m;
int profit[100], cost[100];
int requires[100][100];
// 최대 순이익 반환
int maxProfit() {
	// 네트워크 만들기
	const int SRC = 0, SNK = 1;
	V = n + m + 2;
	memset(capacity, 0, sizeof(capacity));
	memset(flow, 0, sizeof(flow));
	for (int i = 0; i < n; i++)
		capacity[SRC][2 + i] = profit[i];
	for (int i = 0; i < m; i++)
		capacity[2 + n + i][SNK] = cost[i];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (requires[i][j])
				capacity[2 + i][2 + n + j] = INF;
	int M = accumulate(profit, profit + n, 0);
	int C = networkFlow(SRC, SNK);
	return M - C;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		cin >> n >> m;
		for (int i = 0; i < n; i++)
			cin >> profit[i];
		for (int i = 0; i < m; i++)
			cin >> cost[i];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> requires[i][j];
		cout << maxProfit() << endl;
	}
}
