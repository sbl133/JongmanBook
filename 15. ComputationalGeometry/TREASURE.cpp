#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
// double형을 다루면서 생길 수 있는 오차를 방지하기 위한 EPSILON
const double EPSILON = 1e-9;
// 벡터를 나타내기 위한 구조체
struct vector2 {
	double x, y;
	explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	// 벡터끼리 같은지
	bool operator==(const vector2& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	// 벡터끼리의 합
	vector2 operator+(const vector2& rhs) const {
		return vector2(x + rhs.x, y + rhs.y);
	}
	// 벡터기리의 차
	vector2 operator-(const vector2& rhs) const {
		return vector2(x - rhs.x, y - rhs.y);
	}
	// 벡터에 상수곱
	vector2 operator*(double rhs) const { 
		return vector2(x * rhs, y * rhs);
	}
	// 벡터의 외적
	double cross(const vector2& rhs) const {
		return x * rhs.y - y * rhs.x;
	}
};
// 원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계 방향이면 음수, 평행이면 0
double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}
// 점 p를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계 방향이면 음수, 평행이면 0
double ccw(vector2 p, vector2 a, vector2 b) {
	return ccw(a - p, b - p);
}
// 벡터ab와 벡터cd가 서로 교차하면 true, 이때 x애는 교차하는 점의 좌표를 저장
bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {
	double det = (b - a).cross(d - c);
	if (fabs(det) < EPSILON) return false;
	x = a + (b - a) * ((c - a).cross(d - c) / det);
	return true;
}
// 좌표들을 편하게 저장하기 위해 polygon정의
typedef vector<vector2> polygon;
// p에 저장된 좌표들 중에서 직선ab 왼쪽에 있는 좌표들과
// 직선ab와 선분p[i]p[j]의 교차점들을 ret에 저장
polygon cutPoly(const polygon& p, const vector2& a, const vector2& b) {
	int n = p.size();
	vector<bool> inside(n);
	// 벡터ab와 벡터ap[i]이 이루는 각도가 반시계 방향이면 p[i]가 직선ab 왼쪽에 있음을 의미 
	for (int i = 0; i < n; i++)
		inside[i] = ccw(a, b, p[i]) >= 0;
	polygon ret;
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		// p에서 직선ab 왼쪽에 있는 점들만 ret에 저장 
		if (inside[i]) ret.push_back(p[i]);
		// 선분p[i]p[j]에 교차점이 있다면 
		if (inside[i] != inside[j]) {
			vector2 cross;
			// 교차점의 좌표를 구해서
			lineIntersection(a, b, p[i], p[j], cross);
			// ret에 저장
			ret.push_back(cross);
		}
	}
	return ret;
}
// 다각형 클리핑
// 주어진 직사각형의 변들을 직선으로해서 주어진 섬을 쪼개면서 조건에 맞게 좌표들을 저장하면
// 찾고자하는 섬의 부분만을 나타내는 다각형의 좌표들이 ret에 저장된다.
polygon intersection(const polygon& p, double x1, double y1, double x2, double y2) {
	vector2 a(x1, y1), b(x2, y1), c(x2, y2), d(x1, y2);
	polygon ret = cutPoly(p, a, b);
	ret = cutPoly(ret, b, c);
	ret = cutPoly(ret, c, d);
	ret = cutPoly(ret, d, a);
	return ret;
}
// 다각형의 꼭짓점들을 순회하면서
// 원점에서부터 다각형의 이웃하는 두 꼭짓점으로 가는 두 벡터를 외적하면 다각형의 넓이를 구할 수 있다.
double area(const polygon& p) {
	double ret = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		ret += p[i].x * p[j].y - p[j].x * p[i].y;
	}
	return fabs(ret) / 2.0;
}
int main() {
	cout << fixed;
	cout.precision(8);
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int x1, y1, x2, y2, dotNum;
		cin >> x1 >> y1 >> x2 >> y2 >> dotNum;
		polygon island;
		vector2 input;
		for (int i = 0; i < dotNum; i++) {
			cin >> input.x >> input.y;
			island.push_back(input);
		}
		// 주어진 직사각형과 섬을 나타내는 다각형의 교집합의 꼭짓점을 저장하고
		polygon searchIsland = intersection(island, x1, y1, x2, y2);
		// 저장한 꼭짓점들로 부터 넓이를 구한다.
		cout << area(searchIsland) << endl;
	}
}
