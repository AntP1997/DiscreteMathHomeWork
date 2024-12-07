#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>
#include <string>

using namespace std;

// This is the Graph class. It holds information about the cities and how they are connected.
class Graph {
public:
    unordered_map<string, int> cityIndex;  // This maps city names to numbers (index)
    vector<string> cities;                 // List of cities
    vector<vector<int>> adjMatrix;         // Matrix to hold travel costs between cities
    vector<vector<pair<string, int>>> adjList; // List to hold city connections with costs
    
    // Constructor to initialize the graph with city names
    Graph(vector<string>& cityNames) {
        cities = cityNames;  // Store city names
        adjMatrix.resize(cities.size(), vector<int>(cities.size(), INT_MAX)); // Create a matrix with 'INF' to start (no path between cities)
        adjList.resize(cities.size()); // Create an empty adjacency list for each city

        // Create a map from city names to numbers
        for (int i = 0; i < cities.size(); i++) {
            cityIndex[cities[i]] = i;
        }
    }

    // Function to add an edge between two cities with a certain travel cost
    void addEdge(const string& city1, const string& city2, int weight) {
        int index1 = cityIndex[city1];  // Get the index for the first city
        int index2 = cityIndex[city2];  // Get the index for the second city

        adjMatrix[index1][index2] = weight;  // Set the travel cost in the matrix for city1 to city2
        adjMatrix[index2][index1] = weight;  // Since the road is two-way, set the reverse too

        adjList[index1].push_back({city2, weight});  // Add the second city to city1's list
        adjList[index2].push_back({city1, weight});  // Add the first city to city2's list
    }

    // Function to display the adjacency matrix (shows how cities are connected with costs)
    void displayAdjMatrix() {
        cout << "Adjacency Matrix:\n";  // Print a title
        for (int i = 0; i < cities.size(); i++) {
            for (int j = 0; j < cities.size(); j++) {
                if (adjMatrix[i][j] == INT_MAX) {  // If there's no path, show "INF"
                    cout << "INF ";  // No connection
                } else {
                    cout << adjMatrix[i][j] << " ";  // Show the travel cost between cities
                }
            }
            cout << endl;  // New line after each row
        }
    }

    // Function to display the adjacency list (shows all connected cities for each city)
    void displayAdjList() {
        cout << "Adjacency List:\n";  // Print a title
        for (int i = 0; i < cities.size(); i++) {
            cout << cities[i] << " connects to: ";  // Print the current city
            for (auto& neighbor : adjList[i]) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";  // Print each neighbor and the cost to get there
            }
            cout << endl;  // New line after each city
        }
    }

    // Function to find the shortest path from the starting city using Dijkstra's algorithm
    void dijkstra(const string& start) {
        int startIndex = cityIndex[start];  // Get the index of the starting city
        vector<int> dist(cities.size(), INT_MAX);  // Set initial distances to "INF"
        vector<int> prev(cities.size(), -1);  // Array to keep track of the path
        vector<bool> visited(cities.size(), false);  // To mark cities we've already visited

        dist[startIndex] = 0;  // The starting city has a distance of 0

        for (int i = 0; i < cities.size(); i++) {
            int u = -1;
            for (int j = 0; j < cities.size(); j++) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;  // Find the city with the shortest distance that hasn't been visited yet
                }
            }

            if (dist[u] == INT_MAX) break; // If there's no more reachable cities, stop

            visited[u] = true;  // Mark the current city as visited

            // Update the distances to neighboring cities
            for (int v = 0; v < cities.size(); v++) {
                if (adjMatrix[u][v] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];  // Update the shortest distance to city v
                    prev[v] = u;  // Set the previous city on the path to v
                }
            }
        }

        // Print the shortest path for each city from the start city
        cout << "\nShortest Paths from " << start << ":\n";
        for (int i = 0; i < cities.size(); i++) {
            if (dist[i] == INT_MAX) {
                cout << cities[i] << ": No path\n";  // If no path exists, print "No path"
            } else {
                cout << cities[i] << ": " << dist[i] << " (Path: ";
                printPath(prev, i);  // Call the function to print the path
                cout << ")\n";
            }
        }
    }

    // Function to print the path from the start city to a destination city
    void printPath(vector<int>& prev, int index) {
        if (index == -1) return;  // If there's no previous city, stop the recursion
        printPath(prev, prev[index]);  // Recur to print the path backwards
        cout << cities[index] << " ";  // Print the current city
    }

    // Function to find the lowest-cost trip (edge) between any two cities
    void findLowCostTrip() {
         // Variable to store the minimum travel cost
        int minCost = INT_MAX;  
        // Variables to store the starting and ending cities of the lowest-cost trip
         string start, end;  

        // Go through all pairs of cities to find the lowest cost
        for (int i = 0; i < cities.size(); i++) {
            for (int j = 0; j < cities.size(); j++) {
                if (adjMatrix[i][j] < minCost && adjMatrix[i][j] != INT_MAX) {
                    minCost = adjMatrix[i][j];  // Update the minimum cost
                    start = cities[i];  // Store the starting city
                    end = cities[j];  // Store the ending city
                }
            }
        }
        // Print the lowest-cost trip
        cout << "\nLow-cost Trip: " << start << " -> " << end << " with cost: " << minCost << endl;
    }
};

int main() {
    // Define the cities
    vector<string> cities = {"Riverside", "Paris", "Hemet", "Moreno Valley"};
    
    // Create a graph object using the list of cities
    Graph g(cities);

    // Add the connections (edges) between the cities with their travel costs
    g.addEdge("Riverside", "Paris", 24);
    g.addEdge("Riverside", "Hemet", 33);
    g.addEdge("Riverside", "Moreno Valley", 16);
    g.addEdge("Paris", "Hemet", 30);
    g.addEdge("Paris", "Moreno Valley", 18);
    g.addEdge("Hemet", "Moreno Valley", 26);

    // Display the adjacency matrix and the adjacency list
    g.displayAdjMatrix();
    g.displayAdjList();

    // Run Dijkstra's algorithm to find the shortest paths from Riverside
    g.dijkstra("Riverside");

    // Find and display the low-cost trip
    g.findLowCostTrip();

    return 0;
}













