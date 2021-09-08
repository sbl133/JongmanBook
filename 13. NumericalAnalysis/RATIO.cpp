#include<iostream>
using namespace std;
int n, m, r;
int ratio() {
	// 현재 승률 r
	r = ((long long)m*100 / n);
	int lo = 1, hi = 2000000000;
	// 할 수있는 모든 게임을 다 이겨도 승률이 안오른다면 return -1
	if (((long long)m + hi)*100 / ((long long)n + hi) < r + 1)
		return -1;
	// abs(hi-lo)가 10^20이하면 이분법을 100번 반복했을때
	// 구한 값과 정답과의 오차는 항상 10^(-7)보다 작다
	for (int i = 0; i < 100; i++) {
		int mid = ((long long)lo + hi) / 2;
		if (((long long)m + mid)*100 / ((long long)n + mid) < r + 1)
			lo = mid;
		else
			hi = mid;
	}
	return hi;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		cin >> n >> m;
		cout << ratio() << endl;
	}
}
