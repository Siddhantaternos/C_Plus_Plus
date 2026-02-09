/*
Experiment : 04  
Problem Statement : 
A business house has several offices in different countries. They want to lease phone lines to connect them with each other, 
and the phone company charges different rent to connect different pairs of cities. 
The business house wants to connect all its offices with a minimum total cost. Solve the problem using Prim's algorithm.
*/

#include <iostream>
#include <vector>
#include <queue>    // For BFS
using namespace std;

// ---------------- BFS FUNCTION ----------------
void BFS(int start, vector<vector<pair<int,int>>> &adj, int V) {
    vector<int> visited(V, 0);
    queue<int> q;

    visited[start] = 1;
    q.push(start);

    cout << "BFS Traversal starting from vertex " << start << ": ";

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (auto neighbor : adj[node]) {
            if (!visited[neighbor.first]) {
                visited[neighbor.first] = 1;
                q.push(neighbor.first);
            }
        }
    }
    cout << endl;
}

// ---------------- DFS FUNCTION ----------------
void DFSUtil(int node, vector<vector<pair<int,int>>> &adj, vector<int> &visited) {
    visited[node] = 1;
    cout << node << " ";

    for (auto neighbor : adj[node]) {
        if (!visited[neighbor.first]) {
            DFSUtil(neighbor.first, adj, visited);
        }
    }
}

void DFS(int start, vector<vector<pair<int,int>>> &adj, int V) {
    vector<int> visited(V, 0);
    cout << "DFS Traversal starting from vertex " << start << ": ";
    DFSUtil(start, adj, visited);
    cout << endl;
}

// ---------------- MAIN ----------------
int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    // adjacency list: (neighbor, weight)
    vector<vector<pair<int,int>>> adj(V);

    cout << "Enter edges (u v cost):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});  // undirected graph
    }

    // Print adjacency list
    cout << "\nAdjacency List:" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << " -> ";
        for (auto x : adj[i]) {
            cout << "(" << x.first << "," << x.second << ") ";
        }
        cout << endl;
    }

    // ---------------- BFS ----------------
    cout << "\n--- BFS Traversal ---\n";
    BFS(0, adj, V);

    // ---------------- DFS ----------------
    cout << "\n--- DFS Traversal ---\n";
    DFS(0, adj, V);

    // ---------------- Prim's Algorithm ----------------
    int visited[20] = {0};
    visited[0] = 1;   // start from vertex 0
    int minCost = 0;

    cout << "\nEdges in Minimum Spanning Tree (Prim's Algorithm):\n";

    for (int count = 0; count < V - 1; count++) {
        int minWeight = 999;
        int u = -1, v = -1;

        // Find minimum edge connecting visited to unvisited
        for (int i = 0; i < V; i++) {
            if (visited[i]) {
                for (auto x : adj[i]) {
                    int neighbor = x.first;
                    int weight = x.second;

                    if (!visited[neighbor] && weight < minWeight) {
                        minWeight = weight;
                        u = i;
                        v = neighbor;
                    }
                }
            }
        }

        visited[v] = 1;       // mark only the new vertex as visited
        minCost += minWeight;
        cout << u << " -> " << v << " = " << minWeight << endl;
    }

    cout << "\nMinimum cost to connect all offices = " << minCost << endl;

    return 0;
}
