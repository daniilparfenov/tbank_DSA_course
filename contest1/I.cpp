#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 0, query = 0, it_count = 0;

    cin >> n;
    vector<bool> arr(n, 0);

    int right_null_idx = n - 1;

    cout << 1 << ' ';
    for (size_t i = 0; i < n; i++) {
        cin >> query;
        query--;
        arr[query] = 1;
        it_count++;
        if (query == right_null_idx) {
            for (size_t j = query; j >= 0; j--) {
                if (arr[j] == 0) {
                    right_null_idx = j;
                    break;
                } else {
                    it_count--;
                }
            }
        }
        cout << it_count + 1 << ' ';  // 1 iteration to check that array is sorted
    } cout << endl;
    return 0;
}

