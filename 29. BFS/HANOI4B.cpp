#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
// index번째 디스크가 몇번째 기둥에 있는지
int get(int state, int index) {
	return (state >> (index * 2)) & 3;
}
// index번째 디스크를 value번째 기둥으로 옮기기
int set(int state, int index, int value) {
	return (state & ~(3 << (index * 2))) | (value << (index * 2));
}
// x 부호 반환
int sgn(int x) { if (!x)return 0; return x > 0 ? 1 : -1; }
// x의 절대값 1증가
int incr(int x) { if (x < 0) return x - 1; return x + 1; }
int c[1 << (12 * 2)];
// discs개의 디스크가 begin상태에서 end상태로 가기위한 최소 움직임 수
int bidir(int discs, int begin, int end) {
	if (begin == end)return 0;
	queue<int> q;
	memset(c, 0, sizeof(c));
	// 정방향 탐색은 양수, 역방향 탐색은 음수로 양방향 탐색
	q.push(begin); c[begin] = 1;
	q.push(end); c[end] = -1;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		int top[4] = { -1,-1,-1,-1 };
		// 각 기둥에 제일 위에 있는 disc계산
		for (int i = discs - 1; i >= 0; i--)
			top[get(here, i)] = i;
		// i번째 기둥 맨 위에 있는 disc를 j번째 기둥으로 옮기기
		for (int i = 0; i < 4; i++) 
			if(top[i]!=-1)
				for(int j=0; j<4; j++)
					// j번째 기둥은 비어 있거나, 맨 위의 disc가 제일 거야함
					if (i != j && (top[j] == -1 || top[j] > top[i])) {
						int there = set(here, top[i], j);
						if (c[there] == 0) {
							c[there] = incr(c[here]);
							q.push(there);
						}
						else if (sgn(c[there]) != sgn(c[here]))
							return abs(c[there]) + abs(c[here]) - 1;
					}
		
	}
	return -1;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int n, begin = 0, end = 0;
		cin >> n;
		for (int i = 0; i < 4; i++) {
			int num;
			cin >> num;
			for (int j = 0; j < num; j++) {
				int discNum;
				cin >> discNum;
				begin |= i << ((discNum - 1) * 2);
			}
		}
		for (int i = 0; i < n; i++) {
			end |= 3 << (i * 2);
		}
		cout << bidir(n, begin, end) << endl;
	}
}
