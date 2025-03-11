#include <cinttypes>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class MinStack {
   private:
    vector<pair<int64_t, int64_t>> stack;

   public:
    void push(int64_t element) {
        if (stack.empty()) {
            stack.push_back(make_pair(element, element));
        } else {
            stack.push_back(make_pair(element, min(element, this->getMin())));
        }
    }

    void pop() { stack.pop_back(); }

    int64_t getMin() { return stack.back().second; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64_t n = 0;
    short query = 0;
    int64_t newElement = 0;
    MinStack minStack;

    cin >> n;
    for (; n > 0; n--) {
        cin >> query;
        switch (query) {
            case 1:
                cin >> newElement;
                minStack.push(newElement);
                break;
            case 2:
                minStack.pop();
                break;
            case 3:
                cout << minStack.getMin() << '\n';
                break;
        }
    }

    return 0;
}
