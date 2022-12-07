#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<int> dirSizes;
int totalSize = 0;

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
	dirSizes.push_back(tmpScore);
	return tmpScore;
}

int main()
{
	string throwaway;
	getline(cin, throwaway);
	totalSize = traverse();
	int minSizeReq = 2147483647;
	for (int x : dirSizes) {
		if (x + 70000000 - totalSize > 30000000 && x < minSizeReq) minSizeReq = x;
	}
	cout << minSizeReq;
	return 0;
}