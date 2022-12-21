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

struct MonkeyVal
{
	double humn = 0;
	double c = 0;
	MonkeyVal() {}
	MonkeyVal(double a, double b): humn(a), c(b) {}
	MonkeyVal operate(char op, MonkeyVal other)
	{
		switch (op)
		{
			case '+': return MonkeyVal(humn + other.humn, c + other.c);
			case '-': return MonkeyVal(humn - other.humn, c - other.c);
			// Hopefully we don't end up squaring humans
			case '*': return MonkeyVal(humn == 0 ? other.humn * c : humn * other.c, c * other.c);
			case '/': return MonkeyVal(humn / other.c, c / other.c);
		}
		throw "Unrecognised Operation";
	}
};

vector<bool> activated(n, 0);
vector<MonkeyVal> value(n);
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
		if (id == idOf("humn"))
		{
			activated[id] = 1;
			value[id].humn = 1;
		}
		else if (isdigit(s[6]))
		{
			activated[id] = 1;
			value[id].c = stoi(s.substr(6));
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
				auto m1Val = value[m1[i]], m2Val = value[m2[i]];
				value[i] = m1Val.operate(op[i], m2Val);
				activated[i] = 1;
			}
		}
	}
	auto m1Val = value[m1[CHECK_MONKEY]], m2Val = value[m2[CHECK_MONKEY]];
	long long val = (m2Val.c - m1Val.c) / (m1Val.humn - m2Val.humn);
	cout << val;
	return 0;
}