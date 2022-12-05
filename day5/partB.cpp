#include <iostream>
#include <string>
#include <deque>
#include <stack>
#include <vector>
using namespace std;

int main()
{
	int n;
	string s;
	getline(cin, s);
	n = (s.length() + 1) / 4;
	vector<deque<char>> towers(n);
	while (s[1] != '1') {
		for (int i = 0; i < n; i++) {
			if (s[i * 4 + 1] != ' ') towers[i].push_front(s[i * 4 + 1]);
		}
		getline(cin, s);
	}
	getline(cin, s);
	while (!cin.eof()) {
		int num, a, b;
		cin >> s >> num >> s >> a >> s >> b;
		stack<char> tmp;
		for (int i = 0; i < num; i++) {
			tmp.push(towers[a - 1].back());
			towers[a - 1].pop_back();
		}
		for (int i = 0; i < num; i++) {
			towers[b - 1].push_back(tmp.top());
			tmp.pop();
		}
		getline(cin, s);
	}
	for (int i = 0; i < n; i++) cout << towers[i].back();
	return 0;
}