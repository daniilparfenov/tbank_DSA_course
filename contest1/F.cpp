#include <math.h>

#include <cinttypes>
#include <iostream>
#include <vector>
using namespace std;

void printVector(vector<uint32_t>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void merge(vector<uint32_t>& arr, uint32_t l, uint32_t mid, uint32_t r, uint64_t& inversyCnt) {
    vector<uint32_t> leftArr(arr.begin() + l, arr.begin() + mid + 1);
    vector<uint32_t> rightArr(arr.begin() + mid + 1, arr.begin() + r + 1);
    uint32_t i = 0, j = 0, k = l;

    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            inversyCnt += leftArr.size() - i;
            j++;
        }
        k++;
    }
    while (i < leftArr.size()) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < rightArr.size()) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(vector<uint32_t>& arr, uint32_t l, uint32_t r, uint64_t& inversyCnt) {
    if (l - r == 0) {
        return;
    }

    uint32_t mid = (l + r) / 2;
    mergeSort(arr, l, mid, inversyCnt);
    mergeSort(arr, mid + 1, r, inversyCnt);
    merge(arr, l, mid, r, inversyCnt);
}

// 1 3 5 2 4 6

int main() {
    uint32_t n = 0;
    cin >> n;
    vector<uint32_t> arr(n);
    for (size_t i = 0; i < n; i++) {
        cin >> arr[i];
    }

    uint64_t inversyCnt = 0;
    mergeSort(arr, 0, arr.size() - 1, inversyCnt);

    cout << inversyCnt << endl;
    printVector(arr);

    return 0;
}
