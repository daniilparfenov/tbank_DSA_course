#include <cinttypes>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n = 0;
    cin >> n;
    vector<uint64_t> prefixSum(n + 1, 0);
    vector<uint64_t> prefixXor(n + 1, 0);
    uint64_t num = 0;
    for (size_t i = 0; i < n; i++) {
        cin >> num;
        prefixSum[i + 1] = prefixSum[i] + num;
        prefixXor[i + 1] = prefixXor[i] ^ num;
    }
    size_t m, l, r;
    short queryType = 1;
    cin >> m;
    for (size_t i = 0; i < m; i++) {
        cin >> queryType >> l >> r;
        if (queryType == 1)
            cout << prefixSum[r] - prefixSum[l - 1] << '\n';
        else
            cout << (prefixXor[r] ^ prefixXor[l - 1]) << '\n';
    }

    return 0;
}

// 5
// 1 2 3 4 5
// 3
// 1 1 3
// 1 2 4
// 1 3 5
// 0
// 5
// 2