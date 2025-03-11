#include <algorithm>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

void findNumLessNumIdx(vector<size_t>& arr, unordered_map<size_t, int>& numLessNumIdx) {
    stack<size_t> st;

    for (size_t i = 0; i < arr.size(); i++) {
        if (st.empty()) {
            st.push(i);
            numLessNumIdx[i] = -1;
            continue;
        }
        while (!st.empty() && arr[i] <= arr[st.top()]) {
            st.pop();
        }
        if (!st.empty()) {
            numLessNumIdx[i] = st.top();
        }
        st.push(i);
        if (!numLessNumIdx.count(i)) {
            numLessNumIdx[i] = -1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n = 0;
    cin >> n;
    vector<size_t> arr(n);
    for (size_t i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<size_t> prefixSum(n);
    prefixSum[0] = arr[0];
    for (size_t i = 1; i < n; i++) {
        prefixSum[i] = prefixSum[i - 1] + arr[i];
    }

    unordered_map<size_t, int> numLessNumIdx;
    unordered_map<size_t, int> numLessNumIdxReverse;
    findNumLessNumIdx(arr, numLessNumIdx);
    reverse(arr.begin(), arr.end());
    findNumLessNumIdx(arr, numLessNumIdxReverse);

    size_t result = 0, left = 0, right = 0;
    for (size_t i = 0; i < n; i++) {
        if (numLessNumIdx[i] == -1 && numLessNumIdxReverse[n - i - 1] == -1) {
            left = 0;
            right = n - 1;
        } else {
            if (numLessNumIdx[i] == -1) {
                left = 0;
            } else {
                left = numLessNumIdx[i] + 1;
            }
            if (numLessNumIdxReverse[n - i - 1] == -1) {
                right = n - 1;
            } else {
                right = n - numLessNumIdxReverse[n - i - 1] - 2;
            }
        }

        size_t sectionSum = 0;
        if (left == right) {
            sectionSum = arr[n - left - 1] * arr[n - left - 1];
        } else {
            if (left == 0) {
                sectionSum = arr[n - i - 1] * prefixSum[right];
            } else {
                sectionSum = arr[n - i - 1] * (prefixSum[right] - prefixSum[left - 1]);
            }
        }

        if (sectionSum > result) {
            result = sectionSum;
        }
    }
    cout << result << '\n';

    return 0;
}
// 0 1 2 3 4 5
// 3 1 6 4 5 2
// 3 4 10 14 19 21
// 3 0 0 1 0 5
