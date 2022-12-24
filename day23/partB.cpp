#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> board;
vector<vector<int>> preferredNum;
vector<vector<int>> dx;
vector<vector<int>> dy;
// vector<vector<int>> prefers;
char& tile(int x, int y)
{
	return board[y][x];
}
string cardinals(int x, int y)
{
	return string(1, tile(x, y - 1)) + string(1, tile(x + 1, y - 1)) + string(1, tile(x + 1, y)) + string(1, tile(x + 1, y + 1)) +
		string(1, tile(x, y + 1)) + string(1, tile(x - 1, y + 1)) + string(1, tile(x - 1, y)) + string(1, tile(x - 1, y - 1));
}
int w, h = 2000;
int main()
{
	string s;
	while (!cin.eof())
	{
		getline(cin, s);
		s = string(1000, '.') + s + string(1000, '.');
		w = s.length();
		board.push_back(s);
		h++;
	}
	for (int i = 0; i < 1000; i++)
	{
		board.push_back(string(w, '.'));
		board.insert(board.begin(), string(w, '.'));
	}
	int k = 0;
	while (true)
	{
		preferredNum = vector<vector<int>>(w, vector<int>(h, 0));
		dx = vector<vector<int>>(w, vector<int>(h, 0));
		dy = vector<vector<int>>(w, vector<int>(h, 0));
		for (int i = 1; i < w - 1; i++)
		{
			for (int j = 1; j < h - 1; j++)
			{
				if (tile(i, j) == '.') continue;
				s = cardinals(i, j);
				if (s == "........") continue;
				bool N = s[0] == '.', NE = s[1] == '.', E = s[2] == '.', SE = s[3] == '.', S = s[4] == '.', SW = s[5] == '.',
					W = s[6] == '.', NW = s[7] == '.';
				switch (k % 4)
				{
					case 0:
						if (NW && N && NE) dy[i][j] = -1;
						else if (SE && S && SW) dy[i][j] = 1;
						else if (SW && W && NW) dx[i][j] = -1;
						else if (NE && E && SE) dx[i][j] = 1;
						break;
					case 1:
						if (SE && S && SW) dy[i][j] = 1;
						else if (SW && W && NW) dx[i][j] = -1;
						else if (NE && E && SE) dx[i][j] = 1;
						else if (NW && N && NE) dy[i][j] = -1;
						break;
					case 2:
						if (SW && W && NW) dx[i][j] = -1;
						else if (NE && E && SE) dx[i][j] = 1;
						else if (NW && N && NE) dy[i][j] = -1;
						else if (SE && S && SW) dy[i][j] = 1;
						break;
					case 3:
						if (NE && E && SE) dx[i][j] = 1;
						else if (NW && N && NE) dy[i][j] = -1;
						else if (SE && S && SW) dy[i][j] = 1;
						else if (SW && W && NW) dx[i][j] = -1;
						break;
				}
				if (dx[i][j] != 0 || dy[i][j] != 0) preferredNum[i + dx[i][j]][j + dy[i][j]]++;
			}
		}
		bool hasMoved = 0;
		for (int i = 1; i < w - 1; i++)
		{
			for (int j = 1; j < h - 1; j++)
			{
				if (dx[i][j] == 0 && dy[i][j] == 0) continue;
				if (preferredNum[i + dx[i][j]][j + dy[i][j]] >= 2) continue;
				tile(i, j) = '.';
				tile(i + dx[i][j], j + dy[i][j]) = '#';
				hasMoved = 1;
			}
		}
		k++;
		if (!hasMoved) break;
	}
	cout << k;
	return 0;
}