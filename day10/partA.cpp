#include <iostream>
#include <vector>
#include <string>
using namespace std;

string s;
string cmd;
int amt;
int cycle = 0;
int reg = 1;

int score = 0;
void countScore()
{
	if (cycle % 40 == 20 && cycle <= 260) score += reg * cycle;
}

int main()
{
	while (!cin.eof())
	{
		cin >> cmd;
		if (cmd == "noop") {
			cycle++;
			countScore();
		}
		else {
			cycle++;
			countScore();
			cycle++;
			countScore();
			cin >> amt;
			reg += amt;
		}
		getline(cin, s);
	}
	cout << score;
	return 0;
}