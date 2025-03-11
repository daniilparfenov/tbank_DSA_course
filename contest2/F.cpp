#include <deque>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n = 0, operand = 0;
    short operation = 0;
    deque<size_t> deq;
    vector<int> positions(100'000 + 1, -1);
    size_t gone = 0;

    cin >> n;

    for (size_t i = 0; i < n; i++) {
        cin >> operation;
        switch (operation) {
            case 1:
                cin >> operand;
                deq.push_back(operand);
                positions[operand] = deq.size() - 1 + gone;
                break;
            case 2:
                positions[deq.front()] = -1;
                deq.pop_front();
                gone++;
                break;
            case 3:
                positions[deq.back()] = -1;
                deq.pop_back();
                break;
            case 4:
                cin >> operand;
                cout << positions[operand] - gone << '\n';
                break;
            case 5:
                cout << deq.front() << '\n';
                break;
        }
    }

    return 0;
}
