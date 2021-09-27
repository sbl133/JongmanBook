#include<iostream>
#include<queue>
using namespace std;
int k, n;
// 실시간으로 입력을 생성하기 위한 구조체
struct RNG {
	unsigned seed;
	RNG() : seed(1983) {}
	unsigned next() {
		unsigned ret = seed;
		seed = ((seed * 214013u) + 2531011u);
		return ret % 10000 + 1;
	}
};
// 신호분석
int ites() {
	queue<int> q;
	int result = 0, queSum = 0;
	RNG rng;
	// n개의 신호를 순회한다.
	for (int i = 0; i < n; i++) {
		// 신호생성
		int newSignal = rng.next();
		q.push(newSignal);
		queSum += newSignal;
		// 큐에 들어있는 신호들의 합이 k이상이면 순서대로 신호 pop
		while (queSum >= k) {
			// 큐에 들어있는 신호들의 합이 k면 result++
			if (queSum == k)
				result++;
			queSum -= q.front();
			q.pop();
		}
	}
	return result;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		cin >> k >> n;
		cout << ites() << endl;
	}
}
