#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>

struct Node {
    int id;
    int heuristic;
    std::vector<int> neighbors;
    std::vector<int> path;

    Node(int id, int heuristic) : id(id), heuristic(heuristic) {}
    bool operator>(const Node& other) const {
        return heuristic > other.heuristic;
    }
};

int heuristic(int currentId, int goalId) {
    return std::abs(currentId - goalId);
}

std::vector<Node> createGraph() {
    std::vector<Node> graph = {
        {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}
    };
    graph[0].neighbors = {1, 2};
    graph[1].neighbors = {0, 3, 4};
    graph[2].neighbors = {0, 5};
    graph[3].neighbors = {1};
    graph[4].neighbors = {1, 5};
    graph[5].neighbors = {2, 4};
    return graph;
}

std::vector<int> beamSearch(int startId, int goalId, int beamWidth, std::vector<Node>& graph) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> beam;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> nextBeam;
    Node startNode = graph[startId];
    startNode.heuristic = heuristic(startId, goalId);
    startNode.path.push_back(startId);
    beam.push(startNode);
    while (!beam.empty()) {
        for (int i = 0; i < beamWidth && !beam.empty(); ++i) {
            Node current = beam.top();
            beam.pop();
            if (current.id == goalId) {
                return current.path;
            }
            for (int neighborId : current.neighbors) {
                Node neighbor = graph[neighborId];
                neighbor.heuristic = heuristic(neighborId, goalId);
                neighbor.path = current.path;
                neighbor.path.push_back(neighborId);
                nextBeam.push(neighbor);
            }
        }
        beam = nextBeam;
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> empty; // Clear the next beam
        std::swap(nextBeam, empty);
    }
    return {};
}

int main() {
    int startId = 0;
    int goalId = 5;
    int beamWidth = 2;
    std::vector<Node> graph = createGraph();
    std::vector<int> path = beamSearch(startId, goalId, beamWidth, graph);
    if (!path.empty()) {
        std::cout << "Path found: ";
        for (int nodeId : path) {
            std::cout << nodeId << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Path not found." << std::endl;
    }
    return 0;
}
