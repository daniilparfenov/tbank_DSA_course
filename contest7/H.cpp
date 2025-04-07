#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> LISS(const vector<int>& arr) {
    size_t n = arr.size();
    vector<int> dp(n + 1, __INT_MAX__);
    dp[0] = -__INT_MAX__;

    vector<int> idx(n + 1, -1);
    vector<int> prev(n, -1);

    for (size_t i = 0; i < n; i++) {
        auto pos = distance(dp.begin(), lower_bound(dp.begin(), dp.end(), arr[i]));
        if (arr[i] < dp[pos]) {
            dp[pos] = arr[i];
            idx[pos] = i;
            prev[i] = idx[pos - 1];
        }
    }

    size_t lissLength = -1;
    for (int i = n; i > 0; i--) {
        if (dp[i] != __INT_MAX__) {
            lissLength = i;
            break;
        }
    }

    vector<int> res;
    for (int i = idx[lissLength]; i != -1; i = prev[i]) {
        res.push_back(arr[i]);
    }

    reverse(res.begin(), res.end());

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;
    vector<int> arr(n, 0);
    for (size_t i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> liss = LISS(arr);
    cout << liss.size() << '\n';
    for (auto&& i : liss) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}
