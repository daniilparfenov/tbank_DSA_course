#include <cinttypes>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

const int64_t k = 31, m = 1e9 + 7;
vector<int64_t> kPows(1e5 + 1, 1);

void getHashArray(const string& s, vector<int64_t>& hash) {
    hash[0] = s[0] - 'a' + 1;
    for (size_t i = 1; i < s.size(); i++) {
        int64_t charCode = s[i] - 'a' + 1;
        hash[i] = (hash[i - 1] * k + charCode) % m;
    }
}

int64_t getHashOfSubstring(const size_t l, const size_t r, const vector<int64_t>& hashArr) {
    if (l == 0) return hashArr[r];
    return ((hashArr[r] - hashArr[l - 1] * kPows[r - l + 1]) % m + m) % m;
}

int64_t getHashOfString(const string& s) {
    int64_t hash = 0;
    for (size_t i = 0; i < s.size(); i++) {
        int64_t charCode = s[i] - 'a' + 1;
        hash = (hash + charCode * kPows[s.size() - i - 1]) % m;
    }
    return hash % m;
}

int64_t LCP(size_t l1, size_t r1, size_t l2, size_t r2, vector<int64_t>& hash) {
    int64_t l = 0, r = min(r1 - l1, r2 - l2), m = 0;
    int64_t s1PrefixHash = 0, s2PrefixHash = 0;
    int64_t lcp = 0;
    while (l <= r) {
        m = l + (r - l) / 2;
        s1PrefixHash = getHashOfSubstring(l1, l1 + m, hash);
        s2PrefixHash = getHashOfSubstring(l2, l2 + m, hash);
        if (s1PrefixHash == s2PrefixHash) {
            lcp = m + 1;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return lcp;
}

// s1 <= s2
bool compareSubStrings(size_t l1, size_t r1, size_t l2, size_t r2, vector<int64_t>& hash,
                       string& s) {
    int64_t lcp = LCP(l1, r1, l2, r2, hash);
    if (lcp == r1 - l1 + 1) return true;
    return s[l1 + lcp] <= s[l2 + lcp];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (size_t i = 1; i < kPows.size(); i++) {
        kPows[i] = (kPows[i - 1] * k) % m;
    }

    string s = "program";
    cin >> s;
    size_t sOriginalSize = s.size();
    s = s + s;
    vector<int64_t> sHash(s.size());
    getHashArray(s, sHash);

    size_t bestL = 0, bestR = sOriginalSize - 1;
    for (size_t i = 0; i + sOriginalSize - 1 < s.size(); i++) {
        if (compareSubStrings(i, i + sOriginalSize - 1, bestL, bestR, sHash, s)) {
            bestL = i;
            bestR = i + sOriginalSize - 1;
        }
    }

    cout << s.substr(bestL, bestR - bestL + 1) << '\n';

    return 0;
}
// 01234 programprogram
