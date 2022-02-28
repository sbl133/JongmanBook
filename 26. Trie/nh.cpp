#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'a'; }
struct TrieNode {
	TrieNode* children[ALPHABETS];
	// 이 노드에서 종료하는 문자열의 번호. 없으면 -1
	int terminal;
	// 실패 연결: 이 노드에서 매칭이 실패했을 때 이 곳으로 가서 계속진행
	// 이 노드에 대응되는 문자열의 접미사이면서 트라이에 포함된 최대 문자열
	TrieNode* fail;
	// 출력 문자열 목록: 이 노드가 방문되었을 때 등장하는 바늘 문자열들의 번호
	vector<int> output;
	// 해당 노드의 번호
	int no;
	// 해당 노드 뒤에 어떤 문자가 붙었을때 어떤 노드를 가지는지
	TrieNode* next[ALPHABETS];
	TrieNode() : terminal(-1) {
		memset(children, 0, sizeof(children));
	};
	~TrieNode() {
		for (int i = 0; i < 26; i++)
			if (children[i])
				delete children[i];
	}
	// 이 노드를 루트로 하는 트라이에 번호 id인 문자열 key를 추가
	void insert(const char* key, int id) {
		if (*key == 0)
			terminal = id;
		else {
			int next = toNumber(*key);
			// 해당 자식 노드가 없다면 생성한다.
			if (children[next] == NULL)
				children[next] = new TrieNode();
			// 해당 자식 노드로 재귀 호출
			children[next]->insert(key + 1, id);
		}
	}
};
TrieNode* readInput(int words) {
	vector<string> input;
	TrieNode* trie = new TrieNode();
	for (int i = 0; i < words; i++) {
		char buf[11];
		cin >> buf;
		trie->insert(buf, i);
	}
	return trie;
}
void computeFailFunc(TrieNode* root) {
	// 루트에서 시작해 한 단계씩 아래로 내려가며 각 노드의 실패 연결 계산
	queue<TrieNode*> q;
	// 루트 실패 연결은 자기 자신
	root->fail = root;
	q.push(root);
	while (!q.empty()) {
		TrieNode* here = q.front();
		q.pop();
		// here의 모든 자손에 대해 실패 연결을 계산하고 큐에 삽입
		for (int edge = 0; edge < ALPHABETS; edge++) {
			TrieNode* child = here->children[edge];
			if (!child) continue;
			// 1레벨 노드의 실패 연결은 항상 루트
			if (here == root)
				child->fail = root;
			else {
				// 아닌 경우 부모의 실패 연결을 따라가면서 실패 연결 탐색
				TrieNode* t = here->fail;
				while (t != root && t->children[edge] == NULL)
					t = t->fail;
				if (t->children[edge])t = t->children[edge];
				child->fail = t;
			}
			// 출력 문자열 목록: 실패 연결을 따라간 노드에서 복사 and
			// 이 위치에서 끝나는 바늘 문자열이 있으면 추가
			child->output = child->fail->output;
			if (child->terminal != -1)
				child->output.push_back(child->terminal);
			q.push(child);
		}
	}
}
// 상태간의 전이 테이블을 next[]에 채운다
void computeTransition(TrieNode* here, int& nodeCounter) {
	// 0에서 시작하는 번호를 매긴다.
	here->no = nodeCounter++;
	// here 뒤에 글자 chr를 붙였을때 어느 상태로 가는지
	for (int chr = 0; chr < ALPHABETS; chr++) {
		// next[] 값을 계산해 저장
		TrieNode* next = here;
		while (next != next->fail && next->children[chr] == NULL)
			next = next->fail;
		if (next->children[chr])next = next->children[chr];
		here->next[chr] = next;
		// 재귀적으로 모든 노드에 대해 전이 테이블 계산
		if (here->children[chr])
			computeTransition(here->children[chr], nodeCounter);
	}
}
const int MOD = 10007;
int cache[101][1001];
// 앞으로 length글자를 더 만들어야 하는데, 아호-코라식 알고리즘의
// 현재 상태가 state에 주어질 때 ids에 걸리지 않는 문자열의 갯수
int count(int length, TrieNode* state) {
	// 기저 사례: 이 상태에 문자열이 출현하면 곧장 종료
	if (state->output.size())return 0;
	// 기저 사례: 문자열을 전부 만든 경우
	if (length == 0)return 1;
	int& ret = cache[length][state->no];
	if (ret != -1)return ret;
	ret = 0;
	// 다음으로 letter글자를 넣은 경우
	for (int letter = 0; letter < ALPHABETS; letter++) {
		ret += count(length - 1, state->next[letter]);
		ret %= MOD;
	}
	return ret;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int n, m;
		cin >> n >> m;
		int nodeCounter = 0;
		TrieNode* trie = readInput(m);
		computeFailFunc(trie);
		computeTransition(trie, nodeCounter);
		memset(cache, -1, sizeof(cache));
		cout << count(n, trie) << endl;
	}
}
