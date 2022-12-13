#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

size_t findNextComma(string s)
{
	int bracketDepth = 0;
	for (size_t i = 0; i < s.length(); i++)
	{
		if (s[i] == '[') bracketDepth++;
		else if (s[i] == ']') bracketDepth--;
		if (bracketDepth == 0 && s[i] == ',') return i;
	}
	return s.length();
}
int testOrder(string left, string right)
{
	if (right.empty() && !left.empty()) return -1;
	else if (left.empty() && !right.empty()) return 1;
	if (left.empty() && right.empty()) return 0;
	if (left[0] != '[' && right[0] != '[') return stoi(right) - stoi(left);
	else if (left[0] == '[' && right[0] != '[') return testOrder(left, '[' + right + ']');
	else if (left[0] != '[' && right[0] == '[') return testOrder('[' + left + ']', right);
	int result = 0;
	string l = left.substr(1, left.size() - 2);
	string r = right.substr(1, right.size() - 2);
	size_t ptrLeft = 0;
	size_t ptrRight = 0;
	while (result == 0)
	{
		ptrLeft = findNextComma(l);
		ptrRight = findNextComma(r);
		result = testOrder(l.substr(0, ptrLeft), r.substr(0, ptrRight));
		if (result) break;
		if (ptrLeft >= l.length() && ptrRight < r.length()) return 1;
		else if (ptrLeft < l.length() && ptrRight >= r.length()) return -1;
		else if (ptrLeft >= l.length() && ptrRight >= r.length()) break;
		l = l.substr(ptrLeft + 1);
		r = r.substr(ptrRight + 1);
	}
	return result;
}

int main()
{
	int score = 0;
	vector<string> packets = { "[[2]]", "[[6]]" };
	string left, right, thrwawy;
	while (true)
	{
		getline(cin, left);
		getline(cin, right);
		packets.push_back(left);
		packets.push_back(right);
		if (cin.eof()) break;
		getline(cin, thrwawy);
	}
	sort(packets.begin(), 
		packets.end(), 
		[](string a, string b) { return testOrder(a, b) > 0; });
	int p2, p6;
	for (int i = 0; i < packets.size(); i++)
	{
		if (packets[i] == "[[2]]") p2 = i;
		else if (packets[i] == "[[6]]") p6 = i;
	}
	cout << (p2 + 1) * (p6 + 1);
	return 0;
}