#include<iostream>
#include<queue>
#include<vector>
using namespace std;
// 그래프의 인접리스트. pair(연결된 정점, 간선 가중치)
vector<pair<int, int>> adj[1001];
int fired[1000];
int firehouse[1000];
vector<int> dijkstra(int v) {
	vector<int> dist(v + 1, 987654321);
	dist[0] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, 0));
	while (!pq.empty()) {
		int here = pq.top().second;
		int cost = -pq.top().first;
		pq.pop();
		// 만약 지금 꺼낸것보다 더 짧은 경로를 이미 확인했으면 그만둔다
		if (dist[here] < cost)continue;
		// 인접 정점들을 검사
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int nextDist = adj[here][i].second + cost;
			// 더 짧은 경로 발견시 dist갱신 후 우선순위 큐에 삽입
			if (nextDist < dist[there]) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int v, e, n, m;
		for (int i = 0; i < 1001; i++)
			adj[i].clear();
		cin >> v >> e >> n >> m;
		for (int i = 0; i < e; i++) {
			int a, b, t;
			cin >> a >> b >> t;
			adj[a].push_back(make_pair(b, t));
			adj[b].push_back(make_pair(a, t));
		}
		for (int i = 0; i < n; i++) {
			int x;
			cin >> x;
			fired[i] = x;
		}
		int output = 0;
		for (int i = 0; i < m; i++) {
			int y;
			cin >> y;
			adj[0].push_back(make_pair(y, 0));
		}
		vector<int> result = dijkstra(v);
		for (int i = 0; i < n; i++)
			output += result[fired[i]];
		cout << output << endl;
	}
}
