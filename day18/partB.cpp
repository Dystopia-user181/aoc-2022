#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>
using namespace std;

vector<vector<vector<bool>>> grid(22, vector<vector<bool>>(22, vector<bool>(22, 0)));
bool outOfBounds(int x, int y, int z)
{
	return (x < 0 || x >= 22 || y < 0 || y >= 22 || z < 0 || z >= 22);
}

vector<vector<int>> freedoms({
	{-1, 0, 0},
	{1, 0, 0},
	{0, -1, 0},
	{0, 1, 0},
	{0, 0, -1},
	{0, 0, 1}
});

vector<vector<vector<bool>>> visited(22, vector<vector<bool>>(22, vector<bool>(22, 0)));
void BFS()
{
	queue<int> BFSqueue;
	BFSqueue.push(0);
	visited[0][0][0] = 1;
	while (BFSqueue.size())
	{
		int coord = BFSqueue.front();
		int x = coord / (22 * 22), y = (coord / 22) % 22, z = coord % 22;
		BFSqueue.pop();
		for (vector<int> d: freedoms)
		{
			int px = x + d[0], py = y + d[1], pz = z + d[2];
			if (outOfBounds(px, py, pz)) continue;
			if (!visited[px][py][pz] && !grid[px][py][pz])
			{
				BFSqueue.push(px * 22 * 22 + py * 22 + pz);
				visited[px][py][pz] = 1;
			}
		}
	}
}

int main()
{
	int score = 0;
	while (!cin.eof())
	{
		string s;
		int a, b, c;
		char thr;
		getline(cin, s);
		stringstream ss;
		ss << s;
		ss >> a >> thr >> b >> thr >> c;
		grid[a + 1][b + 1][c + 1] = 1;
	}
	BFS();
	for (int x = 0; x < 22; x++)
	{
		for (int y = 0; y < 22; y++)
		{
			for (int z = 0; z < 22; z++)
			{
				if (!visited[x][y][z]) continue;
				for (vector<int> d: freedoms)
				{
					int px = x + d[0], py = y + d[1], pz = z + d[2];
					if (outOfBounds(px, py, pz)) continue;
					if (grid[px][py][pz]) score++;
				}
			}
		}
	}
	cout << score;
	return 0;
}