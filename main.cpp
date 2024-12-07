

#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>
#include <string>

using namespace std;


class Graph {
public:
    unordered_map<string, int> cityIndex;  // City to index mapping
    vector<string> cities;                 // List of cities
    vector<vector<int>> adjMatrix;         // Adjacency matrix for the graph
    vector<vector<pair<string, int>>> adjList; // Adjacency list for the graph

    Graph(vector<string>& cityNames) {
        cities = cityNames;
        adjMatrix.resize(cities.size(), vector<int>(cities.size(), INT_MAX));
        adjList.resize(cities.size());

        // Map city names to indices
        for (int i = 0; i < cities.size(); i++) {
            cityIndex[cities[i]] = i;
        }
    }

    // Add an edge to the adjacency list and matrix
    void addEdge(const string& city1, const string& city2, int weight) {
        int index1 = cityIndex[city1];
        int index2 = cityIndex[city2];

        adjMatrix[index1][index2] = weight;
        adjMatrix[index2][index1] = weight;

        adjList[index1].push_back({city2, weight});
        adjList[index2].push_back({city1, weight});
    }

    // Display the adjacency matrix
    void displayAdjMatrix() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < cities.size(); i++) {
            for (int j = 0; j < cities.size(); j++) {
                if (adjMatrix[i][j] == INT_MAX) {
                    cout << "INF ";
                } else {
                    cout << adjMatrix[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    // Display the adjacency list
    void displayAdjList() {
        cout << "Adjacency List:\n";
        for (int i = 0; i < cities.size(); i++) {
            cout << cities[i] << " connects to: ";
            for (auto& neighbor : adjList[i]) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }

    // Dijkstra's Algorithm to find the shortest path
    void dijkstra(const string& start) {
        int startIndex = cityIndex[start];
        vector<int> dist(cities.size(), INT_MAX);
        vector<int> prev(cities.size(), -1);
        vector<bool> visited(cities.size(), false);

        dist[startIndex] = 0;

        for (int i = 0; i < cities.size(); i++) {
            int u = -1;
            for (int j = 0; j < cities.size(); j++) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            if (dist[u] == INT_MAX) break; // No more reachable nodes

            visited[u] = true;

            for (int v = 0; v < cities.size(); v++) {
                if (adjMatrix[u][v] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    prev[v] = u;
                }
            }
        }

        // Display the shortest path from the start city
        cout << "\nShortest Paths from " << start << ":\n";
        for (int i = 0; i < cities.size(); i++) {
            if (dist[i] == INT_MAX) {
                cout << cities[i] << ": No path\n";
            } else {
                cout << cities[i] << ": " << dist[i] << " (Path: ";
                printPath(prev, i);
                cout << ")\n";
            }
        }
    }

    // Function to print the path from source to destination
    void printPath(vector<int>& prev, int index) {
        if (index == -1) return;
        printPath(prev, prev[index]);
        cout << cities[index] << " ";
    }

    // Find the low-cost trip (minimum weight edge)
    void findLowCostTrip() {
        int minCost = INT_MAX;
        string start, end;
        for (int i = 0; i < cities.size(); i++) {
            for (int j = 0; j < cities.size(); j++) {
                if (adjMatrix[i][j] < minCost && adjMatrix[i][j] != INT_MAX) {
                    minCost = adjMatrix[i][j];
                    start = cities[i];
                    end = cities[j];
                }
            }
        }
        cout << "\nLow-cost Trip: " << start << " -> " << end << " with cost: " << minCost << endl;
    }
};

int main() {
    // Define the cities
    vector<string> cities = {"Riverside", "Paris", "Hemet", "Moreno Valley"};
    
    // Create the graph
    Graph g(cities);

    // these are all the edages
    g.addEdge("Riverside", "Paris", 24);
    g.addEdge("Riverside", "Hemet", 33);
    g.addEdge("Riverside", "Moreno Valley", 16);
    g.addEdge("Paris", "Hemet", 30);
    g.addEdge("Paris", "Moreno Valley", 18);
    g.addEdge("Hemet", "Moreno Valley", 26);

    // Display the adjacency matrix and list
    g.displayAdjMatrix();
    g.displayAdjList();

    // Find the shortest paths using Dijkstra's algorithm from Riverside
    g.dijkstra("Riverside");

    // Find the low-cost trip
    g.findLowCostTrip();

    return 0;
}




















