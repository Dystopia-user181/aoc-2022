#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool hasOverlap(int a1, int b1, int a2, int b2)
{
	return (a1 <= b2 && b1 >= a2) || (a2 <= b1 && b2 >= a1);
}

struct Pos {
	int x, y;
	Pos(int xi, int yi) : x(xi), y(yi) {}
	Pos() : x(), y() {}
	int dist(Pos pos2)
	{
		return abs(x - pos2.x) + abs(y - pos2.y);
	}
};

struct Sensor: Pos
{
	Pos beacon;
	Sensor(int xi, int yi, int xb, int yb): Pos(xi, yi), beacon(Pos(xb, yb)) {}
	pair<int, int> disabledAtY(int yLevel)
	{
		int distance = dist(beacon) - abs(y - yLevel);
		return make_pair(x - distance, x + distance + 1);
	}
};

vector<Sensor> sensors;
int main()
{
	string thrS;
	char thrC;
	cin >> thrS;
	while (!cin.eof())
	{
		int xS, yS, xC, yC;
		//     at      x       =       ?x    ,       y       =       ?y?   :
		cin >> thrS >> thrC >> thrC >> xS >> thrC >> thrC >> thrC >> yS >> thrC;
		//   closest  beacon   is     at       x       =       ?x?   ,       y       =       ?y?   Sensor
		cin >> thrS >> thrS >> thrS >> thrS >> thrC >> thrC >> xC >> thrC >> thrC >> thrC >> yC >> thrS;
		sensors.push_back(Sensor(xS, yS, xC, yC));
	}
	int area = 4000000;
	for (int i = 0; i <= area; i++)
	{
		vector<pair<int, int>> board;
		for (Sensor sensor: sensors)
		{
			pair<int, int> a = sensor.disabledAtY(i);
			// cout << sensor.x << " " << sensor.y << " | " << a.first << " " << a.second << "\n";
			if (a.first > a.second) continue;
			for (int j = 0; j < board.size(); j++)
			{
				while (j < board.size() && hasOverlap(a.first, a.second, board[j].first, board[j].second))
				{
					a.first = min(a.first, board[j].first);
					a.second = max(a.second, board[j].second);
					board.erase(board.begin() + j);
				}
			}
			board.push_back(a);
		}
		if (board.size() >= 2)
		{
			cout << i + (unsigned long long)min(board[0].second, board[1].second) * 4000000;
			return 0;
		}
	}
	cout << "No solution";
	return 0;
}