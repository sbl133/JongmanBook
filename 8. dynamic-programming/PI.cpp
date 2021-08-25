#include<iostream>
#include<cstring>
using namespace std;
string N;
int cache[10001];
const int INF = 987654321;
// N의 index [a,b]에 해당하는 부분문자열 M의 난이도 구하기
int classify(int a, int b) {
	string M = N.substr(a, b - a + 1);
	// M이 모두 같은문자면 return 1 
	// c++에서는 ==연산으로 두개의 문자열이 같은지 확인가능
	if (M == string(M.size(), M[0]))return 1;
	bool progressive = true;
	for (int i = 0; i < M.size() - 1; i++)
		if (M[i + 1] - M[i] != M[1] - M[0])
			progressive = false;
	// 1씩 증가하거나 감소하면 return 2
	if (progressive && abs(M[1] - M[0]) == 1)
		return 2;
	bool alternating = true;
	for (int i = 0; i < M.size(); i++)
		if (M[i] != M[i % 2])
			alternating = false;
	// 두 문자가 반복되면 return 4
	if (alternating) return 4;
	// 등차 수열이면 return 5
	if (progressive) return 5;
	return 10;
}
// N을 index begin부터 검사
int memorize(int begin) {
	if (begin == N.size())return 0;
	int& ret = cache[begin];
	if (ret != -1) return ret;
	// begin부터 시작한 문자열의 길이가 3미만이면 return INF
	ret = INF;
	for (int L = 3; L <= 5; L++)
		if (begin + L <= N.size())
			ret = min(ret, memorize(begin + L) + classify(begin, begin + L - 1));
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		memset(cache, -1, sizeof(cache));
		cin >> N;
		cout << memorize(0) << endl;
	}
}
