#include <math.h>

#include <iostream>
#include <vector>

using namespace std;

int binarySearch(vector<int>& arr, int target) {
    int l = 0, r = arr.size() - 1, mid = (l + r) / 2;
    int nearest = arr[mid];
    while (l <= r) {
        mid = (l + r) / 2;
        if (abs(arr[mid] - target) < abs(nearest - target) ||
            abs(arr[mid] - target) == abs(nearest - target) && arr[mid] < nearest) {
            nearest = arr[mid];
        }
        if (arr[mid] > target) {
            r = mid - 1;
            continue;
        }
        if (arr[mid] < target) {
            l = mid + 1;
            continue;
        }
        return nearest;
    }
    return nearest;
}

int main() {
    unsigned int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (size_t i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int target;
    for (size_t i = 0; i < k; i++) {
        cin >> target;
        cout << binarySearch(arr, target) << endl;
    }

    return 0;
}

// 5 5
// 1 3 4 6 7 9 10
// 2 4 8 1 6
