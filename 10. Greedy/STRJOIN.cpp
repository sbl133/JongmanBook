#include<iostream>
#include<queue>
using namespace std;
int n;
int strjoin(priority_queue<int, vector<int>, greater<int>>& pq) {
	int ret = 0;
	// pq에 요소가 2개이상있으면 가장짧은거 두개 꺼내서 합친걸 다시 넣는다
	while (pq.size() > 1) {
		int x = pq.top();
		pq.pop();
		int y = pq.top();
		pq.pop();
		ret += x + y;
		pq.push(x + y);
	}
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		// 문자열 길이를 기준으로 오름차순을 위한 우선순위 큐
		priority_queue<int, vector<int>, greater<int>> pq;
		int length;
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> length;
			pq.push(length);
		}
		cout << strjoin(pq) << endl;
	}
}
