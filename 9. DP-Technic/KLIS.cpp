#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAX = 2000000000 + 1;
// LIS의 길이를 구하기 위한 cache, LIS의 갯수를 구하기 위한 cache
int cacheLen[501], cacheCnt[501];
// 입력받은 수열
int S[500];
int n, k;
vector<int> V;
// LIS의 길이를 구하는 함수 lis
int lis(int start) {
	int& ret = cacheLen[start + 1];
	if (ret != -1)return ret;
	ret = 1;
	for (int next = start + 1; next < n; next++) {
		if (start == -1 || S[start] < S[next])
			ret = max(ret, lis(next) + 1);
	}
	return ret;
}
// LIS의 갯수를 구하는 함수 count
int count(int start) {
	if (lis(start) == 1)return 1;
	int& ret = cacheCnt[start + 1];
	if (ret != -1)return ret;
	ret = 0;
	// LIS면 lis(start)==lis(next) + 1 이다.
	for (int next = start + 1; next < n; next++) {
		if ((start == -1 || S[start] < S[next]) && (lis(start) == lis(next) + 1))
			ret = min<long long>(MAX, (long long)ret + count(next));
	}
	return ret;
}
// start이후의 LIS를 사전순으로 skip개 건너뛴 수열을 V에 저장
void reconstruct(int start, int skip) {
	if (start != -1)V.push_back(S[start]);
	vector<pair<int, int>> followers;
	// start 다음으로 올수있는 수들을 followers에 넣고 사전순으로 정렬
	for (int next = start + 1; next < n; next++) {
		if ((start == -1 || S[start] < S[next]) && (lis(start) == lis(next) + 1))
			followers.push_back(make_pair(S[next], next));
	}
	sort(followers.begin(), followers.end());
	// i번째 followers로 만들수 있는 LIS가 skip개 이하면 건너뜀
	for (int i = 0; i < followers.size(); i++) {
		int idx = followers[i].second;
		int cnt = count(idx);
		if (cnt <= skip)
			skip -= cnt;
		else {
			reconstruct(idx, skip);
			break;
		}
	}
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		memset(cacheLen, -1, sizeof(cacheLen));
		memset(cacheCnt, -1, sizeof(cacheCnt));
		V.clear();
		cin >> n >> k;
		for (int i = 0; i < n; i++)
			cin >> S[i];
		cout << lis(-1) - 1 << endl;
		reconstruct(-1, k-1);
		for (int i = 0; i < V.size(); i++)
			cout << V[i] << " ";
		cout << endl;
	}
}
