#include<iostream>
#include<cstring>
using namespace std;
int H, W;
// 90도씩 돌려가며 각각의 블럭을 표현
int dx[4][3] = {
	{0, 0, 1},
	{0, 0, 1},
	{0, 1, 1},
	{-1, 0, 0}
};
int dy[4][3] = {
	{0, 1, 1},
	{0, 1, 0},
	{0, 0, 1},
	{1, 0, 1}
};
char board[21][21];
bool inRange(int x, int y) {
	if (x < 0 || x >= W)
		return false;
	if (y < 0 || y >= H)
		return false;
	return true;
}
int coverNumber() {
	int x, y;
	int ret = 0;
	x = y = -1;
	//빈칸 찾는중...
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) 
			if (board[i][j] == '.') {
				x = j; y = i;
				break;
			}
		if (x != -1)break;
	}
	//빈칸이 없으면 return 1;
	if (x == -1) return 1;
	//90도로 돌려가며 퍼즐을 하나씩 맞춰본다
	for (int i = 0; i < 4; i++) {
		int can = true;
		for (int j = 0; j < 3; j++) {
			int cx = x + dx[i][j];
			int cy = y + dy[i][j];
			if (!inRange(cx, cy) || board[cy][cx] == '#')
				can = false;
		}
		// 퍼즐이 알맞게 들어간다면
		if (can) {
			for (int j = 0; j < 3; j++) {
				int cx = x + dx[i][j];
				int cy = y + dy[i][j];
				board[cy][cx] = '#';
			}
			ret += coverNumber();
			for (int j = 0; j < 3; j++) {
				int cx = x + dx[i][j];
				int cy = y + dy[i][j];
				board[cy][cx] = '.';
			}
		}
	}
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		cin >> H >> W;
		memset(board, 0, sizeof(board));
		for (int i = 0; i < H; i++)
			cin >> board[i];
		cout << coverNumber() << endl;
	}
}
