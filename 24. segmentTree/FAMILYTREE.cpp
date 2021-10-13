#include<iostream>
#include<vector>
#include<limits>
using namespace std;
const int INF_MAX = numeric_limits<int>::max();
// 구간 최소 쿼리를 위한 구조체
struct RMQ {
	int n;
	// 각 구간의 최소치
	vector<int> rangeMin;
	RMQ(vector<int>& arr) {
		n = arr.size();
		rangeMin.resize(4 * n);
		init(arr, 0, n - 1, 1);
	}
	// node번째 노드가 arr[left, right] 배열을 표현할 때
	// node번째 노드를 루트로 하는 서브트리를 초기화하고, 이 구간의 최소치를 반환
	int init(vector<int>& arr, int left, int right, int node) {
		// 리프노드까지 오면 자기 rangeMin에 자기 자신 저장후 return
		if (left == right)
			return rangeMin[node] = arr[left];
		int mid = (left + right) / 2;
		// 두 구간의 최소값중 작은값이 두구간을 합친 구간의 최솟값
		rangeMin[node] = min(init(arr, left, mid, node * 2),
			init(arr, mid + 1, right, 2 * node + 1));
		return rangeMin[node];
	}
	// node가 표현하는 범위 arr[nodeLeft, nodeRight]가 주어질 때
	// 이 범위와 arr[left, right]의 교집합의 최소치 구하기
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		// 구하고자 하는 범위를 벗어나면 엄청나게 큰 값을 return
		if (left > nodeRight || right < nodeLeft)
			return INF_MAX;
		// 구하고자 하는 범위에 완전히 속해있으면 구간 최솟값 return
		if (left <= nodeLeft && right >= nodeRight)
			return rangeMin[node];
		// 둘다 아니면 양쪽 구간을 쪼개서 풀고 그 결과를 합친다
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid),
			query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}
	// query를 외부애서 호출하기 위한 overloading
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}
};
const int MAX_N = 100000;
int n;
vector<int> child[MAX_N];
// 트리의 번호와 일련번호(전위탐색순서) 사이의 대응관계
int no2serial[MAX_N], serial2no[MAX_N];
// 각 노드가 trip에 처음 등장하는 위치, 각 노드의 깊이
int locInTrip[MAX_N], depth[MAX_N];
// 다음 일련번호
int nextSerial;
// 깊이가 d인 노드 here에 자식들을 전위 탐색
void traverse(int here, int d, vector<int>& trip) {
	// traverse가 처음 방문하자마자 일련 번호 부여
	no2serial[here] = nextSerial;
	serial2no[nextSerial] = here;
	nextSerial++;
	// 깊이 저장
	depth[here] = d;
	// 현재 노드가 trip에 처음 등장하는 위치 = 현재 trip의 끝
	locInTrip[here] = trip.size();
	trip.push_back(no2serial[here]);
	// 자식들을 방문
	for (int i = 0; i < child[here].size(); i++) {
		traverse(child[here][i], d + 1, trip);
		// 자식 방문이 끝날때마다 다시 자기 자신으로 돌아옴
		trip.push_back(no2serial[here]);
	}
}
// trip에 대한 RMQ트리를 생성
RMQ* prepareRMQ() {
	nextSerial = 0;
	vector<int> trip;
	// trip 생성
	traverse(0, 0, trip);
	return new RMQ(trip);
}
// u와 v사이의 거리를 계산
int distance(RMQ* rmq, int u, int v) {
	int lu = locInTrip[u];
	int lv = locInTrip[v];
	if (lu > lv)swap(lu, lv);
	// rmq에서 u와 v의 공통 조상를 찾아서
	int lca = serial2no[rmq->query(lu, lv)];
	// u와 v 사이의 거리 계산
	return depth[u] + depth[v] - 2 * depth[lca];
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		for (int i = 0; i < MAX_N; i++)
			child[i].clear();
		int q;
		cin >> n >> q;
		for (int i = 1; i < n; i++) {
			int parent;
			cin >> parent;
			child[parent].push_back(i);
		}
		RMQ* rmq = prepareRMQ();
		for (int i = 0; i < q; i++) {
			int a, b;
			cin >> a >> b;
			cout << distance(rmq, a, b) << endl;
		}
	}
}
