#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

inline double polynom(double x, int a, int b, int c, int d) {
    return a * pow(x, 3) + b * pow(x, 2) + c * x + d;
}

double solve(int a, int b, int c, int d) {
    double l = -10'000, r = 10'000, mid = 0;
    double accuracy = 0.0001;
    while (r - l > accuracy) {
        mid = (l + r) / 2;
        double lVal = polynom(l, a, b, c, d);
        double rVal = polynom(r, a, b, c, d);
        double midVal = polynom(mid, a, b, c, d);

        if (midVal == 0) {
            return mid;
        }

        if (lVal * midVal < 0) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return mid;
}

int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    cout << std::fixed << setprecision(6) << solve(a, b, c, d) << endl;
    return 0;
}
