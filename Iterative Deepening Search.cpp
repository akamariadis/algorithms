#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    Graph(int V);
    void addEdge(int u, int v);
    bool DFS_Limited(int start, int target, int depth);
    bool IterativeDeepeningSearch(int start, int target);
private:
    int V;
    vector<vector<int>> adj;
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

bool Graph::DFS_Limited(int start, int target, int depth) {
    if (depth == 0 && start == target) {
        cout << "Found target " << target << " at depth " << depth << endl;
        return true;
    }
    if (depth > 0) {
        for (int neighbor : adj[start]) {
            if (DFS_Limited(neighbor, target, depth - 1)) {
                return true;
            }
        }
    }
    return false;
}

bool Graph::IterativeDeepeningSearch(int start, int target) {
    for (int depth = 0; depth < V; ++depth) {
        cout << "Depth " << depth << ":" << endl;
        if (DFS_Limited(start, target, depth)) {
            return true;
        }
    }
    return false;
}

int main() {
    int V, E;
    cout << "Enter the number of nodes (V): ";
    cin >> V;
    Graph g(V);
    cout << "Enter the number of edges (E): ";
    cin >> E;
    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
    int start, target;
    cout << "Enter the starting node: ";
    cin >> start;
    cout << "Enter the target node: ";
    cin >> target;
    bool found = g.IterativeDeepeningSearch(start, target);
    if (!found) {
        cout << "Target node " << target << " not found." << endl;
    }
    return 0;
}