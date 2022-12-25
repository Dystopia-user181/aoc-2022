#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int w, h = 0;
int cycles = 0;

struct Blizzard
{
	int x, y;
	char facing;
	Blizzard() {}
	Blizzard(int X, int Y, char Facing): x(X), y(Y), facing(Facing) {}
	int realX()
	{
		switch (facing)
		{
			case '<': return ((x - cycles - 1) % (w - 2) + w - 2) % (w - 2) + 1;
			case '>': return (x + cycles - 1) % (w - 2) + 1;
		}
		return x;
	}
	int realY()
	{
		switch (facing)
		{
			case '^': return ((y - cycles - 1) % (h - 2) + h - 2) % (h - 2) + 1;
			case 'v': return (y + cycles - 1) % (h - 2) + 1;
		}
		return y;
	}
};
vector<Blizzard> blizzards;

bool isOccupied(int x, int y)
{
	if (x == 0 || x == w - 1) return true;
	if ((y == 0 && x != 1) || (y == h - 1 && x != w - 2)) return true;
	for (auto blizzard: blizzards)
	{
		if (blizzard.realX() == x && blizzard.realY() == y) return true;
	}
	return false;
}

vector<bool> targets(h * w, 0);
int BFS(int start, int end)
{
	targets = vector<bool>(h * w, 0);
	targets[start] = 1;
	while (true)
	{
		cycles++;
		vector<bool> canGo(h * w, 1);
		for (auto blizzard: blizzards)
		{
			canGo[blizzard.realY() * w + blizzard.realX()] = 0;
		}
		for (int i = 0; i < h; i++)
		{
			canGo[i * w] = 0;
			canGo[(i + 1) * w - 1] = 0;
		}
		for (int i = 0; i < w; i++)
		{
			if (i != 1) canGo[i] = 0;
			if (i != w - 2) canGo[i + (h - 1) * w] = 0;
		}
		vector<bool> newTargets(h * w, 0);
		for (int i = 0; i < h * w; i++)
		{
			if (!targets[i]) continue;
			int x = i % w, y = i / w;
			if (canGo[i]) newTargets[i] = 1;
			if (x > 0 && canGo[i - 1]) newTargets[i - 1] = 1;
			if (x <= w - 1 && canGo[i + 1]) newTargets[i + 1] = 1;
			if (y > 0 && canGo[i - w]) newTargets[i - w] = 1;
			if (y <= h - 1 && canGo[i + w]) newTargets[i + w] = 1;
		}
		targets = newTargets;
		if (newTargets[end])
		{
			break;
		}
	}
	return cycles;
}

int main()
{
	while (!cin.eof())
	{
		string s;
		getline(cin, s);
		w = s.length();
		for (int i = 0; i < w; i++)
		{
			if (s[i] != '.' && s[i] != '#') blizzards.push_back(Blizzard(i, h, s[i]));
		}
		h++;
	}
	BFS(1, h * w - 2);
	BFS(h * w - 2, 1);
	BFS(1, h * w - 2);
	cout << cycles;
	return 0;
}