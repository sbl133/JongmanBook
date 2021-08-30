#include<iostream>
#include<cstring>
using namespace std;
int n, m;
int price[20], prefer[20];
// 선호도를 계산할때 budget[money-price[kind]]를 이용하면 되므로
// budget의 공간은 최대 price[kind]의 최댓값 만큼만 필요하다
int budget[201];
int sushi() {
	int ret = 0;
	budget[0] = 0;
	for (int money = 1; money <= m; money++) {
		int cand = 0;
		for (int kind = 0; kind < n; kind++) 
			if (money >= price[kind])
				// money-price[kind]만큼의 예산을 가지고 있었을때 구한 선호도의 최대합과
				// prefer[kind]를 더한값을 kind별로 탐색해서 선호도의 최대합을 구한다.
				cand = max(cand, budget[(money - price[kind])%201] + prefer[kind]);
		//budget[money]를 budget[money-201]에 덮어씌운다.
		budget[money % 201] = cand;
	}
	return budget[m % 201];
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		cin >> n >> m;
		m /= 100;
		for (int i = 0; i < n; i++) {
			cin >> price[i] >> prefer[i];
			price[i] /= 100;
		}
		cout << sushi() << endl;
	}
}
