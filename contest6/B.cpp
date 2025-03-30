#include <iostream>
#include <set>
#include <stack>
#include <vector>

using namespace std;

bool dfs(vector<set<size_t>>& edges, vector<short>& colors, size_t curVertex) {
    colors[curVertex] = 1;
    for (auto curVertexNeighbor : edges[curVertex]) {
        if (colors[curVertexNeighbor] == 1) {
            return true;
        } else if (colors[curVertexNeighbor] == 0) {
            bool d = dfs(edges, colors, curVertexNeighbor);
            if (d) return d;
        }
    }
    colors[curVertex] = 2;
    return false;
}

bool hasCycle(vector<set<size_t>>& edges) {
    vector<short> colors(edges.size(), 0);
    for (size_t i = 0; i < edges.size(); i++) {
        if (colors[i] == 0) {
            bool d = dfs(edges, colors, i);
            if (d) {
                return d;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t N, M;
    cin >> N >> M;

    size_t s, f;
    vector<set<size_t>> edges(N);
    for (size_t i = 0; i < M; i++) {
        cin >> s >> f;
        edges[s - 1].insert(f - 1);
    }

    cout << hasCycle(edges) << '\n';

    return 0;
}
