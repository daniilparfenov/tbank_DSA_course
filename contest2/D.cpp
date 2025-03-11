#include <cinttypes>
#include <iostream>
#include <stack>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    stack<pair<uint8_t, uint32_t>> st;  // (num, numCount)
    uint32_t n = 0, num = 0, result = 0;
    cin >> n;

    for (; n > 0; n--) {
        cin >> num;
        if (st.empty()) {
            st.push(make_pair(num, 1));
            continue;
        }

        uint8_t lastNum = st.top().first;
        if (num == lastNum) {
            st.top().second++;
            continue;
        } else {
            uint32_t lastNumCount = st.top().second;
            if (lastNumCount >= 3) {
                result += lastNumCount;
                st.pop();
            }
            if (!st.empty() && st.top().first == num) {
                st.top().second++;
                continue;
            } else {
                st.push(make_pair(num, 1));
            }
        }
    }

    if (!st.empty() && st.top().second >= 3) {
        result += st.top().second;
    }

    cout << result << '\n';

    return 0;
}
