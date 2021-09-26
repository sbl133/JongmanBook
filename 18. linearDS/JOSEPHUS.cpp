#include<iostream>
#include<list>
using namespace std;
int n, k;
void josephus() {
	list<int> survivors;
	for (int i = 1; i <= n; i++)
		survivors.push_back(i);
	list<int>::iterator kill = survivors.begin();
	while (n > 2) {
		// 현재 가르키는 사람 죽임
		// list.erase()반환값은 삭제한 노드의 다음 노드를 가르키는 iterator
		kill = survivors.erase(kill);
		// 끝에 다다르면 다시 처음사람을 가르킴
		if (kill == survivors.end())
			kill = survivors.begin();
		n--;
		// k-1번 다음 사람을 가르킴 
		for (int i = 0; i < k - 1; i++) {
			kill++;
			if (kill == survivors.end())
				kill = survivors.begin();
		}
	}
	cout << survivors.front() << " " << survivors.back() << endl;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		cin >> n >> k;
		josephus();
	}
}
