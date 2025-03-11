#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (size_t i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    for (size_t i = 2; i < n; i++) {
        swap(arr[i], arr[i / 2]);
    }

    for (size_t i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
