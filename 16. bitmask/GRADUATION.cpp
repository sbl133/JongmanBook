#include<iostream>
#include<cstring>
using namespace std;
const int INF = 987654321;
// 각 과목당 선수과목을 나타내는 비트마스크
int prerequisited[12];
// 학기당 열리는 과목을 나타내는 비트마스크
int classes[10];
// 메모이제이션을 위한 캐시
int cache[10][1 << 12];
int n, k, m, l;
// n에 켜져있는 비트의 갯수를 return
int bitCount(int n) {
	if (n == 0)return 0;
	return n % 2 + bitCount(n / 2);
}
// semester번째 학기이고 이제까지 들은 과목이 taken일때
// 앞으로 들어야 하는 학기수 return 
int graduate(int semester, int taken) {
	// k개 이상의 과목을 들었으면 졸업 가능
	if (bitCount(taken) >= k)return 0;
	// 학기가 다 지나도 k개 이상의 과목을 못들었으면 졸업불가
	if (semester == m)return INF;
	int& ret = cache[semester][taken];
	if (ret != -1)return ret;
	ret = INF;
	// 이번 학기에 열리는 과목에서 이제까지 들은 과목을 빼고
	int canTake = (classes[semester] & ~taken);
	// 선수과목을 아직 안들어서 못듣는 과목을 빼고
	// 남은 과목들이 이번학기에 들을수 있는과목들
	for (int i = 0; i < n; i++)
		if ((canTake & (1 << i)) && (taken & prerequisited[i]) != prerequisited[i])
			canTake &= ~(1 << i);
	// canTake의 부분집합중 과목수가 l(엘)개 이하인 집합들을 순회
	for (int take = canTake; take > 0; take = canTake & (take - 1)) {
		if (bitCount(take) > l)continue;
		ret = min(ret, graduate(semester + 1, taken | take) + 1);
	}
	// 이번학기 아예 건너뛰는 경우도 고려
	ret = min(ret, graduate(semester + 1, taken));
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		cin >> n >> k >> m >> l;
		memset(cache, -1, sizeof(cache));
		memset(classes, 0, sizeof(classes));
		memset(prerequisited, 0, sizeof(prerequisited));
		// 선수과목들을 prerequisited에 저장
		for (int i = 0; i < n; i++) {
			int r;
			cin >> r;
			for (int j = 0; j < r; j++) {
				int pre;
				cin >> pre;
				prerequisited[i] |= (1 << pre);
			}
		}
		// 학기당 열리는 과목들을 classes에 저장
		for (int i = 0; i < m; i++) {
			int openNum;
			cin >> openNum;
			for (int j = 0; j < openNum; j++) {
				int obj;
				cin >> obj;
				classes[i] |= (1 << obj);
			}
		}
		int result = graduate(0, 0);
		if (result == INF)
			cout << "IMPOSSIBLE" << endl;
		else
			cout << result << endl;
	}
}
