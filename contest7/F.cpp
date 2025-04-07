#include <iostream>
#include <vector>
using namespace std;

void get2DPrefSum(const vector<vector<int>>& arr, vector<vector<int>>& pSum) {
    size_t n = arr.size();
    size_t m = arr[0].size();
    for (size_t i = 1; i < n; i++) {
        for (size_t j = 1; j < m; j++) {
            pSum[i][j] = pSum[i - 1][j] + pSum[i][j - 1] - pSum[i - 1][j - 1] + arr[i][j];
        }
        cout << '\n';
    }
}

int getSquareSum(const vector<vector<int>>& pSum, size_t row, size_t col, size_t length) {
    size_t i = row + length - 1;
    size_t j = col + length - 1;
    if (i >= pSum.size() || j >= pSum[0].size()) return 0;

    return pSum[i][j] - pSum[row - 1][j] - pSum[i][col - 1] + pSum[row - 1][col - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // initialization
    size_t n, m;
    cin >> n >> m;
    vector<vector<int>> field(n + 1, vector<int>(m + 1, 0));
    for (size_t i = 1; i < n + 1; i++) {
        for (size_t j = 1; j < m + 1; j++) {
            cin >> field[i][j];
        }
    }

    // 2D prefix sum calculating
    vector<vector<int>> pSum(n + 1, vector<int>(m + 1, 0));
    get2DPrefSum(field, pSum);

    int l = 1, r = min(n, m);
    bool foundNecessarySquare = false;
    vector<int> bestSquare = {0, 0, 0};
    while (l <= r) {
        int mid = l + (r - l) / 2;
        foundNecessarySquare = false;
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < m + 1; j++) {
                if (getSquareSum(pSum, i, j, mid) == mid * mid) {
                    l = mid + 1;
                    foundNecessarySquare = true;
                    if (mid >= bestSquare[0]) bestSquare = {mid, i, j};
                }
            }
        }
        if (!foundNecessarySquare) r = mid - 1;
    }

    cout << bestSquare[0] << '\n';
    cout << bestSquare[1] << ' ' << bestSquare[2] << '\n';

    return 0;
}

// 4 5
// 1 0 1 0 1
// 1 1 1 0 1
// 1 1 1 0 1
// 1 0 1 1 0
