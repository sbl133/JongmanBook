#include<iostream>
using namespace std;
int n, k;
int l[5000], m[5000], g[5000];
// dist만큼 왔을때 지나친 표지판의 갯수
int decision(int dist) {
	int ret = 0;
	for (int i=0; i < n; i++) 
		// 0부터 dist까지하고 구간[l[i]-m[i]]에 겹치는 구간이 있으면
		if (dist >= l[i] - m[i]) 
			ret += (min(dist, l[i]) - (l[i] - m[i])) / g[i] + 1;
	return ret >= k;
}
// decision이 참이면 지나친 표지판 갯수가 k보다 많으므로
// 범위 낮추고 거짓이면 반대로 범위 높이고
int optimize() {
	int lo = -1, hi = 8030001;
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		cin >> n >> k;
		for (int i = 0; i < n; i++)
			cin >> l[i] >> m[i] >> g[i];
		cout << optimize() << endl;
	}
}
