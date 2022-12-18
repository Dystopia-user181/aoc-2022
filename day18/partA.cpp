#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

vector<vector<vector<bool>>> grid(20, vector<vector<bool>>(20, vector<bool>(20, 0)));
bool gridVal(int x, int y, int z)
{
	if (x < 0 || x >= 20 || y < 0 || y >= 20 || z < 0 || z >= 20) return 0;
	return grid[x][y][z];
}

int main()
{
	int score = 0;
	while (!cin.eof())
	{
		score += 6;
		string s;
		int a, b, c;
		char thr;
		getline(cin, s);
		stringstream ss;
		ss << s;
		ss >> a >> thr >> b >> thr >> c;
		grid[a][b][c] = 1;
		if (gridVal(a - 1, b, c)) score -= 2;
		if (gridVal(a + 1, b, c)) score -= 2;
		if (gridVal(a, b - 1, c)) score -= 2;
		if (gridVal(a, b + 1, c)) score -= 2;
		if (gridVal(a, b, c - 1)) score -= 2;
		if (gridVal(a, b, c + 1)) score -= 2;
	}
	cout << score;
	return 0;
}