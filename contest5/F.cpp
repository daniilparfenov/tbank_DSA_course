#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int64_t getPalindromCount(const string& s) {
    string t = "@";
    for (const char c : s) {
        t += "#";
        t += c;
    }
    t += "#%";

    int64_t l = 0, r = -1, n = t.size();
    vector<int64_t> rad(n, 0);
    for (int64_t i = 0; i < n; i++) {
        if (i <= r) {
            rad[i] = min(r - i + 1, rad[r - i + l]);
        } else {
            rad[i] = 1;
        }
        while (i + rad[i] < n && i - rad[i] >= 0 && t[i + rad[i]] == t[i - rad[i]]) {
            rad[i]++;
        }
        if (i + rad[i] - 1 > r) {
            l = i - rad[i] + 1;
            r = i + rad[i] - 1;
        }
    }

    int64_t palindromCount = 0;
    for (size_t i = 0; i < n; i++) {
        palindromCount += rad[i] / 2;
    }

    return palindromCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s = "abacaba";
    cin >> s;

    cout << getPalindromCount(s) << '\n';
    return 0;
}

// aaa
// 0 1 2 3 4 5 6 7 8
// @ # a # a # a # %
// 1 1 2 3 4 3 2 1 1
