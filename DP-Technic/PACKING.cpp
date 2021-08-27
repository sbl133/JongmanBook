#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
int cache[101][1001];
vector<string> choice;
int N, W;
// vector <이름, <부피, 절박도>> V;
vector<pair<string, pair<int, int>>> V;
int packing(int pos, int weight) {
	if (pos == N) return 0;
	int& ret = cache[pos][weight];
	if (ret != -1) return ret;
	// 해당위치의 물건을 선택안할경우
	ret = packing(pos + 1, weight);
	// 여분의 공간이 있을때 해당위치의 물건을 선택하는 경우
	if (weight >= V[pos].second.first)
		ret = max(ret, packing(pos + 1,
			weight - V[pos].second.first) + V[pos].second.second);
	return ret;
}
void reconstruct(int pos, int weight) {
	if (pos == N)return;
	// pos를 고려하는거랑 그냥 넘어가는거랑 같으면 pos를 선택안한것
	if (packing(pos, weight) == packing(pos + 1, weight))
		reconstruct(pos + 1, weight);
	// 그렇지 않으면 pos를 선택한것
	else {
		choice.push_back(V[pos].first);
		reconstruct(pos + 1, weight - V[pos].second.first);
	}
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		V.clear();
		choice.clear();
		memset(cache, -1, sizeof(cache));
		cin >> N >> W;
		for (int i = 0; i < N; i++) {
			string name;
			int volume, howNeed;
			cin >> name >> volume >> howNeed;
			V.push_back(make_pair(name, make_pair(volume, howNeed)));
		}
		reconstruct(0, W);
		cout << packing(0, W) << " " << choice.size() << endl;
		for (int i = 0; i < choice.size(); i++)
			cout << choice[i] << endl;
	}
}
