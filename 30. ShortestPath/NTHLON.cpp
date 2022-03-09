/*#include<queue>
#include<vector>
#include<iostream>
using namespace std;

int V;
const int INF = 987654321;
vector<pair<int, int>> adj[410];
const int START = 401;
vector<int> dijkstra(int src) {
	vector<int> dist(V, INF);
	dist[src] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()) {
		int here = pq.top().second;
		int cost = -pq.top().first;
		pq.pop();
		if (cost > dist[here])continue;
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}

int vertex(int delta) {
	return 200 + delta;
}
int solve(const vector<int>& a, const vector<int>& b) {
	V = 402;
	for (int i = 0; i < V; i++)
		adj[i].clear();
	for (int i = 0; i < a.size(); i++) {
		int delta = a[i] - b[i];
		adj[START].push_back(make_pair(vertex(delta), a[i]));
	}
	for (int delta = -200; delta <= 200; delta++) {
		for (int i = 0; i < a.size(); i++) {
			int next = delta + a[i] - b[i];
			if (abs(next) > 200)continue;
			adj[vertex(delta)].push_back(make_pair(vertex(next), a[i]));
		}
	}
	vector<int> shortest = dijkstra(START);
	int ret = shortest[vertex(0)];
	if (ret == INF) return -1;
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int games;
		cin >> games;
		vector<int> a, b;
		int time1, time2;
		int result;
		while (games--) {
			cin >> time1 >> time2;
			a.push_back(time1);
			b.push_back(time2);
		}
		result = solve(a, b);
		if (result == -1)
			cout << "IMPOSSIBLE" << endl;
		else
			cout << result << endl;
	}
}*/
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
			int there = adj[here][i].second;
			int nextDist = cost + adj[here][i].first;
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
		cout << solve(a, b) << endl;
	}
}
