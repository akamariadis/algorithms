#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int node_cnt = 6;

bool findAugmentingPath(vector<vector<int>> &residualGraph, int source, int sink, vector<int> &parent) {
    vector<bool> visited(node_cnt, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (int next = 0; next < node_cnt; next++) {
            if (!visited[next] && residualGraph[current][next] > 0) {
                parent[next] = current;
                if (next == sink) return true;
                q.push(next);
                visited[next] = true;
            }
        }
    }
    return false;
}

int computeMaxFlow(vector<vector<int>> &capacityGraph, int source, int sink) {
    vector<vector<int>> residualGraph = capacityGraph;
    vector<int> parent(node_cnt);
    int maxFlow = 0;
    while (findAugmentingPath(residualGraph, source, sink, parent)) {
        int flow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            flow = min(flow, residualGraph[u][v]);
        }
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= flow;
            residualGraph[v][u] += flow;
        }
        maxFlow += flow;
    }
    return maxFlow;
}

int main() {
    vector<vector<int>> capacityGraph = {
        {0, 12, 14, 0, 0, 0},
        {0, 0, 4, 10, 0, 0},
        {0, 2, 0, 0, 9, 0},
        {0, 0, 7, 0, 0, 11},
        {0, 0, 0, 6, 0, 7},
        {0, 0, 0, 0, 0, 0}
    };
    int sourceNode = 0, sinkNode = 5;
    cout << "The maximum flow in the network is " << computeMaxFlow(capacityGraph, sourceNode, sinkNode) << endl;
    return 0;
}
