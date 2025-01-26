#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

struct Node {
    int id;
    float hCost;
    int parent;
    bool operator>(const Node& other) const {
        return hCost > other.hCost;
    }
};

float heuristic(int current, int goal) {
    return abs(current / 10 - goal / 10) + abs(current % 10 - goal % 10);
}

void bestFirstSearch(const vector<vector<int>>& graph, int start, int goal, int rows, int cols) {
    int totalNodes = rows * cols;
    vector<Node> openList;
    vector<bool> closedList(totalNodes, false);
    openList.push_back({start, heuristic(start, goal), -1});
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(openList[0]);
    while (!pq.empty()) {
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
            Node neighborNode = {neighbor, heuristic(neighbor, goal), current.id};
            pq.push(neighborNode);
            openList.push_back(neighborNode);
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
            if (i > 0) graph[node].push_back((i - 1) * cols + j);
            if (i < rows - 1) graph[node].push_back((i + 1) * cols + j);
            if (j > 0) graph[node].push_back(i * cols + (j - 1));
            if (j < cols - 1) graph[node].push_back(i * cols + (j + 1));
        }
    }
    int start = 0;
    int goal = 24;
    bestFirstSearch(graph, start, goal, rows, cols);
    return 0;
}
