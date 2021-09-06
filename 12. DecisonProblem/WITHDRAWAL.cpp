#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n, k;
int c[1000], r[1000];
// k개의 과목만 계산헸을때 누적등수가 average보다 큰지 작은지
bool decision(double average) {
	// sum(c[i]/r[i]) <= x
	// sum(x*r[i]-c[i]) >= 0
	vector<double> v;
	for (int i = 0; i < n; i++)
		v.push_back(average * c[i] - r[i]);
	sort(v.begin(), v.end());
	double sum = 0.0;
	for (int i = n - k; i < n; i++)
		sum += v[i];
	return sum >= 0;
}
// 이분법을 사용해서 최소누적등수 추적
double optimize() {
	double lo = 0.0, hi = 1;
	for (int it = 0; it < 100; it++) {
		double mid = (lo + hi) / 2;
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}
int main() {
	cout << fixed;
	cout.precision(8);
	int testcase;
	cin >> testcase;
	while (testcase--) {
		cin >> n >> k;
		for (int i = 0; i < n; i++)
			cin >> r[i] >> c[i];
		cout << optimize() << endl;
	}
}
