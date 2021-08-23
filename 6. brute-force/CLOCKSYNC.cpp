#include<iostream>
#include<vector>
using namespace std;
const int INF = 987654321, SWITCHES = 10, CLOCKS = 16;
vector<int> clocks;
// 스위치랑 연결된 시계
const char linked[SWITCHES][CLOCKS + 1] = {
	"xxx.............",
	"...x...x.x.x....",
	"....x.....x...xx",
	"x...xxxx........",
	"......xxx.x.x...",
	"x.x...........xx",
	"...x..........xx",
	"....xx.x......xx",
	".xxxxx..........",
	"...xxx...x...x.."
};
//모든 시계가 12시를 가르키는지 확인
bool areAligned() {
	for (int i = 0; i < 16; i++) {
		if (clocks[i] != 12)
			return false;
	}
	return true;
}
//해당 스위치랑 연결된 시계를 돌림
void push(int swtch) {
	for (int clock = 0; clock < CLOCKS; clock++) {
		if (linked[swtch][clock] == 'x')
			clocks[clock] += 3;
		if (clocks[clock] == 15) clocks[clock] = 3;
	}
}
int solve(int swtch) {
	if (swtch == SWITCHES) return areAligned() ? 0 : INF;
	int ret = INF;
	for (int i = 0; i < 4; i++) {
		ret = min(ret, solve(swtch + 1) + i);
		push(swtch);
	}
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int time;
		clocks.clear();
		for (int i = 0; i < 16; i++) {
			cin >> time;
			clocks.push_back(time);
		}
		int output = solve(0);
		if (output == INF)
			cout << -1 << endl;
		else
			cout << solve(0) << endl;
	}
}
