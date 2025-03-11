#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int id;
    int height;
    Node* left;
    Node* right;
};

void fillHeight(Node* root) {
    if (root == nullptr) return;
    if (!root->left && !root->right) {
        root->height = 0;
    } else {
        fillHeight(root->left);
        fillHeight(root->right);
        if (!root->left)
            root->height = root->right->height + 1;
        else if (!root->right)
            root->height = root->left->height + 1;
        else
            root->height = max(root->left->height, root->right->height) + 1;
    }
}

bool isAVL(Node* root) {
    if (!root) return true;
    if (!root->left && !root->right) return true;
    if (root->left && root->left->id > root->id) return false;
    if (root->right && root->right->id < root->id) return false;
    if (root->left && root->right && abs(root->left->height - root->right->height) > 1)
        return false;
    return isAVL(root->left) && isAVL(root->right);
}

int main() {
    int n, rootId;
    int leftChild, rightChild;
    cin >> n >> rootId;
    vector<Node*> nodes(n);
    for (int i = 0; i < n; i++) {
        nodes[i] = new Node{i, 0, nullptr, nullptr};
    }
    for (int i = 0; i < n; i++) {
        cin >> leftChild >> rightChild;
        if (leftChild != -1) nodes[i]->left = nodes[leftChild];
        if (rightChild != -1) nodes[i]->right = nodes[rightChild];
    }
    fillHeight(nodes[rootId]);
    cout << isAVL(nodes[rootId]) << '\n';
    return 0;
}

//   3
//  1    4
// 0 2  5
