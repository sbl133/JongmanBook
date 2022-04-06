#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
// kruscal 알고리즘을 사용하기 위한 disjointSet 
struct DisjointSet {
	vector<int> rank, parent;
	DisjointSet(int v) : rank(v), parent(v, 1) {
		for (int i = 0; i < v; i++)
			parent[i] = i;
	}
	// 자신의 최고 조상을 찾는 메서드
	int find(int u) {
		if (parent[u] == u)
			return u;
		return parent[u] = find(parent[u]);
	}
	// u, v가 공통조상을 갖도록 합치는 메서드
	void merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) return;
		if (rank[u] < rank[v])
			swap(u, v);
		parent[v] = u;
		if (rank[u] == rank[v])rank[u]++;
	}
};
int V;
double adj[500][500];
// kruscal 알고리즘
double kruscal() {
	// 최소 스패닝트리를 만드는데 드는 총 비용 반환
	double ret = 0;
	// 모든 간선들을 비용의 오름차순으로 정렬
	vector<pair<double, pair<int, int>>> edges;
	for(int i=0; i<V; i++)
		for (int j = 0; j < V; j++) {
			double cost = adj[i][j];
			edges.push_back(make_pair(cost, make_pair(i, j)));
		}
	sort(edges.begin(), edges.end());
	// disjointSet를 이용해서 트리에 소속되어 있는지 확인
	DisjointSet sets(V);
	for (int i = 0; i < edges.size(); i++) {
		double cost = edges[i].first;
		int u = edges[i].second.first;
		int v = edges[i].second.second;
		// 트리에 소속되어있지 않다면 소속시킨다
		if (sets.find(u) == sets.find(v))continue;
		sets.merge(u, v);
		ret += cost;
	}
	return ret;
}
int x[500];
int y[500];
const int INF = 987654321;
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int cable;
		cin >> V >> cable;
		for (int i = 0; i < V; i++)
			cin >> x[i];
		for (int i = 0; i < V; i++)
			cin >> y[i];
		for(int i=0; i<V; i++)
			for (int j = 0; j < V; j++) {
				double dist = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
				adj[i][j] = adj[j][i] = dist;
			}
		// 이미 연결된 케이블은 비용이 0으로 처리
		for (int i = 0; i < cable; i++) {
			int src, des;
			cin >> src >> des;
			adj[src][des] = 0;
			adj[des][src] = 0;
		}
		cout << fixed;
		cout.precision(10);
		cout << kruscal() << endl;
	}
}
