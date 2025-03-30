#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int findMinPath(const unordered_map<string, vector<string>>& edges, const string& start,
                const string& finish) {
    queue<string> q;
    unordered_map<string, size_t> depths;
    set<string> visited;

    for (auto& [s, d] : edges) {
        depths[s] = 0;
    }

    q.push(start);
    while (!q.empty()) {
        string s = q.front();
        if (s == finish) return depths[s];
        q.pop();
        if (edges.count(s) == 0) continue;
        for (auto neighbor : edges.at(s)) {
            if (visited.count(neighbor) == 0) {
                q.push(neighbor);
                depths[neighbor] = depths[s] + 1;
                visited.insert(neighbor);
            }
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t m;
    unordered_map<string, vector<string>> edges;
    cin >> m;
    for (size_t i = 0; i < m; i++) {
        string source, sep, dest;
        cin >> source >> sep >> dest;
        edges[source].push_back(dest);
    }

    string start = "0", finish = "0";
    cin >> start;
    cin >> finish;
    cout << findMinPath(edges, start, finish);

    return 0;
}
