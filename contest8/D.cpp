#include <climits>
#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
   private:
    vector<int> st;
    vector<int> initArr;
    int neutral;
    size_t n;
    void build(size_t tl, size_t tr, size_t node);
    int operation(int op1, int op2);
    void updateInner(const size_t idx, const int val, size_t tl, size_t tr, size_t node);
    ssize_t getInner(const size_t l, const int x, size_t tl, size_t tr, size_t node);

   public:
    SegmentTree(const vector<int>& initArr);
    void update(const size_t idx, const int val);
    ssize_t get(const size_t l, const int x);
};

SegmentTree::SegmentTree(const vector<int>& initArr) {
    this->initArr = initArr;
    n = initArr.size();
    neutral = INT_MIN;
    st.resize(4 * n, neutral);
    build(0, n - 1, 1);
}

int SegmentTree::operation(int op1, int op2) { return max(op1, op2); }

void SegmentTree::build(size_t tl, size_t tr, size_t node) {
    if (tl == tr) {
        st[node] = initArr[tl];
        return;
    }

    size_t m = (tl + tr) / 2;
    build(tl, m, node * 2);
    build(m + 1, tr, node * 2 + 1);
    st[node] = operation(st[node * 2], st[node * 2 + 1]);
}

void SegmentTree::update(const size_t idx, const int val) { return updateInner(idx, val, 1, n, 1); }

void SegmentTree::updateInner(const size_t idx, const int val, size_t tl, size_t tr, size_t node) {
    if (tl == tr) {
        initArr[idx - 1] = val;
        st[node] = val;
        return;
    }

    size_t m = (tl + tr) / 2;
    if (tl <= idx && idx <= m)
        updateInner(idx, val, tl, m, node * 2);
    else
        updateInner(idx, val, m + 1, tr, node * 2 + 1);
    st[node] = operation(st[node * 2], st[node * 2 + 1]);
}

ssize_t SegmentTree::get(const size_t l, const int x) { return getInner(l, x, 1, n, 1); }

ssize_t SegmentTree::getInner(const size_t l, const int x, size_t tl, size_t tr, size_t node) {
    if (tr < l || st[node] < x) return -1;
    if (tl == tr) return tl;
    size_t m = (tl + tr) / 2;
    auto left = getInner(l, x, tl, m, node * 2);
    if (left != -1) return left;
    return getInner(l, x, m + 1, tr, node * 2 + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<int> v(n, 0);
    for (size_t i = 0; i < n; i++) {
        cin >> v[i];
    }

    SegmentTree st(v);
    int operation, op1, op2;
    for (size_t i = 0; i < m; i++) {
        cin >> operation >> op1 >> op2;
        if (operation == 1) {
            st.update(op1 + 1, op2);
        } else {
            auto res = st.get(op2 + 1, op1);
            if (res == -1)
                cout << -1 << '\n';
            else
                cout << res - 1 << '\n';
        }
    }

    return 0;
}

// 5 5
// 1 2 2 2 3
// 2 2 0
// 2 2 1
// 2 2 2
// 2 2 3
// 2 2 4
// 1
// // 2
// // 3
// // -1
// // -1
