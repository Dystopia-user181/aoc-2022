#include <iostream>
#include <vector>
using namespace std;

int tx = 5000, ty = 5000, hx = 5000, hy = 5000;
int score = 1;
vector<vector<bool>> visited(10000, vector<bool>(10000, 0));

int sign(int x)
{
	return (x > 0) - (x < 0);
}

bool isTouching()
{
	return abs(tx - hx) <= 1 && abs(ty - hy) <= 1;
}

void moveIfNotTouching()
{
	if (isTouching()) return;
	tx += sign(hx - tx);
	ty += sign(hy - ty);
	if (!visited[tx][ty])
	{
		visited[tx][ty] = 1;
		score++;
	}
}

int main()
{
	visited[5000][5000] = 1;
	while (!cin.eof())
	{
		char dir = '.';
		int m;
		cin >> dir >> m;
		if (dir == '.') break;
		for (int i = 0; i < m; i++)
		{
			switch (dir)
			{
				case 'R':
					hx++; break;
				case 'L':
					hx--; break;
				case 'U':
					hy--; break;
				case 'D':
					hy++; break;
			}
			moveIfNotTouching();
		}
	}
	cout << score;
	return 0;
}