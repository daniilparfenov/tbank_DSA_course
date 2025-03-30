#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;
    vector<pair<size_t, size_t>> edges(m);

    for (size_t i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }

    vector<size_t> pos(n + 1);
    size_t vertex;
    for (size_t i = 1; i < n + 1; i++) {
        cin >> vertex;
        pos[vertex] = i;
    }

    bool isValidTopSort = true;
    for (auto& [s, d] : edges) {
        if (pos[s] >= pos[d]) {
            isValidTopSort = false;
            break;
        }
    }

    if (isValidTopSort)
        cout << "YES";
    else
        cout << "NO";
    cout << '\n';

    return 0;
}
