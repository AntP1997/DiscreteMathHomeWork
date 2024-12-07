#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

// Graph class
class Graph {
public:
    // Map to store the graph: city -> list of (neighbor, weight)
    unordered_map<string, vector<pair<string, int>>> adjList;

    // Function to add edges to the graph
    void addEdge(const string& city1, const string& city2, int weight) {
        adjList[city1].push_back({city2, weight});
        adjList[city2].push_back({city1, weight}); // Since it's an undirected graph
    }

    // Function to display the graph
    void displayGraph() {
        for (auto& city : adjList) {
            cout << city.first << " connects to: ";
            for (auto& neighbor : city.second) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    // Create the graph
    Graph g;

    // Add the edges based on the description
    g.addEdge("Paris", "Riverside", 24);  // Paris to Riverside with weight 24
    g.addEdge("Paris", "Hamet", 30);      // Paris to Hamet with weight 30
    g.addEdge("Riverside", "Hamet", 33);  // Riverside to Hamet with weight 33
    g.addEdge("Moreno Valley", "Paris", 18); // Moreno Valley to Paris with weight 18
    g.addEdge("Moreno Valley", "Hamet", 26); // Moreno Valley to Hamet with weight 26
    g.addEdge("Moreno Valley", "Riverside", 16); // Moreno Valley to Riverside with weight 16

    // Display the graph
    g.displayGraph();

    return 0;
}
