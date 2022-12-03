#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
	int currentElf = 0;
	int maxElf = 0;
	while (!cin.eof())
	{
		string c;
		getline(cin, c);
		if (c.empty()) {
			maxElf = max(maxElf, currentElf);
			currentElf = 0;
		} else {
			currentElf += stoi(c);
		}
	}
	maxElf = max(maxElf, currentElf);
	currentElf = 0;
	cout << maxElf;
}