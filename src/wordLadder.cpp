#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <queue>

using namespace std;
// TODO: Everything

// Generate a graph given an input file.
// Graph of format: Map of string -> vector<string>
void generateGraph(map<string*, vector<string*>> &graph, string inputFile) {

}

// Gets longest shortest path from begin in graph
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
	cout << "Hello world" << endl;
}
