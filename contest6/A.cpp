#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

vector<set<size_t>> getComponents(vector<set<size_t>>& edges) {
    set<size_t> visited;
    vector<set<size_t>> components;
    queue<size_t> q;

    for (size_t i = 0; i < edges.size(); i++) {
        if (visited.count(i) != 0) continue;

        q.push(i);
        components.push_back({i});
        visited.insert(i);
        while (!q.empty()) {
            size_t qVertex = q.front();
            q.pop();
            for (auto qVertexNeighbor : edges[qVertex]) {
                if (visited.count(qVertexNeighbor) == 0) {
                    q.push(qVertexNeighbor);
                    components.back().insert(qVertexNeighbor);
                    visited.insert(qVertexNeighbor);
                }
            }
        }
    }
    return components;
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
        edges[f - 1].insert(s - 1);
    }

    auto components = getComponents(edges);

    cout << components.size() << '\n';
    for (auto& component : components) {
        cout << component.size() << '\n';
        for (auto& vertex : component) {
            cout << vertex + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}
