#include <iostream>
#include <vector>

using namespace std;

int binarySearch(vector<int>& arr, int target) {
  int l = 0, r = arr.size() - 1, mid = 0;

  while (l <= r) {
    mid = (l - r) / 2 + r;
    if (target > arr[mid]) {
      l = mid + 1;
      continue;
    }
    if (target < arr[mid]) {
      r = mid - 1;
      continue;
    }
    return mid;
  }
  return -1;
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
    if (binarySearch(arr, target) != -1) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }

  return 0;
}
