#include<iostream>
#include<vector>
using namespace std;
// 팬윅트리의 구현
// 초기화시 A[]의 원소가 전부 0이라 생각
struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}
	// A[0,pos]의 부분 합을 계산
	int sum(int pos) {
		int ret = 0;
		pos++;
		while (pos > 0) {
			ret += tree[pos];
			pos &= (pos - 1);
		}
		return ret;
	}
	// A[pos]에 val을 더함
	void add(int pos, int val) {
		pos++;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};
// 팬윅트리를 이용해 문제를 해결
long long countMoves(const vector<int>& A) {
	FenwickTree tree(1000000);
	long long ret = 0;
	// 배열의 요소를 하나씩 추가하면서 자기보다 큰 요소의 갯수를 구함
	for (int i = 0; i < A.size(); i++) {
		ret += tree.sum(999999) - tree.sum(A[i]);
		tree.add(A[i], 1);
	}
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int n;
		cin >> n;
		vector<int> arr;
		int element;
		for (int i = 0; i < n; i++) {
			cin >> element;
			arr.push_back(element);
		}
		cout << countMoves(arr) << endl;
	}
}
