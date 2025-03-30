#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;
    vector<vector<size_t>> adjMatrix(n, vector<size_t>(n, SIZE_MAX / 3));

    size_t u, v, w;
    for (size_t i = 0; i < m; i++) {
        cin >> u >> v >> w;
        u--;
        v--;
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w;
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            for (size_t k = 0; k < n; k++) {
                adjMatrix[j][k] = min(adjMatrix[j][k], adjMatrix[j][i] + adjMatrix[i][k]);
            }
        }
    }

    size_t bestCity = 1, minRoad = SIZE_MAX;
    for (size_t i = 0; i < n; i++) {
        size_t maxRoadFromCurCity = *max_element(adjMatrix[i].begin(), adjMatrix[i].end());
        if (maxRoadFromCurCity < minRoad) {
            minRoad = maxRoadFromCurCity;
            bestCity = i + 1;
        }
    }

    cout << bestCity << '\n';

    return 0;
}
