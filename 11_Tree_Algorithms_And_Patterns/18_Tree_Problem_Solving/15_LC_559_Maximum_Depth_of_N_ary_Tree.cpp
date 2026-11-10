/*
Author: Sarvan Yaduvanshi
Created : 2026-11-08 05:29:56
*/

/*
 * ============================================================================
 *  559. Maximum Depth of N-ary Tree
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 559
 *  Difficulty : Easy
 *  Topics     : Tree, Depth-First Search, Breadth-First Search
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given a n-ary tree, find its maximum depth.
 *
 *  The maximum depth is the number of nodes along the longest path from the
 *  root node down to the farthest leaf node.
 *
 *  Nary-Tree input serialization is represented in their level order
 *  traversal, each group of children is separated by the null value
 *  (See examples).
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                  1                Level 1 (depth 1)
 *                / | \
 *               3  2  4             Level 2 (depth 2)
 *              / \
 *             5   6                 Level 3 (depth 3)
 *
 *      Longest path : 1 -> 3 -> 5   (3 nodes)
 *
 *  Input  : root = [1,null,3,2,4,null,5,6]
 *  Output : 3
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *                       1                      depth 1
 *                 /   /   \   \
 *                2   3     4   5               depth 2
 *                   / \    |   / \
 *                  6   7   8   9  10           depth 3
 *                      |   |   |
 *                     11  12  13               depth 4
 *                      |
 *                     14                       depth 5
 *
 *      Longest path : 1 -> 3 -> 7 -> 11 -> 14   (5 nodes)
 *
 *  Input  : root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,
 *                   null,11,null,12,null,13,null,null,14]
 *  Output : 5
 *
 * ----------------------------------------------------------------------------
 *  How to read the serialization (Example 1):
 *
 *      [1, null, 3, 2, 4, null, 5, 6]
 *       ^   ^    ^------^   ^    ^--^
 *       |   |    children   |    children of 3
 *       |   |    of 1       |
 *       |   |               end of the group of 1
 *       |   end of root (root has no siblings)
 *       root
 *
 *      Rule: after the root, each group of children is closed by null.
 *            Groups come in level order: group of 1, then group of 3,
 *            then group of 2, then group of 4, ...
 *            A node with no children gives an empty group (just null).
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The total number of nodes is in the range [0, 10^4].
 *      - The depth of the n-ary tree is less than or equal to 1000.
 * ============================================================================
 */