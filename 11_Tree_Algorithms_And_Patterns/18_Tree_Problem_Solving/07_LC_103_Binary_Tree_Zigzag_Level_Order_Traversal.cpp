/*
Author: Sarvan Yaduvanshi
Created : 2026-11-04 07:44:14
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iomanip>
#include <random>
#include <chrono>
using namespace std;

// --- Type Definitions ---
struct TreeNode{
	int val;
	TreeNode* left;
	TreeNode* right;

	// Constructor initializes the node with a value and sets left and right children to nullptr
	explicit TreeNode(const int v) : val(v), left(nullptr), right(nullptr) {}
};

static vector<vector<int>> zigzagLevelOrder(TreeNode* root){
	vector<vector<int>> ans;

	if (root == nullptr)
		return ans;

	queue<TreeNode*> q;
	q.push(root);

	bool left_to_right = true;

	while (!q.empty()){
		size_t level_size = q.size();
		vector<int> current_level(level_size);

		for (size_t i = 0; i < level_size; i++){
			TreeNode* current_node = q.front();
			q.pop();

			size_t idx = left_to_right ? i : (level_size - i - 1);
			current_level[idx] = current_node->val;

			if (current_node->left != nullptr)
				q.push(current_node->left);

			if (current_node->right != nullptr)
				q.push(current_node->right);
		}

		ans.emplace_back(std::move(current_level));
		left_to_right = !left_to_right;
	}

	return ans;
}

// Function to build a binary tree from a vector of values (for testing purposes)
TreeNode* buildTree(const vector<int>& values){
	int n = values.size();

	// Edge case: empty tree or root is null
	if (n == 0 || values[0] == -1)
		return nullptr;

	TreeNode* root = new TreeNode(values[0]);

	queue<TreeNode*> q;
	q.push(root);

	int idx = 1;
	while (!q.empty() && idx < n){
		TreeNode* current = q.front();
		q.pop();

		// Left child
		if (idx < n && values[idx] != -1){
			current->left = new TreeNode(values[idx]);
            q.push(current->left);
		}

		// Move to the next index for the right child
		idx++;

		// Right child
		if (idx < n && values[idx] != -1){
			current->right = new TreeNode(values[idx]);
			q.push(current->right);
		}

		idx++;
	}

	return root;
}

// Function to print traversal result
static void printTraversal(const vector<int>& traversal){
	cout << "[";
	for (size_t i = 0; i < traversal.size(); ++i){
		cout << traversal[i];
        if (i < traversal.size() - 1)
            cout << " ";
	}
	cout << "]\n";
}

static void solve(){
	int n;
	cout << "Enter number of nodes in the tree: ";
	cin >> n;

	vector<int> values(n);
	cout << "Enter the values of the nodes (space-separated): ";
	for (int& val : values)
		cin >> val;

	// Print original tree values
	cout << "Original tree values: [";
	for (size_t i = 0; i < values.size(); ++i){
		cout << values[i];
        if (i < values.size() - 1)
            cout << " ";
	}
	cout << "]\n";

	// Build the binary tree from the input values
	TreeNode* root = buildTree(values);

	// Approach 1: Level Order Traversal (BFS) with Reversal
	vector<vector<int>> bfs_result = levelOrderBottom(root);
	cout << "BFS Level Order Traversal (grouped by levels):\n[";
	for (size_t i = 0; i < bfs_result.size(); ++i){
		cout << "[";
		for (size_t j = 0; j < bfs_result[i].size(); ++j){
			cout << bfs_result[i][j];
			if (j < bfs_result[i].size() - 1)
				cout << " ";
		}
		cout << "]";
		if (i < bfs_result.size() - 1)
			cout << ", ";
	}
	cout << "]\n";

	// Approach 2: Using Depth-First Search (DFS) with Level Tracking
	vector<vector<int>> resultDFS = levelOrderBottomUseDFS(root);
	cout << "DFS Level Order Traversal (grouped by levels):\n[";
	for (size_t i = 0; i < resultDFS.size(); ++i){
		cout << "[";
        for (size_t j = 0; j < resultDFS[i].size(); ++j){
            cout << resultDFS[i][j];
            if (j < resultDFS[i].size() - 1)
                cout << " ";
        }
        cout << "]";
        if (i < resultDFS.size() - 1)
            cout << ", ";
	}
	cout << "]\n";
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}