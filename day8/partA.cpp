#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int score = 0;
	string s;
	vector<vector<int>> trees;
	vector<vector<bool>> visible;
	int w, h = 0;
	while (!cin.eof()) {
		getline(cin, s);
		w = s.length();
		trees.push_back(vector<int>(w));
		visible.push_back(vector<bool>(w));
		for (int i = 0; i < w; i++) {
			trees[h][i] = s[i] - '0';
			visible[h][i] = 0;
		}
		h++;
	}
	for (int i = 0; i < h; i++) {
		int highestLeft = -1;
		int highestRight = -1;
		for (int j = 0; j < w; j++) {
			if (trees[i][j] > highestLeft) {
				visible[i][j] = 1;
				highestLeft = trees[i][j];
			}
			if (trees[i][w - j - 1] > highestRight) {
				visible[i][w - j - 1] = 1;
				highestRight = trees[i][w - j - 1];
			}
			if (highestLeft == 9 && highestRight == 9) break;
		}
	}
	for (int i = 0; i < w; i++) {
		int highestTop = -1;
		int highestBottom = -1;
		for (int j = 0; j < h; j++) {
			if (trees[j][i] > highestTop) {
				visible[j][i] = 1;
				highestTop = trees[j][i];
			}
			if (trees[h - j - 1][i] > highestBottom) {
				visible[h - j - 1][i] = 1;
				highestBottom = trees[h - j - 1][i];
			}
			if (highestTop == 9 && highestBottom == 9) break;
		}
	}
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			if (visible[i][j]) score++;
	cout << score;
	return 0;
}