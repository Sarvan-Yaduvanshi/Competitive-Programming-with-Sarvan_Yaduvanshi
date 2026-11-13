/*
Author: Sarvan Yaduvanshi
Created : 2026-11-11 18:59:09
*/

/*
 * ============================================================================
 *  110. Balanced Binary Tree
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 110
 *  Difficulty : Easy
 *  Topics     : Tree, Depth-First Search, Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given a binary tree, determine if it is height-balanced.
 *
 *  (A height-balanced binary tree is a binary tree in which the depth of
 *  the two subtrees of EVERY node never differs by more than one.)
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                3                height 3
 *               / \
 *              9   20             9: h=1 | 20: h=2
 *                 /  \
 *                15   7           15: h=1, 7: h=1
 *
 *      Node 3  : left h=1, right h=2  -> diff 1  OK
 *      Node 20 : left h=1, right h=1  -> diff 0  OK
 *
 *  Input  : root = [3,9,20,null,null,15,7]
 *  Output : true
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *                  1
 *                /   \
 *               2     2
 *              / \
 *             3   3
 *            / \
 *           4   4
 *
 *      Node 1 : left h=4 (2 -> 3 -> 4), right h=1  -> diff 3  BAD
 *      Node 2 (left one) : left h=3, right h=1     -> diff 2  BAD
 *
 *  Input  : root = [1,2,2,3,3,null,null,4,4]
 *  Output : false
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      (empty tree)
 *
 *  Input  : root = []
 *  Output : true
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree is in the range [0, 5000].
 *      - -10^4 <= Node.val <= 10^4
 * ============================================================================
 */