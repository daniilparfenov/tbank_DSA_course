#include <cinttypes>
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct maxStElement {
    int64_t val;
    size_t idx;
    int64_t max_val;
    size_t max_idx;
};

class MaxStack {
   private:
    vector<maxStElement> stack;

   public:
    size_t size() { return stack.size(); }
    void push(int64_t element, size_t idx) {
        if (stack.empty()) {
            stack.push_back(maxStElement{element, idx, element, idx});
        } else {
            if (element > this->getMax()) {
                stack.push_back(maxStElement{element, idx, element, idx});
            } else {
                stack.push_back(maxStElement{element, idx, this->getMax(), this->getMaxIdx()});
            }
        }
    }

    void pop() { stack.pop_back(); }

    maxStElement top() { return stack.back(); }

    int64_t getMax() { return stack.back().max_val; }

    size_t getMaxIdx() { return stack.back().max_idx; }

    bool empty() { return stack.empty(); }
};

class MaxQueue {
   private:
    MaxStack st1, st2;

   public:
    size_t size() { return st1.size() + st2.size(); }

    void push(int64_t newElement, size_t idx) { st1.push(newElement, idx); }

    void pop() {
        if (!st2.empty()) {
            st2.pop();
            return;
        }
        while (!st1.empty()) {
            maxStElement el = st1.top();
            st2.push(el.val, el.idx);
            st1.pop();
        }
        st2.pop();
    }

    int64_t getMax() {
        if (st2.empty()) {
            return st1.getMax();
        } else {
            return max(st1.getMax(), st2.getMax());
        }
    }
    size_t getMaxIdx() {
        if (st2.empty()) {
            return st1.getMaxIdx();
        } else {
            if (st1.getMax() > st2.getMax()) {
                return st1.getMaxIdx();
            }
            return st2.getMaxIdx();
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64_t n, k;
    cin >> n >> k;
    vector<int64_t> posts(n, 0);
    for (size_t i = 1; i < n - 1; i++) {
        cin >> posts[i];
    }

    MaxQueue mQueue;
    vector<int64_t> dp(n, 0);
    vector<int64_t> prev(n, 0);
    mQueue.push(dp[0], 0);
    for (size_t i = 1; i < n; i++) {
        dp[i] = posts[i] + mQueue.getMax();
        prev[i] = mQueue.getMaxIdx();
        if (mQueue.size() >= k) {
            mQueue.pop();
        }
        mQueue.push(dp[i], i);
    }

    cout << dp[n - 1] << '\n';

    deque<int64_t> path;
    size_t j = n - 1;
    while (j != 0) {
        path.push_front(j + 1);
        j = prev[j];
    }
    path.push_front(posts[j] + 1);

    cout << path.size() - 1 << '\n';
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i] << ' ';
    }
    cout << '\n';

    return 0;
}
