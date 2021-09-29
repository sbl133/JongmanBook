#include<iostream>
#include<vector>
using namespace std;
// kmp알고리즘을 위한 실패함수
vector<int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);
	int begin = 1, match = 0;
	// 비교할 문자가 N의 끝에 도달할 때까지 찾으면서 부분 일치를 모두 기록
	while (begin + match < m) {
		if (N[begin + match] == N[match]) {
			match++;
			pi[begin + match -1] = match;
		}
		else {
			if (match == 0)
				begin++;
			else {
				begin += match - pi[match - 1];
				match = pi[match - 1];
			}
		}
	}
	return pi;
}
// kmp 알고리즘
vector<int> kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> ret;
	vector<int> pi = getPartialMatch(N);
	int matched = 0;
	// 문자열 H를 순회
	for (int i = 0; i < n; i++) {
		// 해당 위치에서 불일치 할경우 matched를 pi[matched-1]로 줄인다
		while (matched > 0 && H[i] != N[matched])
			matched = pi[matched - 1];
		// 글자가 대응될 경우
		if (H[i] == N[matched]) {
				matched++;
			if (matched == m) {
				ret.push_back(i - matched + 1);
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}
// 시계방향의 경우 현재 다이얼을 오른쪽으로 이동시키면서
// 목표하는 다이얼 모양을 나타내는 문자열 두개를 이어붙인것과 
// 일치하는 처음 위치를 찾는다. (반시계 방향일 경우 target과 origin만 바꾸면 된다.)
int shifts(const string& target, const string& origin) {
	return kmpSearch(target + target, origin)[0];
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int n, ret = 0;
		// 처음에는 시계방향
		bool dir = false;
		cin >> n;
		string ori, tar;
		cin >> tar;
		for (int i = 0; i < n; i++) {
			ori = tar;
			cin >> tar;
			if (dir)
				ret += shifts(ori, tar);
			else 
				ret += shifts(tar, ori);
			dir = !dir;
		}
		cout << ret << endl;
	}
}
