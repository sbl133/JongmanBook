#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
// 성벽 갯수
int n;
// 각 성벽 좌표, 반지름
int x[100], y[100], radius[100];
struct TreeNode {
	vector<TreeNode*> child;
};
// 트리의 잎과 잎사이 가장 긴 길이
int longest;
// 트리의 높이를 반환
int height(TreeNode* root) {
	vector<int> heights;
	// 각 서브트리의 높이를 재귀를 이용해 계산
	for (int i = 0; i < root->child.size(); i++) 
		heights.push_back(height(root->child[i]));
	// leaf노드면 return 0
	if (heights.empty())return 0;
	// 서브트리들의 높이를 오름차순 정렬
	sort(heights.begin(), heights.end());
	// 서브트리중에 가장 높은거 두개 뽑아서 longest계산
	if (heights.size() >= 2)
		longest = max(longest, 2 + heights[heights.size() - 2] +
			heights[heights.size() - 1]);
	// 현재 트리의 높이 = 가장 높은 서브트리의 높이 + 1
	return heights.back() + 1;
}
// 성벽을 넘는 횟수의 최댓값은 
// 가장 긴 루트-잎 경로의 길이 or 가장 긴 잎-잎 경로의 길이
int solve(TreeNode* root) {
	longest = 0;
	int h = height(root);
	return max(longest, h);
}
// 제곱연산
int sqr(int x) {
	return x * x;
}
// a와 b 사이의 거리의 제곱
int sqrdist(int a, int b) {
	return sqr(y[a] - y[b]) + sqr(x[a] - x[b]);
}
// a안에 b가 포함되는지
bool encloses(int a, int b) {
	return radius[a] > radius[b] &&
		sqrdist(a, b) < sqr(radius[a] - radius[b]);
}
// parent는 child를 꼭 직접 포함해야 한다.
bool isChild(int parent, int child) {
	if (!encloses(parent, child))return false;
	for (int i = 0; i < n; i++)
		if (i != parent && i != child &&
			encloses(parent, i) && encloses(i, child))
			return false;
	return true;
}
// root성벽을 루트로 하는 트리를 생성
TreeNode* getTree(int root) {
	TreeNode* ret = new TreeNode();
	for (int i = 0; i < n; i++)
		if (isChild(root, i))
			ret->child.push_back(getTree(i));
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		cin >> n;
		for (int i = 0; i < n; i++) 
			cin >> x[i] >> y[i] >> radius[i];
		cout << solve(getTree(0)) << endl;
	}
}
