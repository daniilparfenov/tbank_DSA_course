#include <math.h>

#include <cinttypes>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// recursive binary search, O(logN)
size_t binSearch(vector<uint64_t>& arr, uint64_t target, int l, int r) {
    if (r < l) {
        if (l >= arr.size())
            return arr.size() - 1;
        else
            return l;
    }

    size_t m = (l + r) / 2;
    if (arr[m] > target)
        return binSearch(arr, target, l, m - 1);
    else if (arr[m] < target)
        return binSearch(arr, target, m + 1, r);
    else
        return m;
}

// O(N*logN), positive arr elements
pair<size_t, size_t> targetSumSearch(vector<uint64_t>& arr, uint64_t target) {
    vector<uint64_t> prefixSum(arr.size() + 1);
    prefixSum[0] = 0;
    for (size_t i = 1; i < prefixSum.size(); i++) {
        prefixSum[i] = prefixSum[i - 1] + arr[i - 1];
    }

    uint64_t bestSum = prefixSum.back();
    pair<size_t, size_t> res = {0, arr.size() - 1};

    for (size_t l = 0; l < arr.size(); l++) {
        int r = binSearch(prefixSum, target + prefixSum[l], l + 1, prefixSum.size() - 1);
        if (llabs(prefixSum[r] - prefixSum[l] - target) < llabs(bestSum - target)) {
            bestSum = prefixSum[r] - prefixSum[l];
            res = {l, r - 1};
        }
    }
    return res;
}

int main() {
    vector<uint64_t> v = {4, 7, 2, 2, 1, 8};
    auto [l, r] = targetSumSearch(v, 5);
    cout << l << ' ' << r << endl;

    return 0;
}

//  0  1  2  3  4  5  6  7
// {5, 4, 7, 2, 2, 1, 8}
//  0  5  9  16 18 10 21 29
