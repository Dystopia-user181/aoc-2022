#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	string s;
	vector<int> initial;
	vector<int> posIdx;
	vector<int> outputPos;
	while (!cin.eof())
	{
		getline(cin, s);
		outputPos.push_back(initial.size());
		posIdx.push_back(initial.size());
		initial.push_back(stoi(s));
	}
	int n = initial.size();
	for (int i = 0; i < n; i++)
	{
		int oldPos = outputPos[i];
		int newPos = ((oldPos + initial[i]) % (n - 1) + n - 1) % (n - 1);
		if (newPos == 0) newPos = n - 1;
		if (oldPos < newPos)
		{
			for (int j = oldPos + 1; j <= newPos; j++)
			{
				outputPos[posIdx[j]] = (outputPos[posIdx[j]] - 1 + n) % n;
			}
		}
		else if (oldPos > newPos)
		{
			for (int j = newPos; j < oldPos; j++)
			{
				outputPos[posIdx[j]] = (outputPos[posIdx[j]] + 1) % n;
			}
		}
		outputPos[i] = newPos;
		for (int j = 0; j < n; j++) posIdx[outputPos[j]] = j;
	}
	int val0;
	for (int i = 0; i < n; i++) if (initial[posIdx[i]] == 0) val0 = i;
	cout << initial[posIdx[(val0 + 1000) % n]] + initial[posIdx[(val0 + 2000) % n]] + initial[posIdx[(val0 + 3000) % n]];
	return 0;
}