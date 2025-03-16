#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64_t n, c;
    int64_t timeDiff;
    cin >> n >> c;
    vector<vector<int64_t>> v(n, vector<int64_t>(3, 0));
    for (size_t i = 0; i < n; i++) {
        cin >> v[i][0] >> timeDiff;
        v[i][1] = v[i][0] + timeDiff;
        v[i][2] = i + 1;
    }

    sort(v.begin(), v.end(), [](auto& p1, auto& p2) { return p1[1] < p2[1]; });

    vector<vector<int64_t>> res;
    res.push_back(v[0]);
    for (auto& segment : v) {
        if (segment[0] >= res.back()[1]) res.push_back(segment);
    }
    
    cout << res.size() * c << '\n';
    cout << res.size() << '\n';
    for (auto& segment : res) {
        cout << segment[2] << ' ';
    }
    cout << '\n';

    return 0;
}
