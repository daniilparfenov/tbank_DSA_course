#include <cinttypes>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int64_t, int64_t> intPair_t;

class SegmentTree {
   private:
    vector<intPair_t> arr;
    intPair_t neutral;
    size_t n;
    void build(vector<int64_t>& initArr, size_t node, size_t l, size_t r);
    intPair_t operation(intPair_t op1, intPair_t op2);
    intPair_t getInner(size_t l, size_t r, size_t curL, size_t curR, size_t node);
    void setInner(size_t idx, int64_t val, size_t l, size_t r, size_t node);

   public:
    SegmentTree(vector<int64_t>& initArr);
    intPair_t get(size_t l, size_t r);
    void set(size_t idx, int64_t val);
};

SegmentTree::SegmentTree(vector<int64_t>& initArr) {
    n = initArr.size();
    neutral = make_pair(INT64_MAX, 1);
    arr.resize(4 * n, neutral);
    this->build(initArr, 1, 0, n - 1);
}

void SegmentTree::build(vector<int64_t>& initArr, size_t node, size_t l, size_t r) {
    if (l == r) {
        arr[node] = make_pair(initArr[l], 1);
        return;
    }
    size_t mid = (r + l) / 2;
    build(initArr, node * 2, l, mid);
    build(initArr, node * 2 + 1, mid + 1, r);
    arr[node] = operation(arr[node * 2], arr[node * 2 + 1]);
}

intPair_t SegmentTree::operation(intPair_t op1, intPair_t op2) {
    if (op1.first == op2.first) return make_pair(op1.first, op1.second + op2.second);
    if (op1.first < op2.first) return op1;
    return op2;
}

intPair_t SegmentTree::get(size_t l, size_t r) { return getInner(l, r, 1, n, 1); }

intPair_t SegmentTree::getInner(size_t l, size_t r, size_t curL, size_t curR, size_t node) {
    if (curL > r || curR < l) return neutral;
    if (curL >= l && curR <= r) return arr[node];

    size_t mid = (curR + curL) / 2;
    intPair_t leftSum = getInner(l, r, curL, mid, node * 2);
    intPair_t rightSum = getInner(l, r, mid + 1, curR, node * 2 + 1);
    return operation(leftSum, rightSum);
}

void SegmentTree::set(size_t idx, int64_t val) { setInner(idx, val, 1, n, 1); }

void SegmentTree::setInner(size_t idx, int64_t val, size_t l, size_t r, size_t node) {
    if (l == r && l == idx) {
        arr[node] = make_pair(val, 1);
        return;
    }
    if (l > idx || idx > r) return;
    size_t mid = (l + r) / 2;
    setInner(idx, val, l, mid, node * 2);
    setInner(idx, val, mid + 1, r, node * 2 + 1);
    arr[node] = operation(arr[node * 2], arr[node * 2 + 1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;
    vector<int64_t> v(n);
    for (size_t i = 0; i < n; i++) {
        cin >> v[i];
    }

    SegmentTree st(v);
    size_t operation, op1, op2;
    for (size_t i = 0; i < m; i++) {
        cin >> operation >> op1 >> op2;
        if (operation == 1) {
            st.set(op1 + 1, op2);
        } else {
            auto [min, count] = st.get(op1 + 1, op2);
            cout << min << ' ' << count << '\n';
        }
    }

    return 0;
}
