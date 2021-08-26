#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int INF = 987654321;
int n;
int A[100], pSum[100], pSqSum[100];
int cache[100][10];
void precalc() {
	// A를 크기순으로 정렬하고
	sort(A, A + n);
	// 부분합과 제곱의 부분합을 미리 계산한다
	pSum[0] = A[0];
	pSqSum[0] = A[0] * A[0];
	for (int i = 1; i < n; i++) {
		pSum[i] = pSum[i - 1] + A[i];
		pSqSum[i] = pSqSum[i - 1] + A[i] * A[i];
	}
}
int minError(int lo, int hi) {
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
	int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo - 1]);
	// 미분결과 m이 A[lo, hi]의 평균일때, m과의 오차 제곱의 합이 가장 낮다
	int m = int(0.5 + (double)sum / (hi - lo + 1));
	int ret = sqSum - 2 * m * sum + m * m * (hi - lo + 1);
	return ret;
}
int quantize(int from, int parts) {
	if (from == n)return 0;
	if (parts == 0)return INF;
	int& ret = cache[from][parts - 1];
	if (ret != -1) return ret;
	ret = INF;
	// 같은 숫자로 표현될 수들을 묶어서 오차제곱의 합을 구하고 남은 수열들은 재귀
	for (int partSize = 1; from + partSize <= n; partSize++)
		ret = min(ret, minError(from, from + partSize - 1)
			+ quantize(from + partSize, parts - 1));
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int parts;
		memset(cache, -1, sizeof(cache));
		cin >> n >> parts;
		for (int i = 0; i < n; i++)
			cin >> A[i];
		precalc();
		cout << quantize(0, parts) << endl;
	}
}
