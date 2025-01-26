#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <map>
using namespace std;

void printPath(const map<int, int>& parentMap, int start, int end) {
    vector<int> path;
    int node = end;
    while (node != start) {
        path.push_back(node);
        node = parentMap.at(node);
    }
    path.push_back(start);
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << path[i] << " ";
    }
    cout << endl;
}

void bidirectionalSearch(const vector<vector<int>>& graph, int start, int goal) {
    if (start == goal) {
        cout << "Start is the same as goal!" << endl;
        return;
    }
    int totalNodes = graph.size();
    queue<int> queueStart, queueGoal;
    unordered_set<int> visitedStart, visitedGoal;
    map<int, int> parentStart, parentGoal;
    queueStart.push(start);
    queueGoal.push(goal);
    visitedStart.insert(start);
    visitedGoal.insert(goal);
    bool found = false;
    while (!queueStart.empty() && !queueGoal.empty()) {
        if (!queueStart.empty()) {
            int currentStart = queueStart.front();
            queueStart.pop();
            for (int neighbor : graph[currentStart]) {
                if (visitedGoal.find(neighbor) != visitedGoal.end()) {
                    parentStart[neighbor] = currentStart;
                    cout << "Path from start to goal: ";
                    printPath(parentStart, start, neighbor);
                    printPath(parentGoal, goal, neighbor);
                    found = true;
                    break;
                }

                if (visitedStart.find(neighbor) == visitedStart.end()) {
                    visitedStart.insert(neighbor);
                    parentStart[neighbor] = currentStart;
                    queueStart.push(neighbor);
                }
            }
        }
        if (found) break;
        if (!queueGoal.empty()) {
            int currentGoal = queueGoal.front();
            queueGoal.pop();
            for (int neighbor : graph[currentGoal]) {
                if (visitedStart.find(neighbor) != visitedStart.end()) {
                    parentGoal[neighbor] = currentGoal;
                    cout << "Path from start to goal: ";
                    printPath(parentStart, start, neighbor);
                    printPath(parentGoal, goal, neighbor);
                    found = true;
                    break;
                }
                if (visitedGoal.find(neighbor) == visitedGoal.end()) {
                    visitedGoal.insert(neighbor);
                    parentGoal[neighbor] = currentGoal;
                    queueGoal.push(neighbor);
                }
            }
        }
        if (found) break;
    }
    if (!found) {
        cout << "No path found!" << endl;
    }
}

int main() {
    int nodes = 6;
    vector<vector<int>> graph(nodes);
    graph[0] = {1, 2};
    graph[1] = {0, 3};
    graph[2] = {0, 3};
    graph[3] = {1, 2, 4};
    graph[4] = {3, 5};
    graph[5] = {4};
    int start = 0;
    int goal = 5;
    bidirectionalSearch(graph, start, goal);
    return 0;
}
