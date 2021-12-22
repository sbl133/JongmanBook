#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
// 알파벳 대문자를 숫자로 표현
int toNumber(char ch) { return ch - 'A'; }
// 트라이의 한 노드를 나타내는 객체
struct TrieNode {
	// 자식이 알파벳 개수만큼 있을 수 있음
	TrieNode* children[26];
	// 해당 노드가 종료 노드이면 id값 아니면 -1
	int terminal;
	// 해당 노드를 루트로 했을때 자동완성가능한 단어 id값
	int first;
	TrieNode(): terminal(-1), first(-1) {
		memset(children, 0, sizeof(children));
	};
	~TrieNode() {
		for (int i = 0; i < 26; i++)
			if (children[i])
				delete children[i];
	}
	// key 문자열을 id값으로 삽입
	void insert(const char* key, int id) {
		// 해당 접두사로 자동완성되는 단어가 없으면 first 갱신
		if (first == -1) first = id;
		// 단어의 끝일경우 terminal 갱신
		if (*key == 0)terminal = id;
		// 단어가 끝이 아닐경우 알맞은 자식노드로 재귀
		else {
			int next = toNumber(*key);
			if (children[next] == NULL)
				children[next] = new TrieNode();
			children[next]->insert(key + 1, id);
		}
	}
	// 해당 노드를 루트로하는 트라이에서 key와 대응되는 노드를 찾기
	TrieNode* find(const char* key) {
		if (*key == 0) return this;
		int next = toNumber(*key);
		// key가 트라이에 없으면 NULL 반환
		if (children[next] == NULL)return NULL;
		return children[next]->find(key + 1);
	}
	// 해당 노드까지 왔을때, id값이 id인 문자열 key를 완성시키기 위해서 쳐야되는 타자횟수
	int type(const char* key, int id) {
		// 단어의 끝이면 다 완성된것이므로 return 0
		if (*key == 0) return 0;
		// 자동완성되는 단어가 치고자 하는 단어면 탭키
		if (first == id)return 1;
		int next = toNumber(*key);
		// 아직 못찾았으면 재귀
		return 1 + children[next]->type(key + 1, id);
	}
};
// 주어진 트라이에서 단어 word를 완성시키기 위해 필요한 타자 횟수
int countKeys(TrieNode* trie, const char* word) {
	TrieNode* node = trie->find(word);
	if (node == NULL || node->terminal == -1) return strlen(word);
	return trie->type(word, node->terminal);
}
// 입력으로 주어진 단어들을 빈도수, 사전순으로 정렬하여 트라이 형태로 삽입
// 정렬을 한 후 차례대로 트라이에 삽입하게 되면 자동완성에 우선순위가 반영된다.
TrieNode* readInput(int words) {
	vector<pair<int, string>> input;
	for (int i = 0; i < words; i++) {
		string buf;
		int freq;
		cin >> buf >> freq;
		input.push_back(make_pair(-freq, buf));
	}
	sort(input.begin(), input.end());
	TrieNode* trie = new TrieNode();
	for (int i = 0; i < input.size(); i++) 
		trie->insert(input[i].second.c_str(), i);
	trie->first = -1;
	return trie;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int n, m, result = 0;
		string tmp;
		cin >> n >> m;
		TrieNode* trie = readInput(n);
		for (int i = 0; i < m; i++) {
			cin >> tmp;
			result += countKeys(trie, tmp.c_str());
		}
		cout << result + m - 1 << endl;
	}
}
