#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64_t N, h, m, s, totalOpenSeconds = 0, totalCloseSeconds = 0;
    cin >> N;
    int64_t nWithout24hStores = N;
    vector<pair<int64_t, int64_t>> v;
    for (size_t i = 0; i < N; i++) {
        cin >> h >> m >> s;
        totalOpenSeconds = h * 3600 + m * 60 + s;
        cin >> h >> m >> s;
        totalCloseSeconds = h * 3600 + m * 60 + s;
        if (totalCloseSeconds == totalOpenSeconds) {
            nWithout24hStores--;
            continue;
        }

        if (totalCloseSeconds < totalOpenSeconds) {
            v.push_back({totalOpenSeconds, -1});
            v.push_back({0, -1});
            v.push_back({86400, 1});
            v.push_back({totalCloseSeconds, 1});
            continue;
        }

        v.push_back({totalOpenSeconds, -1});
        v.push_back({totalCloseSeconds, 1});
    }

    if (v.empty()) {
        cout << 24 * 3600 << '\n';
        return 0;
    }

    sort(v.begin(), v.end());

    int64_t openedCount = 0;
    int64_t totalTimeOfAllOpened = 0, startTime = 0;
    for (auto& [seconds, type] : v) {
        if (type == -1) {
            openedCount++;
            if (openedCount == nWithout24hStores) startTime = seconds;
        } else {
            if (openedCount == nWithout24hStores) totalTimeOfAllOpened += seconds - startTime;
            openedCount--;
        }
    }
    cout << totalTimeOfAllOpened << '\n';

    return 0;
}
