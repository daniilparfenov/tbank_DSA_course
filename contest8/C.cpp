#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class SegmentTree {
   private:
    vector<uint> arr;
    uint neutral;
    size_t n;

    void build(vector<uint>& initArr, size_t node, size_t l, size_t r);
    uint operation(uint op1, uint op2);
    uint getInner(size_t k, size_t tl, size_t tr, size_t node);
    void updateInner(size_t idx, size_t tl, size_t tr, size_t node);

   public:
    SegmentTree(vector<uint>& initArr);
    uint get(size_t k);
    void update(size_t idx);
};

SegmentTree::SegmentTree(vector<uint>& initArr) {
    neutral = 0;
    n = initArr.size();
    arr.resize(4 * n, neutral);
    build(initArr, 1, 0, n - 1);
}

uint SegmentTree::operation(uint op1, uint op2) { return op1 + op2; }

void SegmentTree::build(vector<uint>& initArr, size_t node, size_t l, size_t r) {
    if (l == r) {
        arr[node] = initArr[l];
        return;
    }
    size_t m = (l + r) / 2;
    build(initArr, node * 2, l, m);
    build(initArr, node * 2 + 1, m + 1, r);
    arr[node] = operation(arr[node * 2], arr[node * 2 + 1]);
}

uint SegmentTree::get(size_t k) { return getInner(k, 1, n, 1); }

uint SegmentTree::getInner(size_t k, size_t tl, size_t tr, size_t node) {
    if (tl == tr) return tr;

    size_t m = (tl + tr) / 2;
    if (arr[node * 2] >= k) return getInner(k, tl, m, node * 2);
    return getInner(k - arr[node * 2], m + 1, tr, node * 2 + 1);
}

void SegmentTree::update(size_t idx) { return updateInner(idx, 1, n, 1); }

void SegmentTree::updateInner(size_t idx, size_t tl, size_t tr, size_t node) {
    if (tl == tr) {
        arr[node] = arr[node] == 1 ? 0 : 1;
        return;
    }
    size_t m = (tl + tr) / 2;
    if (tl <= idx && idx <= m)
        updateInner(idx, tl, m, node * 2);
    else
        updateInner(idx, m + 1, tr, node * 2 + 1);
    arr[node] = operation(arr[node * 2], arr[node * 2 + 1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<uint> v(n);
    for (size_t i = 0; i < n; i++) {
        cin >> v[i];
    }

    SegmentTree st(v);

    size_t operation, op;
    for (size_t i = 0; i < m; i++) {
        cin >> operation >> op;
        if (operation == 1) {
            st.update(op + 1);
        } else {
            cout << st.get(op + 1) - 1 << '\n';
        }
    }

    return 0;
}
