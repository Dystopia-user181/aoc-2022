#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
using namespace std;

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
		//	Valve   X     has flow   r  a  t  e  =   <flowrate>   ;
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
int totalCalls = 0;
int bestPressure = 0;
void getBestPressure(
	int currPressure = 0,
	int current = START_NODE_ID,
	int minutesLeft = MINUTES_LEFT
)
{
	if (minutesLeft < 0)
	{
		if (currPressure > bestPressure) bestPressure = currPressure;
		return;
	}
	int newPressure = currPressure + minutesLeft * endGraph[current].flowRate;
	totalCalls++;
	visited[current] = 1;
	for (auto connection: endGraph[current].neighbours)
	{
		if (visited[connection.id]) continue;
		getBestPressure(newPressure, connection.id, minutesLeft - connection.weight);
	}
	visited[current] = 0;
	if (newPressure > bestPressure) bestPressure = newPressure;
}

int main()
{
	getInput();
	translateGraph();
	getBestPressure();
	cout << bestPressure << "\nIterations ran: " << totalCalls;
	return 0;
}