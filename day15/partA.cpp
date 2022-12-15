#include <iostream>
#include <vector>
#include <string>
using namespace std;

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
	int yTest = 2000000;
	int minX = 2147483647, maxX = -2147483648;
	for (Sensor sensor: sensors)
	{
		pair<int, int> a = sensor.disabledAtY(yTest);
		if (a.first > a.second) continue;
		if (a.first < minX) minX = a.first;
		if (a.second > maxX) maxX = a.second;
	}
	vector<bool> board(maxX - minX, 0);
	for (Sensor sensor: sensors)
	{
		pair<int, int> a = sensor.disabledAtY(yTest);
		if (a.first > a.second) continue;
		for (int i = a.first; i < a.second; i++) board[i - minX] = 1;
	}
	for (Sensor sensor: sensors)
	{
		if (sensor.beacon.y == yTest && sensor.beacon.x >= minX && sensor.beacon.x < maxX)
		{
			board[sensor.beacon.x - minX] = 0; 
		}
	}
	int score = 0;
	for (int i = 0; i < maxX - minX; i++) score += board[i];
	cout << score;
	return 0;
}