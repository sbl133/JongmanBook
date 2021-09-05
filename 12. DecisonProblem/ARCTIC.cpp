#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<cstdio>
using namespace std;
int n;
// 좌표저장
vector<pair<double, double>> pos;
// 각 기지들간의 거리
double dist[100][100];
// bfs를 사용하여 모든기지가 하나로 연결되있으면서
// d이하의 거리로 탐색가능한지 확인
bool decision(double d) {
	vector<bool> visited(n, false);
	visited[0] = true;
	queue<int> q;
	q.push(0);
	int seen = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		seen++;
		for(int there=0; there<n; there++)
			if (!visited[there] && dist[here][there] <= d) {
				visited[there] = true;
				q.push(there);
			}
	}
	return seen == n;
}
// decision의 d를 이분법을 사용하여 좁혀가면서 최적해를 찾는다
double optimize() {
	double lo = 0.0, hi = 1500.0;
	for (int it = 0; it < 100; it++) {
		double mid = (hi + lo) / 2;
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		pos.clear();
		cin >> n;
		for (int i = 0; i < n; i++) {
			double x, y;
			cin >> x >> y;
			pos.push_back(make_pair(x, y));
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				dist[i][j] = sqrt(pow(pos[i].first - pos[j].first,2) + 
					pow(pos[i].second - pos[j].second,2));
		printf("%.2f\n", optimize());
	}
}
