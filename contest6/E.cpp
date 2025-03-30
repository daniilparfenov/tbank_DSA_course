#include <cinttypes>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

uint64_t findLowestDigitSumDividedByK(uint64_t k) {
    queue<pair<uint64_t, uint64_t>> q;
    q.push({0, 0});
    uint64_t minDigitSum = UINT64_MAX;
    unordered_map<uint64_t, uint64_t> visited;
    while (!q.empty()) {
        auto [rest, sum] = q.front();
        q.pop();
        if (rest == 0 && sum != 0) {
            if (sum < minDigitSum) minDigitSum = sum;
            continue;
        }
        for (auto& toAdd : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
            if (rest == 0 && toAdd == 0) continue;
            uint64_t nRest = (rest * 10 + toAdd) % k;
            uint64_t nSum = sum + toAdd;
            if (nRest == 0) {
                minDigitSum = min(minDigitSum, nSum);
            }
            if (visited.count(nRest) == 0 || (visited.count(nRest) != 0 && nSum < visited[nRest])) {
                visited[nRest] = nSum;
                q.push({nRest, nSum});
            }
        }
    }

    return minDigitSum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    uint64_t k;
    cin >> k;

    cout << findLowestDigitSumDividedByK(k) << '\n';

    return 0;
}
