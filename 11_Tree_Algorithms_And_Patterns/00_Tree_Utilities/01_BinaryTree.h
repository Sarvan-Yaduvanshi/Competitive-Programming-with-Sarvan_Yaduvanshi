//
// Created by Sarvan Yaduvanshi on 12/11/26.
//

#ifndef COMPETITIVE_PROGRAMMING_WITH_SARVAN_YADUVANSHI_BINARYTREE_H
#define COMPETITIVE_PROGRAMMING_WITH_SARVAN_YADUVANSHI_BINARYTREE_H

#endif //COMPETITIVE_PROGRAMMING_WITH_SARVAN_YADUVANSHI_BINARYTREE_H


#pragma once

// ==========================================
// BINARY TREE — COMMON UTILITIES
// ==========================================

// Standard Headers — macOS Clang
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <cmath>
#include <memory>
#include <utility>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <limits>
#include <numeric>
#include <tuple>
#include <array>
#include <sstream>

// Tree Visualization
#include "03_NaryTree.h"

using namespace std;

// ==========================================
// 1. BINARY TREE NODE
// ==========================================

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(int x)
        : val(x), left(nullptr), right(nullptr) {}
};

// ==========================================
// 2. BUILD BINARY TREE — LEVEL ORDER
// ==========================================

// -1 represents nullptr
// Example: {1, 2, 3, 4, 5, -1, 6}

static TreeNode* buildTree(
    const vector<int>& values
) {
    if (values.empty() || values[0] == -1)
        return nullptr;

    TreeNode* root = new TreeNode(values[0]);

    queue<TreeNode*> q;
    q.push(root);

    size_t idx = 1;

    while (!q.empty() && idx < values.size()) {
        TreeNode* current = q.front();
        q.pop();

        // Left child
        if (idx < values.size() && values[idx] != -1) {
            current->left = new TreeNode(values[idx]);
            q.push(current->left);
        }
        idx++;

        // Right child
        if (idx < values.size() && values[idx] != -1) {
            current->right = new TreeNode(values[idx]);
            q.push(current->right);
        }
        idx++;
    }

    return root;
}

// ==========================================
// 3. PRINT VECTOR OUTPUT
// ==========================================

static void printOutput(
    const vector<int>& ans,
    const string& title = "Output"
) {
    cout << title << ": [";

    for (size_t i = 0; i < ans.size(); ++i) {
        cout << ans[i];

        if (i + 1 < ans.size())
            cout << " ";
    }

    cout << "]\n";
}

// ==========================================
// 4. FREE BINARY TREE MEMORY
// ==========================================

static void deleteTree(TreeNode* root) {
    if (!root)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}