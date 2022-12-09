#include <iostream>
#include <vector>
using namespace std;

const int n = 10;
int xPos[n];
int yPos[n];
int score = 1;
vector<vector<bool>> visited(10000, vector<bool>(10000, 0));

int sign(int x)
{
	return (x > 0) - (x < 0);
}

bool isTouching(int n)
{
	return abs(xPos[n + 1] - xPos[n]) <= 1 && abs(yPos[n + 1] - yPos[n]) <= 1;
}

void moveIfNotTouching()
{
	for (int i = 0; i < n - 1; i++)
	{
		if (isTouching(i)) return;
		xPos[i + 1] += sign(xPos[i] - xPos[i + 1]);
		yPos[i + 1] += sign(yPos[i] - yPos[i + 1]);
	}
	if (!visited[xPos[n - 1]][yPos[n - 1]])
	{
		visited[xPos[n - 1]][yPos[n - 1]] = 1;
		score++;
	}
}

int main()
{
	fill(xPos, xPos + n, 5000);
	fill(yPos, yPos + n, 5000);
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
					xPos[0]++; break;
				case 'L':
					xPos[0]--; break;
				case 'U':
					yPos[0]--; break;
				case 'D':
					yPos[0]++; break;
			}
			moveIfNotTouching();
		}
	}
	cout << score;
	return 0;
}