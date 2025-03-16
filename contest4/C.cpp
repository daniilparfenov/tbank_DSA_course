#include <cinttypes>
#include <iostream>
#include <vector>
using namespace std;

bool isValidDist(vector<uint64_t>& v, size_t k, size_t dist) {
    size_t occupiedStallCnt = 1, lastOccupiedStall = v[0];
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] - lastOccupiedStall < dist) continue;
        occupiedStallCnt++;
        lastOccupiedStall = v[i];
    }
    return occupiedStallCnt >= k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, k;
    cin >> n >> k;
    vector<uint64_t> cords(n);
    for (size_t i = 0; i < n; i++) {
        cin >> cords[i];
    }

    size_t l = 0, r = 1e9;
    while (l + 1 < r) {
        size_t m = (r + l) / 2;
        if (isValidDist(cords, k, m))
            l = m;
        else
            r = m;
    }

    cout << l << '\n';

    return 0;
}
