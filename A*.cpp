#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

struct Node {
    int id;
    float gCost;
    float hCost;
    float fCost() const { return gCost + hCost; }
    int parent;
    bool operator>(const Node& other) const {
        return fCost() > other.fCost();
    }
};

float heuristic(int current, int goal) {
    return abs(current / 10 - goal / 10) + abs(current % 10 - goal % 10);
}

void aStar(const vector<vector<int>>& graph, int start, int goal, int rows, int cols) {
    int totalNodes = rows * cols;
    vector<Node> openList;
    vector<bool> closedList(totalNodes, false);
    openList.push_back({start, 0.0f, heuristic(start, goal), -1});

    while (!openList.empty()) {
        priority_queue<Node, vector<Node>, greater<Node>> pq(openList.begin(), openList.end());
        Node current = pq.top();
        pq.pop();
        if (current.id == goal) {
            cout << "Path: ";
            int node = current.id;
            while (node != -1) {
                cout << node << " ";
                node = openList[node].parent;
            }
            cout << endl;
            return;
        }
        closedList[current.id] = true;
        vector<int> neighbors = graph[current.id];
        for (int neighbor : neighbors) {
            if (closedList[neighbor]) continue;
            float tentativeG = current.gCost + 1;
            if (tentativeG < openList[neighbor].gCost || openList[neighbor].gCost == 0) {
                openList[neighbor].gCost = tentativeG;
                openList[neighbor].hCost = heuristic(neighbor, goal);
                openList[neighbor].parent = current.id;
                pq.push(openList[neighbor]);
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
            if (i > 0) graph[currentNode].push_back((i - 1) * cols + j); // Άνω
            if (i < rows - 1) graph[currentNode].push_back((i + 1) * cols + j); // Κάτω
            if (j > 0) graph[currentNode].push_back(i * cols + j - 1); // Αριστερά
            if (j < cols - 1) graph[currentNode].push_back(i * cols + j + 1); // Δεξιά
        }
    }
    aStar(graph, start, goal, rows, cols);
    return 0;
}
