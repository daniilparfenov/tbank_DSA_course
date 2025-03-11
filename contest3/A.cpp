#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct Node {
    int id;
    vector<Node*> neighbors;
};

pair<Node*, int> findFarthestNode(Node* root, vector<int>& depths, Node* prevNode = nullptr,
                                  int depth = 0) {
    pair<Node*, int> farthest = {root, depth};
    if (!depths.empty()) depths[root->id] = depth;
    pair<Node*, int> found;
    for (Node* neighbor : root->neighbors) {
        if (neighbor != prevNode) {
            found = findFarthestNode(neighbor, depths, root, depth + 1);
            if (found.second > farthest.second) farthest = found;
        }
    }
    return farthest;
}

int getHeight(Node* root, Node* prevNode) {
    if (!root) return 0;
    int heigth = 0;

    for (Node* neighbor : root->neighbors) {
        if (neighbor != prevNode) heigth = max(heigth, getHeight(neighbor, root) + 1);
    }
    return heigth;
}

int getDiameter(Node* root, vector<int>& depths) {
    auto farthestFromRoot = findFarthestNode(root, depths).first;
    vector<int> d;
    auto farthestFromFarthest = findFarthestNode(farthestFromRoot, d);
    return farthestFromFarthest.second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, parentId;
    cin >> n;

    vector<Node*> nodes(n);
    for (int i = 0; i < n; i++) nodes[i] = new Node{i};
    for (int i = 1; i < n; i++) {
        int parentId;
        cin >> parentId;
        nodes[parentId]->neighbors.push_back(nodes[i]);
        nodes[i]->neighbors.push_back(nodes[parentId]);
    }
    Node* root = nodes[0];

    vector<int> depths(n);

    int height = getHeight(root, nullptr);
    int diameter = getDiameter(root, depths);
    cout << height << ' ' << diameter << '\n';
    for (size_t i = 0; i < n; i++) {
        cout << depths[i] << ' ';
    }
    cout << '\n';

    return 0;
}
