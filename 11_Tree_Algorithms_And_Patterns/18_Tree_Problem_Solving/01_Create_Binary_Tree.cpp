/*
Author: Sarvan.DP.GrandMaster
Created : 2026-05-17 00:20:44
*/

#include <iostream>
#include <vector>

using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int val){
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree{
public:
    static Node* buildTree(const vector<int>& nodes, int& idx){
        idx++;

        // Base case: if the value is -1, return a null pointer
        if (nodes[idx] == -1)
            return nullptr;

        Node* newNode = new Node(nodes[idx]);

        newNode->left = buildTree(nodes, idx);
        newNode-> right = buildTree(nodes, idx);

        return newNode;
    }

    static
};
void solve(){
    vector<int> nodes = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};

    int idx = -1;
    Node* root = BinaryTree::buildTree(nodes, idx);

    if (root != nullptr){
        cout << "Preorder Traversal (Root Data) : " << root->data << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}

