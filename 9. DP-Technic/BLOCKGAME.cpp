#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
vector<int> blocks;
// 좌표에 따른 블럭위치를 반환
inline int cell(int y, int x) { return 1 << (5 * y + x); }
// 놓을수 있는 모든 블럭의 위치와 종류를 미리 계산해서 blocks에 저장
void precalc() {
	for(int y=0; y<4; y++)
		for (int x = 0; x < 4; x++) {
			vector<int> cells;
			for(int dy=0; dy<2; dy++)
				for(int dx=0; dx<2; dx++)
					cells.push_back(cell(y + dy, x + dx));
			int square = cells[0] + cells[1] + cells[2] + cells[3];
			for (int i = 0; i < 4; i++)
				blocks.push_back(square - cells[i]);
		}
	for(int i=0; i<5; i++)
		for (int j = 0; j < 4; j++) {
			blocks.push_back(cell(i, j) + cell(i, j + 1));
			blocks.push_back(cell(j, i) + cell(j + 1, i));
		}
}
char cache[1 << 25];
char game(int state) {
	char& ret = cache[state];
	if (ret != -1) return ret;
	ret = 0;
	for (int i = 0; i < blocks.size(); i++) 
		// blocks[i]로 블럭을 놓았을떄 상대방이 지는 경우 return 1;
		if ((blocks[i] & state) == 0) 
			if (!game(state | blocks[i])) {
				ret = 1;
				break;
			}
	return ret;
}
int main() {
	int testcase;
	precalc();
	cin >> testcase;
	while (testcase--) {
		string board[5];
		int state = 0;
		memset(cache, -1, sizeof(cache));
		for (int i = 0; i < 5; i++)
			cin >> board[i];
		for(int i=0; i<5; i++)
			for (int j = 0; j < 5; j++) {
				if (board[i][j] == '#')
					state = state | (1 << (5 * i + j));
			}
		if (game(state))
			cout << "WINNING" << endl;
		else
			cout << "LOSING" << endl;
	}
}
