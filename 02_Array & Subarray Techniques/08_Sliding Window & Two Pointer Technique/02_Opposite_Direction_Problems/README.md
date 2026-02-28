# Module 02: Opposite Direction Problems (2Sum → KSum, Trapping Rain Water, Greedy)

> **Level:** ⭐⭐ Intermediate  
> **Prerequisites:** Module 01 — Two Pointer Fundamentals

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_Two_Sum_All_Versions.cpp` | Two Sum (Unsorted, Sorted, BST, Data Structure, Less Than K) | Easy-Medium |
| 2 | `02_Three_Sum_And_Variants.cpp` | 3Sum, 3Sum Closest, 3Sum Smaller, 3Sum Multiplicity | Medium |
| 3 | `03_Four_Sum_And_KSum.cpp` | 4Sum, 4Sum II, General K-Sum Recursive Framework | Medium-Hard |
| 4 | `04_Container_With_Most_Water.cpp` | LC 11: Greedy converging pointer proof | Medium |
| 5 | `05_Trapping_Rain_Water_All_Versions.cpp` | 1D (Prefix, Two Pointer, Stack), 2D (BFS+Heap) | Medium-Hard |
| 6 | `06_Boats_Tokens_Greedy_Two_Pointer.cpp` | Boats to Save People, Bag of Tokens, Merge to Palindrome | Medium |
| 7 | `07_Sorted_Squares_Triangle_Subsequences.cpp` | Sorted Squares, Reverse String, Assign Cookies, Valid Triangle, Subsequences Sum, CSES Two Sum | Easy-Medium |

## Key Takeaways
- **2Sum sorted** = converging two pointer O(N)
- **3Sum** = fix one + two pointer on rest O(N²)
- **4Sum** = fix two + two pointer on rest O(N³)
- **KSum** = recursive: fix one, solve (K-1)Sum
- **Trapping Rain Water** = `min(leftMax, rightMax) - height[i]`
- **Sorted Squares** = opposite direction merge (largest at ends)
- **Valid Triangle** = fix largest side, two pointer for other two
- **Subsequences** = sort + 2Ptr + 2^(right-left) counting
- Always **skip duplicates** after finding a valid tuple
