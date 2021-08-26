#include<iostream>
#include<cstring>
using namespace std;
int n, p;
double cache[101][50];
int adj[50][50];
int neighbor[50];
// 각 마을에 이웃하는 마을수를 미리 구한다
void precalc() {
	for (int i = 0; i < n; i++) {
		int neighborhood = 0;
		for (int j = 0; j < n; j++) 
			if (adj[i][j])
				neighborhood++;
		neighbor[i] = neighborhood;
	}
}
// day일차때 town에 있을확률
double numb3rs(int day, int town) {
	//0일차때 교도소에 있을확률 1, 그 외 0
	if (day == 0) 
		return town == p ? 1 : 0;
	double& ret = cache[day][town];
	if (ret != -1.0) return ret;
	ret = 0.0;
	// 전날 town에 이웃한 마을 i있다가 town으로 넘어올 확률
	for (int i = 0; i < n; i++) {
		if (adj[town][i]) {
			ret += numb3rs(day - 1, i) / neighbor[i];
		}
	}
	return ret;
}
int main() {
	cout << fixed;
	cout.precision(8);
	int testcase;
	cin >> testcase;
	while (testcase--) {
		fill(&cache[0][0], &cache[100][50], -1.0);
		int day, num;
		cin >> n >> day >> p;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> adj[i][j];
		precalc();
		cin >> num;
		for (int i = 0; i < num; i++) {
			int findedTown;
			cin >> findedTown;
			cout << numb3rs(day, findedTown) << endl;
		}
	}
}
