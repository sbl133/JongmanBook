
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int INF = 987654321;
// 그래프의 정점과 인접행렬 표현
int V, adj[500][500];
// 각 정점에서 음주단속을 할때 걸리는 시간
int delay[500];
int W[500][500];
void solve() {
	// 모든 정점을 단속 소요시간의 오름차순으로 정렬
	vector<pair<int, int>> order;
	for (int i = 0; i < V; i++)
		order.push_back(make_pair(delay[i], i));
	sort(order.begin(), order.end());
	// 정점을 하나도 거치지 않고 갈 수 있는 최단경로
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			if (i == j)
				W[i][j] = 0;
			else
				W[i][j] = adj[i][j];
	for (int k = 0; k < V; k++) {
		// k번째로 예상시간이 적게 걸리는 정점을 지나서 얻을 수 있는 최단거리
		int w = order[k].second;
		for(int i=0; i<V; i++)
			for (int j = 0; j < V; j++) {
				adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
				W[i][j] = min(W[i][j], adj[i][w] + adj[w][j] + delay[w]);
			}
	}
}
int main() {
	int edgeNum;
	cin >> V >> edgeNum;
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			if (i != j)
				adj[i][j] = INF;
	for (int i = 0; i < V; i++)
		cin >> delay[i];
	for (int i = 0; i < edgeNum; i++) {
		int a, b, time;
		cin >> a >> b >> time;
		// 입력에서 정점의 번호가 1번 부터 시작하므로
		// -1 해서 0번부터 시작하게 조작
		adj[a-1][b-1] = time;
		adj[b-1][a-1] = time;
	}
	solve();
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int src, des;
		cin >> src >> des;
		cout << W[src-1][des-1] << endl;
	}
}
