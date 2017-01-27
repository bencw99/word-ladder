#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Checks if the two given words are neighbors
bool areNeighbors(const string &start, const string &finish) {
	int diffCount = 0;
	for(int i = 0; i < start.size(); i ++) {
		if(start[i] != finish[i]) {
			diffCount ++;
		}
		if(diffCount > 1) {
			return false;
		}
	}
	if(diffCount == 1) {
		return true;
	}
	else {
		return false;
	}
}

// Generates a word ladder graph from the given dictionary of words
void generateGraph(vector<vector<int>> &graph, map<string, int> &dictionaryMap, const vector<string> &dictionary) {
	for(int i = 0; i < dictionary.size(); i ++) {
		dictionaryMap[dictionary[i]] = i;
	}
	graph.resize(dictionary.size(), vector<int>());
	for(int i = 0; i < dictionary.size(); i ++) {
		for(int j = i; j < dictionary.size(); j ++) {
			if(areNeighbors(dictionary[i], dictionary[j])) {
				graph[i].push_back(j);
				graph[j].push_back(i);
			}
		}
	}
}

// Gets longest shortest path from begin in graph
int bfs(map<string*, vector<string*>> &graph, string* begin) {
}

int main(int argc, char* argv[]) {
	cout << "Hello world" << endl;
}
