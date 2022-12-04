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
	string s1, s2, s3;
	bool hasChar1[54], hasChar2[54];
	int n1, n2, n3;
	while (!cin.eof())
	{
		fill(hasChar1, hasChar1 + 54, 0);
		fill(hasChar2, hasChar2 + 54, 0);
		getline(cin, s1);
		getline(cin, s2);
		getline(cin, s3);
		n1 = s1.length();
		n2 = s2.length();
		n3 = s3.length();
		for (int i = 0; i < n1; i++)
		{
			hasChar1[charCode(s1[i])] = 1;
		}
		for (int i = 0; i < n2; i++)
		{
			hasChar2[charCode(s2[i])] = 1;
		}
		for (int i = 0; i < n3; i++)
		{
			if (hasChar1[charCode(s3[i])] && hasChar2[charCode(s3[i])])
			{
				score += charCode(s3[i]);
				break;
			}
		}
	}
	cout << score;
	return 0;
}