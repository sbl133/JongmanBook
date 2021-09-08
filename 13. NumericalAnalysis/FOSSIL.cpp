#include<iostream>
#include<vector>
using namespace std;
struct point {
	double x, y;
};
// 두 다각형을 좌표로 표현
vector<point> hull1, hull2;
// 다각형의 볼록부분을 upper에 오목부분을 lower에 다각형 구분없이 넣는다
vector<pair<point, point>> upper, lower;
void decompose(const vector<point>& hull) {
	int n = hull.size();
	for (int i = 0; i < n; i++) {
		if (hull[i].x < hull[(i + 1) % n].x)
			lower.push_back(make_pair(hull[i], hull[(i + 1) % n]));
		else if (hull[i].x > hull[(i + 1) % n].x)
			upper.push_back(make_pair(hull[i], hull[(i + 1) % n]));
	}
}
// x가 a.x와 b.x 사이에 있는가
bool between(const point& a, const point& b, double x) {
	return((a.x <= x && b.x >= x) || (a.x >= x && b.x <= x));
}
// 두 점 a,b를 지나는 직선 위에 있는 점의 x좌표가 x일때, return y좌표
double at(const point& a, const point& b, double x) {
	double dy = b.y - a.y, dx = b.x - a.x;
	return dy / dx * (x - a.x) + a.y;
}
// x에서 교집합 다각형의 세로길이
double vertical(double x) {
	double minUp = 1e20, maxLow = -1e20;
	for (int i = 0; i < upper.size(); i++)
		// x를 포함하는 두 다각형의 오목부분 중에서
		if (between(upper[i].first, upper[i].second, x))
			// 더 작은것이 교집합 다각형의 윗 부분이다
			minUp = min(minUp, at(upper[i].first, upper[i].second, x));
	for (int i = 0; i < lower.size(); i++)
		// x를 포함하는 두 다각형의 볼록부분 중에서
		if (between(lower[i].first, lower[i].second, x))
			// 더 큰것이 교집합 다각형의 아랫 부분이다
			maxLow = max(maxLow, at(lower[i].first, lower[i].second, x));
	return minUp - maxLow;
}
// 다각형 hull에서 제일 작은 x좌표
double minX(const vector<point>& hull) {
	double ret = 1e20;
	for (int i = 0; i < hull.size(); i++)
		ret = min(ret, hull[i].x);
	return ret;
}
// 다각형 hull에서 제일 큰 x좌표
double maxX(const vector<point>& hull) {
	double ret = -1e20;
	for (int i = 0; i < hull.size(); i++)
		ret = max(ret, hull[i].x);
	return ret;
}
double solve() {
	// 각각의 다각형에 제일 작은 x좌표중 큰쪽이 lo의 초기값
	double lo = max(minX(hull1), minX(hull2));
	// 각각의 다각형에 제일 큰 x좌쵸중 작은쪽이 hi의 초기값
	double hi = min(maxX(hull1), maxX(hull2));
	if (hi < lo)return 0;
	// 삼분법 실행
	for (int i = 0; i < 100; i++) {
		double aab = (lo * 2 + hi) / 3.0;
		double abb = (lo + hi * 2) / 3.0;
		if (vertical(aab) < vertical(abb))
			lo = aab;
		else
			hi = abb;
	}
	return max(0.0, vertical(hi));
}
int main() {
	cout << fixed;
	cout.precision(8);
	int testcase;
	cin >> testcase;
	while (testcase--) {
		hull1.clear(); hull2.clear();
		upper.clear(); lower.clear();
		int n, m;
		cin >> n >> m;
		for (int i = 0; i < n; i++) {
			point dot;
			cin >> dot.x >> dot.y;
			hull1.push_back(dot);
		}
		for (int i = 0; i < m; i++) {
			point dot;
			cin >> dot.x >> dot.y;
			hull2.push_back(dot);
		}
		decompose(hull1); decompose(hull2);
		cout << solve() << endl;
	}
}
