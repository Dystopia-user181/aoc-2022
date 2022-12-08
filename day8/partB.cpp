#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int score = 0;
	string s;
	vector<vector<int>> trees;
	int w, h = 0;
	while (!cin.eof()) {
		getline(cin, s);
		w = s.length();
		trees.push_back(vector<int>(w));
		for (int i = 0; i < w; i++) {
			trees[h][i] = s[i] - '0';
		}
		h++;
	}
	for (int i = 1; i < h - 1; i++)
		for (int j = 1; j < w - 1; j++) {
			int height = trees[i][j];
			int dirN = 1, dirE = 1, dirS = 1, dirW = 1;
			while (i - dirN > 0 && trees[i - dirN][j] < height) dirN++;
			while (j + dirE < w - 1 && trees[i][j + dirE] < height) dirE++;
			while (i + dirS < h - 1 && trees[i + dirS][j] < height) dirS++;
			while (j - dirW > 0 && trees[i][j - dirW] < height) dirW++;
			if (dirN * dirE * dirS * dirW > score) score = dirN * dirE * dirS * dirW;
		}
	cout << score;
	return 0;
}