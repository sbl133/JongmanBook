#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
// 벡터를 나타내기 위한 구조체
struct vector2 {
	double x, y;
	vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	// 벡터끼리 같은지
	bool operator==(vector2& rhs) {
		return x == rhs.x && y == rhs.y;
	}
	// *min_element를 위한 비교연산자
	// x좌표 먼저 비교후 같으면 y좌표 비교
	bool operator <(vector2 rhs) { 
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}
	// 벡터끼리의 합
	vector2 operator+(vector2 rhs) { 
		return vector2(x + rhs.x, y + rhs.y);
	}
	// 벡터끼리의 차
	vector2 operator-(vector2 rhs) { 
		return vector2(x - rhs.x, y - rhs.y);
	}
	// 벡터에 상수곱
	vector2 operator*(double rhs) { 
		return vector2(x * rhs, y * rhs);
	}
	// 벡터의 크기
	double norm() { 
		return hypot(x, y);
	}
	// 벡터 외적
	double cross(const vector2& rhs) {
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
// 선분과 선분이 교차하는지 확인
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);
	// 두 선분이 한 직선 위에 있거나 끝점이 겹치는 경우
	if (ab == 0 && cd == 0) {
		if (b < a)swap(a, b);
		if (d < c)swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}
typedef vector<vector2> polygon;
// 점 q가 다각형 p안에 포함되어 있을 경우 참, 아닌 경우 거짓을 반환
bool isInside(vector2 q, const polygon& p) {
	int crosses = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		// (p[i], p[j])가 q에서 시작한 반직선을 세로로 가로지르는가
		if ((p[i].y > q.y) != (p[j].y > q.y)) {
			// 가로지르는 x 좌표를 계산
			double atX = (p[j].x - p[i].x) * (q.y - p[i].y)
				/ (p[j].y - p[i].y) + p[i].x;
			if (q.x < atX)
				++crosses;
		}
	}
	return crosses % 2 > 0;
}
// points에 있는 점들을 모두 포함하는 최소의 볼록 다각형을 찾는다
polygon giftWrap(polygon& points) {
	int n = points.size();
	polygon hull;
	// 가장 왼쪽 아래 점을 찾는다. 이 점은 껍질에 반드시 포함된다.
	vector2 pivot = *min_element(points.begin(), points.end());
	hull.push_back(pivot);
	while (true) {
		// ph에서 시작하는 벡터가 가장 왼쪽인 점 next를 찾는다.
		// 평행인 점이 여러 개 있으면 가장 먼 것을 선택한다.
		vector2 ph = hull.back();
		vector2 next = points[0];
		for (int i = 1; i < n; i++) {
			double cross = ccw(ph, next, points[i]);
			double dist = (next - ph).norm() - (points[i] - ph).norm();
			if (cross > 0 || (cross == 0 && dist < 0))
				next = points[i];
		}
		// 시작점으로 돌아왔으면 종료
		if (next == pivot) break;
		hull.push_back(next);
	}
	return hull;
}
// 두 다각형이 서로 닿거나 겹치는지 여부를 판단
bool polygonIntersects(const polygon& p, const polygon& q) {
	int n = p.size(), m = q.size();
	// 우선 한 다각형이 다른 다각형에 포함 되어 있는 경우를 확인
	if (isInside(p[0], q) || isInside(q[0], p))return true;
	// 서로 닿는 두변을 확인
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (segmentIntersects(p[i], p[(i + 1) % n], q[j], q[(j + 1) % m]))
				return true;
	return false;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int n;
		cin >> n;
		polygon nerd, noNerd;
		int isNerd, s, v;
		for (int i = 0; i < n; i++) {
			cin >> isNerd >> s >> v;
			if (isNerd)
				nerd.push_back(vector2(s, v));
			else
				noNerd.push_back(vector2(s, v));
		}
		polygon hull1 = giftWrap(nerd);
		polygon hull2 = giftWrap(noNerd);
		if (polygonIntersects(hull1, hull2))
			cout << "THEORY IS INVALID" << endl;
		else
			cout << "THEORY HOLDS" << endl;
	}
}
