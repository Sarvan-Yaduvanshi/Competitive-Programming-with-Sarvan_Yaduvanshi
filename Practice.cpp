#include <iostream>
#include <vector>
using namespace std;

#include "../00_Tree_Utilities/01_BinaryTree.h"
#include "../00_Tree_Utilities/02_Print_BinaryTree.h"

/*
 * Definition for a binary tree node.
 * struct TreeNode {
 *   int val;
 *   TreeNode *left;
 *   TreeNode *right;
 *   TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:

};

static void solve(){
	int n;
	cout << "Enter number of nodes in the tree: ";
	cin >> n;

	vector<int> values(n);
	cout << "Enter the values of the nodes (space-separated): ";
	for (int& val : values)
		cin >> val;

	TreeNode* root = buildTree(values);
	TreeVisualization::printTree(root);

	// Approach 1: Calculate maximum width using BFS
	const int maxWidthBFS = Solution::widthOfBinaryTreeUseBFS(root);
	cout << "Maximum Width of Binary Tree (BFS): " << maxWidthBFS << "\n";

	// Approach 2: Calculate maximum width using DFS
	const int maxWidthDFS = Solution::widthOfBinaryTreeUseDFS(root);
	cout << "Maximum Width of Binary Tree (DFS): " << maxWidthDFS << "\n";
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}