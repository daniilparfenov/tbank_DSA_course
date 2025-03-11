#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

// // 5
// // 1 3 5 2 4

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n = 0, train = 0, to_add = 0, to_remove = 0, expected = 1;
    stack<size_t> st;
    vector<pair<short, size_t>> moves;

    cin >> n;

    size_t added = 0;
    for (size_t i = 0; i < n; i++) {
        cin >> train;
        if (train != expected) {
            st.push(train);
            to_add++;
            continue;
        }
        to_add++;
        moves.push_back(make_pair(1, to_add));
        to_add = 0;
        st.push(train);

        while (!st.empty() && st.top() == expected) {
            to_remove++;
            expected++;
            added++;
            st.pop();
        }
        moves.push_back(make_pair(2, to_remove));
        to_remove = 0;
    }

    if (added != n) {
        cout << 0 << endl;
        return 0;
    }
    cout << moves.size() << endl;
    for (const auto& move : moves) {
        cout << move.first << ' ' << move.second << endl;
    }
}
