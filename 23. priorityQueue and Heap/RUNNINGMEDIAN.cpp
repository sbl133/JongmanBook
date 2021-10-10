#include<iostream>
#include<queue>
using namespace std;
int n;
struct RNG {
	int a, b, seed;
	RNG(int _a, int _b) :a(_a), b(_b), seed(1983) {}
	int next() {
		int ret = seed;
		seed = (seed * (long long)a + b) % 20090711;
		return ret;
	}
};
int runningMedian(RNG rng) {
	priority_queue<int> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;
	int ret = 0;
	for (int i = 0; i < n; i++) {
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());
		if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()) {
			int a = minHeap.top();
			int b = maxHeap.top();
			minHeap.pop(); maxHeap.pop();
			minHeap.push(b); maxHeap.push(a);
		}
		ret = (ret + maxHeap.top()) % 20090711;
	}
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int a, b;
		cin >> n >> a >> b;
		RNG rng(a, b);
		cout << runningMedian(rng) << endl;
	}
}
