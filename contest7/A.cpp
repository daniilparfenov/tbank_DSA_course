#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> costs(n + 1);
    costs[0] = 0;
    for (size_t i = 1; i < n + 1; i++) {
        cin >> costs[i];
    }

    vector<int> dp(n + 1, __INT_MAX__);
    dp[0] = 0;
    dp[1] = costs[1];

    for (size_t i = 2; i < n + 1; i++) {
        dp[i] = min(dp[i - 1], dp[i - 2]) + costs[i];
    }

    cout << dp[n] << '\n';
    return 0;
}
