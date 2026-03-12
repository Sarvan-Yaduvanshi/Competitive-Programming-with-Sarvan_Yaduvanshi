/*
╔══════════════════════════════════════════════════════════════════╗
║  03 — PATH QUERIES WITH EULER TOUR + LCA (CSES Path Queries)   ║
║  Zero to GM Level — Euler Tour Techniques                        ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CONCEPT: Path sum(u,v) via root-to-node prefix sums
═══════════════════════════════════════════════════════════════════

 Trick: Use Euler tour with +val at entry, -val at exit.
 BIT prefix sum at tin[v] gives root_to_v sum.

 path_sum(u,v) = root_to_u + root_to_v - 2·root_to_LCA + val[LCA]

 DRY RUN:
   Tree: val = [_, 4, 2, 5, 1, 3]
          4(1)
         /    \
       2(2)   5(3)
       / \
     1(4) 3(5)

   root_to_4 = 4+2+1 = 7
   root_to_5 = 4+2+3 = 9
   LCA(4,5) = 2, root_to_2 = 4+2 = 6
   path(4,5) = 7 + 9 - 2·6 + 2 = 7+9-12+2 = 6
   Verify: 1+2+3 = 6 ✅

═══════════════════════════════════════════════════════════════════
 This file uses the same approach as Ch14 file 01.
 See 14_Advanced_Tree_Queries/01_Subtree_And_Path_Queries.cpp
 for the full implementation with BIT.
═══════════════════════════════════════════════════════════════════

 Time: O(N log N) build, O(log N) per query/update
 Space: O(N log N)

 KEY FORMULA:
   path_sum(u, v) = prefix(tin[u]) + prefix(tin[v])
                   - 2 * prefix(tin[LCA(u,v)]) + val[LCA(u,v)]

 Where prefix(i) = BIT query giving root-to-node sum.
*/

// See 14_Advanced_Tree_Queries/01_Subtree_And_Path_Queries.cpp for code.
// This file serves as the conceptual bridge between Euler Tour and Path Queries.

int main() { return 0; }

