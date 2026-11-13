//
// Created by Sarvan Yaduvanshi on 12/11/26.
//

#ifndef COMPETITIVE_PROGRAMMING_WITH_SARVAN_YADUVANSHI_NARYTREE_H
#define COMPETITIVE_PROGRAMMING_WITH_SARVAN_YADUVANSHI_NARYTREE_H

#endif //COMPETITIVE_PROGRAMMING_WITH_SARVAN_YADUVANSHI_NARYTREE_H


#pragma once

// ==========================================
// N-ARY TREE — COMMON UTILITIES
// ==========================================

// Standard Headers — macOS Clang
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
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
#include <deque>

using namespace std;

// ==========================================
// 1. N-ARY TREE NODE — LEETCODE STYLE
// ==========================================

struct Node {
    int val;
    vector<Node*> children;

    Node() : val(0), children() {}

    explicit Node(int x)
        : val(x), children() {}

    Node(int x, vector<Node*> children)
        : val(x), children(children) {}
};

// ==========================================
// 2. BUILD N-ARY TREE — LEVEL ORDER
// ==========================================

// -1 represents nullptr.
//
// LeetCode:
// [1, null, 3, 2, 4, null, 5, 6]
//
// Local:
// {1, -1, 3, 2, 4, -1, 5, 6}

inline Node* buildNaryTree(
    const vector<int>& values
) {
    if (values.empty() || values[0] == -1)
        return nullptr;

    Node* root = new Node(values[0]);

    queue<Node*> q;
    q.push(root);

    size_t idx = 2;

    while (!q.empty() && idx < values.size()) {
        Node* current = q.front();
        q.pop();

        // Build children until -1 separator
        while (idx < values.size() && values[idx] != -1) {
            Node* child = new Node(values[idx++]);

            current->children.push_back(child);
            q.push(child);
        }

        // Skip null separator
        if (idx < values.size() && values[idx] == -1)
            ++idx;
    }

    return root;
}

// ==========================================
// 3. PRINT VECTOR OUTPUT
// ==========================================

inline void printNary(
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

