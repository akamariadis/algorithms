#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
public:
    Graph(int V);
    void addEdge(int u, int v);
    void DFS(int start);
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

void Graph::DFS(int start) {
    vector<bool> visited(V, false);
    stack<int> s;
    s.push(start);
    while (!s.empty()) {
        int node = s.top();
        s.pop();
        if (!visited[node]) {
            visited[node] = true;
            cout << node << " ";
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }
}

int main() {
    int V, E;
    cout << "Εισάγετε τον αριθμό των κόμβων (V): ";
    cin >> V;
    Graph g(V);
    cout << "Εισάγετε τον αριθμό των ακμών (E): ";
    cin >> E;
    cout << "Εισάγετε τις ακμές (u v): " << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
    int start;
    cout << "Εισάγετε τον κόμβο εκκίνησης για τον DFS: ";
    cin >> start;
    cout << "Αποτελέσματα DFS από τον κόμβο " << start << ": ";
    g.DFS(start);
    cout << endl;
    return 0;
}