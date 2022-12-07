#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int score = 0;

int traverse()
{
	string s;
	int tmpScore = 0;
	// Remove "$ ls" first
	getline(cin, s);
	getline(cin, s);
	while (s[0] != '$')
	{
		stringstream ss;
		ss << s;
		int a = -1;
		ss >> a;
		if (a >= 0) tmpScore += a;
		if (cin.eof()) break;
		getline(cin, s);
	}
	// If "cd .."
	while (s[s.length() - 1] != '.' && !cin.eof())
	{
		tmpScore += traverse();
		getline(cin, s);
	}
	if (tmpScore < 100000) score += tmpScore;
	return tmpScore;
}

int main()
{
	string throwaway;
	getline(cin, throwaway);
	traverse();
	cout << score;
	return 0;
}