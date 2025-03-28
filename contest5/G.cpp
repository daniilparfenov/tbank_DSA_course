#include <cinttypes>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

uint64_t getHashOfSubSeq(uint64_t l, uint64_t r, vector<uint64_t>& hash) {
    if (l == 0) return hash[r];
    return hash[r] - hash[l - 1];
}

uint64_t getMaxAnagramSize(uint64_t n, uint64_t m, vector<uint64_t>& hash1,
                           vector<uint64_t>& hash2) {
    for (uint64_t length = min(n, m); length > 0; length--) {
        for (uint64_t i = 0; i + length - 1 < n; i++) {
            for (uint64_t j = 0; j + length - 1 < m; j++) {
                uint64_t subSeqHash1 = getHashOfSubSeq(i, i + length - 1, hash1);
                uint64_t subSeqHash2 = getHashOfSubSeq(j, j + length - 1, hash2);
                if (subSeqHash1 == subSeqHash2) return length;
            }
        }
    }
    return 0;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<uint64_t> dist(1, (uint64_t)1 << 32);
    vector<uint64_t> hash(100'000 + 1);
    for (uint64_t i = 1; i < hash.size(); i++) {
        hash[i] = dist(gen);
    }

    uint64_t num;
    uint64_t n, m;

    // first array
    cin >> n;
    vector<uint64_t> hash1(n, 0);
    cin >> num;
    hash1[0] = hash[num];
    for (uint64_t i = 1; i < n; i++) {
        cin >> num;
        hash1[i] = hash1[i - 1] + hash[num];
    }

    // second array
    cin >> m;
    vector<uint64_t> hash2(m, 0);
    cin >> num;
    hash2[0] = hash[num];
    for (uint64_t i = 1; i < m; i++) {
        cin >> num;
        hash2[i] = hash2[i - 1] + hash[num];
    }

    uint64_t maxAnagramSize = getMaxAnagramSize(n, m, hash1, hash2);
    cout << maxAnagramSize << '\n';

    return 0;
}

// 2 2 3 1 3 3
