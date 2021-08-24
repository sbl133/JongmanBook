#include<iostream>
#include<vector>
using namespace std;
// a, b 의 곱셈
vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size() + b.size() + 1, 0);
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < b.size(); j++)
			c[i + j] += a[i] * b[j];
	// 팬미팅 문제에서는 0이상인지만 판별하면 되므로 normalize생략
	//normalize(c);
	return c;
}
// a, b^k 의 덧셈
void addTo(vector<int>& a, const vector<int>& b, int k) {
	a.resize(max(a.size(), b.size() + k));
	for (int i = 0; i < b.size(); i++)
		a[k + i] += b[i];
}
// a에 b를 뺌 (a>=b라 가정)
void subFrom(vector<int>& a, const vector<int>& b) {
	a.resize(max(a.size(), b.size()) + 1);
	for (int i = 0; i < b.size(); i++)
		a[i] -= b[i];
}
// 카라츠바 알고리즘
vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();
	if (an < bn)karatsuba(b, a);
	if (an == 0 || bn == 0)return vector<int>();
	// 일정길이 이하면 표준 곱셈알고리즘 사용
	if (an <= 50)return multiply(a, b);
	int half = an / 2;
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());
	// z2 = a1 * b1
	vector<int> z2 = karatsuba(a1, b1);
	// z0 = a0 * b0
	vector<int> z0 = karatsuba(a0, b0);
	addTo(a0, a1, 0); addTo(b0, b1, 0);
	// z1 = (a0 + a1) * (b0 + b1) - z0 - z1
	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z2);
	subFrom(z1, z0);
	// ret = z0 + z1*10^half + z2*10^(half+half)
	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);
	return ret;
}
void hugs(const string& members, const string& fans) {
	int N = members.size(), M = fans.size();
	vector<int> mem(N, 0);
	vector<int> fan(M, 0);
	// 남자일때 1를 넣어준다
	for (int i = 0; i < N; i++)
		mem[i] = (members[i] == 'M');
	for (int i = 0; i < M; i++)
		fan[M - i - 1] = (fans[i] == 'M');
	// 곱해서 0인것은 모두 포옹을 한 턴을 의미
	vector<int> c = karatsuba(mem, fan);
	int ret = 0;
	for (int i = N - 1; i < M; i++) 
		if (c[i] == 0)
			ret++;
	cout << ret << endl;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		string a, b;
		cin >> a >> b;
		hugs(a, b);
	}
}
