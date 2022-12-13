#include <iostream>
#include <queue>
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
	int i = 0;
	string left, right, thrwawy;
	while (true)
	{
		i++;
		getline(cin, left);
		getline(cin, right);
		if (testOrder(left, right) > 0) score += i;
		if (cin.eof()) break;
		getline(cin, thrwawy);
	}
	cout << score;
	return 0;
}