/*
 * ============================================================================
 *              🏆 CLASSICAL ARRAY CONCEPTS — MASTER PROBLEM CHEAT SHEET
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Level   : Zero to Grandmaster (GM)
 *  Total   : 100+ Curated Problems
 *
 *  FORMAT:
 *  [ ] Problem Name | Platform | Difficulty | Key Technique | Link
 *
 *  PLATFORMS: LC = LeetCode, CF = Codeforces, CSES = CSES Problem Set,
 *             GFG = GeeksForGeeks, CC = CodeChef
 *
 *  DIFFICULTY: E = Easy, M = Medium, H = Hard, EX = Expert, GM = GM-Level
 *  CF RATINGS: Approximate Codeforces problem ratings shown in parentheses
 *
 *  ✅ = Solved   ❌ = Not Solved   🔄 = Needs Revision
 * ============================================================================
 *
 * ╔══════════════════════════════════════════════════════════════════════════╗
 * ║            MODULE 01: STATIC ARRAY & VECTOR BASICS                       ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                          ║
 * ║ [ ] LC 1929  - Concatenation of Array          | E  | Vector Basics      ║
 * ║     https://leetcode.com/problems/concatenation-of-array/                ║
 * ║                                                                          ║
 * ║ [ ] LC 1920  - Build Array from Permutation    | E  | Index Mapping      ║
 * ║     https://leetcode.com/problems/build-array-from-permutation/          ║
 * ║                                                                          ║
 * ║ [ ] LC 1470  - Shuffle the Array               | E  | Interleave         ║
 * ║     https://leetcode.com/problems/shuffle-the-array/                     ║
 * ║                                                                          ║
 * ║ [ ] LC 1365  - How Many Numbers Smaller        | E  | Counting           ║
 * ║     https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/ ║
 * ║                                                                        ║
 * ║ [ ] CF 1742A - Sum                             | E  (800)  | Basics   ║
 * ║     https://codeforces.com/problemset/problem/1742/A                   ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║            MODULE 02: INPUT / OUTPUT PATTERNS                          ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] CF 71A   - Way Too Long Words              | E  (800)  | I/O      ║
 * ║     https://codeforces.com/problemset/problem/71/A                     ║
 * ║                                                                        ║
 * ║ [ ] CF 4A    - Watermelon                      | E  (800)  | I/O      ║
 * ║     https://codeforces.com/problemset/problem/4/A                      ║
 * ║                                                                        ║
 * ║ [ ] CSES 1068 - Weird Algorithm                | E  | I/O + Loop      ║
 * ║     https://cses.fi/problemset/task/1068                               ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║            MODULE 03: TRAVERSAL PATTERNS                               ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 1672  - Richest Customer Wealth         | E  | 2D Traversal    ║
 * ║     https://leetcode.com/problems/richest-customer-wealth/             ║
 * ║                                                                        ║
 * ║ [ ] LC 1431  - Kids with Greatest Candies      | E  | Traversal       ║
 * ║     https://leetcode.com/problems/kids-with-the-greatest-number-of-candies/ ║
 * ║                                                                        ║
 * ║ [ ] LC 2011  - Final Value After Operations    | E  | Traversal       ║
 * ║     https://leetcode.com/problems/final-value-of-variable-after-performing-operations/ ║
 * ║                                                                        ║
 * ║ [ ] LC 1480  - Running Sum of 1d Array         | E  | Prefix Traversal║
 * ║     https://leetcode.com/problems/running-sum-of-1d-array/             ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║            MODULE 04: SEARCHING IN ARRAY                               ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 704   - Binary Search                   | E  | Classic BinSrch ║
 * ║     https://leetcode.com/problems/binary-search/                       ║
 * ║                                                                        ║
 * ║ [ ] LC 35    - Search Insert Position           | E  | Lower Bound    ║
 * ║     https://leetcode.com/problems/search-insert-position/              ║
 * ║                                                                        ║
 * ║ [ ] LC 33    - Search in Rotated Sorted Array  | M  | Modified BinSrch║
 * ║     https://leetcode.com/problems/search-in-rotated-sorted-array/      ║
 * ║                                                                        ║
 * ║ [ ] LC 81    - Search in Rotated Sorted II     | M  | Duplicates      ║
 * ║     https://leetcode.com/problems/search-in-rotated-sorted-array-ii/   ║
 * ║                                                                        ║
 * ║ [ ] LC 34    - First & Last Position            | M  | Two BinSrch    ║
 * ║     https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/ ║
 * ║                                                                        ║
 * ║ [ ] LC 153   - Find Min in Rotated Sorted      | M  | BinSrch Variant║
 * ║     https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/║
 * ║                                                                        ║
 * ║ [ ] LC 162   - Find Peak Element               | M  | BinSrch on Ans ║
 * ║     https://leetcode.com/problems/find-peak-element/                   ║
 * ║                                                                        ║
 * ║ [ ] CSES 1621 - Distinct Numbers               | E  | Set / Sort     ║
 * ║     https://cses.fi/problemset/task/1621                               ║
 * ║                                                                        ║
 * ║ [ ] CF 1352B - Same Parity Summands            | E  (800)  | Search   ║
 * ║     https://codeforces.com/problemset/problem/1352/B                   ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║            MODULE 05: ARRAY ROTATION CONCEPTS                          ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 189   - Rotate Array                    | M  | Reversal Algo   ║
 * ║     https://leetcode.com/problems/rotate-array/                        ║
 * ║                                                                        ║
 * ║ [ ] GFG      - Rotate Array by K               | E  | Left Rotation   ║
 * ║     https://practice.geeksforgeeks.org/problems/rotate-array-by-n-elements/ ║
 * ║                                                                        ║
 * ║ [ ] LC 796   - Rotate String                   | E  | Concat Trick    ║
 * ║     https://leetcode.com/problems/rotate-string/                       ║
 * ║                                                                        ║
 * ║ [ ] CF 1798A - Showering                       | E  (800) | Rotation  ║
 * ║     https://codeforces.com/problemset/problem/1798/A                   ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║            MODULE 06: REVERSAL & REARRANGEMENT                         ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 283   - Move Zeroes                     | E  | Two Pointer     ║
 * ║     https://leetcode.com/problems/move-zeroes/                         ║
 * ║                                                                        ║
 * ║ [ ] LC 75    - Sort Colors (Dutch Flag)        | M  | Three-Way Part  ║
 * ║     https://leetcode.com/problems/sort-colors/                         ║
 * ║                                                                        ║
 * ║ [ ] LC 905   - Sort Array By Parity            | E  | Partition       ║
 * ║     https://leetcode.com/problems/sort-array-by-parity/                ║
 * ║                                                                        ║
 * ║ [ ] LC 922   - Sort Array By Parity II         | E  | Two Pointer     ║
 * ║     https://leetcode.com/problems/sort-array-by-parity-ii/             ║
 * ║                                                                        ║
 * ║ [ ] LC 977   - Squares of Sorted Array         | E  | Two Pointer     ║
 * ║     https://leetcode.com/problems/squares-of-a-sorted-array/           ║
 * ║                                                                        ║
 * ║ [ ] GFG      - Segregate 0s and 1s             | E  | Partition       ║
 * ║     https://practice.geeksforgeeks.org/problems/segregate-0s-and-1s/   ║
 * ║                                                                        ║
 * ║ [ ] LC 1968  - Array With Elements Not Equal   | M  | Rearrange       ║
 * ║     https://leetcode.com/problems/array-with-elements-not-equal-to-average-of-neighbors/ ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║            MODULE 07: SECOND LARGEST & KTH ELEMENT                     ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 215   - Kth Largest Element              | M  | Quickselect    ║
 * ║     https://leetcode.com/problems/kth-largest-element-in-an-array/     ║
 * ║                                                                        ║
 * ║ [ ] LC 347   - Top K Frequent Elements          | M  | Heap / Bucket  ║
 * ║     https://leetcode.com/problems/top-k-frequent-elements/             ║
 * ║                                                                        ║
 * ║ [ ] LC 414   - Third Maximum Number             | E  | Track Top 3    ║
 * ║     https://leetcode.com/problems/third-maximum-number/                ║
 * ║                                                                        ║
 * ║ [ ] GFG      - Second Largest                   | E  | Single Pass    ║
 * ║     https://practice.geeksforgeeks.org/problems/second-largest/        ║
 * ║                                                                        ║
 * ║ [ ] CSES 1640 - Sum of Two Values              | E  | Hash / 2-Ptr   ║
 * ║     https://cses.fi/problemset/task/1640                               ║
 * ║                                                                        ║
 * ║ [ ] LC 703   - Kth Largest in a Stream          | E  | Min Heap       ║
 * ║     https://leetcode.com/problems/kth-largest-element-in-a-stream/     ║
 * ║                                                                        ║
 * ║ [ ] CF 1512C - A-B Palindrome                   | M  (1200) | Order  ║
 * ║     https://codeforces.com/problemset/problem/1512/C                   ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║            MODULE 08: INDEX SHIFTING & MATH TRICKS                     ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 41    - First Missing Positive           | H  | Index Encoding ║
 * ║     https://leetcode.com/problems/first-missing-positive/              ║
 * ║                                                                        ║
 * ║ [ ] LC 442   - Find All Duplicates in Array     | M  | Sign Marking   ║
 * ║     https://leetcode.com/problems/find-all-duplicates-in-an-array/     ║
 * ║                                                                        ║
 * ║ [ ] LC 448   - Find Disappeared Numbers         | E  | Index Marking  ║
 * ║     https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/ ║
 * ║                                                                        ║
 * ║ [ ] LC 287   - Find the Duplicate Number        | M  | Cycle Detection║
 * ║     https://leetcode.com/problems/find-the-duplicate-number/           ║
 * ║                                                                        ║
 * ║ [ ] LC 1920  - Build Array from Permutation     | E  | In-place Encode║
 * ║     https://leetcode.com/problems/build-array-from-permutation/        ║
 * ║                                                                        ║
 * ║ [ ] CF 1352C - K-th Not Divisible              | E  (1200) | Math     ║
 * ║     https://codeforces.com/problemset/problem/1352/C                   ║
 * ║                                                                        ║
 * ║ [ ] LC 268   - Missing Number                   | E  | XOR / Math     ║
 * ║     https://leetcode.com/problems/missing-number/                      ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║            MODULE 09: ADVANCED REARRANGEMENT                           ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 31    - Next Permutation                 | M  | Permutation    ║
 * ║     https://leetcode.com/problems/next-permutation/                    ║
 * ║                                                                        ║
 * ║ [ ] LC 169   - Majority Element                 | E  | Boyer-Moore    ║
 * ║     https://leetcode.com/problems/majority-element/                    ║
 * ║                                                                        ║
 * ║ [ ] LC 229   - Majority Element II              | M  | Extended B-M   ║
 * ║     https://leetcode.com/problems/majority-element-ii/                 ║
 * ║                                                                        ║
 * ║ [ ] LC 121   - Best Time to Buy and Sell Stock  | E  | Track Min      ║
 * ║     https://leetcode.com/problems/best-time-to-buy-and-sell-stock/     ║
 * ║                                                                        ║
 * ║ [ ] LC 122   - Best Time Buy Sell II            | M  | Greedy         ║
 * ║     https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/  ║
 * ║                                                                        ║
 * ║ [ ] GFG      - Leaders in an Array             | E  | Right Scan     ║
 * ║     https://practice.geeksforgeeks.org/problems/leaders-in-an-array/   ║
 * ║                                                                        ║
 * ║ [ ] LC 724   - Find Pivot Index                 | E  | Prefix Sum     ║
 * ║     https://leetcode.com/problems/find-pivot-index/                    ║
 * ║                                                                        ║
 * ║ [ ] LC 46    - Permutations                     | M  | Backtracking   ║
 * ║     https://leetcode.com/problems/permutations/                        ║
 * ║                                                                        ║
 * ║ [ ] CF 1579C - Ticks                           | M  (1500) | Pattern  ║
 * ║     https://codeforces.com/problemset/problem/1579/C                   ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║            MODULE 10: MERGE & PARTITION TECHNIQUES                     ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 88    - Merge Sorted Array               | E  | Two Pointer    ║
 * ║     https://leetcode.com/problems/merge-sorted-array/                  ║
 * ║                                                                        ║
 * ║ [ ] LC 912   - Sort an Array                    | M  | Merge Sort     ║
 * ║     https://leetcode.com/problems/sort-an-array/                       ║
 * ║                                                                        ║
 * ║ [ ] GFG      - Merge Without Extra Space        | H  | Gap Method     ║
 * ║     https://practice.geeksforgeeks.org/problems/merge-two-sorted-arrays/ ║
 * ║                                                                        ║
 * ║ [ ] LC 148   - Sort List                        | M  | Merge Sort     ║
 * ║     https://leetcode.com/problems/sort-list/                           ║
 * ║                                                                        ║
 * ║ [ ] LC 4     - Median of Two Sorted Arrays      | H  | Binary Merge   ║
 * ║     https://leetcode.com/problems/median-of-two-sorted-arrays/         ║
 * ║                                                                        ║
 * ║ [ ] CSES 1091 - Concert Tickets                | M  | Multiset Merge ║
 * ║     https://cses.fi/problemset/task/1091                               ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║            EXISTING: MAX/MIN, PAIRS, SUBARRAY, HASHING                 ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] GFG      - Max and Min in Array            | E  | Tournament      ║
 * ║     https://practice.geeksforgeeks.org/problems/find-minimum-and-maximum-element-in-an-array/ ║
 * ║                                                                        ║
 * ║ [ ] LC 53    - Maximum Subarray (Kadane's)     | M  | Kadane's Algo   ║
 * ║     https://leetcode.com/problems/maximum-subarray/                    ║
 * ║                                                                        ║
 * ║ [ ] LC 152   - Maximum Product Subarray        | M  | Track Min/Max  ║
 * ║     https://leetcode.com/problems/maximum-product-subarray/            ║
 * ║                                                                        ║
 * ║ [ ] LC 1    - Two Sum                           | E  | HashMap         ║
 * ║     https://leetcode.com/problems/two-sum/                             ║
 * ║                                                                        ║
 * ║ [ ] LC 15   - 3Sum                              | M  | Sort + 2-Ptr   ║
 * ║     https://leetcode.com/problems/3sum/                                ║
 * ║                                                                        ║
 * ║ [ ] LC 18   - 4Sum                              | M  | Sort + 2-Ptr   ║
 * ║     https://leetcode.com/problems/4sum/                                ║
 * ║                                                                        ║
 * ║ [ ] LC 560  - Subarray Sum Equals K             | M  | Prefix + Hash  ║
 * ║     https://leetcode.com/problems/subarray-sum-equals-k/               ║
 * ║                                                                        ║
 * ║ [ ] LC 974  - Subarray Sums Divisible by K     | M  | Modular Hash   ║
 * ║     https://leetcode.com/problems/subarray-sums-divisible-by-k/        ║
 * ║                                                                        ║
 * ║ [ ] LC 128  - Longest Consecutive Sequence      | M  | HashSet        ║
 * ║     https://leetcode.com/problems/longest-consecutive-sequence/        ║
 * ║                                                                        ║
 * ║ [ ] LC 238  - Product of Array Except Self      | M  | Prefix/Suffix  ║
 * ║     https://leetcode.com/problems/product-of-array-except-self/        ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║            BONUS: GM-LEVEL ARRAY PROBLEMS                              ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] CF 1305C - Kuroni and Impossible Calc      | M  (1600) | Pigeon   ║
 * ║     https://codeforces.com/problemset/problem/1305/C                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1367D - Task Distribution                | M  (1700) | Greedy  ║
 * ║     https://codeforces.com/problemset/problem/1367/D                   ║
 * ║                                                                        ║
 * ║ [ ] LC 42   - Trapping Rain Water               | H  | Two Pointer    ║
 * ║     https://leetcode.com/problems/trapping-rain-water/                 ║
 * ║                                                                        ║
 * ║ [ ] LC 84   - Largest Rectangle in Histogram    | H  | Stack          ║
 * ║     https://leetcode.com/problems/largest-rectangle-in-histogram/      ║
 * ║                                                                        ║
 * ║ [ ] LC 239  - Sliding Window Maximum            | H  | Deque          ║
 * ║     https://leetcode.com/problems/sliding-window-maximum/              ║
 * ║                                                                        ║
 * ║ [ ] CF 1744D - Divisibility by 2^n             | M  (1200) | Greedy   ║
 * ║     https://codeforces.com/problemset/problem/1744/D                   ║
 * ║                                                                        ║
 * ║ [ ] CSES 1643 - Maximum Subarray Sum           | E  | Kadane's        ║
 * ║     https://cses.fi/problemset/task/1643                               ║
 * ║                                                                        ║
 * ║ [ ] CSES 1644 - Maximum Subarray Sum II        | H  | Deque + PreSum ║
 * ║     https://cses.fi/problemset/task/1644                               ║
 * ║                                                                        ║
 * ╚══════════════════════════════════════════════════════════════════════════╝
 *
 * ============================================================================
 *                    QUICK REFERENCE BY TECHNIQUE
 * ============================================================================
 *
 *  🔹 Two Pointer      : LC 283, 75, 88, 977, 167, 15
 *  🔹 Binary Search     : LC 704, 33, 34, 35, 153, 162, 4
 *  🔹 Kadane's          : LC 53, 152, 918, CSES 1643
 *  🔹 Prefix Sum        : LC 560, 974, 724, 238
 *  🔹 Hashing           : LC 1, 128, 442, 448, 287
 *  🔹 Index Tricks      : LC 41, 442, 448, 1920, 268
 *  🔹 Sorting           : LC 75, 215, 912, 347
 *  🔹 Rotation          : LC 189, 796, 33, 81, 153
 *  🔹 Permutation       : LC 31, 46, 47
 *  🔹 Stack-based       : LC 42, 84, 239
 *
 * ============================================================================
 */

