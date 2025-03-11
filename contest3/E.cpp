#include <iostream>
#include <vector>
using namespace std;

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// l: 2i + 1; r: 2i + 2
class MinHeap {
   private:
    vector<int> arr;
    void siftUp(size_t idx);
    void siftDown(size_t idx);

   public:
    void insert(int val);
    int extract();
};

void MinHeap::siftUp(size_t idx) {
    size_t parentIdx = (idx - 1) / 2;
    while (arr[idx] < arr[parentIdx]) {
        swap(arr[idx], arr[parentIdx]);
        idx = parentIdx;
        if (idx == 0) break;
        parentIdx = (idx - 1) / 2;
    }
}

void MinHeap::siftDown(size_t idx) {
    size_t left, right, idxMin;
    while (2 * idx + 1 < arr.size()) {
        left = 2 * idx + 1;
        right = 2 * idx + 2;
        idxMin = left;
        if (right < arr.size() && arr[right] < arr[left]) idxMin = right;
        if (arr[idx] < arr[idxMin]) break;
        swap(arr[idx], arr[idxMin]);
        idx = idxMin;
    }
}

void MinHeap::insert(int val) {
    arr.push_back(val);
    if (arr.size() != 1) siftUp(arr.size() - 1);
}

int MinHeap::extract() {
    int minVal = arr[0];
    swap(arr[0], arr[arr.size() - 1]);
    arr.pop_back();
    siftDown(0);
    return minVal;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    MinHeap heap;
    size_t n;
    cin >> n;
    int num;
    for (size_t i = 0; i < n; i++) {
        cin >> num;
        heap.insert(num);
    }
    for (size_t i = 0; i < n; i++) {
        cout << heap.extract() << ' ';
    }
    cout << '\n';

    return 0;
}

// 10
// 1 8 2 1 4 7 3 2 3 6
