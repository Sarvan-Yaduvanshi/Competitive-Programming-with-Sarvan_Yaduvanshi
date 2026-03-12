# 08 — Tree DP

## What You'll Learn
- Tree DP foundations — process via DFS bottom-up
- Tree Diameter (two longest paths through each node)
- House Robber III / Max Independent Set on tree
- Vertex Cover on tree
- Tree Coloring DP
- Maximum Matching in tree
- **Rerooting DP** — compute answer for EVERY node as root in O(n)
- Sum of Distances (LeetCode 834)
- Tree Painting (CF 1187E)

## Files
| File | Topics Covered |
|------|---------------|
| `01_Tree_DP_Foundations.cpp` | Diameter, Independent Set, Vertex Cover, Coloring, Matching, Rerooting (sum of distances) |
| `02_Rerooting_DP.cpp` | Detailed rerooting: Sum of Distances, Max Subtree Sum, Tree Painting |

## Key Pattern
```
dp[node] depends on dp[children]
Process: DFS bottom-up (leaves → root)
Rerooting: 2 DFS passes (down + up)
```

## Practice Problems
- LeetCode: 337, 124, 834, 543
- CSES: Tree Diameter, Tree Distances I/II
- AtCoder DP: P (Independent Set), V (Subtree)
- CF: 1187E (Tree Painting)

