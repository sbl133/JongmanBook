#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
// 학생수
int n;
// 친구를 나타내는 2차원배열
bool areFriends[10][10];
int countPairings(bool taken[10]) {
	// 짝궁이 안정해진 맨 앞번호
	int firstFree = -1;
	int ret = 0;
	for (int i = 0; i < n; i++)
		if (taken[i] == false) {
			firstFree = i;
			break;
		}
	if (firstFree == -1) return 1;
	for (int pairWith = firstFree + 1; pairWith < n; pairWith++) {
		if (taken[pairWith] == false && areFriends[firstFree][pairWith]) {
			taken[firstFree] = taken[pairWith] = true;
			ret += countPairings(taken);
			taken[firstFree] = taken[pairWith] = false;
		}
	}
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int numberOfPair;
		int x, y;
		bool taken[10];
		memset(taken, 0, sizeof(taken));
		memset(areFriends, 0, sizeof(areFriends));
		cin >> n >> numberOfPair;
		for (int i = 0; i < numberOfPair; i++) {
			cin >> x >> y;
			areFriends[x][y] = true;
			areFriends[y][x] = true;
		}
		cout << countPairings(taken) << endl;
	}
}
