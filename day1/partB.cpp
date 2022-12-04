#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
	int currentElf = 0;
	int maxElf1 = 0, maxElf2 = 0, maxElf3 = 0;
	while (!cin.eof())
	{
		string c;
		getline(cin, c);
		if (c.empty()) {
			if (currentElf > maxElf1) {
				maxElf3 = maxElf2;
				maxElf2 = maxElf1;
				maxElf1 = currentElf;
			} else if (currentElf > maxElf2) {
				maxElf3 = maxElf2;
				maxElf2 = currentElf;
			} else if (currentElf > maxElf3) {
				maxElf3 = currentElf;
			}
			currentElf = 0;
		} else {
			currentElf += stoi(c);
		}
	}
	if (currentElf > maxElf1) {
		maxElf3 = maxElf2;
		maxElf2 = maxElf1;
		maxElf1 = currentElf;
	} else if (currentElf > maxElf2) {
		maxElf3 = maxElf2;
		maxElf2 = currentElf;
	} else if (currentElf > maxElf3) {
		maxElf3 = currentElf;
	}
	cout << maxElf1 + maxElf2 + maxElf3;
	return 0;
}