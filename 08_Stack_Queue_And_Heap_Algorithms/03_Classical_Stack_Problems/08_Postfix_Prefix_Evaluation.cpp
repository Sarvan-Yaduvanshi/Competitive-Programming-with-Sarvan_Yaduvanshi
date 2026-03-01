/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           08 — POSTFIX & PREFIX EVALUATION + EXPRESSION TREE                 ║
║           From Zero to Grandmaster — Classical Stack Problems               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

POSTFIX EVALUATION:
──────────────────
  Scan left to right:
    Operand → push to stack
    Operator → pop two, compute, push result

  DRY RUN: "2 3 1 * + 9 -" → equivalent to (2 + 3*1) - 9 = -4

  ┌──────────┬────────────────────────────────┬──────────┐
  │ Token    │ Action                         │ Stack    │
  ├──────────┼────────────────────────────────┼──────────┤
  │ 2        │ push 2                         │ [2]      │
  │ 3        │ push 3                         │ [2,3]    │
  │ 1        │ push 1                         │ [2,3,1]  │
  │ *        │ pop 1,3 → 3*1=3 → push        │ [2,3]    │
  │ +        │ pop 3,2 → 2+3=5 → push        │ [5]      │
  │ 9        │ push 9                         │ [5,9]    │
  │ -        │ pop 9,5 → 5-9=-4 → push       │ [-4]     │
  └──────────┴────────────────────────────────┴──────────┘
  Result: -4 ✅

PREFIX EVALUATION:
─────────────────
  Scan RIGHT to LEFT:
    Operand → push
    Operator → pop two (A first, then B), compute A op B, push

  DRY RUN: "- + 2 * 3 1 9" → (2 + 3*1) - 9 = -4

  Scan R→L: 9, 1, 3, *, 2, +, -
  ┌──────────┬────────────────────────────────┬──────────┐
  │ Token    │ Action                         │ Stack    │
  ├──────────┼────────────────────────────────┼──────────┤
  │ 9        │ push 9                         │ [9]      │
  │ 1        │ push 1                         │ [9,1]    │
  │ 3        │ push 3                         │ [9,1,3]  │
  │ *        │ pop 3,1 → 3*1=3 → push        │ [9,3]    │
  │ 2        │ push 2                         │ [9,3,2]  │
  │ +        │ pop 2,3 → 2+3=5 → push        │ [9,5]    │
  │ -        │ pop 5,9 → 5-9=-4 → push       │ [-4]     │
  └──────────┴────────────────────────────────┴──────────┘
  Result: -4 ✅

EXPRESSION TREE:
───────────────
  Expression tree for "A + B * C":
          +
         / \
        A    *
            / \
           B   C

  Build from POSTFIX: ABC*+
    Read A → leaf(A), push
    Read B → leaf(B), push
    Read C → leaf(C), push
    Read * → pop C,B → node(*,B,C), push
    Read + → pop (*-node),A → node(+,A,*-node), push

TIME: O(n) for all evaluations
*/

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: POSTFIX EVALUATION (LC 150)
// ═══════════════════════════════════════════════════════════════

int evaluatePostfix(string expr) {
    stack<int> st;
    stringstream ss(expr);
    string token;

    while (ss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();

            if (token == "+") st.push(a + b);
            else if (token == "-") st.push(a - b);
            else if (token == "*") st.push(a * b);
            else st.push(a / b);  // Integer division
        } else {
            st.push(stoi(token));
        }
    }
    return st.top();
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: PREFIX EVALUATION
// ═══════════════════════════════════════════════════════════════

int evaluatePrefix(string expr) {
    stack<int> st;

    // Tokenize and reverse
    stringstream ss(expr);
    string token;
    vector<string> tokens;
    while (ss >> token) tokens.push_back(token);

    // Process right to left
    for (int i = tokens.size() - 1; i >= 0; i--) {
        string& t = tokens[i];
        if (t == "+" || t == "-" || t == "*" || t == "/") {
            int a = st.top(); st.pop();
            int b = st.top(); st.pop();

            if (t == "+") st.push(a + b);
            else if (t == "-") st.push(a - b);
            else if (t == "*") st.push(a * b);
            else st.push(a / b);
        } else {
            st.push(stoi(t));
        }
    }
    return st.top();
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: EXPRESSION TREE
// ═══════════════════════════════════════════════════════════════

struct TreeNode {
    string val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string v) : val(v), left(nullptr), right(nullptr) {}
};

TreeNode* buildExpressionTree(string postfix) {
    stack<TreeNode*> st;

    for (char c : postfix) {
        if (c == ' ') continue;
        TreeNode* node = new TreeNode(string(1, c));

        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            node->right = st.top(); st.pop();
            node->left = st.top(); st.pop();
        }
        st.push(node);
    }
    return st.top();
}

// Inorder traversal → gives infix expression
void inorder(TreeNode* root) {
    if (!root) return;
    if (root->left) cout << "(";
    inorder(root->left);
    cout << root->val;
    inorder(root->right);
    if (root->right) cout << ")";
}

// Postorder → postfix
void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val;
}

// Preorder → prefix
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val;
    preorder(root->left);
    preorder(root->right);
}

void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  POSTFIX & PREFIX EVALUATION + EXPRESSION TREE           ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Postfix evaluation
    cout << "═══ POSTFIX EVALUATION ═══\n";
    string pf1 = "2 3 1 * + 9 -";  // (2 + 3*1) - 9 = -4
    string pf2 = "5 1 2 + 4 * + 3 -";  // 5 + (1+2)*4 - 3 = 14
    cout << "  \"" << pf1 << "\" = " << evaluatePostfix(pf1) << "\n";
    cout << "  \"" << pf2 << "\" = " << evaluatePostfix(pf2) << "\n";

    // Prefix evaluation
    cout << "\n═══ PREFIX EVALUATION ═══\n";
    string pr1 = "- + 2 * 3 1 9";  // -4
    string pr2 = "- + 5 * + 1 2 4 3";  // 14
    cout << "  \"" << pr1 << "\" = " << evaluatePrefix(pr1) << "\n";
    cout << "  \"" << pr2 << "\" = " << evaluatePrefix(pr2) << "\n";

    // Expression tree
    cout << "\n═══ EXPRESSION TREE ═══\n";
    string postfixExpr = "ABC*+";
    TreeNode* root = buildExpressionTree(postfixExpr);

    cout << "  Postfix: " << postfixExpr << "\n";
    cout << "  Infix:   "; inorder(root); cout << "\n";
    cout << "  Prefix:  "; preorder(root); cout << "\n";
    cout << "  Postfix: "; postorder(root); cout << "\n";

    /*
      Tree visualization:
            +
           / \
          A    *
              / \
             B   C
    */

    freeTree(root);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE PROBLEMS:\n";
    cout << "───────────────────\n";
    cout << "1. LC 150  — Evaluate Reverse Polish Notation\n";
    cout << "2. LC 224  — Basic Calculator\n";
    cout << "3. LC 227  — Basic Calculator II\n";
    cout << "4. LC 772  — Basic Calculator III\n";
    cout << "5. LC 1628 — Design Expression Tree\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

