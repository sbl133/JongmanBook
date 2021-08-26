#include<iostream>
#include<cstring>
using namespace std;
const int MOD = 1000000007;
int n;
int cache[101];
int wholeTiling(int width) {
	if (width <= 1)return 1;
	int& ret = cache[width];
	if (ret != -1)return ret;
	// 타일을 세로로 한개 놓거나 가로로 두개 놓거나
	ret = (wholeTiling(width - 1) + wholeTiling(width - 2)) % MOD;
	return ret;
}
int asysmTiling(int width) {
	int ret;
	// width가 홀수일 경우 가운데 세로로 타일하나 붙이면 대칭형성가능
	if (width % 2) {
		ret = wholeTiling(width) - wholeTiling((width - 1) / 2);
	}
	// width가 짝수일 경우 정확히 반으로 나눠서 대칭형성하거나
	// 가운데 2칸에 타일을 가로로 두개 붙으면 대칭형성가능
	else {
		ret = wholeTiling(width) 
			- wholeTiling(width / 2) - wholeTiling((width - 2) / 2);
	}
	while (ret < 0)
		ret += MOD;
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		memset(cache, -1, sizeof(cache));
		cin >> n;
		cout << asysmTiling(n) << endl;
	}
}
