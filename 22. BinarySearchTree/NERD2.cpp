#include<iostream>
#include<map>
using namespace std;
// <x, y>를 점으로 추상화
map<int, int> coords;
// 새로운 점 (x,y)가 기존의 다른 점들에 지배당하는지 확인
bool isDominated(int x, int y) {
	// x보다 오른쪽에 있는 점중에 가장 왼쪽에 있는점
	map<int, int>::iterator it = coords.lower_bound(x);
	// 없으면 지배당하지 않는다
	if (it == coords.end())return false;
	// 이 점은 x보다 오른쪽에 있는 점들 중 가장 왼쪽에 -> 가장 위에 있는 점
	// 이 점 보다 밑에 있으면 이점보다 x값도 작고 y값도 작은게 됨 -> 너드 아님
	return y < it->second;
}
// 새로운 점 (x, y)에 지배당하는 점들을 map에서 지움
void removeDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);
	// x보다 왼쪽에 있는 점이 없는 경우
	if (it == coords.begin())return;
	--it;
	while (true) {
		// it가 가르키는 점보다 y가 작으면 더 이상 지울게 없음
		if (it->second > y)break;
		// it다음 점이 없으므로 it가 가르키는 점만 지우고 종료 
		if (it == coords.begin()) {
			coords.erase(it);
			break;
		}
		// it를 지우고 다음 왼쪽 점을 가르킨다. 
		else {
			map<int, int>::iterator jt = it;
			jt--;
			coords.erase(it);
			it = jt;
		}
	}
}
// (x,y)가 추가되었을 때 coords를 갱신하고 남아있는 점의 갯수 반환
int registered(int x, int y) {
	// 새 점이 지배당하면 그냥 새 점을 버리고 끝
	if (isDominated(x, y))return coords.size();
	// 새 점에 의해 지워지는 점들을 제거하고 coords갱신
	removeDominated(x, y);
	coords[x] = y;
	return coords.size();
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		coords.clear();
		int n, x, y, sum = 0;
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> x >> y;
			sum += registered(x, y);
		}
		cout << sum << endl;
	}
}
