#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

vector<string> board;
vector<vector<bool>> visited;
vector<vector<bool>> landed;
vector<vector<int>> pathLength;
vector<vector<int>> parent;
int x, y;
int w, h;
int endX, endY, startX, startY;
bool canGo(int dX, int dY)
{
	if (x + dX < 0 || x + dX >= w || y + dY < 0 || y + dY >= h) return 0;
	if (visited[y + dY][x + dX]) return 0;
	return board[y][x] - board[y + dY][x + dX] <= 1;
}

void printBoard()
{
	vector<string> z(h);
	for (int i = 0; i < h; i++)
	{
		string s = "";
		for (int j = 0; j < w; j++) s += '.';
		z[i] = s;
	}

	int pX = parent[y][x] % w, pY = parent[y][x] / w;
	z[pY][pX] = '#';
	while (pX != endX || pY != endY)
	{
		int c = parent[pY][pX];
		pX = c % w;
		pY = c / w;
		z[pY][pX] = '#';
	}
	z[y][x] = '*';
	for (int i = 0; i < h; i++) cout << z[i] << "\n";
}

int main()
{
	while (!cin.eof())
	{
		string s;
		getline(cin, s);
		w = s.length();
		size_t sPos = s.find('S');
		if (sPos != string::npos)
		{
			s[sPos] = 'a';
		}
		size_t ePos = s.find('E');
		if (ePos != string::npos)
		{
			endX = ePos; endY = board.size();
			x = endX; y = endY;
			s[ePos] = 'z';
		}
		board.push_back(s);
		visited.push_back(vector<bool>(w, 0));
		landed.push_back(vector<bool>(w, 0));
		pathLength.push_back(vector<int>(w, 2147483647));
		parent.push_back(vector<int>(w, 0));
	}
	h = board.size();

	visited[y][x] = 1;
	pathLength[y][x] = 0;

	pair<int, int> d[] = { make_pair(1, 0), make_pair(0, 1), make_pair(-1, 0), make_pair(0, -1) };
	queue<int> BFS;
	BFS.push(x + y * w);
	while (BFS.size() > 0)
	{
		int c = BFS.front();
		BFS.pop();
		x = c % w;
		y = c / w;
		landed[y][x] = 1;
		int dist = pathLength[y][x];
		if (board[y][x] == 'a')
		{
			printBoard();
			cout << "Shortest path: " << dist;
			return 0;
		}
		for (pair<int, int> diff: d)
		{
			int dX = diff.first;
			int dY = diff.second;
			if (!canGo(dX, dY)) continue; 
			BFS.push((x + dX) + (y + dY) * w);
			visited[y + dY][x + dX] = 1;
			pathLength[y + dY][x + dX] = dist + 1;
			parent[y + dY][x + dX] = c;
		}
	}
	return 0;
}