#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
const double pi = 2.0 * acos(0);
const int INF = 987654321;
int n;
double x[100], y[100], r[100];
// <초소구역 시작 라디안각도, 초소구역 끝 라디안각도>ranges
pair<double, double>ranges[100];
// 각 초소에 대한 정보들로 ranges구성
void convertToRange() {
	for (int i = 0; i < n; i++) {
		// 초소 위치에 대한 라디안
		double loc = fmod(atan2(y[i], x[i]) + 2 * pi, 2 * pi);
		// 초소 감시 범위에 대한 라디안
		double range = 2.0 * asin(r[i] / 2.0 / 8.0);
		// 초소 감시범위를 ranges에 저장
		ranges[i] = make_pair(loc - range, loc + range);
	}
	sort(ranges, ranges + n);
}
// 선형으로 문제를 푸는 함수 전방선언
int solveLinear(double begin, double end);
// 시작점(끝점)을 완전히 덮는 초소 하나를 원형으로 선택하고 나머지를 선형으로 해결
int solveCircular() {
	int ret = INF;
	for (int i = 0; i < n; i++) 
		if (ranges[i].first <= 0 || ranges[i].second >= 2 * pi) {
			// 시작점(끝점)을 완전히 덮는 초소에대한 감시범위를 범위[0, 2pi]로 정규화
			double begin = fmod(ranges[i].second, 2 * pi);
			double end = fmod(ranges[i].first + 2 * pi, 2 * pi);
			// 나머지를 선형으로 해결했을때 가장 적은 초소를 들이는 경우를 계산
			ret = min(ret, solveLinear(begin, end) + 1);
		}
	return ret;
}
int solveLinear(double begin, double end) {
	int used = 0, idx = 0;
	// 범위를 완전히 덮을때까지 반복
	while (begin < end) {
		// 선형으로 어디까지 덮었는지 나타냄
		double maxCover = -1;
		while (idx < n && ranges[idx].first <= begin) {
			// begin전에 시작해서 오른쪽으로 가장 크게 뻗는 초소 선택
			maxCover = max(maxCover, ranges[idx].second);
			idx++;
		}
		// begin전에 시작하는 초소가 없으면 완전히 덮을수 있는 방법 없음
		if (maxCover <= begin)return INF;
		// begin전에 시작하는 초고 잘 골랐으면 begin 갱신
		begin = maxCover;
		used++;
	}
	return used;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> y[i] >> x[i] >> r[i];
		convertToRange();
		int result = solveCircular();
		if (result == INF)
			cout << "IMPOSSIBLE" << endl;
		else
			cout << result << endl;
	}
}
