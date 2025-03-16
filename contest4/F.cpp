#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
    size_t n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (size_t i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
    }

    sort(v.begin(), v.end());

    int l = v[0].first, r = v[0].second;
    size_t totalLength = 0;
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i].first <= r && v[i].second > r) {
            r = v[i].second;
        } else if (v[i].first > r) {
            totalLength += r - l;
            l = v[i].first;
            r = v[i].second;
        }
    }
    totalLength += r - l;

    cout << totalLength << '\n';

    return 0;
}
