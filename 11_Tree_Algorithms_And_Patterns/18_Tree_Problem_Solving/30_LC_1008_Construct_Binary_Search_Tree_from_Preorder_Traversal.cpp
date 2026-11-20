/*
Author: Sarvan Yaduvanshi
Created : 2026-11-15 17:54:31
*/

/*
 * ============================================================================
 *  1008. Construct Binary Search Tree from Preorder Traversal
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 1008
 *  Difficulty : Medium
 *  Topics     : Array, Stack, Tree, Binary Search Tree, Monotonic Stack,
 *               Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given an array of integers preorder, which represents the preorder
 *  traversal of a BST (i.e., binary search tree), construct the tree and
 *  return its root.
 *
 *  It is guaranteed that there is always possible to find a binary search
 *  tree with the given requirements for the given test cases.
 *
 *  A binary search tree is a binary tree where for every node, any
 *  descendant of Node.left has a value strictly less than Node.val, and any
 *  descendant of Node.right has a value strictly greater than Node.val.
 *
 *  A preorder traversal of a binary tree displays the value of the node
 *  first, then traverses Node.left, then traverses Node.right.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      preorder : [8, 5, 1, 7, 10, 12]
 *
 *      Built tree:
 *
 *                  8
 *                /   \
 *               5     10
 *              / \      \
 *             1   7      12
 *
 *      How it splits:
 *          8 is the ROOT (first item).
 *          Values < 8  : [5, 1, 7]  -> left subtree
 *          Values > 8  : [10, 12]   -> right subtree
 *
 *  Input  : preorder = [8,5,1,7,10,12]
 *  Output : [8,5,10,1,7,null,12]
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      preorder : [1, 3]
 *
 *      Built tree:
 *
 *          1
 *           \
 *            3
 *
 *      3 > 1, so 3 goes to the RIGHT of 1.
 *
 *  Input  : preorder = [1,3]
 *  Output : [1,null,3]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= preorder.length <= 100
 *      - 1 <= preorder[i] <= 1000
 *      - All the values of preorder are unique.
 * ============================================================================
 */