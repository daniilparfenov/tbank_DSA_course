#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int val;
    Node* parent;
    vector<Node*> neighbors;
};

void dfs(Node* root, vector<int>& depths, Node* prevNode = nullptr, int depth = 0) {
    depths[root->val] = depth;
    for (Node* neighbor : root->neighbors) {
        if (neighbor != prevNode) dfs(neighbor, depths, root, depth + 1);
    }
}

Node* LCA(Node* n1, Node* n2, vector<int>& depths) {
    Node *l = n1, *r = n2;
    while (l != r) {
        while (depths[l->val] < depths[r->val]) r = r->parent;
        while (depths[l->val] > depths[r->val]) l = l->parent;
        if (l == r) break;
        if (l->val != 0) l = l->parent;
        if (r->val != 0) r = r->parent;
    }
    return l;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, parentId;
    cin >> n;
    vector<Node*> nodes(n);
    for (int i = 0; i < n; i++) nodes[i] = new Node{i, nullptr, {}};
    for (int i = 1; i < n; i++) {
        int parentId;
        cin >> parentId;
        nodes[i]->parent = nodes[parentId];
        nodes[parentId]->neighbors.push_back(nodes[i]);
        nodes[i]->neighbors.push_back(nodes[parentId]);
    }
    Node* root = nodes[0];

    vector<int> depths(n);
    dfs(root, depths);

    int m, u, v;
    cin >> m;
    for (size_t i = 0; i < m; i++) {
        cin >> u >> v;
        cout << LCA(nodes[u], nodes[v], depths)->val << '\n';
    }

    return 0;
}

// 8
// 0 0 1 1 2 2 3
// 7
// 3 4
// 3 1
// 2 4
// 7 0
// 7 6
// 7 4
// 6 5

//             0
//         1       2        8
//     3       4 5     6
// 7
