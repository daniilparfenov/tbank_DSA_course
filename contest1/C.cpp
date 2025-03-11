#include <iostream>
#include <string>
#include <vector>

using namespace std;

void query(int query, string& answer) {
    cout << query << endl;
    fflush(stdout);
    cin >> answer;
}

int main() {
    int n = 0;
    cin >> n;

    if (n == 1) {
        cout << "! 1" << endl;
        fflush(stdout);
        return 0;
    }

    int l = 1, r = n, mid = 0;
    string answer("");
    while (l <= r) {
        mid = (l + r) / 2;

        query(mid, answer);
        if (answer == "<") {
            r = mid;
        } else if (answer == ">=") {
            l = mid;
        }

        if (r - l == 1) {
            query(r, answer);
            cout << "! ";
            if (answer == ">=") {
                cout << r << endl;
            } else {
                cout << l << endl;
            }
            fflush(stdout);
            break;
        }
    }

    return 0;
}

//  8 9
//  9 10
