#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

string reconstruct(int l, int r, vector<vector<int>>& path, const string& s) {
    if (l > r) return "";
    if (l == r) return "";
    if (path[l][r] == -1) {
        return reconstruct(l, r - 1, path, s);
    } else {
        int i = path[l][r];
        string left = (i > l) ? reconstruct(l, i - 1, path, s) : "";
        string middle = reconstruct(i + 1, r - 1, path, s);
        return left + string(1, s[i]) + middle + string(1, s[r]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s = "{([)}][]";
    unordered_map<char, char> map = {
        {'(', ')'},
        {'{', '}'},
        {'[', ']'},
    };
    cin >> s;
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> path(n, vector<int>(n, 0));
    dp[0][0] = 1;
    path[0][0] = -1;

    for (int r = 0; r < n; r++) {
        for (int l = 0; l <= r; l++) {
            if (r == 0) continue;
            if (s[r] == '(' || s[r] == '[' || s[r] == '{') {
                dp[l][r] = dp[l][r - 1] + 1;
                path[l][r] = -1;
                continue;
            }
            dp[l][r] = dp[l][r - 1] + 1;
            path[l][r] = -1;
            for (int i = l; i < r; i++) {
                if (map[s[i]] == s[r]) {
                    if (i == 0) {
                        if (dp[i + 1][r - 1] <= dp[l][r]) {
                            dp[l][r] = dp[i + 1][r - 1];

                            path[l][r] = i;
                        }
                    } else {
                        if (dp[l][i - 1] + dp[i + 1][r - 1] <= dp[l][r]) {
                            dp[l][r] = dp[l][i - 1] + dp[i + 1][r - 1];
                            path[l][r] = i;
                        }
                    }
                }
            }
        }
    }

    cout << reconstruct(0, n - 1, path, s) << '\n';
    return 0;
}
