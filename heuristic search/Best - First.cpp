#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
    int id;
    float hCost;

    bool operator>(const Node& other) const {
        return hCost > other.hCost;
    }
};

float heuristic(int current, int goal, int cols) {
    return abs(current / cols - goal / cols) + abs(current % cols - goal % cols);
}

void bestFirstSearch(const vector<vector<int>>& graph, int start, int goal, int rows, int cols) {
    int totalNodes = rows * cols;

    vector<int> parents(totalNodes, -1);
    vector<bool> closedList(totalNodes, false);
    vector<bool> inQueue(totalNodes, false);

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    pq.push({start, heuristic(start, goal, cols)});
    inQueue[start] = true;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.id == goal) {
            cout << "Path: ";
            vector<int> path;
            int node = current.id;

            while (node != -1) {
                path.push_back(node);
                node = parents[node];
            }

            reverse(path.begin(), path.end());

            for (int n : path) cout << n << " ";
            cout << endl;
            return;
        }

        closedList[current.id] = true;

        vector<int> neighbors = graph[current.id];
        for (int neighbor : neighbors) {
            if (closedList[neighbor] || inQueue[neighbor]) continue;

            parents[neighbor] = current.id;
            inQueue[neighbor] = true;

            pq.push({neighbor, heuristic(neighbor, goal, cols)});
        }
    }
    cout << "Path not found!" << endl;
}

int main() {
    int rows = 5, cols = 5;
    int totalNodes = rows * cols;
    vector<vector<int>> graph(totalNodes);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int node = i * cols + j;
            if (i > 0) graph[node].push_back((i - 1) * cols + j);        // Up
            if (i < rows - 1) graph[node].push_back((i + 1) * cols + j); // Down
            if (j > 0) graph[node].push_back(i * cols + (j - 1));        // Left
            if (j < cols - 1) graph[node].push_back(i * cols + (j + 1)); // Right
        }
    }

    int start = 0;
    int goal = 24;
    bestFirstSearch(graph, start, goal, rows, cols);

    return 0;
}
