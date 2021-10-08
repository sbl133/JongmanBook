#include<iostream>
using namespace std;
// 트립을 구성하느 노드
struct Node {
	// 노드의 원소
	int key;
	// 노드의 우선순위, 해당 노드를 루트로하는 트리의 크기
	int priority, size;
	Node* left, * right;
	Node(const int _key) : key(_key), priority(rand()),
		size(1), left(NULL), right(NULL) {}
	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }
	// 자식노트가 바뀔때마다 size를 갱신
	void calcSize() {
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};
typedef pair<Node*, Node*> NodePair;
// root를 루트로 하는 트립의 key 미만의 값과 이상의 값을 갖는
// 두개의 트립으로 분리
NodePair split(Node* root, int key) {
	// 리프노드에 도달할 경우
	if (root == NULL)return NodePair(NULL, NULL);
	// 루트가 key미만이면 오른쪽 서브트리를 다시 split
	if (root->key < key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	// 루트가 key 이상이면 왼쪽 서브트리를 다시 split
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}
// root를 루트로 하는 트립에서 새 노드 node를 삽입한 뒤 결과 트립의
// 루트를 반환한다.
Node* insert(Node* root, Node* node) {
	if (root == NULL) return node;
	// node가 루트를 대체하는 경우
	// 해당 트리를 node->key기준으로 split해서 각각 자손으로 한다.
	if (root->priority < node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	else if (node->key < root->key)
		root->setLeft(insert(root->left, node));
	else
		root->setRight(insert(root->right, node));
	return root;
}
// a와 b가 두 개의 트립이고, max(a) < min(b)일 때 이 둘을 합친다.
Node* merge(Node* a, Node* b) {
	if (a == NULL)return b;
	if (b == NULL)return a;
	if (a->priority < b->priority) {
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}
// root를 루트로 하는 트립에서 key를 지우고 결과 트립의 루트를 반환
Node* erase(Node* root, int key) {
	if (root == NULL) return root;
	// root를 지우고 양 서브트리를 합친 뒤 반환
	if (root->key == key) {
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	if (key < root->key)
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));
	return root;
}
// root를 루트로 하는 트리 중에서 k번째 원소를 반환
Node* kth(Node* root, int k) {
	int leftSize = 0;
	// 왼쪽 서브트리의 크기를 먼저 계산
	if (root->left != NULL) leftSize = root->left->size;
	if (k <= leftSize)return kth(root->left, k);
	if (k == leftSize + 1)return root;
	return kth(root->right, k - leftSize - 1);
}
// shifted[i] = A[i]가 왼쪽으로 몇칸 움직이는가?
int n, shifted[50000];
int A[50000];
// n, shifted[]를 보고 A[]에 값을 저장
void solve() {
	Node* candidates = NULL;
	// 트립 형성
	for (int i = 0; i < n; i++)
		candidates = insert(candidates, new Node(i + 1));
	// 뒤에서부터 A[]채우기
	for (int i = n - 1; i >= 0; i--) {
		int larger = shifted[i];
		Node* k = kth(candidates, i + 1 - larger);
		A[i] = k->key;
		candidates = erase(candidates, k->key);
	}
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> shifted[i];
		solve();
		for (int i = 0; i < n; i++)
			cout << A[i] << " ";
		cout << endl;
	}
}
