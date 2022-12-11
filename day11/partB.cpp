#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct Monkey {
	unsigned long long op1, op2;
	char op;
	int divBy;
	int monkeyTrue, monkeyFalse;
	int score = 0;

	unsigned long long doOp(unsigned long long num) {
		if (op == '+') return (op1 ? op1 : num) + (op2 ? op2 : num);
		return (unsigned long long)(op1 ? op1 : num) * (unsigned long long)(op2 ? op2 : num);
	}
};

vector<vector<unsigned long long>> monkeyItems;
vector<Monkey> monkeys;

int main()
{
	unsigned long long lcm = 1;
	string s;
	int n = 0;
	while (!cin.eof()) {
		monkeyItems.push_back(vector<unsigned long long>());
		monkeys.push_back(Monkey());
		// Get rid of "Monkey x" line
		getline(cin, s);

		// Get rid of "Starting items:"
		cin >> s >> s;
		getline(cin, s);
		stringstream ss;
		ss << s;
		char x = ',';
		while (x == ',') {
			x = '.';
			int a; ss >> a >> x; monkeyItems[n].push_back(a);
		}

		// Get rid of "Operation: new = "
		cin >> s >> s >> s;
		cin >> s;
		if (s == "old") monkeys[n].op1 = 0; else monkeys[n].op1 = stoi(s);
		cin >> monkeys[n].op;
		cin >> s;
		if (s == "old") monkeys[n].op2 = 0; else monkeys[n].op2 = stoi(s);

		// Get rid of "Test: divisible by "
		cin >> s >> s >> s;
		cin >> monkeys[n].divBy;
		lcm *= monkeys[n].divBy;
		// Get rid of "If true: throw to monkey "
		cin >> s >> s >> s >> s >> s >> monkeys[n].monkeyTrue;
		// Get rid of "If false: throw to monkey "
		cin >> s >> s >> s >> s >> s >> monkeys[n].monkeyFalse;

		n++;
		getline(cin, s);
		if (cin.eof()) break;
		getline(cin, s);
	}
	for (int i = 0; i < 10000; i++) {
		for (int j = 0; j < n; j++) {
			for (unsigned long long x : monkeyItems[j])
			{
				monkeys[j].score++;
				unsigned long long result = monkeys[j].doOp(x) % lcm;
				if (result % monkeys[j].divBy) monkeyItems[monkeys[j].monkeyFalse].push_back(result);
				else monkeyItems[monkeys[j].monkeyTrue].push_back(result);
			}
			monkeyItems[j] = vector<unsigned long long>();
		}
	}
	for (int j = 0; j < n; j++) cout << monkeys[j].score << "\n";
	return 0;
}