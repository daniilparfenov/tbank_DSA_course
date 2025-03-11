#include <math.h>

#include <algorithm>
#include <cinttypes>
#include <iostream>
using namespace std;

int main() {
    int64_t t = 0, n = 0, m = 0;  // запросы, строки, столбцы
    cin >> t;

    for (; t > 0; t--) {
        cin >> n >> m;

        // best vertical split
        int64_t bestVerticalDiff = INT64_MAX;
        int64_t bestVerticalAlpha = 0;
        int64_t l = 1, r = m - 1, alpha = 0;
        int64_t leftSum = 0, rightSum = 0, totalSum = (int64_t)((1 + n * m) / 2.0 * n * m);
        while (l <= r) {
            alpha = (l + r) / 2;
            leftSum = (int64_t)(alpha * n * (1 + alpha + m * (n - 1)) / 2.0);
            rightSum = totalSum - leftSum;
            if (abs(rightSum - leftSum) < bestVerticalDiff) {
                bestVerticalDiff = llabs(rightSum - leftSum);
                bestVerticalAlpha = alpha;
            }

            if (leftSum == rightSum) {
                break;
            }
            if (leftSum > rightSum) {
                r = alpha - 1;
            } else {
                l = alpha + 1;
            }
        }

        // best horizontal split
        int64_t bestHorizontalDiff = INT64_MAX, upSum = 0, downSum = 0;
        int64_t bestHorizontalAlpha = 0;
        l = 1;
        r = n - 1;
        while (l <= r) {
            alpha = (l + r) / 2;
            upSum = (int64_t)((1 + alpha * m) / 2.0 * alpha * m);
            downSum = totalSum - upSum;
            if (abs(upSum - downSum) < bestHorizontalDiff) {
                bestHorizontalDiff = llabs(upSum - downSum);
                bestHorizontalAlpha = alpha;
            }

            if (upSum == downSum) {
                break;
            }
            if (upSum > downSum) {
                r = alpha - 1;
            } else {
                l = alpha + 1;
            }
        }

        if (bestHorizontalDiff < bestVerticalDiff) {
            cout << "H " << bestHorizontalAlpha + 1 << endl;
        } else {
            cout << "V " << bestVerticalAlpha + 1 << endl;
        }
    }

    return 0;
}
