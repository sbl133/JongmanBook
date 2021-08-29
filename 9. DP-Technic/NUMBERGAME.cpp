#include<iostream>
using namespace std;
const int EMPTY = -987654321;
int board[50];
int n, cache[50][50];
int game(int left, int right) {
	if (left > right)return 0;
	int& ret = cache[left][right];
	if (ret != EMPTY) return ret;
	// 왼쪽 또는 오른쪽 끝에 있는 숫자 하나를 고르는 경우
	ret = max(board[left] - game(left + 1, right), 
		board[right] - game(left, right - 1));
	// 양끝 중 한끝에 숫자두개를 지우는 경우
	if (right - left >= 1) {
		ret = max(ret, -game(left + 2, right));
		ret = max(ret, -game(left, right - 2));
	}
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		fill(&cache[0][0], &cache[49][50], EMPTY);
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> board[i];
		cout << game(0, n - 1) << endl;
	}
}
