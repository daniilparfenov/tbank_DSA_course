#include <math.h>

#include <iomanip>
#include <iostream>

using namespace std;

double solve(double C) {
    double lX = 0, rX = 1'000'000;
    double curVal = 0, curX;
    double precision = 0.000001;

    if (C > 1'000'000'000) {
        precision = 0.001;
    }

    while (abs(curVal - C) > precision) {
        curX = (rX - lX) / 2 + lX;
        curVal = curX * curX + sqrt(curX + 1);
        if (curVal > C) {
            rX = curX;
        } else {
            lX = curX;
        }
    }
    return curX;
}

int main() {
    double C = 0;
    cin >> C;
    cout << setprecision(13) << solve(C) << endl;

    return 0;
}
