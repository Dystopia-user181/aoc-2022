#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int BOARD_WIDTH = 7;
vector<string> board({ "#######" });
int height = 1;

int pid = 0;
struct PieceType
{
	vector<vector<bool>> geometry;
	int width, height, id;
	PieceType() { id = pid++; }
	PieceType(vector<vector<bool>> g): geometry(g) {
		height = g.size();
		width = 0;
		for (vector<bool> section: g)
		{
			if (section.size() > width) width = section.size();
		}
		id = pid++;
	}
};

vector<PieceType> pieces({
PieceType({
	{1,1,1,1}
}),
PieceType({
	{0,1},
	{1,1,1},
	{0,1}
}),
PieceType({
	{1,1,1},
	{0,0,1},
	{0,0,1}
}),
PieceType({
	{1},
	{1},
	{1},
	{1}
}),
PieceType({
	{1,1},
	{1,1}
})
});

int typesOfPieces = pieces.size();

string windPattern;
int windPatternLength;
int windPatternId = 0;

int pieceId = 0;
PieceType randomPiece;
PieceType& piece = randomPiece;
int x, y;

bool isOverlapping()
{
	for (int i = 0; i < piece.height; i++)
	{
		if (y + i >= height) return 0;
		for (int j = 0; j < piece.geometry[i].size(); j++)
		{
			if (!piece.geometry[i][j]) continue;
			if (board[y + i][x + j] == '#') return 1;
		}
	}
	return 0;
}

//const int WIND_CYCLES = 1;
vector<vector<int>> windCombos; //(typesOfPieces * WIND_CYCLES);
vector<int> heights;
int piecesPlaced = 0;
void placePiece()
{
	piecesPlaced++;
	y = height + 3;
	x = 2;
	piece = pieces[pieceId];
	while (!isOverlapping())
	{
		int dx = windPattern[windPatternId] == '<' ? -1 : 1;
		windPatternId = (windPatternId + 1) % windPatternLength;
		int oldX = x;
		x = min(max(x + dx, 0), BOARD_WIDTH - piece.width);
		if (isOverlapping()) {
			x = oldX;
		}
		y--;
	}
	y++;
	height = max(height, y + piece.height);
	heights.push_back(height);
	while (board.size() < height) board.push_back("       ");

	for (int i = 0; i < piece.height; i++)
	{
		for (int j = 0; j < piece.geometry[i].size(); j++)
		{
			if (piece.geometry[i][j]) board[y + i][x + j] = '#';
		}
	}
	pieceId = (pieceId + 1) % typesOfPieces;
}

bool cmpVector(vector<int>& a, vector<int>& b)
{
	if (a.size() != b.size()) return 0;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != b[i]) return 0;
	}
	return 1;
}

long long haveCycle()
{
	if (windCombos.size() == 0) return -1;
	for (int i = 0; i < windCombos.size() - 1; i++)
	{
		if (cmpVector(windCombos[i], windCombos[windCombos.size() - 1])) return i;
	}
	return -1;
}

int main()
{
	getline(cin, windPattern);
	windPatternLength = windPattern.length();
	vector<int> currentCombo(typesOfPieces, 0);
	while (haveCycle() == -1)
	{
		for (int i = 0; i < typesOfPieces; i++)
		{
			currentCombo[i] = windPatternId;
			placePiece();
		}
		windCombos.push_back(currentCombo);
	}
	long long idx = haveCycle();
	long long cycleLength = (windCombos.size() - 1 - idx) * typesOfPieces;
	long long startCycle = idx * typesOfPieces;
	long long cyclesNo = (1000000000000 - startCycle) / cycleLength;
	long long heightBeforeCycle = heights[startCycle - 1];
	long long heightPerCycle = heights[startCycle - 1 + cycleLength] - heightBeforeCycle;
	long long piecesAfterCycle = 1000000000000 - cyclesNo * cycleLength - startCycle;
	long long heightAfterCycle = heights[startCycle + piecesAfterCycle - 1] - heightBeforeCycle;
	long long realHeight = cyclesNo * heightPerCycle + heightAfterCycle + heightBeforeCycle;
	cout << realHeight - 1;
	return 0;
}