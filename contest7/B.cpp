#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> dp(3, vector<int>(n + 1, 0));

    dp[0][1] = dp[1][1] = dp[2][1] = 1;

    for (size_t i = 2; i < n + 1; i++) {
        dp[0][i] = dp[1][i - 1] + dp[2][i - 1];
        dp[1][i] = dp[2][i] = dp[0][i - 1] + dp[1][i - 1] + dp[2][i - 1];
    }
    cout << dp[0][n] + dp[1][n] + dp[2][n] << '\n';

    return 0;
}
