#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <tuple>

using namespace std;

// Generate map of string->int and int->string passed in by reference
void readInputFile(map<string, int> &si, string inputFile) {
	ifstream fin(inputFile);
	string s;
	int length = -1;
	int index = 0;
	while (fin >> s) {
		if (s.length() < 0) length = s.length();
		else if (s.length() != length) cout << "Goddamn it." << endl;
		si[s] = index;
		index++;
	}
}
	
// Generate a graph given an input file.
// Graph of format: Map of string -> vector<string>
void generateGraph(map<int, vector<int>> &graph, string inputFile) {

}

// Gets longest shortest path from begin in graph
int bfs(map<int, vector<int>> &graph, int begin) {

}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "More arguments." << endl;
		return 1;
	}
	int maxLength = 0;
	string s1, s2;
	tuple<int, int, int> tpl;
	for (int i = 2; i < argc; i++) {
		map<string, int> si;
		map<int, vector<int>> g;
		vector<string> v;

		// do the thing
		readInputFile(si, v, argv[i]);
		generateGraph(g, si);
		// get the result
		tpl = bfs(g);
	}
	cout << "Max length: " << get<0>(tpl) << endl;
	cout << "Beginning :" << v[get<1>(tpl)] << endl;
	cout << "Ending: " << v[get<2>(tpl)] << endl;
	return 0;
}
