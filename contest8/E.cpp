#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

const int MOD = 1000000000 + 7;

using namespace std;

typedef pair<int, int> intPair;

size_t next_power_of_two_log(size_t n) {
    if (n == 0) return 1;
    double log2n = std::log2(n);
    return 1u << static_cast<size_t>(std::ceil(log2n));
}

vector<int> compress(vector<int> v) {
    vector<int> b = v;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (auto& x : v) {
        x = lower_bound(b.begin(), b.end(), x) - b.begin();
    }
    return v;
}

class SegmentTree {
   private:
    vector<intPair> st;
    size_t n;
    intPair neutral;

    intPair operation(intPair op1, intPair op2);
    intPair findInternal(size_t l, size_t r, size_t node, size_t tl, size_t tr);
    void setInternal(size_t idx, int val, int count, size_t node, size_t tl, size_t tr);

   public:
    SegmentTree(vector<int> compressedInitArr);
    intPair find(size_t l, size_t r);
    void set(size_t idx, int val, int count);
};

intPair SegmentTree::operation(intPair op1, intPair op2) {
    if (op1.first > op2.first) return op1;
    if (op1.first < op2.first) return op2;
    return {op1.first, (op1.second + op2.second) % MOD};
}

SegmentTree::SegmentTree(vector<int> compressedInitArr) {
    neutral = {INT_MIN, 0};
    n = next_power_of_two_log(*max_element(compressedInitArr.begin(), compressedInitArr.end()) + 1);
    st.resize(4 * n, neutral);
}

intPair SegmentTree::find(size_t l, size_t r) { return findInternal(l, r, 1, 0, n - 1); }

intPair SegmentTree::findInternal(size_t l, size_t r, size_t node, size_t tl, size_t tr) {
    if (tr < l || tl > r) return neutral;
    if (tr <= r && tl >= l) return st[node];
    size_t m = (tr + tl) / 2;
    auto left = findInternal(l, r, node * 2, tl, m);
    auto right = findInternal(l, r, node * 2 + 1, m + 1, tr);
    return operation(left, right);
}

void SegmentTree::set(size_t idx, int val, int count) {
    return setInternal(idx, val, count, 1, 0, n - 1);
}

void SegmentTree::setInternal(size_t idx, int val, int count, size_t node, size_t tl, size_t tr) {
    if (tl == tr) {
        st[node] = {val, st[node].second + count};
        return;
    }
    size_t m = (tl + tr) / 2;
    if (tl <= idx && idx <= m)
        setInternal(idx, val, count, node * 2, tl, m);
    else if (m < idx && idx <= tr)
        setInternal(idx, val, count, node * 2 + 1, m + 1, tr);
    st[node] = operation(st[node * 2], st[node * 2 + 1]);
}

uint findLISSCount(vector<int>& v) {
    auto compressed = compress(v);
    size_t n = compressed.size();

    SegmentTree st(compressed);

    for (size_t i = 0; i < n; i++) {
        if (compressed[i] == 0) {
            st.set(compressed[i], 1, 1);
            continue;
        }
        auto maxLessNum = st.find(0, compressed[i] - 1);
        if (maxLessNum.first == INT_MIN) {
            st.set(compressed[i], 1, 1);
            continue;
        }
        st.set(compressed[i], maxLessNum.first + 1, maxLessNum.second);
    }
    return st.find(0, n - 1).second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n = 0;
    cin >> n;
    vector<int> v(n);
    for (size_t i = 0; i < n; i++) {
        cin >> v[i];
    }

    cout << findLISSCount(v) << '\n';

    return 0;
}
