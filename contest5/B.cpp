#include <cinttypes>
#include <iostream>
#include <string>
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

vector<int64_t> findStr(const vector<int64_t>& tHash, const string& s) {
    vector<int64_t> result;
    int64_t sHash = getHashOfString(s);
    for (size_t i = 0; i + s.size() - 1 < tHash.size(); i++) {
        int64_t curSubstrHash = getHashOfSubstring(i, i + s.size() - 1, tHash);
        if (sHash == curSubstrHash) result.push_back(i);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (size_t i = 1; i < kPows.size(); i++) {
        kPows[i] = (kPows[i - 1] * k) % m;
    }

    string t, s;
    cin >> t;
    vector<int64_t> tHash(t.size());
    getHashArray(t, tHash);
    size_t q;
    cin >> q;

    for (size_t i = 0; i < q; i++) {
        cin >> s;
        auto found = findStr(tHash, s);
        cout << found.size() << ' ';
        for (auto f : found) {
            cout << f << ' ';
        }
        cout << '\n';
    }

    return 0;
}
