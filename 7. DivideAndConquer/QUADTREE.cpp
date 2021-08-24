#include<iostream>
using namespace std;
string reverse(string::iterator& it) {
	char head = *it;
	it++;
	if (head == 'b' || head == 'w')
		return string(1, head);
	//각 조각을 상하 반전시키고
	string upperleft = reverse(it);
	string upperright = reverse(it);
	string lowerleft = reverse(it);
	string lowerright = reverse(it);
	// 밑에 두족각을 올려주고 위에 두조각을 내려주면 상하반전과 같다
	return string("x") + lowerleft + lowerright + upperleft + upperright;
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		string str;
		cin >> str;
		string::iterator it(str.begin());
		cout << reverse(it) << endl;
	}
}
