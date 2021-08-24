#include<iostream>
#include<vector>
using namespace std;
vector<int> h;
int solve(int left, int right) {
	if (left == right) return h[left];
	int ret = 0;
	int mid = (left + right) / 2;
	// mid를 기준으로 왼편과 오른편중 큰판자를 선택
	ret = max(solve(left, mid), solve(mid + 1, right));
	int toLeft = mid; int toRight = mid + 1;
	int height = min(h[toLeft], h[toRight]);
	ret = max(ret, height * 2);
	// 판자가 mid에 걸쳐지는 경우 중간에서부터 높이가 큰방향으로 너비 확장
	while (toLeft>left || toRight<right) {
		if (toRight < right && (toLeft == left || h[toLeft - 1] < h[toRight + 1])) {
			toRight++;
			height = min(height, h[toRight]);
		}
		else {
			toLeft--;
			height = min(height, h[toLeft]);
		}
    // 계산하면서 제일 큰 판자를 저장
		ret = max(ret, height * (toRight - toLeft + 1));
	}
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		h.clear();
		int fence, height;
		cin >> fence;
		for (int i = 0; i < fence; i++) {
			cin >> height;
			h.push_back(height);
		}
		cout << solve(0, fence - 1) << endl;
	}
}
