#include<algorithm>
#include<cmath>
#include<cstring>
#include<iostream>
using namespace std;
int n, m; // n:출력단어수 m:저장된단어수
int R[100]; //분류기가 인식한 문장의 각 단어번호
double T[501][501];//T[i][j]:i다음j가 올 확률
double M[501][501];//M[i][j]:i를j로 해석할 확률
int choice[102][502];
double cache[102][502];
int q;//출력해야할 문장수
string corpus[501]; // 단어사전
double recognize(int segment, int previousmatch) {
	if (segment == n)return 0;
	double& ret = cache[segment][previousmatch];
	if (ret != 1.0)return ret;
	ret = -1e200;
	int& choose = choice[segment][previousmatch];
	// 로그를 취했으므로 확률을 곱이 아닌 합으로 구한다
	for (int thismatch = 1; thismatch <= m; thismatch++) {
		double cand = T[previousmatch][thismatch]
			+ M[thismatch][R[segment]]
			+ recognize(segment + 1, thismatch);
		if (ret < cand) {
			ret = cand;
			choose = thismatch;
		}
	}
	return ret;
}
string reconstruct(int segment, int previousmatch) {
	int choose = choice[segment][previousmatch];
	string ret = corpus[choose];
	if (segment < n - 1)
		ret = ret + " " + reconstruct(segment + 1, choose);
	return ret;
}
void init() {
	cin >> m >> q;
	string temp;
	for (int i = 1; i <= m; i++) 
		cin >> corpus[i];
	double b;//B를 T에 넣는과정
	for (int i = 1; i <= m; i++) {
		cin >> b;
		T[0][i] = log(b);//첫번째로 i가 올 확률
	}
	double lg;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++) {
			cin >> lg;
			T[i][j] = log(lg);
		}
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++) {
			cin >> lg;
			M[i][j] = log(lg);
		}
}
int main() {
	init();
	while (q--) {
		fill(&cache[0][0], &cache[101][502], 1.0);
		cin >> n;
		string temp;
		for (int i = 0; i < n; i++) {
			cin >> temp;
			for (int j = 1; j <= m; j++)
				if (temp == corpus[j]) {
					R[i] = j;
					break;
				}
		}
		recognize(0, 0);
		cout << reconstruct(0, 0) << endl;
	}
}
