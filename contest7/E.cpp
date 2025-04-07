#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int DamerauLevenshteinDistance(const string& S, const string& T) {
    int M = S.size();
    int N = T.size();

    vector<vector<int>> d(M + 1, vector<int>(N + 1, 0));

    d[0][0] = 0;
    for (int i = 1; i < M + 1; i++) d[i][0] = d[i - 1][0] + 1;
    for (int j = 1; j < N + 1; j++) d[0][j] = d[0][j - 1] + 1;

    for (int i = 1; i < M + 1; i++) {
        for (int j = 1; j < N + 1; j++) {
            if (S[i - 1] == T[j - 1])
                d[i][j] = d[i - 1][j - 1];
            else
                d[i][j] = d[i - 1][j - 1] + 1;

            d[i][j] = min({d[i][j], d[i - 1][j] + 1, d[i][j - 1] + 1});

            if (i > 1 && j > 1 && S[i - 1] == T[j - 2] && S[i - 2] == T[j - 1]) {
                d[i][j] = min(d[i][j], d[i - 2][j - 2] + 1);
            }
        }
    }

    return d[M][N];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1, s2;
    cin >> s1;
    cin >> s2;
    cout << DamerauLevenshteinDistance(s1, s2) << '\n';

    return 0;
}
