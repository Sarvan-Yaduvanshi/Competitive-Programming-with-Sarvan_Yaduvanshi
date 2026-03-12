/*
╔══════════════════════════════════════════════════════════════════╗
║       05 — BINARY TREE NODE STRUCTURE (Pointer-Based)           ║
║       Zero to GM Level — Tree Representations                    ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CONCEPT
═══════════════════════════════════════════════════════════════════

 Each node stores:
   - A value
   - Pointer to left child (nullptr if none)
   - Pointer to right child (nullptr if none)

 struct TreeNode {
     int val;
     TreeNode* left;
     TreeNode* right;
 };

 This is the LEETCODE-STYLE representation.
 Rarely used in CP (adjacency list is preferred), but essential
 for understanding binary tree problems.

═══════════════════════════════════════════════════════════════════
 VISUALIZATION
═══════════════════════════════════════════════════════════════════

 Tree:
         1
        / \
       2   3
      /     \
     4       5

 Memory (pointer-based):

 ┌───────────────────┐
 │ val=1             │
 │ left ──→ [node 2] │
 │ right ──→ [node 3]│
 └───────────────────┘
        ↙             ↘
 ┌───────────────────┐  ┌───────────────────┐
 │ val=2             │  │ val=3             │
 │ left ──→ [node 4] │  │ left ──→ nullptr  │
 │ right ──→ nullptr │  │ right ──→ [node 5]│
 └───────────────────┘  └───────────────────┘
        ↙                           ↘
 ┌───────────────────┐  ┌───────────────────┐
 │ val=4             │  │ val=5             │
 │ left ──→ nullptr  │  │ left ──→ nullptr  │
 │ right ──→ nullptr │  │ right ──→ nullptr │
 └───────────────────┘  └───────────────────┘

═══════════════════════════════════════════════════════════════════
 BUILDING TREE FROM LEVEL ORDER INPUT
═══════════════════════════════════════════════════════════════════

 LeetCode style input: [1, 2, 3, 4, null, null, 5]

 Step 1: Create root = new TreeNode(1)
 Step 2: Queue = [root]
 Step 3: Process queue:
   Pop node(1):
     Left = 2 → create node(2), attach as left
     Right = 3 → create node(3), attach as right
     Queue = [node(2), node(3)]
   Pop node(2):
     Left = 4 → create node(4), attach as left
     Right = null → skip
     Queue = [node(3), node(4)]
   Pop node(3):
     Left = null → skip
     Right = 5 → create node(5), attach as right
     Queue = [node(4), node(5)]

 Result:
         1
        / \
       2   3
      /     \
     4       5

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────┬────────────┬──────────────┐
 │ Operation                │ Time       │ Space        │
 ├──────────────────────────┼────────────┼──────────────┤
 │ Access left/right child  │ O(1)       │ —            │
 │ Build from level order   │ O(N)       │ O(N)         │
 │ Traversal                │ O(N)       │ O(H) stack   │
 │ Space per node           │ —          │ O(1) + ptrs  │
 └──────────────────────────┴────────────┴──────────────┘

═══════════════════════════════════════════════════════════════════
 CODE
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

// ═══════════════════════════════════════════════════════════════
// Binary Tree Node Structure
// ═══════════════════════════════════════════════════════════════
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Build tree from level-order input
// -1 represents null
TreeNode* buildFromLevelOrder(vec<int>& vals) {
    if (vals.empty() || vals[0] == -1) return nullptr;

    TreeNode* root = new TreeNode(vals[0]);
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < sz(vals)) {
        TreeNode* node = q.front(); q.pop();

        // Left child
        if (i < sz(vals) && vals[i] != -1) {
            node->left = new TreeNode(vals[i]);
            q.push(node->left);
        }
        i++;

        // Right child
        if (i < sz(vals) && vals[i] != -1) {
            node->right = new TreeNode(vals[i]);
            q.push(node->right);
        }
        i++;
    }
    return root;
}

// Traversals
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}

void levelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int levelSize = sz(q);
        cout << "[";
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front(); q.pop();
            if (i) cout << ", ";
            cout << node->val;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        cout << "] ";
    }
}

// Free memory
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

void solve() {
    int n;
    cin >> n;
    vec<int> vals(n);
    read(vals); // -1 for null

    TreeNode* root = buildFromLevelOrder(vals);

    cout << "Preorder:    "; preorder(root); cout << nl;
    cout << "Inorder:     "; inorder(root); cout << nl;
    cout << "Postorder:   "; postorder(root); cout << nl;
    cout << "Level order: "; levelOrder(root); cout << nl;

    freeTree(root);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    cin >> TC;
    while (TC--) solve();

    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE INPUT / OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
7
1 2 3 4 -1 -1 5

Tree built:
         1
        / \
       2   3
      /     \
     4       5

Output:
Preorder:    1 2 4 3 5
Inorder:     4 2 1 3 5
Postorder:   4 2 5 3 1
Level order: [1] [2, 3] [4, 5]

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Node structure: {val, left*, right*} — the LeetCode standard
 ✅ Build from level-order using BFS queue
 ✅ -1 (or null) represents missing children
 ✅ In CP, prefer adjacency list over pointer-based trees
 ✅ Pointer-based is for interview prep / LeetCode style problems
═══════════════════════════════════════════════════════════════════
*/

