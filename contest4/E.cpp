#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <vector>

using namespace std;

bool isPossibleToGetMaxSumLessX(vector<uint64_t>& v, uint64_t x, uint64_t k) {
    if (k > v.size()) return false;

    uint64_t curSum = 0;
    uint64_t usedSegments = 1;

    for (auto num : v) {
        if (curSum + num <= x) {
            curSum += num;
        } else {
            usedSegments++;
            curSum = num;
            if (usedSegments > k) return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    uint64_t n, k;
    cin >> n >> k;
    vector<uint64_t> v(n);
    for (size_t i = 0; i < n; i++) {
        cin >> v[i];
    }

    uint64_t l = 0, r = 0;
    for (auto num : v) {
        r += num;
        if (num > l) l = num;
    }

    while (l < r) {
        uint64_t m = (l + r) / 2;
        if (isPossibleToGetMaxSumLessX(v, m, k))
            r = m;
        else
            l = m + 1;
    }
    cout << l << '\n';
    return 0;
}

// 5 3
// 1 1 2 2 5

// 10 3
// 1 2 1 3 1 4 1 5 2 1
// 1 2 5 1 4 1 3 1 2 1
