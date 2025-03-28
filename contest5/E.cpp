#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int64_t> zFunction(const string& s) {
    size_t n = s.size();
    vector<int64_t> z(n, 0);
    int64_t l = 0, r = 0;
    for (int64_t i = 1; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (z[i] + i < n && (s[z[i] + i] == s[z[i]])) z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string p = "aaaa";
    string t = "caaabdaaaa";
    cin >> p;
    cin >> t;

    if (t.size() < p.size()) {
        cout << 0 << '\n';
        return 0;
    }

    auto z = zFunction(p + "#" + t);

    reverse(p.begin(), p.end());
    reverse(t.begin(), t.end());
    auto zReverse = zFunction(p + "#" + t);

    vector<int64_t> result;
    for (size_t i = 0; i < t.size() - p.size() + 1; i++) {
        if (z[i + p.size() + 1] == p.size()) {
            result.push_back(i);
            continue;
        }
        if (z[i + p.size() + 1] + zReverse[t.size() - i + 1] == p.size() - 1) result.push_back(i);
    }

    cout << result.size() << '\n';
    for (auto r : result) {
        cout << r + 1 << ' ';
    }
    cout << '\n';

    return 0;
}
