/*#include<vector>
#include<iostream>
using namespace std;

int V;
vector<int> adj[1000];
vector<bool> visited;
const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;
int installed;
int dfs(int here) {
	visited[here] = true;
	int children[3] = { 0,0,0 };
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		if (!visited[there])
			++children[dfs(there)];
	}
	if (children[UNWATCHED]) {
		installed++;
		return INSTALLED;
	}
	if (children[INSTALLED])
		return WATCHED;
	return UNWATCHED;
}
int installCamera() {
	installed = 0;
	visited = vector<bool>(V, false);
	for (int i = 0; i < V; i++) {
		if (!visited[i] && dfs(i) == UNWATCHED) 
			installed++;
	}
	return installed;
}
int main() {
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		int edges;
		cin >> V >> edges;
		for (int j = 0; j < edges; j++) {
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		cout << installCamera() << endl;
		for (int j = 0; j < V; j++)
			adj[j].clear();
	}
}*/
#include<iostream>
#include<vector>
using namespace std;
vector<int> adj[1000];
vector<bool> visited;
const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;
// 지금까지 설치한 카메라의 수
int installed;
int dfs(int here) {
	visited[here] = true;
	int children[3] = { 0,0,0 };
	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];
		if (!visited[there])
			children[dfs(there)]++;
	}
	// 자손 노드 중 감시되지 않는 노드가 있을 경우 카메라 설치
	if (children[UNWATCHED]) {
		installed++;
		return INSTALLED;
	}
	// 자손 노드 중 카메라가 설치된 노드가 있을 경우 설치할 필요 없음
	if (children[INSTALLED])
		return WATCHED;
	return UNWATCHED;
}
int installCamera(int v) {
	installed = 0;
	visited = vector<bool>(v, false);
	// 여러개의 컴포넌트들이 있을 수 있으므로 전체 갤러리 확인
	// 루트갤러리가 UNWATCHED상태라면 루트에 카메라 설치가 필요
	for (int i = 0; i < v; i++)
		if (!visited[i] && dfs(i) == UNWATCHED)
			installed++;
	return installed;
}
void makeGraph(int h) {
	for (int i = 0; i < h; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int g, h;
		cin >> g >> h;
		for (int i = 0; i < 1000; i++)
			adj[i].clear();
		makeGraph(h);
		cout << installCamera(g) << endl;
	}
}
