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

int main()
{
	getline(cin, windPattern);
	windPatternLength = windPattern.length();
	for (int i = 0; i < 2022; i++) placePiece();
	cout << height - 1;
	return 0;
}