#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
using namespace std;

const int TRAINING_TIME = 4;
const int MINUTES_LEFT = 30;
const int TRAVEL_TIME = 1;
const int OPEN_TIME = 1;
const string START_NODE = "AA";

int valveId(string s)
{
	return (s[0] - 'A') * 26 + s[1] - 'A';
}
int valveId(char c1, char c2)
{
	return (c1 - 'A') * 26 + c2 - 'A';
}

int START_NODE_ID = valveId(START_NODE);
int MAX_ID = valveId("ZZ");

unsigned long boolVectorToKey(vector<bool> v)
{
	unsigned long a = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i]) a += 1 << i;
	}
	return a;
}

struct Node
{
	int flowRate;
	vector<int> neighbours;
	int dist;
	Node() {}
	Node(int f): flowRate(f) {}
	void addNeighbour(int n)
	{
		neighbours.push_back(n);
	}
	void addNeighbour(string n)
	{
		addNeighbour(valveId(n));
	}
	void addNeighbour(char c1, char c2)
	{
		addNeighbour(valveId(c1, c2));
	}
};

vector<Node> graph(MAX_ID + 1, Node());

vector<int> usefulValves = { START_NODE_ID };
int usefulValvesSize;

void getInput()
{
	char C;
	string S;
	while (!cin.eof())
	{
		stringstream ss;
		getline(cin, S);
		ss << S;
		string valve;
		int flowRate;
		//	Valve X	   has flow r  a  t  e  =   <flowrate>   ;
		ss >> S >> valve >> S >> S >>C>>C>>C>>C>>C >> flowRate >> C;
		Node newNode(flowRate);
		// Tunnels lead to valves
		ss >> S >> S >> S >> S;
		char c1, c2;
		while (!ss.eof())
		{
			ss >> c1 >> c2 >> C;
			newNode.addNeighbour(c1, c2);
		}
		if (flowRate > 0) usefulValves.push_back(valveId(valve));
		graph[valveId(valve)] = newNode;
	}
	usefulValvesSize = usefulValves.size();
}

int BFS(int current, int target)
{
	vector<bool> visited(MAX_ID + 1, 0);
	queue<int> BFSqueue;
	BFSqueue.push(current);
	visited[current] = 1;
	graph[current].dist = 0;
	while (true)
	{
		Node newNode = graph[BFSqueue.front()];
		BFSqueue.pop();
		for (int neighbour: newNode.neighbours)
		{
			if (!visited[neighbour])
			{
				if (neighbour == target) return newNode.dist + 1;
				BFSqueue.push(neighbour);
				visited[neighbour] = 1;
				graph[neighbour].dist = newNode.dist + 1;
			}
		}
	}
}

struct WeightedConnection
{
	int id, weight;
	WeightedConnection() {}
	WeightedConnection(int i, int w): id(i), weight(w) {}
};

struct WeightedNode: Node
{
	int flowRate;
	vector<WeightedConnection> neighbours;
	WeightedNode() {}
	WeightedNode(int f): flowRate(f) {}
	void addNeighbour(int i, int w)
	{
		neighbours.push_back(WeightedConnection(i, w));
	}
};
vector<WeightedNode> endGraph(MAX_ID + 1);

void translateGraph()
{
	for (int valve: usefulValves) endGraph[valve] = WeightedNode(graph[valve].flowRate);
	for (int i = 0; i < usefulValves.size(); i++)
	{
		int current = usefulValves[i];
		for (int j = i + 1; j < usefulValves.size(); j++)
		{
			int destination = usefulValves[j];
			int dist = BFS(current, destination) * TRAVEL_TIME + OPEN_TIME;
			endGraph[current].addNeighbour(destination, dist);
			endGraph[destination].addNeighbour(current, dist);
		}
	}
}

vector<bool> visited(MAX_ID + 1, 0);

unsigned long getKeyFromVisited()
{
	unsigned long k = 0;
	for (int i = 1; i < usefulValvesSize; i++)
	{
		if (visited[usefulValves[i]]) k += 1 << (i - 1);
	}
	return k;
}

vector<int> pressures;
int totalCalls = 0;
void DFSForPressure(
	int currPressure = 0,
	int current = START_NODE_ID,
	int minutesLeft = MINUTES_LEFT - TRAINING_TIME
)
{
	visited[current] = 1;
	int key = getKeyFromVisited();
	int newPressure = currPressure + max(minutesLeft, 0) * endGraph[current].flowRate;
	if (newPressure > pressures[key]) pressures[key] = newPressure;
	totalCalls++;
	if (minutesLeft >= 0)
	{
		for (auto connection: endGraph[current].neighbours)
		{
			if (visited[connection.id]) continue;
			DFSForPressure(newPressure, connection.id, minutesLeft - connection.weight);
		}
	}
	visited[current] = 0;
}

int genPressureForVectorBoolSubsets(
	vector<bool> vecBool = vector<bool>(usefulValvesSize - 1, 1),
	int idx = 0
)
{
	if (idx >= usefulValvesSize - 1) return 0;
	unsigned long key = boolVectorToKey(vecBool);
	if (pressures[key]) return pressures[key];
	auto type1 = vecBool;
	auto type2 = vecBool;
	type2[idx] = 0;
	int pressure1 = genPressureForVectorBoolSubsets(type1, idx + 1);
	int pressure2 = genPressureForVectorBoolSubsets(type2, idx + 1);
	pressures[key] = max(pressure1, pressure2);
	return pressures[key];
}

vector<vector<bool>> combos = vector<vector<bool>>({{}});
vector<bool> invertBoolVector(vector<bool>& input)
{
	int n = input.size();
	vector<bool> output(n);
	for (int i = 0; i < n; i++)
	{
		output[i] = !input[i];
	}
	return output;
}
void genCombosVector()
{
	for (int k = 0; k < usefulValvesSize - 1; k++)
	{
		int comboSize = combos.size();
		for (int i = 0; i < comboSize; i++)
		{
			combos.push_back(vector<bool>(combos[i]));
			combos[i].push_back(0);
			combos[i + comboSize].push_back(1);
		}
	}
}

int getMaxPressure()
{
	genPressureForVectorBoolSubsets();
	int maxPressure = 0;
	for (auto i: combos)
	{
		int pressure = pressures[boolVectorToKey(i)] + pressures[boolVectorToKey(invertBoolVector(i))];
		if (pressure > maxPressure) maxPressure = pressure;
	}
	return maxPressure;
}

int main()
{
	getInput();
	translateGraph();
	pressures = vector<int>(1 << (usefulValvesSize - 1), 0);
	genCombosVector();
	DFSForPressure();
	cout << getMaxPressure() << "\nIterations ran: " << totalCalls << "\n";
	return 0;
}