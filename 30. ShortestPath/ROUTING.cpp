#include<iostream>
#include<vector>
#include<queue>
#include<limits>
using namespace std;
// 정점의 갯수
int V;
// 인접리스트
vector<pair<int, double>> adj[10000];
// 각 정점까지의 최소 증폭량 구하는 다익스트라 알고리즘
vector<double> dijkstra(int src) {
	vector<double> dist(V, numeric_limits<double>::max());
	// 간선을 지날때마다 곱 연산을 해야하므로 초기 값 1.0
	dist[src] = 1.0;
	// priority_queue<해당 정점까지의 증폭량, 정점번호>
	priority_queue<pair<double, int>> pq;
	// 우선순위 큐는 디폴트가 내림차순이므로 -1 곱해서 넣어준다
	pq.push(make_pair(-1.0, src));
	while (!pq.empty()) {
		double cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (dist[here] < cost)continue;
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			// here에서 there로 갔을때 증폭량
			double nextDist = cost * adj[here][i].second;
			// 이제까지 구한것 중에서 가장 작으면 우선순위큐에 넣는다.
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}
int main() {
	cout << fixed;
	cout.precision(10);
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int edges;
		cin >> V >> edges;
		for (int i = 0; i < V; i++)
			adj[i].clear();
		int a, b;
		double c;
		for (int i = 0; i < edges; i++) {
			cin >> a >> b >> c;
			adj[a].push_back(make_pair(b, c));
			adj[b].push_back(make_pair(a, c));
		}
		vector<double> output = dijkstra(0);
		cout << output[V - 1] << endl;
	}
}
