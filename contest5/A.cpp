#include <cinttypes>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int64_t k = 31, m = 1e9 + 7;
vector<int64_t> kPows(1e5 + 1, 1);

// s0 * h ^(n-1) + s1 * h^(n-2) + ... + sn-2 * h + sn-1
void getHashArray(string& s, vector<int64_t>& hash) {
    hash[0] = s[0] - 'a' + 1;
    for (size_t i = 1; i < s.size(); i++) {
        int64_t charCode = s[i] - 'a' + 1;
        hash[i] = (hash[i - 1] * k + charCode) % m;
    }
}

int64_t getHashOfSubstring(size_t l, size_t r, vector<int64_t>& hashArr) {
    if (l == 0) return hashArr[r];
    return ((hashArr[r] - hashArr[l - 1] * kPows[r - l + 1]) % m + m) % m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (size_t i = 1; i < kPows.size(); i++) {
        kPows[i] = (kPows[i - 1] * k) % m;
    }

    string s;
    size_t q;
    cin >> s;
    cin >> q;

    vector<int64_t> hashArr(s.size(), 0);
    getHashArray(s, hashArr);

    size_t l1, r1, l2, r2;
    for (size_t i = 0; i < q; i++) {
        cin >> l1 >> r1 >> l2 >> r2;
        l1--;
        l2--;
        r1--;
        r2--;
        int64_t hash1 = getHashOfSubstring(l1, r1, hashArr);
        int64_t hash2 = getHashOfSubstring(l2, r2, hashArr);
        if (hash1 != hash2) {
            cout << "No" << '\n';
        } else {
            // for (size_t j = 0; j < r1 - l1 + 1; j++) {
            //     if (s[l1 + j] != s[l2 + j]) {
            //         cout << "No" << '\n';
            //         break;
            //     }
            // }
            cout << "Yes" << '\n';
        }
    }

    return 0;
}
