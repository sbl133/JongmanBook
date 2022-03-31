
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
const int INF = 987654321;
// 은하계의 수
int V;
// 얼마나 미래로 갈 수 있는지 계산하기 위한 adj
vector<pair<int, int>> adjForMax[100];
// 얼마나 과거로 갈 수 있는지 계산하기 위한 adj
vector<pair<int, int>> adjForMin[100];
// src에서 des로 갈 수 있는지 없는지 판단하기 위한 2차원 배열
bool reachable[100][100];
// floyd알고리즘을 이용해 reachable 계산
void calcReachable() {
	for (int i = 0; i < V; i++)
		reachable[i][i] = true;
	for (int k = 0; k < V; k++)
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				reachable[i][j] = reachable[i][j] || (reachable[i][k] && reachable[k][j]);
}
// src에서 target까지의 최단 거리 계산
int bellman(int src, int target, vector<pair<int, int>>* adj) {
	// 시작점을 제외한 모든 정점의까지의 최단 거리 상한을 INF로 초기화
	vector<int> upper(V, INF);
	upper[src] = 0;
	// V-1번 순회
	for (int iter = 0; iter < V - 1; iter++)
		for (int here = 0; here < V; here++) 
			for (int i = 0; i < adj[here].size(); i++) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				// upper 완화 시도
				upper[there] = min(upper[there], upper[here] + cost);
			}
	// upper가 갱신되면 음수 사이클 존재
	for (int here = 0; here < V; here++) 
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int cost = adj[here][i].second;
			if (upper[here] + cost < upper[there])
				// 음수 사이클이 경로상에 존재하면 무한으로 발산
				if (reachable[src][here] && reachable[here][target])
					return -INF;
		}
	return upper[target];
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		memset(reachable, false, sizeof(reachable));
		for (int i = 0; i < 100; i++) {
			adjForMax[i].clear();
			adjForMin[i].clear();
		}
		int edgeSize;
		cin >> V >> edgeSize;
		for (int i = 0; i < edgeSize; i++) {
			int src, des, cost;
			cin >> src >> des >> cost;
			adjForMin[src].push_back(make_pair(des, cost));
			adjForMax[src].push_back(make_pair(des, -cost));
			reachable[src][des] = true;
		}
		calcReachable();
		int minimum = bellman(0, 1, adjForMin);
		int maximum = bellman(0, 1, adjForMax);
		// 경로가 없어도 upper[target]은 갱신 가능하기 때문에 minimum == INF 조건은 절대 안됨!!!
		// 대신 reachable를 사용해서 도달 가능한지 판단
		if (!reachable[0][1])
			cout << "UNREACHABLE" << endl;
		else {
			if (minimum == -INF)
				cout << "INFINITY ";
			else
				cout << minimum << " ";
			if (maximum == -INF)
				cout << "INFINITY" << endl;
			else
				cout << -maximum << endl;
		}
	}
}
