#include <cinttypes>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m, k;
    cin >> n >> m >> k;

    vector<vector<uint64_t>> prefSum(n + 1, vector<uint64_t>(m + 1, 0));

    uint64_t num = 0;
    for (size_t i = 1; i < n + 1; i++) {
        for (size_t j = 1; j < m + 1; j++) {
            cin >> num;
            prefSum[i][j] = num + prefSum[i][j - 1] + prefSum[i - 1][j] - prefSum[i - 1][j - 1];
        }
    }

    size_t y1, x1, y2, x2;
    uint64_t requiredSum = 0;
    for (size_t i = 0; i < k; i++) {
        cin >> y1 >> x1 >> y2 >> x2;
        requiredSum =
            prefSum[y2][x2] - prefSum[y2][x1 - 1] - prefSum[y1 - 1][x2] + prefSum[y1 - 1][x1 - 1];
        cout << requiredSum << '\n';
    }

    return 0;
}

// 3 3 3

// 1 2 3
// 4 5 6
// 7 8 9

// 1 1 3 3  ->
// 3 3 3 3
// 1 2 2 2

// 0  0 0  0
// 0  1 3  6
// 0  5 12 21
// 0 12 27 45

// 2 3 1 1
// 2 1 1 1
// 3 2 1 2
