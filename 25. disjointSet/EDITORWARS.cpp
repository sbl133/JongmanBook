#include<iostream>
#include<vector>
using namespace std;
// 트리구조를 이용해 상호배타적 집합 구현
struct BipartiteUnionFind {
	// parent[i] = i의 부모 노드, 루트라면 i
	// rank[i] = i가 루트인 경우, i를 루트로 하는 트리의 랭크
	// enemy[i] = i가 루트인 경우, 해당 집합과 적대 관계인 집합의 루트의 번호(없으면 -1)
	// size[i] = i가 루트인 경우, 해당 집합의 크기
	vector<int> parent, rank, enemy, size;
	BipartiteUnionFind(int n) : parent(n), rank(n, 0), enemy(n, -1), size(n, 1) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}
	// u가 속한 트리의 루트를 찾는 함수
	int find(int u) {
		if (parent[u] == u)return u;
		return parent[u] = find(parent[u]);
	}
	// u가 속한 트리와 v가 속한 트리를 병합
	int merge(int u, int v) {
		if (u == -1 || v == -1)return max(u, v);
		u = find(u); v = find(v);
		if (u == v)return u;
		// 균일한 트리를 유지하기 위해서 트리의 높이가 큰 쪽이 루트
		if (rank[u] > rank[v])swap(u, v);
		parent[u] = v;
		size[v] += size[u];
		return v;
	}
	// u와 v가 서로 적대하는 집합
	bool dis(int u, int v) {
		u = find(u); v = find(v);
		// 모순발생
		if (u == v)return false;
		// 적의 적은 나의 동지
		int a = merge(u, enemy[v]);
		int b = merge(v, enemy[u]);
		enemy[a] = b; enemy[b] = a;
		return true;
	}
	// u와 v가 같은 집합
	bool ack(int u, int v) {
		u = find(u); v = find(v);
		// 모순발생
		if (enemy[u] == v)return false;
		// 동지의 적은 나의 적
		int a = merge(u, v);
		int b = merge(enemy[u], enemy[v]);
		enemy[a] = b;
		// 두 집합 다 적대하는 집합이 없으면 b는 -1일 수도 있기 때문에 예외처리
		if (b != -1)enemy[b] = a;
		return true;
	}
};
int n;
// 한 파티에 올 가능성이 있는 최대 인원 구하기
int maxParty(const BipartiteUnionFind& buf) {
	int ret = 0;
	for (int node = 0; node < n; node++) 
		if (buf.parent[node] == node) {
			int enemy = buf.enemy[node];
			// 중복으로 세는것을 막기 위해 enemy < node인 경우에만 계산
			if (enemy > node)continue;
			int mySize = buf.size[node];
			int enemySize = (enemy == -1 ? 0 : buf.size[enemy]);
			ret += max(mySize, enemySize);
		}
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int comments;
		cin >> n >> comments;
		BipartiteUnionFind uf(n);
		string relation;
		bool isContradiction = true;
		int a, b, isContradictionIndex = -1;
		for (int i = 0; i < comments; i++) {
			cin >> relation >> a >> b;
			if (relation == "ACK")
				isContradiction = isContradiction && uf.ack(a, b);
			else
				isContradiction = isContradiction && uf.dis(a, b);
			if (isContradictionIndex == -1 && !isContradiction)
				isContradictionIndex = i;
		}
		if (isContradiction)
			cout << "MAX PARTY SIZE IS " << maxParty(uf) << endl;
		else
			cout << "CONTRADICTION AT " << isContradictionIndex + 1 << endl;
	}
}
