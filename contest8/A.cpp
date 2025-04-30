#include <cinttypes>
#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
   private:
    vector<uint64_t> arr;
    uint64_t neutral;
    size_t n;
    void build(vector<uint64_t>& initArr, size_t node, size_t l, size_t r);
    uint64_t operation(uint64_t op1, uint64_t op2);
    uint64_t getSumInner(size_t l, size_t r, size_t curL, size_t curR, size_t node);
    void setElementInner(size_t idx, uint64_t val, size_t l, size_t r, size_t node);

   public:
    SegmentTree(vector<uint64_t>& initArr);
    uint64_t getSum(size_t l, size_t r);
    void setElement(size_t idx, uint64_t val);
};

SegmentTree::SegmentTree(vector<uint64_t>& initArr) {
    n = initArr.size();
    neutral = 0;
    arr.resize(4 * n, neutral);
    this->build(initArr, 1, 0, n - 1);
}

void SegmentTree::build(vector<uint64_t>& initArr, size_t node, size_t l, size_t r) {
    if (l == r) {
        arr[node] = initArr[l];
        return;
    }
    size_t mid = (r + l) / 2;
    build(initArr, node * 2, l, mid);
    build(initArr, node * 2 + 1, mid + 1, r);
    arr[node] = operation(arr[node * 2], arr[node * 2 + 1]);
}

uint64_t SegmentTree::operation(uint64_t op1, uint64_t op2) { return op1 + op2; }

uint64_t SegmentTree::getSum(size_t l, size_t r) { return getSumInner(l, r, 1, n, 1); }

uint64_t SegmentTree::getSumInner(size_t l, size_t r, size_t curL, size_t curR, size_t node) {
    if (curL > r || curR < l) return neutral;
    if (curL >= l && curR <= r) return arr[node];

    size_t mid = (curR + curL) / 2;
    uint64_t leftSum = getSumInner(l, r, curL, mid, node * 2);
    uint64_t rightSum = getSumInner(l, r, mid + 1, curR, node * 2 + 1);
    return operation(leftSum, rightSum);
}

void SegmentTree::setElement(size_t idx, uint64_t val) { setElementInner(idx, val, 1, n, 1); }

void SegmentTree::setElementInner(size_t idx, uint64_t val, size_t l, size_t r, size_t node) {
    if (l == r && l == idx) {
        arr[node] = val;
        return;
    }
    if (l > idx || idx > r) return;
    size_t mid = (l + r) / 2;
    setElementInner(idx, val, l, mid, node * 2);
    setElementInner(idx, val, mid + 1, r, node * 2 + 1);
    arr[node] = operation(arr[node * 2], arr[node * 2 + 1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;
    vector<uint64_t> arr(n);
    for (size_t i = 0; i < n; i++) {
        cin >> arr[i];
    }

    SegmentTree st(arr);
    size_t operation, op1, op2;
    for (size_t i = 0; i < m; i++) {
        cin >> operation >> op1 >> op2;
        if (operation == 1) {
            st.setElement(op1 + 1, op2);
        } else {
            cout << st.getSum(op1 + 1, op2) << '\n';
        }
    }

    return 0;
}

// 5 5
// 5 4 2 3 5

// 2 0 3 -> 11
// 1 1 1 
// 2 0 3
// 1 3 1
// 2 0 5
