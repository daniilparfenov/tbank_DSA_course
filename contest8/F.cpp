#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
   private:
    vector<int64_t> st;
    vector<int64_t> arr;
    int64_t n;
    int64_t neutral;

    void updateInternal(int64_t idx, int64_t toAdd, int64_t node, int64_t tl, int64_t tr);
    int64_t getInternal(int64_t l, int64_t r, int64_t node, int64_t tl, int64_t tr);
    int64_t operation(int64_t op1, int64_t op2);

   public:
    SegmentTree(const int64_t n);
    void update(int64_t idx, int64_t toAdd);
    int64_t get(int64_t l, int64_t r);
};

SegmentTree::SegmentTree(const int64_t n) {
    this->n = n;
    neutral = 0;
    this->arr.resize(n, neutral);
    st.resize(4 * n, neutral);
}

int64_t SegmentTree::operation(int64_t op1, int64_t op2) { return op1 + op2; }

int64_t SegmentTree::get(int64_t l, int64_t r) { return getInternal(l, r, 1, 0, n - 1); }

int64_t SegmentTree::getInternal(int64_t l, int64_t r, int64_t node, int64_t tl, int64_t tr) {
    if (tr < l || tl > r) return neutral;
    if (tr <= r && tl >= l) return st[node];

    int64_t m = (tl + tr) / 2;
    int64_t left = getInternal(l, r, node * 2, tl, m);
    int64_t right = getInternal(l, r, node * 2 + 1, m + 1, tr);
    return operation(left, right);
}

void SegmentTree::update(int64_t idx, int64_t toAdd) { updateInternal(idx, toAdd, 1, 0, n - 1); }

void SegmentTree::updateInternal(int64_t idx, int64_t toAdd, int64_t node, int64_t tl, int64_t tr) {
    if (tl == tr) {
        arr[tl] += toAdd;
        st[node] += toAdd;
        return;
    }

    int64_t m = (tl + tr) / 2;
    if (tl <= idx && idx <= m) updateInternal(idx, toAdd, node * 2, tl, m);
    if (m < idx && idx <= tr) updateInternal(idx, toAdd, node * 2 + 1, m + 1, tr);
    st[node] = operation(st[node * 2], st[node * 2 + 1]);
}

vector<int64_t> compress(vector<int64_t> v) {
    vector<int64_t> t = v;
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());

    for (auto& num : v) {
        num = lower_bound(t.begin(), t.end(), num) - t.begin();
    }
    return v;
}

int64_t get3InversionCount(const vector<int64_t>& v) {
    int64_t n = v.size();

    auto compressed = compress(v);
    vector<SegmentTree> trees(2, SegmentTree(n));

    int64_t result = 0;
    for (int64_t i = 0; i < n; i++) {
        auto num = compressed[i];
        trees[0].update(num, 1);
        trees[1].update(num, trees[0].get(num + 1, n - 1));
        result += trees[1].get(num + 1, n - 1);
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64_t n = 0;
    cin >> n;

    vector<int64_t> v(n);
    for (int64_t i = 0; i < n; i++) {
        cin >> v[i];
    }

    cout << get3InversionCount(v) << '\n';

    return 0;
}
