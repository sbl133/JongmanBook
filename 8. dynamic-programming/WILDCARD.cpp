#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
string W, S;
// 메모이제이션을 위한 캐시
int cache[101][101];
int match(int w, int s) {
	int& ret = cache[w][s];
	if (ret != -1) return ret;
	// 일치하는 문자열이 있으면 다음문자로
	while (w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s])) {
		w++;
		s++;
	}
	// 패턴이 끝에 도달했을떄 문자열도 끝이면 return true
	if (w == W.size())
		return ret = (s == S.size());
	// 패턴이 별을 만나면 skip을 0부터 1씩 증가시키면서 skip한 문자열과 다음 패턴을 match
	if (W[w] == '*') {
		for (int skip = 0; s + skip <= S.size(); skip++)
			if (match(w + 1, s + skip))
				return ret = 1;
	}
	// 문자열이 끝에 달했는데 패턴도 남았고 남은 패턴이 별이 아니면 return false
	return ret = 0;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int number;
		vector<string> result;
		cin >> W;
		cin >> number;
		for (int i = 0; i < number; i++) {
			memset(cache, -1, sizeof(cache));
			cin >> S;
			if (match(0, 0))
				result.push_back(S);
		}
		sort(result.begin(), result.end());
		for (int i = 0; i < result.size(); i++)
			cout << result[i] << endl;
	}
}
