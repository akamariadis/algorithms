#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

struct Node {
    int id;
    float fCost;
    bool operator>(const Node& other) const {
        return fCost > other.fCost;
    }
};

float heuristic(int current, int goal, int cols) {
    return abs(current / cols - goal / cols) + abs(current % cols - goal % cols);
}

void aStar(const vector<vector<int>>& graph, int start, int goal, int rows, int cols) {
    int totalNodes = rows * cols;

    vector<float> gCosts(totalNodes, numeric_limits<float>::infinity());
    vector<int> parents(totalNodes, -1);
    vector<bool> closedList(totalNodes, false);

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    gCosts[start] = 0.0f;
    pq.push({start, heuristic(start, goal, cols)});

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

        if (closedList[current.id]) continue;
        closedList[current.id] = true;

        vector<int> neighbors = graph[current.id];
        for (int neighbor : neighbors) {
            if (closedList[neighbor]) continue;

            float tentativeG = gCosts[current.id] + 1.0f;

            if (tentativeG < gCosts[neighbor]) {
                parents[neighbor] = current.id;
                gCosts[neighbor] = tentativeG;

                float fCost = tentativeG + heuristic(neighbor, goal, cols);
                pq.push({neighbor, fCost});
            }
        }
    }
    cout << "No path found!" << endl;
}

int main() {
    int rows = 5, cols = 5;
    int start = 0, goal = 24;
    vector<vector<int>> graph(rows * cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int currentNode = i * cols + j;
            if (i > 0) graph[currentNode].push_back((i - 1) * cols + j);        // Up
            if (i < rows - 1) graph[currentNode].push_back((i + 1) * cols + j); // Down
            if (j > 0) graph[currentNode].push_back(i * cols + j - 1);          // Left
            if (j < cols - 1) graph[currentNode].push_back(i * cols + j + 1);   // Right
        }
    }

    aStar(graph, start, goal, rows, cols);
    return 0;
}
