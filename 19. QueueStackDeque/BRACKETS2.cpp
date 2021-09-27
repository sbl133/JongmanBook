#include<iostream>
#include<stack>
using namespace std;
bool wellMatched(const string& formula) {
	// 여는 괄호 문자들과 닫는 괄호 문자가 대응되는것 끼리 index가 같게 문자열 생성
	string opening("({["), closing(")}]");
	stack<char> openStack;
	for (int i = 0; i < formula.length(); i++) 
		// 여는 괄호면 스택에 넣는다
		if (opening.find(formula[i]) != -1)
			openStack.push(formula[i]);
		// 닫는 괄호면
		else {
			// 스택이 비어있거나
			if (openStack.empty())
				return false;
			// 스택탑이 대응하는 여는 괄호가 아니라면 return false
			else if (opening.find(openStack.top()) != closing.find(formula[i]))
				return false;
			// 스택탑이 대응하는 여는 괄호라면 pop 
			openStack.pop();
		}
	return openStack.empty();
}
int main() {
	int testcase;
	cin >> testcase;
	while (testcase--) {
		string str;
		cin >> str;
		if (wellMatched(str))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}
