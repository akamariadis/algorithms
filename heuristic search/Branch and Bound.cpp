#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

#define INF INT_MAX

class BranchAndBound {
public:
    int n;
    vector<vector<int>> dist;
    int final_res = INF;

    BranchAndBound(int n, vector<vector<int>>& dist) : n(n), dist(dist) {}
    int calculateLowerBound(vector<int>& curr_path) {
        int bound = 0;
        for (int i = 0; i < n; i++) {
            int min_edge = INF;
            for (int j = 0; j < n; j++) {
                if (dist[i][j] < min_edge && i != j && find(curr_path.begin(), curr_path.end(), j) == curr_path.end()) {
                    min_edge = dist[i][j];
                }
            }
            bound += min_edge;
        }

        return bound;
    }
    void branchAndBound(vector<int>& curr_path, vector<bool>& visited, int curr_cost, int level) {
        if (level == n) {
            if (dist[curr_path[level - 1]][curr_path[0]] != INF) {
                int total_cost = curr_cost + dist[curr_path[level - 1]][curr_path[0]];
                final_res = min(final_res, total_cost);
            }
            return;
        }
        int bound = curr_cost + calculateLowerBound(curr_path);
        if (bound >= final_res) return;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[curr_path[level - 1]][i] != INF) {
                visited[i] = true;
                curr_path[level] = i;
                branchAndBound(curr_path, visited, curr_cost + dist[curr_path[level - 1]][i], level + 1);
                visited[i] = false;
            }
        }
    }
    int solve() {
        vector<int> curr_path(n);
        vector<bool> visited(n, false);
        curr_path[0] = 0;
        visited[0] = true;
        branchAndBound(curr_path, visited, 0, 1);
        return final_res;
    }
};

int main() {
    int n = 4;
    vector<vector<int>> dist = {
            {INF, 10, 15, 20},
            {10, INF, 35, 25},
            {15, 35, INF, 30},
            {20, 25, 30, INF}
    };
    BranchAndBound bnb(n, dist);
    int result = bnb.solve();
    cout << "Minimum cost for TSP: " << result << endl;
    return 0;
}