#include <iostream>
#include <vector>
#include <string>
using namespace std;

string s;
string cmd;
int amt;
int cycle = 0;
int reg = 0;

char draw[240];
void countScore()
{
	if (cycle % 40 >= reg && cycle % 40 < reg + 3) draw[cycle] = '#';
	else draw[cycle] = ' ';
}

int main()
{
	while (!cin.eof())
	{
		cin >> cmd;
		if (cmd == "noop") {
			countScore();
			cycle++;
		}
		else {
			countScore();
			cycle++;
			countScore();
			cycle++;
			cin >> amt;
			reg += amt;
		}
		getline(cin, s);
	}
	countScore();
	for (int i = 0; i < 240; i++)
	{
		cout << draw[i] << draw[i];
		if (i % 40 == 39) cout << "\n";
	}
	return 0;
}