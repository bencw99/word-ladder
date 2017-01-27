#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <queue>

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
	return (diffCount ==1);
}

// Generate map of string->int passed in by reference from inputFile
void readInputFile(vector<string> &v, string inputFile) {
	ifstream fin(inputFile);
	string s;
	int length = -1;
	int index = 0;
	// Read in words from file
	while (fin >> s) {
		// Find set length of words in file (hopefully)
		if (length < 0) length = s.length();
		// Checks if words deviate from set length
		else if (length != -1 && s.length() != length) cout << "Goddamn it." << endl;
		// Add to needed data structures
		v.push_back(s);
		// Increment
		index++;
	}
}
	
// Generates a word ladder graph from the given dictionary of words
void generateGraph(vector<vector<int> > &graph, const vector<string> &dictionary) {
	int dsize = dictionary.size();
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

// Gets longest shortest path in given graph
tuple<int, int, int > bfs(vector<vector<int > > &graph) {
    int c = 0, first, second, maxx = -1;
    for(int i = 0; i < graph.size(); i++){
        queue<int > q;
        vector<int > distance (graph.size(), 0);
        q.push(i);
	distance[i] = 1;
        while(!q.empty()){
		c++;
		if (!(c % 10000000)) cout << c << " somethings done." << endl;
		int current = q.front(); q.pop();
		if(distance[current] > maxx){
			maxx = distance[current]; first = i; second = current;
		}
		for(int j = 0; j < graph[current].size(); j++){
			if(distance[graph[current][j]] == 0){
				q.push(graph[current][j]);
				distance[graph[current][j]] = distance[current] + 1;
			}
		}
        }
    }
    tuple<int, int, int > WeDidIt(maxx, first, second);
    return WeDidIt;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "More arguments." << endl;
		return 1;
	}
	string s1, s2;
	tuple<int, int, int> tpl;
	int maxLength = 0;
	for (int i = 1; i < argc; i++) {
		vector<vector<int> > g;
		vector<string> v;

		// do the thing
		readInputFile(v, argv[i]);
		cout << "File inputted" << endl;
		generateGraph(g, v);
		cout << "Graph generated" << endl;

		// get the result
		tpl = bfs(g);

		if (get<0>(tpl) > maxLength) {
			maxLength = get<0>(tpl);
			s1 = v[get<1>(tpl)];
			s2 = v[get<2>(tpl)];
		}
	}
	cout << "Max length: " << maxLength << endl;
	cout << "Beginning:" << s1 << endl;
	cout << "Ending: " << s2 << endl;
	return 0;
}
