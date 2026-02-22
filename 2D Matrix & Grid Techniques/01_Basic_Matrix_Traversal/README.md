# 📐 Basic Matrix Traversal — Zero to GM Mastery

> **Author:** Sarvan Yaduvanshi  
> **Language:** C++ (Competitive Programming Style)  
> **Topics:** 14 Files covering ALL Matrix Traversal Concepts

---

## 📁 File Structure

| # | File | Topics Covered | Level |
|---|------|---------------|-------|
| 01 | `01_Matrix_Basics.cpp` | Declaration, Initialization, I/O, Memory Layout, Direction Arrays | 0→2 |
| 02 | `02_Row_Wise_Traversal.cpp` | L→R, R→L, Bottom-Up, Even/Odd Rows, Row Aggregation, Flatten | 0→5 |
| 03 | `03_Column_Wise_Traversal.cpp` | T→B, B→T, R→L Columns, All 4 Combos, Cache Performance | 0→4 |
| 04 | `04_Boundary_Traversal.cpp` | Clockwise/Anti-CW Boundary, Sum, Edge Cases (1×1, 1×N) | 0→5 |
| 05 | `05_Snake_Zigzag_Traversal.cpp` | Row Zigzag, Column Zigzag, Snake Index Mapping, Grid Shift | 0→5 |
| 06 | `06_Transpose_Matrix.cpp` | In-Place, Extra Space, Rectangular, Symmetric/Skew Check | 0→5 |
| 07 | `07_Matrix_Search_Techniques.cpp` | Linear, Binary, Staircase (LC #74, #240), Peak, Kth Smallest | 0→7 |
| 08 | `08_Matrix_Rotation.cpp` | 90° CW/CCW, 180°, 270°, 4-Way Swap, Rectangular, LC #48 | 0→6 |
| 09 | `09_Spiral_Matrix_Traversal.cpp` | Spiral Order, Generation, Anti-CW, Inside-Out (LC #54, #59, #885) | 0→6 |
| 10 | `10_Diagonal_Traversal.cpp` | Primary, Anti, All Diagonals, Zigzag (LC #498, #1424, #1572) | 0→7 |
| 11 | `11_Matrix_Layer_Ring_Traversal.cpp` | Ring Extraction, Ring Rotation (LC #1914), Ring Aggregation | 0→5 |
| 12 | `12_Flood_Fill_DFS_BFS_Grid.cpp` | DFS/BFS, Flood Fill, Islands, Rotting Oranges (LC #200, #994, #1091) | 0→8 |
| 13 | `13_Prefix_Sum_2D_Matrix.cpp` | 2D Prefix Sum, Submatrix Query, Diff Array, 2D Kadane (LC #304, #1074) | 0→7 |
| 14 | `14_Advanced_GM_Level_Patterns.cpp` | Saddle Point, Toeplitz, Magic Square, Sparse, Game of Life, GM Cheat Sheet | 5→9 |

---

## 🗺️ Concept Map

```
                    Matrix Traversal
                         │
          ┌──────────────┼──────────────┐
          │              │              │
     Basic Traversal  Pattern-Based  Algorithm-Based
          │              │              │
    ┌─────┼─────┐    ┌───┼───┐    ┌────┼────┐
    │     │     │    │   │   │    │    │    │
  Row   Col  Bound Spiral Diag Snake DFS  2D-PS
  Wise  Wise ary         nal  Zig  BFS  Prefix
                                   │    Sum
                              ┌────┼────┐
                              │    │    │
                           Flood Islands Shortest
                           Fill         Path
```

---

## 🔑 Key Formulas & Patterns

### Direction Arrays (Most Used Pattern!)
```cpp
// 4-directional
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// 8-directional  
int dx[] = {-1,-1,-1,0,0,1,1,1};
int dy[] = {-1,0,1,-1,1,-1,0,1};
```

### Index Mappings
| Mapping | Formula |
|---------|---------|
| 2D → 1D (row-major) | `idx = i * M + j` |
| 1D → 2D | `i = idx / M, j = idx % M` |
| Transpose | `mat[i][j] ↔ mat[j][i]` |
| 90° CW | `(i,j) → (j, N-1-i)` |
| 90° CCW | `(i,j) → (N-1-j, i)` |
| 180° | `(i,j) → (N-1-i, N-1-j)` |
| Layer/Ring # | `min(i, j, N-1-i, M-1-j)` |
| Same primary diagonal | `i - j = constant` |
| Same anti-diagonal | `i + j = constant` |

### 2D Prefix Sum
```
Build: pre[i][j] = mat[i][j] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1]
Query: sum(r1,c1,r2,c2) = pre[r2][c2] - pre[r1-1][c2] - pre[r2][c1-1] + pre[r1-1][c1-1]
```

---

## 📝 LeetCode Problems Covered

| Problem | File | Technique |
|---------|------|-----------|
| LC #48 - Rotate Image | 08 | Transpose + Reverse |
| LC #54 - Spiral Matrix | 09 | 4-Pointer Boundary |
| LC #59 - Spiral Matrix II | 09 | Spiral Generation |
| LC #73 - Set Matrix Zeroes | 14 | First Row/Col as Markers |
| LC #74 - Search 2D Matrix | 07 | Binary Search O(log NM) |
| LC #130 - Surrounded Regions | 12 | Border DFS |
| LC #200 - Number of Islands | 12 | DFS/BFS Components |
| LC #240 - Search 2D Matrix II | 07 | Staircase O(N+M) |
| LC #289 - Game of Life | 14 | Bit Encoding |
| LC #304 - Range Sum Query 2D | 13 | 2D Prefix Sum |
| LC #378 - Kth Smallest Sorted Matrix | 07 | Binary Search on Value |
| LC #498 - Diagonal Traverse | 10 | Anti-diagonal Zigzag |
| LC #695 - Max Area Island | 12 | DFS Area Count |
| LC #733 - Flood Fill | 12 | DFS Color Fill |
| LC #766 - Toeplitz Matrix | 14 | Diagonal Property |
| LC #885 - Spiral Matrix III | 09 | Outward Spiral |
| LC #994 - Rotting Oranges | 12 | Multi-source BFS |
| LC #1074 - Submatrix Sum Target | 13 | 2D Prefix + HashMap |
| LC #1091 - Shortest Path Binary Matrix | 12 | BFS 8-dir |
| LC #1260 - Shift 2D Grid | 05 | Flatten + Rotate |
| LC #1351 - Count Negatives | 07 | Staircase |
| LC #1380 - Lucky Numbers | 14 | Row Min + Col Max |
| LC #1424 - Diagonal Traverse II | 10 | Anti-diag Grouping |
| LC #1572 - Matrix Diagonal Sum | 10 | Primary + Secondary |
| LC #1886 - Rotation Check | 08 | Try All 4 Rotations |
| LC #1914 - Cyclically Rotating Grid | 11 | Ring Rotation |

---

## 🚀 How to Compile & Run

```bash
# Single file
g++ -std=c++17 -O2 01_Matrix_Basics.cpp -o run && ./run

# With all warnings
g++ -std=c++17 -O2 -Wall -Wextra filename.cpp -o run && ./run
```

---

## 💡 Complexity Summary

| Traversal Type | Time | Space |
|---------------|------|-------|
| Row/Col-wise | O(N×M) | O(1) |
| Boundary | O(N+M) | O(1) |
| Spiral | O(N×M) | O(1) |
| Diagonal (all) | O(N×M) | O(1) |
| Transpose (in-place) | O(N²) | O(1) |
| Rotation (in-place) | O(N²) | O(1) |
| DFS/BFS Grid | O(N×M) | O(N×M) |
| 2D Prefix Sum Build | O(N×M) | O(N×M) |
| 2D Prefix Sum Query | O(1) | O(1) |
| Binary Search 2D | O(log(NM)) | O(1) |
| Staircase Search | O(N+M) | O(1) |

---

*Happy Coding! 🏆 From Zero to GM — Master Every Matrix Pattern!*

