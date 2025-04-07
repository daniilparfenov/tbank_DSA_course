#include <cinttypes>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64_t n, m;
    cin >> n >> m;
    vector<vector<int64_t>> dp(n + 2, vector<int64_t>(m + 2, 0));
    dp[2][2] = 1;

    for (int64_t diag = 4; diag < n + m + 3; diag++) {
        for (int64_t j = 2; j < m + 2; j++) {
            int64_t i = diag - j;
            if (i < 2 || i >= n + 2) continue;
            dp[i][j] += dp[i - 2][j - 1] + dp[i - 1][j - 2];
            if (j + 1 < m + 2) {
                dp[i][j] += dp[i - 2][j + 1];
            }
            if (i + 1 < n + 2) {
                dp[i][j] += dp[i + 1][j - 2];
            }
        }
    }
    cout << dp[n + 1][m + 1] << '\n';

    return 0;
}
