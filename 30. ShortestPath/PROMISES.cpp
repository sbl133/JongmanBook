#include<iostream>
#include<vector>
using namespace std;
const int INF = 987654321;
int V, adj[200][200];
// 기존 고속도로로 최단거리를 계산하는 플로이드 알고리즘
void floyd() {
	for (int i = 0; i < V; i++)
		adj[i][i] = 0;
	for (int k = 0; k < V; k++)
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}
// (a,b)를 연결하는 비용 c인 간선을 추가했을때의 adj를 적절히 갱신
// 간선이 아무런 의미가 없을 경우 false반환
bool update(int a, int b, int c) {
	if (adj[a][b] <= c)return false;
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			// i~j의 최단경로가 (a,b)를 이용하려면
			// i~a-b~j or i~b-a~y의 형태를 가져야 한다.
			adj[i][j] = min(adj[i][j],
				min(adj[i][a] + c + adj[b][j], 
					adj[i][b] + c + adj[a][j]));
	return true;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		for (int i = 0; i < 200; i++)
			for (int j = 0; j < 200; j++)
				adj[i][j] = INF;
		int m, n, result = 0;
		cin >> V >> m >> n;
		for (int i = 0; i < m; i++) {
			int src, des, cost;
			cin >> src >> des >> cost;
			adj[src][des] = min(adj[src][des], cost);
			adj[des][src] = min(adj[src][des], cost);
		}
		floyd();
		for (int i = 0; i < n; i++) {
			int src, des, cost;
			cin >> src >> des >> cost;
			if (!update(src, des, cost))
				result++;
		}
		cout << result << endl;
	}
}
