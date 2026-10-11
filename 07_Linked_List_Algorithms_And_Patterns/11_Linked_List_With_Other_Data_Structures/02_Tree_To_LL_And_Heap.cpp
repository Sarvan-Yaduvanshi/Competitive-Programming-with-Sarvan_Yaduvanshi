/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — BINARY TREE TO LINKED LIST & LL + HEAP PATTERNS             ║
║           From Zero to Grandmaster — LL with Other Data Structures         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Flatten Binary Tree to Linked List (LeetCode 114)
 2. BST to Sorted Circular DLL (LeetCode 426)
 3. Linked List + Heap Integration
 4. Linked List Cycle Detection in Graph Context

FLATTEN BINARY TREE TO LL:
─────────────────────────
  Given:           Flattened:
       1           1
      / \           \
     2   5          2
    / \   \          \
   3   4   6         3
                      \
                       4
                        \
                         5
                          \
                           6

  Uses pre-order traversal: 1 → 2 → 3 → 4 → 5 → 6
  All left pointers become NULL, right pointers form the list.

DRY RUN — Morris-like approach:
  For each node with left child:
    1. Find rightmost node of left subtree
    2. Connect it to current node's right child
    3. Move left subtree to right
    4. Set left to NULL

  Node 1: left=2, rightmost of left subtree = 4
          4->right = 5 (original right of 1)
          1->right = 2, 1->left = NULL
          Now: 1 → 2 → 3, 4 → 5 → 6, 2->right = 3

  Node 2: left=3, rightmost of left = 3
          3->right = 4
          2->right = 3, 2->left = NULL
          Now: 1 → 2 → 3 → 4 → 5 → 6 ✅
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// 1. FLATTEN BINARY TREE TO LINKED LIST (LeetCode 114)
// ═══════════════════════════════════════════════════════════════

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Approach 1: Morris-like O(n) time, O(1) space
void flatten(TreeNode* root) {
    TreeNode* curr = root;
    while (curr) {
        if (curr->left) {
            // Find rightmost of left subtree
            TreeNode* rightmost = curr->left;
            while (rightmost->right) rightmost = rightmost->right;

            // Connect rightmost to curr's right
            rightmost->right = curr->right;

            // Move left to right
            curr->right = curr->left;
            curr->left = nullptr;
        }
        curr = curr->right;
    }
}

// Approach 2: Recursive (reverse post-order)
TreeNode* prev_flat = nullptr;
void flattenRecursive(TreeNode* root) {
    if (!root) return;
    flattenRecursive(root->right);
    flattenRecursive(root->left);
    root->right = prev_flat;
    root->left = nullptr;
    prev_flat = root;
}

void printFlatTree(TreeNode* root) {
    while (root) {
        cout << root->val;
        if (root->right) cout << " -> ";
        root = root->right;
    }
    cout << " -> NULL\n";
}

void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// ═══════════════════════════════════════════════════════════════
// 2. BST TO SORTED CIRCULAR DLL (LeetCode 426 concept)
// ═══════════════════════════════════════════════════════════════
/*
  Convert BST to sorted circular doubly linked list IN-PLACE.

  BST:        DLL (circular):
       4       ┌──────────────────────┐
      / \      ▼                      │
     2   5     1 ⟷ 2 ⟷ 3 ⟷ 4 ⟷ 5 ──┘
    / \
   1   3

  In-order traversal gives sorted order: 1, 2, 3, 4, 5
  Link prev ↔ next using left and right pointers.
*/

struct BSTNode {
    int val;
    BSTNode* left;   // Will become 'prev' in DLL
    BSTNode* right;  // Will become 'next' in DLL
    BSTNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BSTtoDLL {
    BSTNode* first = nullptr;
    BSTNode* last = nullptr;

    void inorder(BSTNode* node) {
        if (!node) return;
        inorder(node->left);

        if (last) {
            last->right = node;
            node->left = last;
        } else {
            first = node;
        }
        last = node;

        inorder(node->right);
    }

public:
    BSTNode* convert(BSTNode* root) {
        first = last = nullptr;
        inorder(root);

        // Make circular
        if (first && last) {
            first->left = last;
            last->right = first;
        }
        return first;
    }
};

// ═══════════════════════════════════════════════════════════════
// 3. LINKED LIST + HEAP — Sort LL using Min-Heap
// ═══════════════════════════════════════════════════════════════

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

Node* sortUsingHeap(Node* head) {
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // Push all elements to heap
    Node* curr = head;
    while (curr) {
        minHeap.push(curr->data);
        curr = curr->next;
    }

    // Rebuild list from heap (sorted)
    curr = head;
    while (curr) {
        curr->data = minHeap.top();
        minHeap.pop();
        curr = curr->next;
    }
    return head;
}

void printList(Node* head) {
    while (head) { cout << head->data; if (head->next) cout << " -> "; head = head->next; }
    cout << " -> NULL\n";
}

void freeList(Node* head) {
    while (head) { Node* t = head; head = head->next; delete t; }
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  BINARY TREE TO LL, BST TO DLL, LL + HEAP             ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Flatten Binary Tree
    cout << "═══ FLATTEN BINARY TREE TO LL (LC 114) ═══\n";
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(6);

    cout << "Tree: 1(2(3,4),5(null,6))\n";
    flatten(root);
    cout << "Flattened: "; printFlatTree(root);
    freeTree(root);

    // BST to sorted circular DLL
    cout << "\n═══ BST TO SORTED CIRCULAR DLL ═══\n";
    BSTNode* bst = new BSTNode(4);
    bst->left = new BSTNode(2);
    bst->right = new BSTNode(5);
    bst->left->left = new BSTNode(1);
    bst->left->right = new BSTNode(3);

    cout << "BST: 4(2(1,3),5)\n";
    BSTtoDLL converter;
    BSTNode* dll = converter.convert(bst);

    cout << "Circular DLL: ";
    BSTNode* curr = dll;
    for (int i = 0; i < 5; i++) {
        cout << curr->val;
        if (i < 4) cout << " <-> ";
        curr = curr->right;
    }
    cout << " <-> (back to " << dll->val << ")\n";

    // Break circular for cleanup
    if (dll) {
        BSTNode* tail = dll->left;
        tail->right = nullptr;
        dll->left = nullptr;
        while (dll) { BSTNode* t = dll; dll = dll->right; delete t; }
    }

    // Sort LL using heap
    cout << "\n═══ SORT LINKED LIST USING HEAP ═══\n";
    Node* head = new Node(4);
    head->next = new Node(2);
    head->next->next = new Node(1);
    head->next->next->next = new Node(3);
    cout << "Before: "; printList(head);
    head = sortUsingHeap(head);
    cout << "After:  "; printList(head);
    freeList(head);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LeetCode 114, 426, 109 (Sorted List to BST)\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

