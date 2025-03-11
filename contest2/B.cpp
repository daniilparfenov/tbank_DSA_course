#include <cinttypes>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class MinStack {
   private:
    vector<pair<int32_t, int32_t>> stack;

   public:
    void push(int32_t element) {
        if (stack.empty()) {
            stack.push_back(make_pair(element, element));
        } else {
            stack.push_back(make_pair(element, min(element, this->getMin())));
        }
    }

    void pop() { stack.pop_back(); }

    pair<int32_t, int32_t> top() { return stack.back(); }

    int32_t getMin() { return stack.back().second; }

    bool empty() { return stack.empty(); }
};

class MinQueue {
   private:
    MinStack st1, st2;

   public:
    void push(int32_t newElement) { st1.push(newElement); }

    void pop() {
        if (!st2.empty()) {
            st2.pop();
            return;
        }
        while (!st1.empty()) {
            st2.push(st1.top().first);
            st1.pop();
        }
        st2.pop();
    }

    int32_t getMin() {
        if (st2.empty()) {
            return st1.getMin();
        } else {
            return min(st1.getMin(), st2.getMin());
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    MinQueue minQueue;
    size_t n, k, i;

    cin >> n >> k;

    int32_t newEl = 0;
    for (i = 0; i < k; i++) {
        cin >> newEl;
        minQueue.push(newEl);
    }

    for (i; i <= n; i++) {
        cout << minQueue.getMin() << ' ';
        if (i != n) {
            minQueue.pop();
            cin >> newEl;
            minQueue.push(newEl);
        }
    }
    cout << '\n';

    return 0;
}
