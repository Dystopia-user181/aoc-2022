#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

int idOf(string s)
{
	return (((s[0] - 'a') * 26 + s[1] - 'a') * 26 + s[2] - 'a') * 26 + s[3] - 'a';
}

const int n = 26 * 26 * 26 * 26;
const int CHECK_MONKEY = idOf("root");

vector<bool> activated(n, 0);
vector<long long> value(n);
vector<char> op(n);
vector<int> m1(n, n);
vector<int> m2(n, n);

int main()
{
	string s;
	while (!cin.eof())
	{
		getline(cin, s);
		int id = idOf(s.substr(0, 4));
		if (isdigit(s[6]))
		{
			activated[id] = 1;
			value[id] = stoi(s.substr(6));
		}
		else
		{
			m1[id] = idOf(s.substr(6, 4));
			m2[id] = idOf(s.substr(13, 4));
			op[id] = s[11];
		}
	}

	while (!activated[CHECK_MONKEY])
	{
		for (int i = 0; i < n; i++)
		{
			if (activated[i] || m1[i] >= n) continue;
			if (activated[m1[i]] && activated[m2[i]])
			{
				long long m1Val = value[m1[i]], m2Val = value[m2[i]];
				switch (op[i])
				{
					case '+': value[i] = m1Val + m2Val; break;
					case '-': value[i] = m1Val - m2Val; break;
					case '*': value[i] = m1Val * m2Val; break;
					case '/': value[i] = m1Val / m2Val; break;
				}
				activated[i] = 1;
			}
		}
	}
	cout << value[CHECK_MONKEY];
	return 0;
}