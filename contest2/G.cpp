#include <deque>
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    deque<size_t> half1, half2;
    size_t n = 0;
    cin >> n;

    char operation = '+';
    size_t operand = 0;

    for (size_t i = 0; i < n; i++) {
        cin >> operation;

        if (operation == '+') {
            cin >> operand;
            half2.push_back(operand);
        } else if (operation == '*') {
            cin >> operand;
            half1.push_back(operand);
        } else {
            if (!half1.empty()) {
                cout << half1.front() << '\n';
                half1.pop_front();
            } else {
                cout << half2.front() << '\n';
                half2.pop_front();
            }
        }
        if (half1.size() > half2.size() + 1) {
            half2.push_front(half1.back());
            half1.pop_back();
        } else if (half1.size() < half2.size()) {
            half1.push_back(half2.front());
            half2.pop_front();
        }
    }

    return 0;
}

// 1 3 4 2 5
// 10
// + 1
// + 2
// * 3
// * 4
// + 5
// -
// -
// -
// -
// -
// 1 3 4 2 5
