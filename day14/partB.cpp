#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

vector<vector<char>> board;
char& getTile(int x, int y)
{
	return board[y][x];
}

int main()
{
	int maxY = 0;
	while (!cin.eof())
	{
		stringstream ss;
		string s;
		getline(cin, s);
		ss << s;
		char thrwawy;
		vector<int> x, y;
		int n = 0;
		while (!ss.eof()) {
			x.push_back(0);
			y.push_back(0);
			ss >> x[n] >> thrwawy >> y[n] >> s;
			if (y[n] > maxY)
			{
				maxY = y[n];
				while (board.size() <= maxY + 1) board.push_back(vector<char>(1000, ' '));
			}
			n++;
		}
		for (int i = 0; i < n - 1; i++)
		{
			int x1 = x[i], x2 = x[i + 1], y1 = y[i], y2 = y[i + 1];
			if (x1 == x2) for (int j = min(y1, y2); j <= max(y1, y2); j++) getTile(x1, j) = '#';
			else if (y1 == y2) for (int j = min(x1, x2); j <= max(x1, x2); j++) getTile(j, y1) = '#';
		}
	}
	board.push_back(vector<char>(1000, '#'));

	int score = 0;
	while (true)
	{
		int x = 500, y = 0;
		while (true)
		{
			if (getTile(x, y + 1) == ' ') y++;
			else if (getTile(x - 1, y + 1) == ' ') { y++; x--; }
			else if (getTile(x + 1, y + 1) == ' ') { y++; x++; }
			else { score++; getTile(x, y) = 'o'; break; }
		}
		if (getTile(500, 0) == 'o') break;
	}
	cout << score;
	return 0;
}