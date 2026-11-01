/*
Author: Sarvan Yaduvanshi
Created : 2026-11-01 03:16:00
*/

/*
 * ============================================================================
 *  114. Flatten Binary Tree to Linked List
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 114
 *  Difficulty : Medium
 *  Topics     : Linked List, Stack, Tree, Depth-First Search, Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, flatten the tree into a "linked list":
 *
 *      - The "linked list" should use the same TreeNode class where the
 *        right child pointer points to the next node in the list and the
 *        left child pointer is always null.
 *      - The "linked list" should be in the same order as a pre-order
 *        traversal of the binary tree.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      Before:                 After:
 *
 *            1                 1
 *           / \                 \
 *          2   5                 2
 *         / \   \                 \
 *        3   4   6                 3
 *                                   \
 *                                    4
 *                                     \
 *                                      5
 *                                       \
 *                                        6
 *
 *      Pre-order : 1 -> 2 -> 3 -> 4 -> 5 -> 6
 *
 *  Input  : root = [1,2,5,3,4,null,6]
 *  Output : [1,null,2,null,3,null,4,null,5,null,6]
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      Before :  (empty tree)
 *      After  :  (empty tree)
 *
 *  Input  : root = []
 *  Output : []
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      Before :  0
 *      After  :  0
 *
 *  Input  : root = [0]
 *  Output : [0]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree is in the range [0, 2000].
 *      - -100 <= Node.val <= 100
 *
 * ----------------------------------------------------------------------------
 *  Follow up: Can you flatten the tree in-place (with O(1) extra space)?
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <iomanip>
#include <random>
#include <chrono>
#include <cctype>

using namespace std;

class FlattenBinaryTreeToLinkedList{
private:
	struct TreeNode{
		int val;
		TreeNode* left;
		TreeNode* right;

        explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	TreeNode* root;

public:
	FlattenBinaryTreeToLinkedList() : root(nullptr) {}

	~FlattenBinaryTreeToLinkedList(){
		clear();
	}

	void clear(){
		if (root == nullptr)
			return;

		stack<TreeNode*> nodes;
		nodes.push(root);
		while (!nodes.empty()){
			TreeNode* current = nodes.top();
			nodes.pop();

			if (current->left != nullptr)
				nodes.push(current->left);
			if (current->right != nullptr)
				nodes.push(current->right);
			delete current;
		}
		root = nullptr;
	}

	TreeNode* getRoot() const{
		return root;
	}

	void build(const vector<string>& values){
		clear();

		if (values.empty() || values[0] == "null")
			return;

		root = new TreeNode(stoi(values[0]));
		queue<TreeNode*> nodes;
		nodes.push(root);
		size_t index = 1;

		while (!nodes.empty() && index < values.size()){
			TreeNode* current = nodes.front();
			nodes.pop();

			if (values[index] != "null"){
				current->left = new TreeNode(stoi(values[index]));
				nodes.push(current->left);
			}
			++index;

			if (index < values.size() && values[index] != "null"){
				current->right = new TreeNode(stoi(values[index]));
				nodes.push(current->right);
			}
			++index;
		}
	}

	void printOriginalTree() const{
		cout << "Original tree (level-order): ";
		if (root == nullptr){
			cout << "[]\n";
			return;
		}

		vector<string> values;
		queue<TreeNode*> nodes;
		nodes.push(root);

		while (!nodes.empty()){
			TreeNode* current = nodes.front();
			nodes.pop();

			if (current == nullptr){
				values.push_back("null");
				continue;
			}

			values.push_back(to_string(current->val));
			nodes.push(current->left);
			nodes.push(current->right);
		}

		while (!values.empty() && values.back() == "null")
			values.pop_back();

		cout << "[";
		for (size_t i = 0; i < values.size(); ++i)
			cout << (i == 0 ? "" : ",") << values[i];
		cout << "]\n";
	}

	void printFlattenedList() const{
		cout << "Flattened linked list: ";
		if (root == nullptr){
			cout << "[]\n";
			return;
		}

		TreeNode* current = root;
		while (current != nullptr){
			cout << current->val;
			if (current->right != nullptr)
				cout << " -> ";
			current = current->right;
		}
		cout << "\n";
	}

	/*
 * ============================================================================
 * DESIGN & FLATTEN PATTERN 2B: 114. Flatten Binary Tree to Linked List (O(1) Space)
 * ============================================================================
 *
 * - Core Idea (Morris-Style Rightmost Predecessor Splice — Identical to LC 430!):
 *   Treat `curr->right` as `curr->next`, and `curr->left` as `curr->child`!
 *   Whenever `curr->left != nullptr`:
 *     1. Find the rightmost node in `curr->left`'s subtree (`predecessor = curr->left`,
 *        walk `while (predecessor->right != nullptr)`).
 *     2. Attach `curr->right` to `predecessor->right`.
 *     3. Move `curr->left` to `curr->right`, and set `curr->left = nullptr`.
 *     4. Advance `curr = curr->right`.
 *
 * - Quick Dry Run:
 *         1                1                 1
 *        / \      ==>       \       ==>       \
 *       2   5                2                 2
 *      / \   \              / \                 \
 *     3   4   6            3   4                 3 -> 4 -> 5 -> 6
 *                               \
 *                                5 -> 6
 *
 * - Complexity:
 *   Time  : O(N) — Every tree edge is traversed at most twice.
 *   Space : O(1) — Strict O(1) auxiliary space (no recursion stack!).
 * ============================================================================
 */
	static void flatten(TreeNode* root){
		// Base case: If the current node is null, return
		if (root == nullptr)
			return;

		TreeNode* curr = root;

		while (curr != nullptr){
			// Case 1: If the current node has a left child, we need to rewire the connections
			if (curr->left != nullptr){
				// Find the rightmost node of the left subtree
                TreeNode* leftTail = curr->left;
                while (leftTail->right != nullptr)
                    leftTail = leftTail->right;

                // Rewire the connections:
                // 1. Connect the rightmost node's right pointer to the current node's right child
                leftTail->right = curr->right;
                // 2. Move the left subtree to the right
                curr->right = curr->left;
                // 3. Set the left child to null
                curr->left = nullptr;
			}

			// Move to the next node in the "linked list" (which is now the right child)
			curr = curr->right;
		}
	}
};

static vector<string> parseInput(const string& input){
	string cleaned;
	for (char character : input){
		if (character != '[' && character != ']' && !isspace(static_cast<unsigned char>(character)))
			cleaned += character;
	}

	vector<string> values;
	if (cleaned.empty())
		return values;

	size_t start = 0;
	while (start <= cleaned.size()){
		size_t comma = cleaned.find(',', start);
		string value = cleaned.substr(start, comma - start);
		if (value == "None" || value == "none" || value == "NULL" || value == "null")
			value = "null";
		values.push_back(value);

		if (comma == string::npos)
			break;
		start = comma + 1;
	}
	return values;
}

static void solve(){
	string input;
	getline(cin, input);

	FlattenBinaryTreeToLinkedList tree;
	tree.build(parseInput(input));
	tree.printOriginalTree();
	FlattenBinaryTreeToLinkedList::flatten(tree.getRoot());
	tree.printFlattenedList();
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
