#include<iostream>
#include<vector>
#include<queue>
using namespace std;
// 그래프의 인접 리스트 (연결된 정점 번호, 간선의 가중치)
vector<pair<int, int>> adj[402];
int v;
const int INF = 987654321;
vector<int> dijkstra(int src) {
	vector<int> dist(v, INF);
	dist[src] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (cost > dist[here])continue;
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			if (nextDist < dist[there]) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}
int start = 401;
// (a국 선수의 예상 시간 - b국 선수의 예상 시간)의 정점 번호를 반환
int vertex(int delta) {
	return delta + 200;
}
// a[] = A국 선수의 종목별 예상 시간
// b[] = B국 선수의 종목별 예상 시간
int solve(const vector<int>& a, const vector<int>& b) {
	// 정점의 개수
	v = 402;
	for (int i = 0; i < v; i++)
		adj[i].clear();
	for (int i = 0; i < a.size(); i++) {
		int delta = a[i] - b[i];
		adj[start].push_back(make_pair(vertex(delta), a[i]));
	}
	for (int delta = -200; delta <= 200; delta++) {
		// i번째 종목을 뒤에 붙일 경우
		for (int i = 0; i < a.size(); i++) {
			int next = delta + a[i] - b[i];
			// 두 선수의 시간차가 200이상 날 필요가 없다.
			if (abs(next) > 200)continue;
			adj[vertex(delta)].push_back(make_pair(vertex(next), a[i]));
		}
	}
	vector<int> shortest = dijkstra(start);
	int ret = shortest[vertex(0)];
	if (ret == INF) return -1;
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int m;
		vector<int> a, b;
		cin >> m;
		for (int i = 0; i < m; i++) {
			int timeA, timeB;
			cin >> timeA >> timeB;
			a.push_back(timeA);
			b.push_back(timeB);
		}
		int result = solve(a, b);
		if (result == -1)
			cout << "IMPOSSIBLE" << endl;
		else
			cout << result << endl;
	}
}
