#include<iostream>
#include<vector>
using namespace std;
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }
struct TrieNode {
	TrieNode* children[ALPHABETS];
	// 이 노드에서 종료하는 문자열의 번호. 없으면 -1
	int terminal;
	// 실패 연결: 이 노드에서 매칭이 실패했을 때 이 곳으로 가서 계속진행
	// 이 노드에 대응되는 문자열의 접미사이면서 트라이에 포함된 최대 문자열
	TrieNode* fail;
	// 출력 문자열 목록: 이 노드가 방문되었을 때 등장하는 바늘 문자열들의 번호
	vector<int> output;
	TrieNode();
	~TrieNode();
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
};
