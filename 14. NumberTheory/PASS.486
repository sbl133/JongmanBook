#include<iostream>
#include<cmath>
using namespace std;
const int MAX_N = 10000000;
// index의 가장 작은 소인수
int minFactor[MAX_N + 1];
// index를 소인수 분해 했을때, minFactor[index]가 몇 승 포함되었는지
int minFactorPower[MAX_N + 1];
// index의 약수 갯수
int factor[MAX_N];
int n;
// 에라토스테네스의 체를 이용해서 minFactor저장
void eratosthenes2() {
	minFactor[0] = minFactor[1] = -1;
	int sqrtn = (int)(sqrt(MAX_N));
	for (int i = 2; i <= MAX_N; i++)
		minFactor[i] = i;
	// n의 소인수는 항상 sqrt(n)이하이다
	for (int i = 2; i <= sqrtn; i++) {
		if (minFactor[i] == i) {
			for (int j = i * i; j <= MAX_N; j += i)
				if (minFactor[j] == j)
					minFactor[j] = i;
		}
	}
}
void getFactorsSmart() {
	factor[1] = 1;
	for (int i = 2; i <= MAX_N; i++) {
		// i가 소수일 경우
		if (minFactor[i] == i) {
			minFactorPower[i] = 1;
			factor[i] = 2;
		}
		// i가 소수가 아닐경우
		else {
			int p = minFactor[i];
			int m = i / p;
			// i에서 p의 승수가 1일때
			if (p != minFactor[m])
				minFactorPower[i] = 1;
			// i에서 p의 승수가 2이상일때
			else
				minFactorPower[i] = minFactorPower[m] + 1;
			int a = minFactorPower[i];
			factor[i] = factor[m] * (a + 1) / a;
		}
	}
}
int main() {
	int testcase;
	cin >> testcase;
	eratosthenes2();
	getFactorsSmart();
	while (testcase--) {
		int lo, hi, result = 0;
		cin >> n >> lo >> hi;
		for (int i = lo; i <= hi; i++)
			if (factor[i] == n)
				result++;
		cout << result << endl;
	}
}
