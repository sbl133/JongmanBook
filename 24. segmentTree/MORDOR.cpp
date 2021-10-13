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
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int n, q;
		cin >> n >> q;
		// 최솟값을 구하기 위한 vector a
		// 최댓값을 구하기 위한 vector b
		vector<int> a, b;
		int sign;
		for (int i = 0; i < n; i++) {
			cin >> sign;
			a.push_back(sign);
			// 최댓값을 구하기 위해서 원소에 부호를 반대로
			b.push_back(-sign);
		}
		RMQ rmqA(a);
		RMQ rmqB(b);
		for (int i = 0; i < q; i++) {
			int left, right;
			cin >> left >> right;
			cout << -rmqB.query(left, right) - rmqA.query(left, right) << endl;
		}
	}
}
