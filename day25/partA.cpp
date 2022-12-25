#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int SNAFU(char x)
{
	switch(x)
	{
		case '1': return 1;
		case '2': return 2;
		case '-': return -1;
		case '=': return -2;
	}
	return 0;
}
int UFANS(int x)
{
	switch(x)
	{
		case 1: return '1';
		case 2: return '2';
		case -1: return '-';
		case -2: return '=';
	}
	return '0';
}
int main()
{
	long long n = 0;
	while (!cin.eof())
	{
		string s;
		getline(cin, s);
		int x = s.length();
		long long a = 0;
		for (int i = 0; i < x; i++)
		{
			a *= 5;
			a += SNAFU(s[i]);
		}
		n += a;
	}
	long  long x = 1;
	string s = "";
	int i = 0;
	while (n != 0 && i < 20)
	{
		i++;
		long long a = (n % (x * 5)) / x;
		if (a > 2) a = a - 5;
		n -= a * x;
		s = string(1, UFANS(a)) + s;
		x *= 5;
	}
	cout << s;
	return 0;
}