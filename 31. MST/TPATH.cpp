#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int INF = 987654321;
// kruscal 알고리즘을 사용하기 위한 disjointSet
struct DisjointSet {
	vector<int> rank, parent;
	DisjointSet(int v) : rank(v, 1), parent(v) {
		for (int i = 0; i < v; i++)
			parent[i] = i;
	}
	int find(int u) {
		if (parent[u] == u)return u;
		return parent[u] = find(parent[u]);
	}
	void merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v)
			return;
		if (rank[u] < rank[v])
			swap(u, v);
		parent[v] = u;
		if (rank[u] == rank[v])
			rank[u]++;
	}
};
int V;
vector<pair<int, pair<int, int>>> edges;
// edges를 미리 정렬 시키고 가중치가 low이상인 간선만 이용해서 0~(v-1)의 경로를 만듦
int kruscalMinUpperBound(int low) {
	DisjointSet disjointSet(V);
	for (int i = low; i < edges.size(); i++) {
		// edges[i]를 그래프에 추가
		disjointSet.merge(edges[i].second.first, edges[i].second.second);
		// 0~(v-1)이 연결되었으면 가장 최근에 추가한 간선이 최대치
		if (disjointSet.find(0) == disjointSet.find(V - 1)) 
			return edges[i].first;
	}
	return INF;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		edges.clear();
		int edgeNum;
		cin >> V >> edgeNum;
		for (int i = 0; i < edgeNum; i++) {
			int src, des, cost;
			cin >> src >> des >> cost;
			edges.push_back(make_pair(cost, make_pair(src, des)));
		}
		// edges를 미리 정렬
		sort(edges.begin(), edges.end());
		int result = INF;
		// 가중치가 low이상인 간선들만 이용해서 경로 만들어 보기
		for (int i = 0; i < edges.size(); i++) 
			result = min(result, kruscalMinUpperBound(i) - edges[i].first);
		cout << result << endl;
	}
}
