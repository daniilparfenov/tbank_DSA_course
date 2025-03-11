#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// int main() {
//   uint32_t n, k;
//   cin >> n >> k;

//   vector<uint32_t> nums(n);
//   for (size_t i = 0; i < n; i++) {
//     cin >> nums[i];
//   }

//   if (k == 0) {
//     cout << -1;
//     return 0;
//   }

//   sort(nums.begin(), nums.end());

//   if (n == k) {
//     cout << nums[k - 1];
//     return 0;
//   }

//   if (nums[k - 1] != nums[k]) {
//     cout << nums[k - 1];
//   } else {
//     cout << -1;
//   }
//   return 0;

// }

int main() {
  uint32_t n, k;
  cin >> n >> k;

  vector<uint32_t> nums(n);
  for (size_t i = 0; i < n; i++) {
    cin >> nums[i];
  }

  if (k == 0) {
    cout << -1;
    return 0;
  }

  sort(nums.begin(), nums.end());

  if (n == k) {
    cout << nums[k - 1];
    return 0;
  }
  0 1 2 3 4
  1 1 1 3 3

  for (size_t i = 0; i < n; i++)
  {
    if
  }
  

  return 0;
}