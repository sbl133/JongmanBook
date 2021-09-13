#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
// 벡터를 표현하기 위한 구조체
struct vector2{
	double x, y;
	explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	// 벡터끼리의 + 연산
	vector2 operator+(const vector2& rhs) const {
		return vector2(x + rhs.x, y + rhs.y);
	}
	// 벡터끼리의 - 연산
	vector2 operator-(const vector2& rhs) const {
		return vector2(x - rhs.x, y - rhs.y);
	}
	// 벡터의 상수 곱
	vector2 operator*(double rhs) const {
		return vector2(rhs * x, rhs * y);
	}
	// 벡터 길이
	double norm() const {
		return hypot(x, y);
	}
	// 단위 벡터로 바꾸기
	vector2 normalize()const {
		return vector2(x / norm(), y / norm());
	}
	// 벡터 내적
	double dot(const vector2& a) {
		return x * a.x + y * a.y;
	}
	// 벡터 정사영
	vector2 project(const vector2& rhs) {
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}
};
// double연산의 오차로 인한 에러를 방지하기 위해 EPSILON의 여유를 둔다.
const double EPSILON = 1e-9;
const double INFTY = 1e200;
// ax^2+bx+c=0의 해를 반환
vector<double> solve2(double a, double b, double c) {
	double d = b * b - 4 * a * c;
	if (d < -EPSILON) return vector<double>();
	if (d < EPSILON) return vector<double>(1, -b / (2 * a));
	vector<double> ret;
	ret.push_back((-b - sqrt(d)) / (2 * a));
	ret.push_back((-b + sqrt(d)) / (2 * a));
	return ret;
}
// 공이 here에서부터 dir방향으로 갈때 반지름 rad이고 중심이 center인 원에 부딪히는 지점
// f(t)=here + dir*t라고 하면 |center-f(t)|=rad이고 양변에 제곱하고 식을 전개하면 abc를 얻을 수 있다.
double hitCircle(vector2 here, vector2 dir, vector2 center, int rad) {
	double a = dir.dot(dir);
	double b = 2 * dir.dot(here - center);
	double c = center.dot(center) + here.dot(here) 
		- 2 * here.dot(center) - rad * rad;
	vector<double> sols = solve2(a, b, c);
	if (sols.empty() || sols[0] < EPSILON)return INFTY;
	// 두 해가 모두 양수라면 작은 값이 부딪히는 지점이다
	return sols[0];
}
// -dir를 contact-center에 사영시킨 값을 이용하면 다음을 알 수 있다.
vector2 reflect(vector2 dir, vector2 center, vector2 contact) {
	return (dir - dir.project(contact - center) * 2).normalize();
}
int n;
double radius[50];
vector2 center[50];
void simulate(vector2 here, vector2 dir) {
	dir = dir.normalize();
	int hitCount = 0;
	while (hitCount < 100) {
		int circle = -1;
		// 충분히 큰 값으로 초기화
		double time = INFTY * 0.5;
		for (int i = 0; i < n; i++) {
			// 공의 크기를 고려하는 대신 원의 반지름을 1씩 증가시킨다.
			double cand = hitCircle(here, dir, center[i], radius[i] + 1);
			// 제일 먼저 부딪히는 지점을 찾는다
			if (cand < time) {
				time = cand;
				circle = i;
			}
		}
		if (circle == -1)break;
		if (hitCount++) cout << " ";
		cout << circle;
		vector2 contact = here + dir * time;
		// 원에 부딪혀 방향이 바뀐다
		dir = reflect(dir, center[circle], contact);
		here = contact;
	}
	cout << endl;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int x, y, dx, dy;
		cin >> x >> y >> dx >> dy >> n;
		for (int i = 0; i < n; i++) {
			cin >> center[i].x >> center[i].y >> radius[i];
		}
		simulate(vector2(x, y), vector2(dx, dy));
	}
}
