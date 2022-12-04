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
		score += m2 - 'X' + 1;
		// A draw: Diff. mod 3 is always 0
		// A win: Diff. mod 3 is always 1
		// A loss: Diff. mod 3 is always -1 (2)
		int id = ((m2 - 'X') - (m1 - 'A') + 3) % 3;
		switch (id) {
			case 0:
				// Draw
				score += 3; break;
			case 1:
				// Win
				score += 6; break;
			case 2:
				// Lose
				score += 0; break;
		}
	}
	cout << score;
	return 0;
}