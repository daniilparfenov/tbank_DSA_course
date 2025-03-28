#include <cinttypes>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

const int64_t k = 67, m = 1e9 + 7;
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (size_t i = 1; i < kPows.size(); i++) {
        kPows[i] = (kPows[i - 1] * k) % m;
    }

    string a = "abcabc", b = "abc";
    cin >> a;
    cin >> b;
    size_t bOriginalSize = b.size();
    b = b + b;
    vector<int64_t> bHash(b.size());
    getHashArray(b, bHash);

    unordered_set<int64_t> cyclesHash;
    for (size_t i = 0; i + bOriginalSize - 1 < b.size(); i++) {
        cyclesHash.insert(getHashOfSubstring(i, i + bOriginalSize - 1, bHash));
    }

    vector<int64_t> aHash(a.size());
    getHashArray(a, aHash);
    int64_t result = 0;
    for (size_t i = 0; i + bOriginalSize - 1 < a.size(); i++) {
        int64_t aSubStrHash = getHashOfSubstring(i, i + bOriginalSize - 1, aHash);
        if (cyclesHash.count(aSubStrHash)) {
            result++;
        }
    }
    cout << result << '\n';
    return 0;
}

// a = abcabc
// b = abcabc

// a = aAaa8aaAa
// b = aAaaAa
