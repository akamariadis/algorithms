#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

#define INF INT_MAX

int calculateCost(const vector<vector<int>>& dist, const vector<int>& path) {
    int cost = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        cost += dist[path[i]][path[i + 1]];
    }
    cost += dist[path[path.size() - 1]][path[0]];
    return cost;
}
int bruteForceSearch(const vector<vector<int>>& dist, int n) {
    vector<int> cities(n);
    for (int i = 0; i < n; i++) {
        cities[i] = i;
    }
    int minCost = INF;
    do {
        int currentCost = calculateCost(dist, cities);
        minCost = min(minCost, currentCost);
    } while (next_permutation(cities.begin() + 1, cities.end()));
    return minCost;
}

int main() {
    int n = 4;
    vector<vector<int>> dist = {
            {INF, 10, 15, 20},
            {10, INF, 35, 25},
            {15, 35, INF, 30},
            {20, 25, 30, INF}
    };
    int result = bruteForceSearch(dist, n);
    cout << "Minimum cost for TSP using Brute Force: " << result << endl;
    return 0;
}
