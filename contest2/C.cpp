#include <cinttypes>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int64_t operation(int64_t op1, int64_t op2, string& operation) {
    int64_t result = 0;
    if (operation == "+") {
        result = op2 + op1;
    } else if (operation == "-") {
        result = op2 - op1;
    } else {
        result = op2 * op1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string c;
    stack<int64_t> st;

    while (cin >> c) {
        if (c == "+" || c == "-" || c == "*") {
            int64_t op1 = st.top();
            st.pop();
            int64_t op2 = st.top();
            st.pop();
            st.push(operation(op1, op2, c));
        } else if (c != " ") {
            st.push(stoi(c));
        }
    }
    cout << st.top() << '\n';
    return 0;
}
