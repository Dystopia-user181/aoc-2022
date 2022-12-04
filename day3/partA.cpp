#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

int charCode(char x)
{
	if (x < 'a') return x - 'A' + 27;
	return x - 'a' + 1;
}

int main()
{
	int score = 0;
	string s;
	bool hasChar[54];
	int n;
	while (!cin.eof())
	{
		fill(hasChar, hasChar + 54, 0);
		getline(cin, s);
		n = s.length() / 2;
		for (int i = 0; i < n; i++)
		{
			hasChar[charCode(s[i])] = 1;
		}
		for (int i = 0; i < n; i++)
		{
			if (hasChar[charCode(s[i + n])])
			{
				score += charCode(s[i + n]);
				break;
			}
		}
	}
	cout << score;
	return 0;
}