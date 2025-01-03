#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(const vector<vector<int>>& graph, int startNode) {
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    visited[startNode] = true;
    q.push(startNode);
    cout << "BFS Traversal: ";
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current << " ";
        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

int main() {
    int nodes, edges;
    cout << "Enter the number of nodes: ";
    cin >> nodes;
    cout << "Enter the number of edges: ";
    cin >> edges;
    vector<vector<int>> graph(nodes);
    cout << "Enter the edges (node1 node2):" << endl;
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    int startNode;
    cout << "Enter the starting node for BFS: ";
    cin >> startNode;
    bfs(graph, startNode);
    return 0;
}