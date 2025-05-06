#include <iostream>
#include <omp.h>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

// Number of vertices in the graph
int vertices = 6;

// Adjacency list representation of the graph
vector<vector<int>> graph = {
    {1},        // Node 0 connects to 1
    {0, 2, 3},  // Node 1 connects to 0, 2, 3
    {1, 4, 5},  // Node 2 connects to 1, 4, 5
    {1, 4},     // Node 3 connects to 1, 4
    {2, 3},     // Node 4 connects to 2, 3
    {2}         // Node 5 connects to 2
};

// Visited array to track which nodes have been visited
vector<bool> visited(vertices, false);

// Reset visited array to all false
void initialize_visited() {
    visited.assign(vertices, false);
}

// Print the adjacency list of the graph
void printGraph() {
    cout << "Adjacency List:\n";
    for (int i = 0; i < vertices; i++) {
        cout << i << " -> ";
        for (int j : graph[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
}

// Parallel Depth First Search
void parallel_dfs(int start) {
    stack<int> s;           // Stack for DFS
    s.push(start);          // Start from given node
    visited[start] = true;  // Mark it visited

    cout << "Parallel DFS: ";
    while (!s.empty()) {
        int current = s.top();  // Get the current node from top of stack
        cout << current << " ";

        // Critical section to avoid race condition on stack
        #pragma omp critical
        s.pop();

        // Explore neighbors of current node in parallel
        #pragma omp parallel for
        for (int j = 0; j < graph[current].size(); j++) {
            int neighbor = graph[current][j];

            // If neighbor hasn't been visited, visit and push it to stack
            if (!visited[neighbor]) {
                #pragma omp critical  // Only one thread at a time modifies shared data
                {
                    s.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
    cout << endl;
}

// Parallel Breadth First Search
void parallel_bfs(int start) {
    queue<int> q;           // Queue for BFS
    q.push(start);          // Start from given node
    visited[start] = true;  // Mark it visited

    cout << "Parallel BFS: ";
    while (!q.empty()) {
        int current = q.front();  // Get current node from front of queue
        cout << current << " ";

        // Critical section to avoid race condition on queue
        #pragma omp critical
        q.pop();

        // Explore neighbors of current node in parallel
        #pragma omp parallel for
        for (int j = 0; j < graph[current].size(); j++) {
            int neighbor = graph[current][j];

            // If neighbor hasn't been visited, visit and enqueue it
            if (!visited[neighbor]) {
                #pragma omp critical  // Only one thread at a time modifies shared data
                {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
    cout << endl;
}

// Main function
int main() {
    printGraph();           // Display the graph structure
    initialize_visited();   // Reset visited before DFS
    parallel_dfs(0);        // Perform parallel DFS from node 0

    initialize_visited();   // Reset visited before BFS
    parallel_bfs(0);        // Perform parallel BFS from node 0

    return 0;
}