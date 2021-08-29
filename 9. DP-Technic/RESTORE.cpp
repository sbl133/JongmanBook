#include<iostream>
#include<cstring>
using namespace std;
int cache[1 << 16][16];
int overlap[16][16];
string word[16];
int k;
// last와 next가 겹치는 글자갯수 overlap을 미리 계산
void precalc() {
	for(int last=0; last<k; last++)
		for (int next = 0; next < k; next++) {
			int overlapLength = min(word[last].length(), word[next].length());
			int it = word[last].find(word[next]);
			//  next가 last에 완전히 포함되는경우
			if (it >= 0 && (word[last].length() > it + word[next].length()) &&
				(word[next] == word[last].substr(it, word[next].length())))
				overlap[last][next] = overlapLength;
			// 그 이외의 경우
			else 
				for (; overlapLength > 0; overlapLength--) {
					string a = word[last].substr(word[last].length() - overlapLength);
					string b = word[next].substr(0, overlapLength);
					if (a == b) {
						overlap[last][next] = overlapLength;
						break;
					}
				}
		}
}
// 단어들을 나열하면서 overlap의 최대값의 경우들을 구하기
int restore(int taken, int last) {
	if ((1 << k) - 1 == taken)return 0;
	int& ret = cache[taken][last];
	if (ret != -1)return ret;
	ret = 0;
	for (int next = 0; next < k; next++) 
		if (((1 << next) & taken) == 0) {
			int cand;
			// next가 last에 완전히 포함되는경우 next대신 last로 재귀호출
			if (overlap[last][next] == word[next].size()) 
				cand = overlap[last][next] +
					restore(taken + (1 << next), last);
			else
				cand = overlap[last][next] +
					restore(taken + (1 << next), next);
			ret = max(ret, cand);
		}
	return ret;
}
string reconstruct(int taken, int last) {
	if ((1 << k) - 1 == taken)return "";
	for(int next=0; next<k; next++)
		if (((1 << next) & taken) == 0) {
			int candLength;
			// next가 last에 완전히 포함되는경우 추가되는 글자는 없다
			if (overlap[last][next] == word[next].size()) {
				candLength = overlap[last][next] +
					restore(taken + (1 << next), last);
				if (candLength == restore(taken, last))
					return reconstruct(taken + (1 << next), last);
			}
			else {
				candLength = overlap[last][next] +
					restore(taken + (1 << next), next);
				if (candLength == restore(taken, last))
					return word[next].substr(overlap[last][next]) +
					reconstruct(taken + (1 << next), next);
			}
		}
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		memset(cache, -1, sizeof(cache));
		memset(overlap, 0, sizeof(overlap));
		cin >> k;
		// word에 ""를 추가하고 ""를 선택하여 초기 last값을 준다
		word[0] = "";
		for (int i = 1; i <= k; i++) {
			cin >> word[i];
		}
		k += 1;
		precalc();
		cout << reconstruct(1, 0) << endl;
	}
}
