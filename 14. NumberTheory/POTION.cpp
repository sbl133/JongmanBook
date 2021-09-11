#include<iostream>
#include<vector>
using namespace std;
// 각각 재료에 들어가야 하는 재료의 양, 이미 넣은 양, 앞으로 넣어야 되는 양
vector<int> recipe, put, ret;
int n;
// a,b의 최소공배수 구하기 (gcd(p,q) == gcd(p-q, q)를 이용)
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}
// a/b보다 작지않은 최소 자연수
int ceil(int a, int b) {
	return (a + b - 1) / b;
}
// 재료들 중에서 put/recipe의 최댓값이 X라 할때
// X이상이고 recipe들과의 곱이 항상 정수인 유리수를 a/b라고 하면 b는 recipe들의 최대공약수
vector<int> solve() {
	int b = recipe[0];
	for (int i = 1; i < n; i++) 
		b = gcd(b, recipe[i]);
	// 비율이 1은 넘어가야 하므로 a는 b이상이다.
	int a = b;
	for (int i = 0; i < n; i++)
		a = max(a, ceil(put[i] * b, recipe[i]));
	ret.resize(n);
	for (int i = 0; i < n; i++)
		ret[i] = recipe[i] * a / b - put[i];
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		recipe.clear(); put.clear(); ret.clear();
		int r, p;
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> r;
			recipe.push_back(r);
		}
		for (int i = 0; i < n; i++) {
			cin >> p;
			put.push_back(p);
		}
		solve();
		for (int i = 0; i < n; i++)
			cout << ret[i] << " ";
		cout << endl;
	}
}
