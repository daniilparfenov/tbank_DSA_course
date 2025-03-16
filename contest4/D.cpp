#include <cinttypes>
#include <iostream>

using namespace std;

uint64_t countNumsLessX(uint64_t n, uint64_t x) {
    uint64_t numLessXCount = 0;
    for (size_t i = 1; i < n + 1; i++) {
        numLessXCount += min(n, x / i);
    }
    return numLessXCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    uint64_t n, k;
    cin >> n >> k;

    uint64_t l = 1, r = n * n;
    while (l < r) {
        uint64_t m = (l + r) / 2;
        if (countNumsLessX(n, m) < k)
            l = m + 1;
        else
            r = m;
    }

    cout << l << '\n';

    return 0;
}
