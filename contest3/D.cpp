#include <iostream>
#include <vector>

using namespace std;

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// l: 2i + 1; r: 2i + 2
class MaxHeap {
   private:
    vector<int> arr;
    void siftUp(size_t idx);
    void siftDown(size_t idx);

   public:
    void insert(int val);
    int extract();
};

void MaxHeap::siftUp(size_t idx) {
    size_t parentIdx = (idx - 1) / 2;
    while (arr[idx] > arr[parentIdx]) {
        swap(arr[idx], arr[parentIdx]);
        idx = parentIdx;
        if (idx == 0) break;
        parentIdx = (idx - 1) / 2;
    }
}

void MaxHeap::siftDown(size_t idx) {
    size_t left, right, idxMax;
    while (2 * idx + 1 < arr.size()) {
        left = 2 * idx + 1;
        right = 2 * idx + 2;
        idxMax = left;
        if (right < arr.size() && arr[right] > arr[left]) idxMax = right;
        if (arr[idx] > arr[idxMax]) break;
        swap(arr[idx], arr[idxMax]);
        idx = idxMax;
    }
}

// void MaxHeap::siftDown(size_t idx) {
//     size_t idxOfMax = idx;
//     size_t lChildIdx = 2 * idx + 1;
//     size_t rChildIdx = 2 * idx + 2;

//     while (true) {
//         if (lChildIdx >= arr.size() && rChildIdx >= arr.size()) break;

//         if (lChildIdx >= arr.size()) {
//             if (arr[rChildIdx] > arr[idx])
//                 swap(arr[rChildIdx], arr[idx]);
//             else
//                 break;
//         } else if (rChildIdx >= arr.size()) {
//             if (arr[lChildIdx] > arr[idx])
//                 swap(arr[lChildIdx], arr[idx]);
//             else
//                 break;
//         } else {
//             if (arr[lChildIdx] > arr[rChildIdx] && arr[lChildIdx] > arr[idx])
//                 idxOfMax = lChildIdx;
//             else if (arr[rChildIdx] > arr[lChildIdx] && arr[rChildIdx] > arr[idx])
//                 idxOfMax = rChildIdx;
//             else
//                 break;
//             swap(arr[idxOfMax], arr[idx]);
//             idx = idxOfMax;
//             lChildIdx = 2 * idx + 1;
//             rChildIdx = 2 * idx + 2;
//         }
//     }
// }

void MaxHeap::insert(int val) {
    arr.push_back(val);
    if (arr.size() != 1) siftUp(arr.size() - 1);
}

int MaxHeap::extract() {
    int maxVal = arr[0];
    swap(arr[0], arr[arr.size() - 1]);
    arr.pop_back();
    siftDown(0);
    return maxVal;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    MaxHeap heap;
    size_t n;
    bool operation;
    size_t operand;
    cin >> n;
    for (size_t i = 0; i < n; i++) {
        cin >> operation;
        if (operation) {
            cout << heap.extract() << '\n';
        } else {
            cin >> operand;
            heap.insert(operand);
        }
    }

    return 0;
}

// 0    1   2   3   4  5  6
// 100, 50, 25, 12, 4, 5, 6

//         100
//     50       25
// 12     4    5   6

// 8
// 0 1
// 0 2
// 0 3
// 1
// 0 100
// 0 200
// 1
// 1
