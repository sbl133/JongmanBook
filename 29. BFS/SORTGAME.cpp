#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;
// toSort[vector] = vector를 정렬시키는데 필요한 뒤집기 횟수
map<vector<int>, int> toSort;
// 크기가 n인 배열이 배치될수 있는 모든 경우의 뒤집기 횟수 계산
void precalc(int n) {
	vector<int> perm(n);
	for (int i = 0; i < n; i++)
		perm[i] = i;
	queue<vector<int>> q;
	q.push(perm);
	toSort[perm] = 0;
	while (!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		// 현재 비용
		int cost = toSort[here];
		// 모든 뒤집기 상황 고려
		for(int i=0; i<n; i++)
			for (int j = i + 2; j <= n; j++) {
				reverse(here.begin() + i, here.begin() + j);
				// 배열을 뒤집었을때 아직 계산이 안된 배열이면
				if (toSort.count(here) == 0) {
					// 현재 배열 비용에 +1
					toSort[here] = cost + 1;
					q.push(here);
				}
				// 배열 원상복구
				reverse(here.begin() + i, here.begin() + j);
			}
	}
}
// 상대적 크기만 고려하면 되므로 입력으로 주어진 perm을 정규화 시킨후 toSort에서 찾기
int solve(const vector<int>& perm) {
	int n = perm.size();
	vector<int> fixed(n);
	for (int i = 0; i < n; i++) {
		int smaller = 0;
		for (int j = 0; j < n; j++) 
			if (perm[j] < perm[i])
				smaller++;
		fixed[i] = smaller;
	}
	return toSort[fixed];
}
int main() {
	for (int i = 1; i <= 8; i++)
		precalc(i);
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int n;
		cin >> n;
		vector<int> v;
		int tmp;
		for (int i = 0; i < n; i++) {
			cin >> tmp;
			v.push_back(tmp);
		}
		cout << solve(v) << endl;
	}
}
