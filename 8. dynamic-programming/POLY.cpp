#include<iostream>
#include<cstring>
using namespace std;
const int MOD = 10000000;
int n;
int cache[101][101];
// 위에 overBlock개의 블록이 놓여있을때 Blocks개의 블록을 놓는 경우의 수
int poly(int Blocks, int overBlock) {
	if (Blocks == 0)return 1;
	int& ret = cache[Blocks][overBlock];
	if (ret != -1)return ret;
	ret = 0;
	for (int how = 1; how <= Blocks; how++) {
		// 현재라인에 how개의 블록을 놓는 경우의 수는 overBlock+how-1
		// 단 맨위 라인이라면 경우의 수는 1
		int curCase = (overBlock == 0 ? 1 : overBlock + how - 1);
		ret = (ret + poly(Blocks - how, how) * curCase) % MOD;
	}
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		cin >> n;
		memset(cache, -1, sizeof(cache));
		cout << poly(n, 0) << endl;
	}
}
