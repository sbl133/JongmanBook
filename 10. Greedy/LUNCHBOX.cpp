#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n;
// <먹는시간, 데우는시간>
vector<pair<int, int>> timeTable;
int launchbox() {
	// 먹는시간을 기준으로 오래걸리는 도시락이 앞에온다
	sort(timeTable.begin(), timeTable.end());
	int ret = -timeTable[0].first + timeTable[0].second;
	// 이전까지 선택한 도시락들의 총 데우는 시간
	int warmTime = 0;
	for (int i = 1; i < timeTable.size(); i++) {
		int curTime = -timeTable[i].first + timeTable[i].second;
		warmTime += timeTable[i-1].second;
		// warmTime + 직전에 선택한 도시락을 먹는시간과
		// warmTime + 현재 도시락 데우는시간 + 현재도시락 먹는시간 비교
		ret = max(ret, warmTime + curTime);
	}
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		timeTable.clear();
		cin >> n;
		int* warm = new int[n];
		int* eat = new int[n];
		for (int i = 0; i < n; i++)
			cin >> warm[i];
		for (int i = 0; i < n; i++)
			cin >> eat[i];
		// 먹는시간을 내림차순으로 정렬하기 위해 음수를 취해준다
		for (int i = 0; i < n; i++)
			timeTable.push_back(make_pair(-eat[i], warm[i]));
		cout << launchbox() << endl;
	}
}
