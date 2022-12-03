#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
	int score = 0;
	char m1, m2;
	while (!cin.eof())
	{
		m2 = 'A';
		cin >> m1 >> m2;
		if (m2 == 'A') {
			cout << score;
			return 0;
		}
		// X - X (Loss): 0, Y - X (Draw): 1, Z - X (Win): 2
		int rndState = m2 - 'X' - 1;
		score += (rndState + 1) * 3;
		// Win: Always shift by 1
		// Draw: Always shift by 0
		// Lose: Always shift by -1
		int chooseState = (m1 - 'A' + rndState + 3) % 3;
		score += chooseState + 1;
	}
	cout << score;
}