#include <iostream>
#include <string>
using namespace std;

bool hasRepeat(string s, int i, int minRepeat)
{
	for (int j = 0; j < minRepeat; j++)
		for (int k = j + 1; k < minRepeat; k++)
			if (s[i + j] == s[i + k]) return 1;
	return 0;
}

int main()
{
	string s;
	const int minRepeat = 4;
	cin >> s;
	for (int i = 0; i <= s.length() - minRepeat; i++)
	{
		if (!hasRepeat(s, i, minRepeat))
		{
			cout << i + minRepeat;
			return 0;
		}
	}
	return 0;
}