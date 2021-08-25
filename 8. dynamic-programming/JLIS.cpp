#include<iostream>
#include<cstring>
#include<limits>
using namespace std;

const long long NEGINF = numeric_limits<long long>::min();
int n, m, A[100], B[100];
int cache[101][101];
int jlis(int indexA, int indexB) {
	int& ret = cache[indexA + 1][indexB + 1];
	if (ret != -1)return ret;
	ret = 2;
	// 처음에 전체순회를 위해 index를 -1부터 시작
	// index == -1이면 가장 작은값이 들어간다
	long long a = (indexA == -1 ? NEGINF : A[indexA]);
	long long b = (indexB == -1 ? NEGINF : B[indexB]);
	// 지금까지 담은 수열중에 가장 큰 값 maxElement
	long long maxElement = max(a, b);
	// A와 B에서 현재 index 다음으로 오는 요소중 maxElement보다 작은 것들을 검사
	for (int nextA = indexA + 1; nextA < n; nextA++)
		if (maxElement < A[nextA])
			ret = max(ret, jlis(nextA, indexB) + 1);
	for (int nextB = indexB + 1; nextB < m; nextB++)
		if (maxElement < B[nextB])
			ret = max(ret, jlis(indexA, nextB) + 1);
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		memset(cache, -1, sizeof(cache));
		cin >> n >> m;
		long long input;
		for (int i = 0; i < n; i++) {
			cin >> input;
			A[i] = input;
		}
		for (int i = 0; i < m; i++) {
			cin >> input;
			B[i] = input;
		}
		cout << jlis(-1, -1) - 2 << endl;
	}
}
