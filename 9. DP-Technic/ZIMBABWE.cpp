#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
const int MOD = 1000000007;
string e, digits;
int n, m;
int cache[1 << 14][20][2];
// index: 이번에 채울 자리 인덱스, taken: 지금까지 사용한 수
// mod: 지금까지 만든 가격의 m에 대한 나머지, less: e보다 작으면 1 아니면 0
int price(int index, int taken, int mod, int less) {
	// 끝자리까지 왔는데 나머지가 있거나 less가 1이면(e랑 똑같은가격)이면 return 0;
	if (index == n)
		return (less && mod == 0) ? 1 : 0;
	int& ret = cache[taken][mod][less];
	if (ret != -1)return ret;
	ret = 0;
	for (int next = 0; next < n; next++) 
		// next가 아직 안사용한 숫자
		if (((1 << next) & taken) == 0) {
			// e보다 크면 continue
			if (!less && e[index] < digits[next])
				continue;
			// 숫자의 중복사용 방지
			if (next > 0 && digits[next - 1] == digits[next]
				&& (taken & (1 << (next - 1))) == 0)
				continue;
			int nextTaken = taken | (1 << next);
			int nextMod = (mod * 10 + (digits[next]-'0')) % m;
			int nextLess = less || digits[next] < (e[index]);
			ret += price(index + 1, nextTaken, nextMod, nextLess);
			ret %= MOD;
		}
	return ret;
}
int main() {

	int testcase;
	cin >> testcase;
	while (testcase--) {
		memset(cache, -1, sizeof(cache));
		digits.clear();
		// digits를 만들기 위한 vector toDigits
		vector<int> toDigits;
		cin >> e >> m;
		n = e.length();
		long long curCost = stoll(e);
		for (int i = 0; curCost > 0; curCost /= 10) {
			int num = curCost % 10;
			toDigits.push_back(num);
		}
		sort(toDigits.begin(), toDigits.end());
		for (int i = 0; i < toDigits.size(); i++) {
			digits += ('0' + toDigits[i]);
		}
		cout << price(0, 0, 0, 0) << endl;
	}
}
