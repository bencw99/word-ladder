#include <iostream>
#include <string>
#include <vector>
#include <map>
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
	if(diffCount == 1) {
		return true;
	}
	else {
		return false;
	}
}

// Generate map of string->int passed in by reference from inputFile
void readInputFile(map<string, int> &si, vector<string> &v, string inputFile) {
	ifstream fin(inputFile);
	string s;
	int length = -1;
	int index = 0;
	while (fin >> s) {
		if (length < 0) length = s.length();
		else if (s.length() != length) cout << "Goddamn it." << endl;
		si[s] = index;
		index++;
	}
}
	
// Generates a word ladder graph from the given dictionary of words
void generateGraph(vector<vector<int> > &graph, map<string, int> &dictionaryMap, const vector<string> &dictionary) {
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

// Gets longest shortest path in given graph
tuple<int, int, int > bfs(vector<vector<int > > &graph) {
    int c = 0, first, second, maxx = -1;
    for(int i = 0; i < graph.size(); i++){
        queue<int > q;
        vector<int > distance (graph.size(), 0);
        q.push(i);
        while(!q.empty()){
            int current = q.front(); q.pop();
            c++;
            for(int j = 0; j < graph[current].size(); j++){
                if(distance[graph[current][j]] == 0){
                    q.push(graph[current][j]);
                    distance[graph[current][j]] = c;
                    if(c > maxx){
                        maxx = c; first = i; second = graph[current][j];
                    }
                }
            }
        }
    }
    tuple<int, int, int > WeDidIt(c, first, second);
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
	for (int i = 2; i < argc; i++) {
		map<string, int> si;
		vector<vector<int> > g;
		vector<string> v;

		// do the thing
		readInputFile(si, v, argv[i]);
		generateGraph(g, si, v);
		// get the result
		tpl = bfs(g);
		if (maxLength < get<0>(tpl)) {
			s1 = v[get<1>(tpl)];
			s2 = v[get<2>(tpl)];
			maxLength = get<0>(tpl);
		}
	}
	cout << "Max length: " << get<0>(tpl) << endl;
	cout << "Beginning:" << s1 << endl;
	cout << "Ending: " << s2 << endl;
	return 0;
}
