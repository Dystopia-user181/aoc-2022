#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
	int score = 0;
	while (!cin.eof()) {
		int a1, b1, a2, b2;
		char thr;
		string s;
		cin >> a1 >> thr >> b1 >> thr >> a2 >> thr >> b2;
		if ((a1 >= a2 && b1 <= b2) || (a2 >= a1 && b2 <= b1)) score++;
		getline(cin, s);
	}
	cout << score;
	return 0;
}