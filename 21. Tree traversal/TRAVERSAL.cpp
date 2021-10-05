#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
// vector v를 [a,b)만큼 복사해서 반환
vector<int> slice(const vector<int>& v, int a, int b) {
	return vector<int>(v.begin() + a, v.begin() + b);
}
void printPostOrder(const vector<int>& preorder, const vector<int>& inorder) {
	// 트리에 포함된 노드 수
	const int N = preorder.size();
	// 기저 사례: 텅빈 트리면 곧장 종료
	if (preorder.empty()) return;
	// 현재 트리의 root는 preorder의 첫번째 요소
	const int root = preorder[0];
	// 왼쪽 서브트리 크기는 중위 탐색의 시작부터 root가 발견되기 전까지의 크기
	const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
	// 왼쪽, 오른쪽 서브트리를 나눠서 재귀
	printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
	printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
	cout << root << ' ';
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int n;
		vector<int> pre, in;
		cin >> n;
		int tmp;
		for (int i = 0; i < n; i++) {
			cin >> tmp;
			pre.push_back(tmp);
		}
		for (int i = 0; i < n; i++) {
			cin >> tmp;
			in.push_back(tmp);
		}
		printPostOrder(pre, in);
		cout << endl;
	}
}
