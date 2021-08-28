#include<iostream>
#include<cstring>
using namespace std;
const int MAX = 1000000000 + 1;
int length[51];
const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";
// length[i] = X or Y를 i세대 확장시킨 문자열의 길이
void precalc() {
	length[0] = 1;
	for (int i = 1; i <= 50; i++)
		length[i] = min(MAX, (2 * length[i - 1] + 2));
}
// dragonCurve를 generation세대 확장시킨 문자열의 skip+1번째 문자
char expand(const string& dragonCurve, int generation, int skip) {
	// 더이상 확장시킬수 없을때
	if (generation == 0) 
		return dragonCurve[skip];

	for (int i = 0; i < dragonCurve.size(); i++) {
		if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y') {
			// skip이 해당문자를 generation확장시킨것보다 크다면 문자건너뛰기
			if (skip >= length[generation])
				skip -= length[generation];
			else if (dragonCurve[i] == 'X')
				return expand(EXPAND_X, generation - 1, skip);
			else
				return expand(EXPAND_Y, generation - 1, skip);
		}
		// skip이 남았는데 +,-,F를 만나면 건너뛰기
		else if (skip > 0)
			--skip;
		// skip이 0이면 해당문자 출력
		else
			return dragonCurve[i];
	}
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int n, p, l;
		cin >> n >> p >> l;
		precalc();
		for (int i = 0; i < l; i++)
			cout << expand("FX", n, p + i - 1);
		cout << endl;
	}
}
