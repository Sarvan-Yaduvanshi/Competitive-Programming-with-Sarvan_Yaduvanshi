/*
 * ============================================================================
 *        🏆 TWO POINTER & SLIDING WINDOW — MASTER PROBLEM CHEAT SHEET
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Level   : Zero to Grandmaster (GM)
 *  Total   : 200+ Curated Problems
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
 *
 * ╔══════════════════════════════════════════════════════════════════════════════╗
 * ║           SECTION A: TWO POINTER TECHNIQUE (MODULES 01-07)                ║
 * ╠══════════════════════════════════════════════════════════════════════════════╣
 * ║                                                                            ║
 * ║  ─────────── MODULE 01: TWO POINTER FUNDAMENTALS ───────────               ║
 * ║                                                                            ║
 * ║ [ ] LC 167  - Two Sum II (Sorted)              | E  | Converging 2Ptr     ║
 * ║     https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/        ║
 * ║                                                                            ║
 * ║ [ ] LC 344  - Reverse String                   | E  | Converging Swap     ║
 * ║     https://leetcode.com/problems/reverse-string/                          ║
 * ║                                                                            ║
 * ║ [ ] LC 977  - Squares of a Sorted Array        | E  | Converging Fill     ║
 * ║     https://leetcode.com/problems/squares-of-a-sorted-array/               ║
 * ║                                                                            ║
 * ║ [ ] LC 283  - Move Zeroes                      | E  | Same Direction      ║
 * ║     https://leetcode.com/problems/move-zeroes/                             ║
 * ║                                                                            ║
 * ║ [ ] LC 26   - Remove Duplicates Sorted Array   | E  | Reader-Writer       ║
 * ║     https://leetcode.com/problems/remove-duplicates-from-sorted-array/     ║
 * ║                                                                            ║
 * ║ [ ] LC 27   - Remove Element                   | E  | Reader-Writer       ║
 * ║     https://leetcode.com/problems/remove-element/                          ║
 * ║                                                                            ║
 * ║ [ ] LC 88   - Merge Sorted Array               | E  | Same Dir Merge      ║
 * ║     https://leetcode.com/problems/merge-sorted-array/                      ║
 * ║                                                                            ║
 * ║ [ ] GFG     - Two Pointer Intro                | E  | Basic 2 Pointer     ║
 * ║     https://practice.geeksforgeeks.org/problems/two-pointer-technique/     ║
 * ║                                                                            ║
 * ║ [ ] CF 1352A - Sum of Round Numbers            | E  (800)  | Basic        ║
 * ║     https://codeforces.com/problemset/problem/1352/A                       ║
 * ║                                                                            ║
 * ║                                                                            ║
 * ║  ─────────── MODULE 02: OPPOSITE DIRECTION PROBLEMS ───────────            ║
 * ║                                                                            ║
 * ║ [ ] LC 1    - Two Sum                          | E  | HashMap (Compare)    ║
 * ║     https://leetcode.com/problems/two-sum/                                 ║
 * ║                                                                            ║
 * ║ [ ] LC 167  - Two Sum II (Sorted)              | M  | Converging 2Ptr     ║
 * ║     https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/        ║
 * ║                                                                            ║
 * ║ [ ] LC 15   - 3Sum                             | M  | Sort + 2Ptr         ║
 * ║     https://leetcode.com/problems/3sum/                                    ║
 * ║                                                                            ║
 * ║ [ ] LC 16   - 3Sum Closest                     | M  | Sort + 2Ptr         ║
 * ║     https://leetcode.com/problems/3sum-closest/                            ║
 * ║                                                                            ║
 * ║ [ ] LC 259  - 3Sum Smaller                     | M  | Sort + 2Ptr Count   ║
 * ║     https://leetcode.com/problems/3sum-smaller/                            ║
 * ║                                                                            ║
 * ║ [ ] LC 18   - 4Sum                             | M  | Sort + Nested 2Ptr  ║
 * ║     https://leetcode.com/problems/4sum/                                    ║
 * ║                                                                            ║
 * ║ [ ] LC 454  - 4Sum II                          | M  | HashMap Split       ║
 * ║     https://leetcode.com/problems/4sum-ii/                                 ║
 * ║                                                                            ║
 * ║ [ ] LC 11   - Container With Most Water        | M  | Converging Greedy   ║
 * ║     https://leetcode.com/problems/container-with-most-water/               ║
 * ║                                                                            ║
 * ║ [ ] LC 42   - Trapping Rain Water              | H  | 2Ptr / PrefixMax    ║
 * ║     https://leetcode.com/problems/trapping-rain-water/                     ║
 * ║                                                                            ║
 * ║ [ ] LC 407  - Trapping Rain Water II (3D)      | H  | BFS + MinHeap       ║
 * ║     https://leetcode.com/problems/trapping-rain-water-ii/                  ║
 * ║                                                                            ║
 * ║ [ ] LC 948  - Bag of Tokens                    | M  | Sort + 2Ptr Greedy  ║
 * ║     https://leetcode.com/problems/bag-of-tokens/                           ║
 * ║                                                                            ║
 * ║ [ ] LC 881  - Boats to Save People             | M  | Sort + 2Ptr Greedy  ║
 * ║     https://leetcode.com/problems/boats-to-save-people/                    ║
 * ║                                                                            ║
 * ║ [ ] LC 923  - 3Sum With Multiplicity           | M  | Sort + 2Ptr + Math  ║
 * ║     https://leetcode.com/problems/3sum-with-multiplicity/                  ║
 * ║                                                                            ║
 * ║ [ ] LC 1498 - Subsequences Satisfy Given Sum   | M  | Sort + 2Ptr + Mod   ║
 * ║     https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/ ║
 * ║                                                                            ║
 * ║ [ ] LC 2422 - Merge Operations Make Palindrome  | M  | 2Ptr Greedy        ║
 * ║     https://leetcode.com/problems/merge-operations-to-turn-array-into-a-palindrome/ ║
 * ║                                                                            ║
 * ║ [ ] CSES 1640 - Sum of Two Values              | M  | Two Pointer / Map   ║
 * ║     https://cses.fi/problemset/task/1640                                   ║
 * ║                                                                            ║
 * ║ [ ] CSES 1641 - Sum of Three Values             | M  | Fix One + 2Ptr     ║
 * ║     https://cses.fi/problemset/task/1641                                   ║
 * ║                                                                            ║
 * ║ [ ] CSES 1642 - Sum of Four Values              | M  | 2Ptr + HashMap     ║
 * ║     https://cses.fi/problemset/task/1642                                   ║
 * ║                                                                            ║
 * ║ [ ] GFG     - Pair with Given Sum in Sorted     | E  | Basic 2Ptr         ║
 * ║     https://practice.geeksforgeeks.org/problems/pair-with-given-sum-in-a-sorted-array/ ║
 * ║                                                                            ║
 * ║ [ ] GFG     - Triplet Sum in Array              | M  | 3Sum Variant       ║
 * ║     https://practice.geeksforgeeks.org/problems/triplet-sum-in-array/      ║
 * ║                                                                            ║
 * ║ [ ] GFG     - Trapping Rain Water               | M  | Classic 2Ptr       ║
 * ║     https://practice.geeksforgeeks.org/problems/trapping-rain-water/       ║
 * ║                                                                            ║
 * ║                                                                            ║
 * ║  ─────────── MODULE 03: PALINDROME & STRING TWO POINTER ───────────        ║
 * ║                                                                            ║
 * ║ [ ] LC 125  - Valid Palindrome                  | E  | 2Ptr + isalnum     ║
 * ║     https://leetcode.com/problems/valid-palindrome/                        ║
 * ║                                                                            ║
 * ║ [ ] LC 680  - Valid Palindrome II               | E  | 2Ptr + Skip 1      ║
 * ║     https://leetcode.com/problems/valid-palindrome-ii/                     ║
 * ║                                                                            ║
 * ║ [ ] LC 1216 - Valid Palindrome III              | H  | DP (LCS variant)    ║
 * ║     https://leetcode.com/problems/valid-palindrome-iii/                    ║
 * ║                                                                            ║
 * ║ [ ] LC 5    - Longest Palindromic Substring     | M  | Expand from Center ║
 * ║     https://leetcode.com/problems/longest-palindromic-substring/           ║
 * ║                                                                            ║
 * ║ [ ] LC 647  - Palindromic Substrings            | M  | Expand from Center ║
 * ║     https://leetcode.com/problems/palindromic-substrings/                  ║
 * ║                                                                            ║
 * ║ [ ] LC 234  - Palindrome Linked List            | E  | Fast/Slow + Rev    ║
 * ║     https://leetcode.com/problems/palindrome-linked-list/                  ║
 * ║                                                                            ║
 * ║ [ ] LC 2108 - Find First Palindromic String     | E  | 2Ptr Check Each    ║
 * ║     https://leetcode.com/problems/find-first-palindromic-string-in-the-array/ ║
 * ║                                                                            ║
 * ║ [ ] LC 1332 - Remove Palindromic Subsequences   | E  | Trick (check palin)║
 * ║     https://leetcode.com/problems/remove-palindromic-subsequences/         ║
 * ║                                                                            ║
 * ║ [ ] LC 1793 - Max Score Good Subarray           | H  | 2Ptr Expand        ║
 * ║     https://leetcode.com/problems/maximum-score-of-a-good-subarray/        ║
 * ║                                                                            ║
 * ║ [ ] GFG     - Palindrome String                 | E  | Basic 2Ptr         ║
 * ║     https://practice.geeksforgeeks.org/problems/palindrome-string/         ║
 * ║                                                                            ║
 * ║                                                                            ║
 * ║  ─────────── MODULE 04: FAST & SLOW POINTERS ───────────                   ║
 * ║                                                                            ║
 * ║ [ ] LC 141  - Linked List Cycle                 | E  | Floyd's Cycle       ║
 * ║     https://leetcode.com/problems/linked-list-cycle/                       ║
 * ║                                                                            ║
 * ║ [ ] LC 142  - Linked List Cycle II              | M  | Floyd's + Find Start║
 * ║     https://leetcode.com/problems/linked-list-cycle-ii/                    ║
 * ║                                                                            ║
 * ║ [ ] LC 287  - Find the Duplicate Number         | M  | Floyd on Array      ║
 * ║     https://leetcode.com/problems/find-the-duplicate-number/               ║
 * ║                                                                            ║
 * ║ [ ] LC 202  - Happy Number                      | E  | Floyd on Math       ║
 * ║     https://leetcode.com/problems/happy-number/                            ║
 * ║                                                                            ║
 * ║ [ ] LC 876  - Middle of the Linked List         | E  | Fast=2x, Slow=1x   ║
 * ║     https://leetcode.com/problems/middle-of-the-linked-list/               ║
 * ║                                                                            ║
 * ║ [ ] LC 19   - Remove Nth Node From End          | M  | Two Ptr Gap=N      ║
 * ║     https://leetcode.com/problems/remove-nth-node-from-end-of-list/        ║
 * ║                                                                            ║
 * ║ [ ] LC 143  - Reorder List                      | M  | Mid + Rev + Merge  ║
 * ║     https://leetcode.com/problems/reorder-list/                            ║
 * ║                                                                            ║
 * ║ [ ] LC 457  - Circular Array Loop               | M  | Floyd on Circular   ║
 * ║     https://leetcode.com/problems/circular-array-loop/                     ║
 * ║                                                                            ║
 * ║ [ ] LC 2095 - Delete Middle Node                | M  | Fast/Slow           ║
 * ║     https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/ ║
 * ║                                                                            ║
 * ║ [ ] GFG     - Detect Loop in Linked List        | E  | Floyd's             ║
 * ║     https://practice.geeksforgeeks.org/problems/detect-loop-in-linked-list/ ║
 * ║                                                                            ║
 * ║                                                                            ║
 * ║  ─────────── MODULE 05: SORTED ARRAY MERGE & PARTITION ───────────         ║
 * ║                                                                            ║
 * ║ [ ] LC 88   - Merge Sorted Array               | E  | Merge from End      ║
 * ║     https://leetcode.com/problems/merge-sorted-array/                      ║
 * ║                                                                            ║
 * ║ [ ] LC 349  - Intersection of Two Arrays        | E  | Set / Sort+2Ptr    ║
 * ║     https://leetcode.com/problems/intersection-of-two-arrays/              ║
 * ║                                                                            ║
 * ║ [ ] LC 350  - Intersection of Two Arrays II     | E  | Map / Sort+2Ptr    ║
 * ║     https://leetcode.com/problems/intersection-of-two-arrays-ii/           ║
 * ║                                                                            ║
 * ║ [ ] LC 26   - Remove Duplicates from Sorted     | E  | Reader-Writer       ║
 * ║     https://leetcode.com/problems/remove-duplicates-from-sorted-array/     ║
 * ║                                                                            ║
 * ║ [ ] LC 80   - Remove Duplicates II (at most 2)  | M  | Reader-Writer       ║
 * ║     https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/  ║
 * ║                                                                            ║
 * ║ [ ] LC 27   - Remove Element                    | E  | Two Pointer Swap    ║
 * ║     https://leetcode.com/problems/remove-element/                          ║
 * ║                                                                            ║
 * ║ [ ] LC 75   - Sort Colors (Dutch National Flag) | M  | 3-Way Partition     ║
 * ║     https://leetcode.com/problems/sort-colors/                             ║
 * ║                                                                            ║
 * ║ [ ] LC 283  - Move Zeroes                       | E  | Reader-Writer       ║
 * ║     https://leetcode.com/problems/move-zeroes/                             ║
 * ║                                                                            ║
 * ║ [ ] LC 905  - Sort Array By Parity              | E  | 2Ptr Partition      ║
 * ║     https://leetcode.com/problems/sort-array-by-parity/                    ║
 * ║                                                                            ║
 * ║ [ ] LC 922  - Sort Array By Parity II           | E  | 2Ptr Even/Odd      ║
 * ║     https://leetcode.com/problems/sort-array-by-parity-ii/                 ║
 * ║                                                                            ║
 * ║ [ ] LC 2161 - Partition Array by Pivot           | M  | 3-Way Partition    ║
 * ║     https://leetcode.com/problems/partition-array-according-to-given-pivot/ ║
 * ║                                                                            ║
 * ║ [ ] GFG     - Sort 0s 1s and 2s                 | E  | Dutch National Flag ║
 * ║     https://practice.geeksforgeeks.org/problems/sort-an-array-of-0s-1s-and-2s/ ║
 * ║                                                                            ║
 * ║ [ ] GFG     - Merge Without Extra Space         | H  | Gap / Shell Sort   ║
 * ║     https://practice.geeksforgeeks.org/problems/merge-two-sorted-arrays5135/ ║
 * ║                                                                            ║
 * ║ [ ] LC 986  - Interval List Intersections        | M  | 2Ptr on Intervals  ║
 * ║     https://leetcode.com/problems/interval-list-intersections/              ║
 * ║                                                                            ║
 * ║ [ ] LC 31   - Next Permutation                   | M  | 2Ptr + Reverse     ║
 * ║     https://leetcode.com/problems/next-permutation/                         ║
 * ║                                                                            ║
 * ║ [ ] LC 189  - Rotate Array                       | M  | 3 Reverses (2Ptr)  ║
 * ║     https://leetcode.com/problems/rotate-array/                             ║
 * ║                                                                            ║
 * ║ [ ] LC 151  - Reverse Words in a String          | M  | Reverse + 2Ptr     ║
 * ║     https://leetcode.com/problems/reverse-words-in-a-string/                ║
 * ║                                                                            ║
 * ║ [ ] LC 443  - String Compression                 | M  | Reader-Writer      ║
 * ║     https://leetcode.com/problems/string-compression/                       ║
 * ║                                                                            ║
 * ║ [ ] LC 844  - Backspace String Compare           | E  | Reverse 2Ptr O(1)  ║
 * ║     https://leetcode.com/problems/backspace-string-compare/                 ║
 * ║                                                                            ║
 * ║ [ ] LC 845  - Longest Mountain in Array          | M  | Expand from Peak   ║
 * ║     https://leetcode.com/problems/longest-mountain-in-array/                ║
 * ║                                                                            ║
 * ║ [ ] LC 611  - Valid Triangle Number              | M  | Sort + 2Ptr Count  ║
 * ║     https://leetcode.com/problems/valid-triangle-number/                    ║
 * ║                                                                            ║
 * ║ [ ] LC 455  - Assign Cookies                     | E  | Sort + Greedy 2Ptr ║
 * ║     https://leetcode.com/problems/assign-cookies/                           ║
 * ║                                                                            ║
 * ║ [ ] LC 148  - Sort List                          | M  | Fast/Slow + Merge  ║
 * ║     https://leetcode.com/problems/sort-list/                                ║
 * ║                                                                            ║
 * ║ [ ] LC 826  - Most Profit Assigning Work         | M  | Sort + 2Ptr Sweep  ║
 * ║     https://leetcode.com/problems/most-profit-assigning-work/               ║
 * ║                                                                            ║
 * ║                                                                            ║
 * ║  ─────────── MODULE 06: BINARY SEARCH + TWO POINTER ───────────            ║
 * ║                                                                            ║
 * ║ [ ] LC 881  - Boats to Save People              | M  | Sort + 2Ptr        ║
 * ║     https://leetcode.com/problems/boats-to-save-people/                    ║
 * ║                                                                            ║
 * ║ [ ] LC 16   - 3Sum Closest                      | M  | Sort + 2Ptr        ║
 * ║     https://leetcode.com/problems/3sum-closest/                            ║
 * ║                                                                            ║
 * ║ [ ] LC 719  - Find K-th Smallest Pair Distance  | H  | BS + 2Ptr Count    ║
 * ║     https://leetcode.com/problems/find-k-th-smallest-pair-distance/        ║
 * ║                                                                            ║
 * ║ [ ] LC 1855 - Max Distance Between Pair          | M  | 2Ptr on 2 Arrays  ║
 * ║     https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/ ║
 * ║                                                                            ║
 * ║ [ ] LC 658  - Find K Closest Elements            | M  | BS + 2Ptr Shrink  ║
 * ║     https://leetcode.com/problems/find-k-closest-elements/                 ║
 * ║                                                                            ║
 * ║ [ ] LC 2824 - Count Pairs Whose Sum < Target     | E  | Sort + 2Ptr       ║
 * ║     https://leetcode.com/problems/count-pairs-whose-sum-is-less-than-target/ ║
 * ║                                                                            ║
 * ║ [ ] LC 532  - K-diff Pairs in Array              | M  | Sort + 2Ptr       ║
 * ║     https://leetcode.com/problems/k-diff-pairs-in-an-array/                ║
 * ║                                                                            ║
 * ║ [ ] LC 1679 - Max Number of K-Sum Pairs          | M  | Sort + 2Ptr       ║
 * ║     https://leetcode.com/problems/max-number-of-k-sum-pairs/               ║
 * ║                                                                            ║
 * ║ [ ] LC 2300 - Successful Pairs Spells+Potions    | M  | Sort + BS         ║
 * ║     https://leetcode.com/problems/successful-pairs-of-spells-and-potions/  ║
 * ║                                                                            ║
 * ║ [ ] CSES 2428 - Subarray Distinct Values         | M  | 2Ptr + Map        ║
 * ║     https://cses.fi/problemset/task/2428                                   ║
 * ║                                                                            ║
 * ║                                                                            ║
 * ║  ─────── MODULE 06 (ADVANCED): CIRCULAR, PREFIX-SUFFIX, PAIR COUNT ─────── ║
 * ║                                                                            ║
 * ║  --- Circular Array Two Pointer ---                                        ║
 * ║                                                                            ║
 * ║ [ ] LC 918  - Max Sum Circular Subarray          | M  | Kadane + Inverse  ║
 * ║     https://leetcode.com/problems/maximum-sum-circular-subarray/            ║
 * ║                                                                            ║
 * ║ [ ] LC 2134 - Min Swaps Group 1s (Circular)      | M  | Circular FixWin   ║
 * ║     https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/ ║
 * ║                                                                            ║
 * ║ [ ] LC 503  - Next Greater Element II (Circular)  | M  | 2N Stack Trick   ║
 * ║     https://leetcode.com/problems/next-greater-element-ii/                  ║
 * ║                                                                            ║
 * ║  --- Prefix-Suffix Two Pointer Balancing ---                               ║
 * ║                                                                            ║
 * ║ [ ] LC 238  - Product of Array Except Self       | M  | Prefix*Suffix     ║
 * ║     https://leetcode.com/problems/product-of-array-except-self/             ║
 * ║                                                                            ║
 * ║ [ ] LC 2270 - Ways to Split Array                | M  | PrefSufSplit      ║
 * ║     https://leetcode.com/problems/number-of-ways-to-split-array/            ║
 * ║                                                                            ║
 * ║ [ ] LC 1525 - Good Ways to Split a String        | M  | DistinctPrefSuf   ║
 * ║     https://leetcode.com/problems/number-of-good-ways-to-split-a-string/    ║
 * ║                                                                            ║
 * ║ [ ] LC 334  - Increasing Triplet Subsequence      | M  | PrefMin Track    ║
 * ║     https://leetcode.com/problems/increasing-triplet-subsequence/           ║
 * ║                                                                            ║
 * ║  --- Advanced Pair Counting in Range [L, R] ---                            ║
 * ║                                                                            ║
 * ║ [ ] LC 2563 - Count Fair Pairs [lower,upper]     | M  | AtMost(R)-AtMost  ║
 * ║     https://leetcode.com/problems/count-the-number-of-fair-pairs/           ║
 * ║                                                                            ║
 * ║ [ ] LC 327  - Count of Range Sum                 | H  | MergeSort+2Ptr   ║
 * ║     https://leetcode.com/problems/count-of-range-sum/                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1324D - Pair of Topics                    | M (1400) | Diff+2Ptr   ║
 * ║     https://codeforces.com/problemset/problem/1324/D                        ║
 * ║                                                                            ║
 * ║  --- Meet in the Middle ---                                                ║
 * ║                                                                            ║
 * ║ [ ] LC 1755 - Closest Subsequence Sum            | H  | MitM + BS/2Ptr   ║
 * ║     https://leetcode.com/problems/closest-subsequence-sum/                  ║
 * ║                                                                            ║
 * ║ [ ] CF 888E - Maximum Subsequence (mod M)        | EX (1800) | MitM+Sort ║
 * ║     https://codeforces.com/problemset/problem/888/E                         ║
 * ║                                                                            ║
 * ║  --- Sweep Line + Geometry Two Pointer ---                                 ║
 * ║                                                                            ║
 * ║ [ ] LC 253  - Meeting Rooms II (Min Platforms)    | M  | SweepLine+2Ptr   ║
 * ║     https://leetcode.com/problems/meeting-rooms-ii/                         ║
 * ║                                                                            ║
 * ║ [ ] LC 1288 - Remove Covered Intervals            | M  | Sort+Sweep       ║
 * ║     https://leetcode.com/problems/remove-covered-intervals/                 ║
 * ║                                                                            ║
 * ║ [ ] CF 1462F - Treasure of the Segments          | H (1800) | Sort+BS     ║
 * ║     https://codeforces.com/problemset/problem/1462/F                        ║
 * ║                                                                            ║
 * ║  --- Mo's Algorithm (Offline Two Pointer) ---                              ║
 * ║                                                                            ║
 * ║ [ ] CF 86D  - Powerful Array                     | EX (2000) | Classic Mo ║
 * ║     https://codeforces.com/problemset/problem/86/D                          ║
 * ║                                                                            ║
 * ║ [ ] CF 617E - XOR and Favorite Number            | EX (2100) | Mo+XOR    ║
 * ║     https://codeforces.com/problemset/problem/617/E                         ║
 * ║                                                                            ║
 * ║ [ ] SPOJ DQUERY - Count Distinct in Range        | M  | Mo's Algorithm    ║
 * ║     https://www.spoj.com/problems/DQUERY/                                   ║
 * ║                                                                            ║
 * ║ [ ] CSES 1734 - Distinct Values Queries          | M  | Mo's / MergSort   ║
 * ║     https://cses.fi/problemset/task/1734                                    ║
 * ║                                                                            ║
 * ║                                                                            ║
 * ║  ─────────── MODULE 07: TWO POINTER CODEFORCES PROBLEMS ───────────        ║
 * ║                                                                            ║
 * ║  --- CF 800-1200 (Easy) ---                                                ║
 * ║                                                                            ║
 * ║ [ ] CF 6A    - Triangle                         | E  (800)  | Sort+Check  ║
 * ║     https://codeforces.com/problemset/problem/6/A                          ║
 * ║                                                                            ║
 * ║ [ ] CF 1385A - Three Pairwise Maximums          | E  (800)  | Sorting     ║
 * ║     https://codeforces.com/problemset/problem/1385/A                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1538C - Number of Pairs                  | M  (1300) | Sort+2Ptr   ║
 * ║     https://codeforces.com/problemset/problem/1538/C                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1462C - Unique Number                    | M  (1100) | Greedy      ║
 * ║     https://codeforces.com/problemset/problem/1462/C                       ║
 * ║                                                                            ║
 * ║  --- CF 1200-1600 (Medium) ---                                             ║
 * ║                                                                            ║
 * ║ [ ] CF 1354B - Ternary String                   | M  (1200) | 2Ptr/SW     ║
 * ║     https://codeforces.com/problemset/problem/1354/B                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1498C - Planar Reflections               | M  (1600) | Simulation  ║
 * ║     https://codeforces.com/problemset/problem/1498/C                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1358D - Buying Lemonade                  | M  (1500) | Sort+2Ptr   ║
 * ║     https://codeforces.com/problemset/problem/1358/D                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1676E - Eating Queries                   | M  (1100) | PrefSum+BS  ║
 * ║     https://codeforces.com/problemset/problem/1676/E                       ║
 * ║                                                                            ║
 * ║ [ ] CF 279B  - Books                            | M  (1400) | Two Pointer ║
 * ║     https://codeforces.com/problemset/problem/279/B                        ║
 * ║                                                                            ║
 * ║ [ ] CF 602B  - Approximating a Constant Range   | M  (1500) | 2Ptr+Deque  ║
 * ║     https://codeforces.com/problemset/problem/602/B                        ║
 * ║                                                                            ║
 * ║  --- CF 1600-2000 (Hard) ---                                               ║
 * ║                                                                            ║
 * ║ [ ] CF 1537D - Deleting Divisors                | H  (1700) | Game Theory ║
 * ║     https://codeforces.com/problemset/problem/1537/D                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1695C - Zero Path                        | H  (1700) | DP + 2Ptr   ║
 * ║     https://codeforces.com/problemset/problem/1695/C                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1849D - Array Painting                   | H  (1700) | Greedy+2Ptr ║
 * ║     https://codeforces.com/problemset/problem/1849/D                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1921D - Very Different Array             | M  (1100) | Sort+2Ptr   ║
 * ║     https://codeforces.com/problemset/problem/1921/D                       ║
 * ║                                                                            ║
 * ║  --- CF 2000-2400+ (Expert/GM) ---                                         ║
 * ║                                                                            ║
 * ║ [ ] CF 1608D - Dominoes                         | EX (2100) | 2Ptr+Math   ║
 * ║     https://codeforces.com/problemset/problem/1608/D                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1548B - Integers Have Friends             | EX (2000) | GCD+2Ptr   ║
 * ║     https://codeforces.com/problemset/problem/1548/B                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1523D - Love-Hate                        | GM (2400) | Random+2Ptr ║
 * ║     https://codeforces.com/problemset/problem/1523/D                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1809E - Two Tanks                        | EX (2200) | 2Ptr Sim    ║
 * ║     https://codeforces.com/problemset/problem/1809/E                       ║
 * ║                                                                            ║
 * ║                                                                            ║
 * ╠══════════════════════════════════════════════════════════════════════════════╣
 * ║        SECTION B: FIXED SIZE SLIDING WINDOW (MODULES 08-10)               ║
 * ╠══════════════════════════════════════════════════════════════════════════════╣
 * ║                                                                            ║
 * ║  ─────────── MODULE 08: FIXED WINDOW FUNDAMENTALS ───────────              ║
 * ║                                                                            ║
 * ║ [ ] GFG     - Max Sum Subarray of Size K        | E  | Basic Fixed Win    ║
 * ║     https://practice.geeksforgeeks.org/problems/max-sum-subarray-of-size-k/ ║
 * ║                                                                            ║
 * ║ [ ] GFG     - First Negative in Every Window K  | E  | Fixed Win + Deque  ║
 * ║     https://practice.geeksforgeeks.org/problems/first-negative-integer-in-every-window-of-size-k/ ║
 * ║                                                                            ║
 * ║ [ ] GFG     - Count Distinct in Every Window    | M  | Fixed Win + Map    ║
 * ║     https://practice.geeksforgeeks.org/problems/count-distinct-elements-in-every-window/ ║
 * ║                                                                            ║
 * ║ [ ] LC 643  - Max Average Subarray I            | E  | Basic Fixed Win    ║
 * ║     https://leetcode.com/problems/maximum-average-subarray-i/              ║
 * ║                                                                            ║
 * ║ [ ] LC 1456 - Max Vowels in Substring Length K  | M  | Fixed Win + Count  ║
 * ║     https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/ ║
 * ║                                                                            ║
 * ║ [ ] LC 1343 - # Subarrays of Size K and Avg ≥ T | M  | Fixed Win + Count ║
 * ║     https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/ ║
 * ║                                                                            ║
 * ║ [ ] LC 2090 - K Radius Subarray Averages        | M  | Fixed Win          ║
 * ║     https://leetcode.com/problems/k-radius-subarray-averages/              ║
 * ║                                                                            ║
 * ║ [ ] LC 1052 - Grumpy Bookstore Owner            | M  | Fixed Win + Prefix ║
 * ║     https://leetcode.com/problems/grumpy-bookstore-owner/                  ║
 * ║                                                                            ║
 * ║ [ ] LC 1984 - Minimum Difference in Student Grp  | E  | Sort + Fixed Win  ║
 * ║     https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/ ║
 * ║                                                                            ║
 * ║ [ ] LC 2379 - Min Recolors to Get K Black Blocks | E  | Fixed Win Count   ║
 * ║     https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks/ ║
 * ║                                                                            ║
 * ║ [ ] LC 2461 - Max Sum Distinct Subarrays Size K  | M  | Fixed Win + Set   ║
 * ║     https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/ ║
 * ║                                                                            ║
 * ║ [ ] CSES 2428 - Subarray Distinct Values         | M  | Fixed/Var + Map   ║
 * ║     https://cses.fi/problemset/task/2428                                   ║
 * ║                                                                            ║
 * ║  --- Bit Manipulation + Fixed Window ---                                   ║
 * ║                                                                            ║
 * ║ [ ] LC 1461 - All Binary Codes of Size K         | M  | Rolling Bitmask   ║
 * ║     https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/ ║
 * ║                                                                            ║
 * ║ [ ] LC 1177 - Palindrome from Substring (Parity) | M  | Parity Mask+Pref ║
 * ║     https://leetcode.com/problems/can-make-palindrome-from-substring/       ║
 * ║                                                                            ║
 * ║  --- Prefix Sum Hybrid + Contribution ---                                  ║
 * ║                                                                            ║
 * ║ [ ] LC 1588 - Sum of All Odd Length Subarrays     | E  | Contribution Trk ║
 * ║     https://leetcode.com/problems/sum-of-all-odd-length-subarrays/          ║
 * ║                                                                            ║
 * ║ [ ] LC 1423 - Max Points from Cards              | M  | Prefix+Suffix Win ║
 * ║     https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/ ║
 * ║                                                                            ║
 * ║  --- Circular Fixed Window ---                                             ║
 * ║                                                                            ║
 * ║ [ ] LC 2134 - Min Swaps Group 1s II (Circular)   | M  | Circular FixWin   ║
 * ║     https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/ ║
 * ║                                                                            ║
 * ║ [ ] LC 1652 - Defuse the Bomb (Circular)         | E  | Circular Win Sum  ║
 * ║     https://leetcode.com/problems/defuse-the-bomb/                          ║
 * ║                                                                            ║
 * ║  --- Fixed Window + Greedy ---                                             ║
 * ║                                                                            ║
 * ║ [ ] LC 1151 - Min Swaps to Group 1s Together     | M  | Window MaxOnes    ║
 * ║     https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together/   ║
 * ║                                                                            ║
 * ║ [ ] LC 2009 - Min Ops to Make Array Continuous   | H  | Sort+FixedWin     ║
 * ║     https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/ ║
 * ║                                                                            ║
 * ║ [ ] LC 2024 - Maximize Confusion of Exam         | M  | K-flip VarWin     ║
 * ║     https://leetcode.com/problems/maximize-the-confusion-of-an-exam/        ║
 * ║                                                                            ║
 * ║ [ ] LC 2516 - Take K of Each Char (Left+Right)   | M  | Middle Window     ║
 * ║     https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/ ║
 * ║                                                                            ║
 * ║                                                                            ║
 * ║  ─────────── MODULE 09: FIXED WINDOW + DEQUE & HASHING ───────────         ║
 * ║                                                                            ║
 * ║ [ ] LC 239  - Sliding Window Maximum             | H  | Deque (Monotonic) ║
 * ║     https://leetcode.com/problems/sliding-window-maximum/                  ║
 * ║                                                                            ║
 * ║ [ ] LC 1438 - Longest Subarray Abs Diff ≤ Limit  | M  | Two Deques       ║
 * ║     https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/ ║
 * ║                                                                            ║
 * ║ [ ] LC 567  - Permutation in String              | M  | Fixed Win + Freq  ║
 * ║     https://leetcode.com/problems/permutation-in-string/                   ║
 * ║                                                                            ║
 * ║ [ ] LC 438  - Find All Anagrams in a String      | M  | Fixed Win + Freq  ║
 * ║     https://leetcode.com/problems/find-all-anagrams-in-a-string/           ║
 * ║                                                                            ║
 * ║ [ ] LC 242  - Valid Anagram                      | E  | Frequency Count    ║
 * ║     https://leetcode.com/problems/valid-anagram/                           ║
 * ║                                                                            ║
 * ║ [ ] LC 187  - Repeated DNA Sequences             | M  | Fixed Win + Hash  ║
 * ║     https://leetcode.com/problems/repeated-dna-sequences/                  ║
 * ║                                                                            ║
 * ║ [ ] LC 1876 - Substrings of Size 3 Distinct Char | E  | Fixed Win 3      ║
 * ║     https://leetcode.com/problems/substrings-of-size-three-with-distinct-characters/ ║
 * ║                                                                            ║
 * ║ [ ] LC 2156 - Find Substring Hash Value           | H  | Rolling Hash     ║
 * ║     https://leetcode.com/problems/find-substring-with-given-hash-value/    ║
 * ║                                                                            ║
 * ║ [ ] LC 480  - Sliding Window Median              | H  | Two Heaps / SortedList ║
 * ║     https://leetcode.com/problems/sliding-window-median/                   ║
 * ║                                                                            ║
 * ║ [ ] LC 346  - Moving Average from Data Stream    | E  | Fixed Window Queue ║
 * ║     https://leetcode.com/problems/moving-average-from-data-stream/         ║
 * ║                                                                            ║
 * ║ [ ] GFG     - Max of All Subarrays of Size K     | M  | Deque Monotonic   ║
 * ║     https://practice.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k/ ║
 * ║                                                                            ║
 * ║ [ ] CSES 1077 - Sliding Window Median            | H  | Multiset / BIT    ║
 * ║     https://cses.fi/problemset/task/1077                                   ║
 * ║                                                                            ║
 * ║ [ ] CSES 1076 - Sliding Window Cost              | H  | Multiset Greedy   ║
 * ║     https://cses.fi/problemset/task/1076                                   ║
 * ║                                                                            ║
 * ║  --- Fixed Window + GCD / LCM ---                                          ║
 * ║                                                                            ║
 * ║ [ ] CF 1548B - Integers Have Friends (GCD+SW)    | EX (2000) | GCD+2Stack ║
 * ║     https://codeforces.com/problemset/problem/1548/B                        ║
 * ║                                                                            ║
 * ║ [ ] CF 475D - CGCDSSQ (count GCD subarrays)      | H  (1800) | GCD+Seg   ║
 * ║     https://codeforces.com/problemset/problem/475/D                         ║
 * ║                                                                            ║
 * ║  --- Rolling Hash (Rabin-Karp) ---                                         ║
 * ║                                                                            ║
 * ║ [ ] LC 28   - Find First Occurrence (Rabin-Karp) | E  | Rolling Hash      ║
 * ║     https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/ ║
 * ║                                                                            ║
 * ║ [ ] LC 1044 - Longest Duplicate Substring         | H  | BS + RollingHash ║
 * ║     https://leetcode.com/problems/longest-duplicate-substring/              ║
 * ║                                                                            ║
 * ║  --- 2D Fixed Sliding Window ---                                           ║
 * ║                                                                            ║
 * ║ [ ] LC 304  - Range Sum Query 2D                 | M  | 2D Prefix Sum    ║
 * ║     https://leetcode.com/problems/range-sum-query-2d-immutable/             ║
 * ║                                                                            ║
 * ║ [ ] LC 363  - Max Sum Rectangle ≤ K              | H  | 2DPrefix + Set   ║
 * ║     https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/    ║
 * ║                                                                            ║
 * ║ [ ] LC 1074 - Submatrices That Sum to Target     | H  | 2DPrefix + Map   ║
 * ║     https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/ ║
 * ║                                                                            ║
 * ║  --- Advanced Competitive Patterns ---                                     ║
 * ║                                                                            ║
 * ║ [ ] LC 2444 - Count Subarrays Fixed Bounds       | H  | ConstraintTrack  ║
 * ║     https://leetcode.com/problems/count-subarrays-with-fixed-bounds/        ║
 * ║                                                                            ║
 * ║ [ ] LC 2762 - Continuous Subarrays (|diff|≤2)    | M  | Two Deques Count ║
 * ║     https://leetcode.com/problems/continuous-subarrays/                     ║
 * ║                                                                            ║
 * ║ [ ] LC 992  - Subarrays K Different Integers     | H  | AtMost(K)-AtMost ║
 * ║     https://leetcode.com/problems/subarrays-with-k-different-integers/      ║
 * ║                                                                            ║
 * ║ [ ] LC 1248 - Count Nice Subarrays (K odds)      | M  | AtMost(K)-AtMost ║
 * ║     https://leetcode.com/problems/count-number-of-nice-subarrays/           ║
 * ║                                                                            ║
 * ║                                                                            ║
 * ║  ─────────── MODULE 10: FIXED WINDOW CODEFORCES PROBLEMS ───────────       ║
 * ║                                                                            ║
 * ║  --- CF 800-1200 (Easy) ---                                                ║
 * ║                                                                            ║
 * ║ [ ] CF 1352B - Same Parity Summands             | E  (800)  | Basic       ║
 * ║     https://codeforces.com/problemset/problem/1352/B                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1669D - Colorful Stamp                   | E  (1000) | Window Chk  ║
 * ║     https://codeforces.com/problemset/problem/1669/D                       ║
 * ║                                                                            ║
 * ║  --- CF 1200-1600 (Medium) ---                                             ║
 * ║                                                                            ║
 * ║ [ ] CF 1551B2 - Wonderful String (Hard)          | M  (1400) | Fixed Win  ║
 * ║     https://codeforces.com/problemset/problem/1551/B2                      ║
 * ║                                                                            ║
 * ║ [ ] CF 1352D - Alice Bob and Candies             | M  (1300) | Simulation ║
 * ║     https://codeforces.com/problemset/problem/1352/D                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1692F - 3Sum Close To Target              | M  (1500) | Sort+2Ptr  ║
 * ║     https://codeforces.com/problemset/problem/1692/F                       ║
 * ║                                                                            ║
 * ║  --- CF 1600-2000 (Hard) ---                                               ║
 * ║                                                                            ║
 * ║ [ ] CF 1598D - Training Session                  | H  (1700) | SW+Hash    ║
 * ║     https://codeforces.com/problemset/problem/1598/D                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1722E - Counting Rectangles               | H  (1600) | 2D Prefix  ║
 * ║     https://codeforces.com/problemset/problem/1722/E                       ║
 * ║                                                                            ║
 * ║ [ ] CF 514D  - R2D2 and Droid Army               | H  (1800) | SW+SegTree ║
 * ║     https://codeforces.com/problemset/problem/514/D                        ║
 * ║                                                                            ║
 * ║  --- CF 2000-2400+ (Expert/GM) ---                                         ║
 * ║                                                                            ║
 * ║ [ ] CF 1849E - Max Stock Profit                  | EX (2200) | SW+Deque   ║
 * ║     https://codeforces.com/problemset/problem/1849/E                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1918E - ace-Subarrays                     | GM (2400) | SW+BIT     ║
 * ║     https://codeforces.com/problemset/problem/1918/E                       ║
 * ║                                                                            ║
 * ║                                                                            ║
 * ╠══════════════════════════════════════════════════════════════════════════════╣
 * ║      SECTION C: VARIABLE SIZE SLIDING WINDOW (MODULES 11-14)              ║
 * ╠══════════════════════════════════════════════════════════════════════════════╣
 * ║                                                                            ║
 * ║  ─────────── MODULE 11: VARIABLE WINDOW FUNDAMENTALS ───────────           ║
 * ║                                                                            ║
 * ║ [ ] LC 209  - Minimum Size Subarray Sum          | M  | Shrink Window     ║
 * ║     https://leetcode.com/problems/minimum-size-subarray-sum/               ║
 * ║                                                                            ║
 * ║ [ ] LC 1004 - Max Consecutive Ones III           | M  | Expand-Shrink     ║
 * ║     https://leetcode.com/problems/max-consecutive-ones-iii/                ║
 * ║                                                                            ║
 * ║ [ ] LC 1493 - Longest Subarray of 1s After Del   | M  | Delete One 0      ║
 * ║     https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/ ║
 * ║                                                                            ║
 * ║ [ ] LC 485  - Max Consecutive Ones               | E  | Basic Scan        ║
 * ║     https://leetcode.com/problems/max-consecutive-ones/                    ║
 * ║                                                                            ║
 * ║ [ ] LC 487  - Max Consecutive Ones II            | M  | Flip at most 1    ║
 * ║     https://leetcode.com/problems/max-consecutive-ones-ii/                 ║
 * ║                                                                            ║
 * ║ [ ] LC 2024 - Max Confusion of an Exam           | M  | Max Consec Variant║
 * ║     https://leetcode.com/problems/maximize-the-confusion-of-an-exam/       ║
 * ║                                                                            ║
 * ║ [ ] LC 1658 - Min Operations to Reduce X to 0    | M  | Reverse Thinking  ║
 * ║     https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/  ║
 * ║                                                                            ║
 * ║ [ ] LC 713  - Subarray Product Less Than K       | M  | Expand-Shrink     ║
 * ║     https://leetcode.com/problems/subarray-product-less-than-k/            ║
 * ║                                                                            ║
 * ║ [ ] GFG     - Longest Subarray with Sum K        | M  | Variable Window   ║
 * ║     https://practice.geeksforgeeks.org/problems/longest-sub-array-with-sum-k/ ║
 * ║                                                                            ║
 * ║ [ ] GFG     - Smallest Subarray with Sum > X     | M  | Shrink Window     ║
 * ║     https://practice.geeksforgeeks.org/problems/smallest-subarray-with-sum-greater-than-x/ ║
 * ║                                                                            ║
 * ║ [ ] CSES 1643 - Max Subarray Sum                 | E  | Kadane (compare)  ║
 * ║     https://cses.fi/problemset/task/1643                                   ║
 * ║                                                                            ║
 * ║                                                                            ║
 * ║  ─────────── MODULE 12: DISTINCT & FREQUENCY PATTERNS ───────────          ║
 * ║                                                                            ║
 * ║ [ ] LC 340  - Longest Substr At Most K Distinct  | M  | Var Win + Map     ║
 * ║     https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/ ║
 * ║                                                                            ║
 * ║ [ ] LC 159  - Longest Substr At Most 2 Distinct  | M  | Var Win K=2       ║
 * ║     https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/ ║
 * ║                                                                            ║
 * ║ [ ] LC 992  - Subarrays with K Different Ints    | H  | ExactK = atMost K - atMost(K-1) ║
 * ║     https://leetcode.com/problems/subarrays-with-k-different-integers/     ║
 * ║                                                                            ║
 * ║ [ ] LC 904  - Fruit Into Baskets                 | M  | At Most 2 Distinct║
 * ║     https://leetcode.com/problems/fruit-into-baskets/                      ║
 * ║                                                                            ║
 * ║ [ ] LC 930  - Binary Subarrays With Sum          | M  | ExactK Trick      ║
 * ║     https://leetcode.com/problems/binary-subarrays-with-sum/               ║
 * ║                                                                            ║
 * ║ [ ] LC 1248 - Count Number of Nice Subarrays     | M  | Odd = ExactK Trick║
 * ║     https://leetcode.com/problems/count-number-of-nice-subarrays/          ║
 * ║                                                                            ║
 * ║ [ ] LC 2962 - Count Subarrays Max Appears >= K   | M  | Var Window Count  ║
 * ║     https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/ ║
 * ║                                                                            ║
 * ║ [ ] LC 1695 - Max Erasure Value                  | M  | Distinct Subarray  ║
 * ║     https://leetcode.com/problems/maximum-erasure-value/                   ║
 * ║                                                                            ║
 * ║ [ ] LC 2958 - Length of Longest Subarray AtMost K | M  | Var Win + Freq   ║
 * ║     https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/ ║
 * ║                                                                            ║
 * ║ [ ] LC 1358 - Number of Substrings All 3 Chars  | M  | AtLeast Trick      ║
 * ║     https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/ ║
 * ║                                                                            ║
 * ║ [ ] LC 2537 - Count Good Subarrays               | M  | Var Win + Pairs  ║
 * ║     https://leetcode.com/problems/count-the-number-of-good-subarrays/      ║
 * ║                                                                            ║
 * ║ [ ] LC 2799 - Count Complete Subarrays            | M  | Var Window       ║
 * ║     https://leetcode.com/problems/count-complete-subarrays-in-an-array/    ║
 * ║                                                                            ║
 * ║ [ ] GFG     - Longest K Unique Characters Substr | M  | At Most K         ║
 * ║     https://practice.geeksforgeeks.org/problems/longest-k-unique-characters-substring/ ║
 * ║                                                                            ║
 * ║                                                                            ║
 * ║  ─────────── MODULE 13: ADVANCED VARIABLE WINDOW ───────────               ║
 * ║                                                                            ║
 * ║ [ ] LC 76   - Minimum Window Substring           | H  | Shrink + Freq    ║
 * ║     https://leetcode.com/problems/minimum-window-substring/                ║
 * ║                                                                            ║
 * ║ [ ] LC 424  - Longest Repeating Char Replacement  | M  | Var Win + MaxFreq║
 * ║     https://leetcode.com/problems/longest-repeating-character-replacement/  ║
 * ║                                                                            ║
 * ║ [ ] LC 3    - Longest Substr Without Repeating   | M  | Var Win + Set     ║
 * ║     https://leetcode.com/problems/longest-substring-without-repeating-characters/ ║
 * ║                                                                            ║
 * ║ [ ] LC 795  - Subarrays with Bounded Maximum     | M  | Count Trick       ║
 * ║     https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/ ║
 * ║                                                                            ║
 * ║ [ ] LC 862  - Shortest Subarray with Sum ≥ K     | H  | Deque + PrefSum   ║
 * ║     https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/   ║
 * ║                                                                            ║
 * ║ [ ] LC 395  - Longest Substr At Least K Repeat   | M  | Divide & Conquer  ║
 * ║     https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/ ║
 * ║                                                                            ║
 * ║ [ ] LC 1438 - Longest Subarray Abs Diff ≤ Limit  | M  | Two Deques       ║
 * ║     https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/ ║
 * ║                                                                            ║
 * ║ [ ] LC 2302 - Count Subarrays Score < K           | H  | Var Win + Count  ║
 * ║     https://leetcode.com/problems/count-subarrays-with-score-less-than-k/  ║
 * ║                                                                            ║
 * ║ [ ] LC 2009 - Min # Operations to Make Continuous | H  | Sort + Var Win   ║
 * ║     https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/ ║
 * ║                                                                            ║
 * ║ [ ] LC 2516 - Take K of Each Char from Both Sides | M | Reverse SW        ║
 * ║     https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/ ║
 * ║                                                                            ║
 * ║ [ ] LC 974  - Subarray Sums Divisible by K       | M  | PrefSum + Mod     ║
 * ║     https://leetcode.com/problems/subarray-sums-divisible-by-k/            ║
 * ║                                                                            ║
 * ║ [ ] LC 1574 - Shortest Subarray Sorted After Del  | M  | Two Pointer      ║
 * ║     https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/ ║
 * ║                                                                            ║
 * ║ [ ] LC 2302 - Count Subarrays Score < K           | H  | Product Window   ║
 * ║     https://leetcode.com/problems/count-subarrays-with-score-less-than-k/  ║
 * ║                                                                            ║
 * ║ [ ] GFG     - Smallest Window Containing All Chars| H  | Min Window       ║
 * ║     https://practice.geeksforgeeks.org/problems/smallest-window-in-a-string-containing-all-the-characters-of-another-string/ ║
 * ║                                                                            ║
 * ║ [ ] CSES 2428 - Subarray Distinct Values          | M  | Var Win + Map   ║
 * ║     https://cses.fi/problemset/task/2428                                   ║
 * ║                                                                            ║
 * ║  --- Bit Manipulation + Variable Window ---                                ║
 * ║                                                                            ║
 * ║ [ ] LC 1371 - Even Count Vowels Substring        | M  | Parity Mask      ║
 * ║     https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/ ║
 * ║                                                                            ║
 * ║ [ ] LC 1542 - Longest Awesome Substring           | H  | Parity Mask 10b ║
 * ║     https://leetcode.com/problems/find-longest-awesome-substring/           ║
 * ║                                                                            ║
 * ║ [ ] LC 1915 - Wonderful Substrings               | M  | Mask Counting    ║
 * ║     https://leetcode.com/problems/number-of-wonderful-substrings/           ║
 * ║                                                                            ║
 * ║ [ ] LC 2401 - Longest Nice Subarray (AND=0)      | M  | Bit Disjoint Win ║
 * ║     https://leetcode.com/problems/longest-nice-subarray/                    ║
 * ║                                                                            ║
 * ║  --- Monotonic Queue + Variable Constraint ---                             ║
 * ║                                                                            ║
 * ║ [ ] LC 2762 - Continuous Subarrays (diff≤2)       | M  | Two Deques Count║
 * ║     https://leetcode.com/problems/continuous-subarrays/                     ║
 * ║                                                                            ║
 * ║  --- Prefix/BS Hybrid (Negatives!) ---                                     ║
 * ║                                                                            ║
 * ║ [ ] LC 1793 - Max Score Good Subarray (expand k)  | H  | Greedy Expand   ║
 * ║     https://leetcode.com/problems/maximum-score-of-a-good-subarray/         ║
 * ║                                                                            ║
 * ║  --- Multiset / Heap Window ---                                            ║
 * ║                                                                            ║
 * ║ [ ] LC 480  - Sliding Window Median               | H  | Two Multisets   ║
 * ║     https://leetcode.com/problems/sliding-window-median/                    ║
 * ║                                                                            ║
 * ║ [ ] CSES 1077 - Sliding Median                    | H  | Multiset        ║
 * ║     https://cses.fi/problemset/task/1077                                    ║
 * ║                                                                            ║
 * ║ [ ] CSES 1076 - Sliding Cost                      | H  | Median+Sum Track║
 * ║     https://cses.fi/problemset/task/1076                                    ║
 * ║                                                                            ║
 * ║  --- Contribution Counting (Variable) ---                                  ║
 * ║                                                                            ║
 * ║ [ ] LC 2444 - Count Subarrays Fixed Bounds        | H  | ConstraintTrack ║
 * ║     https://leetcode.com/problems/count-subarrays-with-fixed-bounds/        ║
 * ║                                                                            ║
 * ║  --- Sorted Array / Value Space Window ---                                 ║
 * ║                                                                            ║
 * ║ [ ] LC 1838 - Freq of Most Frequent Element      | M  | Sort+Budget Win  ║
 * ║     https://leetcode.com/problems/frequency-of-the-most-frequent-element/   ║
 * ║                                                                            ║
 * ║ [ ] LC 2779 - Max Beauty After Operations         | M  | Sort+2Ptr Values║
 * ║     https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/ ║
 * ║                                                                            ║
 * ║  --- Bitmask DP + Window ---                                               ║
 * ║                                                                            ║
 * ║ [ ] LC 1358 - Substrings with All Three Chars     | M  | Mask Coverage   ║
 * ║     https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/ ║
 * ║                                                                            ║
 * ║  --- Circular Variable Window ---                                          ║
 * ║                                                                            ║
 * ║ [ ] LC 1658 - Min Ops Reduce X to Zero           | M  | Complement Win   ║
 * ║     https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/   ║
 * ║                                                                            ║
 * ║  --- Modular Arithmetic + Window ---                                       ║
 * ║                                                                            ║
 * ║ [ ] LC 523  - Continuous Subarray Sum (mult K)    | M  | PrefMod+FirstOcc ║
 * ║     https://leetcode.com/problems/continuous-subarray-sum/                  ║
 * ║                                                                            ║
 * ║ [ ] LC 1590 - Make Sum Divisible by P             | M  | ShortestModSub   ║
 * ║     https://leetcode.com/problems/make-sum-divisible-by-p/                  ║
 * ║                                                                            ║
 * ║ [ ] LC 1497 - Check Array Pairs Divisible K       | M  | RemainderPairing ║
 * ║     https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/  ║
 * ║                                                                            ║
 * ║ [ ] CSES 1662 - Subarray Divisibility             | M  | PrefMod + Count ║
 * ║     https://cses.fi/problemset/task/1662                                    ║
 * ║                                                                            ║
 * ║                                                                            ║
 * ║  ─────────── MODULE 14: VARIABLE WINDOW CODEFORCES PROBLEMS ───────────    ║
 * ║                                                                            ║
 * ║  --- CF 800-1200 (Easy) ---                                                ║
 * ║                                                                            ║
 * ║ [ ] CF 1538B - Friends and Candies              | E  (800)  | Basic        ║
 * ║     https://codeforces.com/problemset/problem/1538/B                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1551B1 - Wonderful String (Easy)          | E  (900)  | Basic      ║
 * ║     https://codeforces.com/problemset/problem/1551/B1                      ║
 * ║                                                                            ║
 * ║  --- CF 1200-1600 (Medium) ---                                             ║
 * ║                                                                            ║
 * ║ [ ] CF 1692E - Binary Deque                     | M  (1200) | Var Window  ║
 * ║     https://codeforces.com/problemset/problem/1692/E                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1354B - Ternary String                   | M  (1200) | Min Var Win ║
 * ║     https://codeforces.com/problemset/problem/1354/B                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1676F - Longest Strike                   | M  (1300) | Var Win     ║
 * ║     https://codeforces.com/problemset/problem/1676/F                       ║
 * ║                                                                            ║
 * ║ [ ] CF 279B  - Books                            | M  (1400) | Var Win Sum ║
 * ║     https://codeforces.com/problemset/problem/279/B                        ║
 * ║                                                                            ║
 * ║ [ ] CF 602B  - Approximating a Constant Range   | M  (1500) | Var+Deque   ║
 * ║     https://codeforces.com/problemset/problem/602/B                        ║
 * ║                                                                            ║
 * ║ [ ] CF 1343C - Alternating Subsequence          | M  (1200) | Greedy      ║
 * ║     https://codeforces.com/problemset/problem/1343/C                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1480B - The Great Hero                   | M  (1400) | Greedy Sim  ║
 * ║     https://codeforces.com/problemset/problem/1480/B                       ║
 * ║                                                                            ║
 * ║  --- CF 1600-2000 (Hard) ---                                               ║
 * ║                                                                            ║
 * ║ [ ] CF 1360F - Spy-string                       | H  (1700) | Brute+SW    ║
 * ║     https://codeforces.com/problemset/problem/1360/F                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1915F - Grading                          | H  (1800) | SW + Sort   ║
 * ║     https://codeforces.com/problemset/problem/1915/F                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1409E - Two Platforms                    | H  (1800) | Sort+BS+SW  ║
 * ║     https://codeforces.com/problemset/problem/1409/E                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1611E2 - Escape The Maze (Hard)          | H  (1700) | BFS+SW      ║
 * ║     https://codeforces.com/problemset/problem/1611/E2                      ║
 * ║                                                                            ║
 * ║ [ ] CF 1462D - Add to Neighbour and Remove      | M  (1400) | Greedy SW   ║
 * ║     https://codeforces.com/problemset/problem/1462/D                       ║
 * ║                                                                            ║
 * ║  --- CF 2000-2400+ (Expert/GM) ---                                         ║
 * ║                                                                            ║
 * ║ [ ] CF 1548B - Integers Have Friends             | EX (2000) | GCD+SW     ║
 * ║     https://codeforces.com/problemset/problem/1548/B                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1906D - Merge Equals Interleaving         | EX (2100) | SW+Sim    ║
 * ║     https://codeforces.com/problemset/problem/1906/D                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1918D - Blocking Elements                 | GM (2400) | BS+SW      ║
 * ║     https://codeforces.com/problemset/problem/1918/D                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1709D - Rorororobot                       | EX (2000) | SpTable+2P ║
 * ║     https://codeforces.com/problemset/problem/1709/D                       ║
 * ║                                                                            ║
 * ║ [ ] CF 1537E2 - Erase and Extend (Hard)          | EX (2100) | String+SW  ║
 * ║     https://codeforces.com/problemset/problem/1537/E2                      ║
 * ║                                                                            ║
 * ║ [ ] CF 1695D - Tree Queries                      | GM (2300) | DFS+2Ptr   ║
 * ║     https://codeforces.com/problemset/problem/1695/D                       ║
 * ║                                                                            ║
 * ╚══════════════════════════════════════════════════════════════════════════════╝
 *
 *
 * ============================================================================
 *                     QUICK REFERENCE BY TECHNIQUE
 * ============================================================================
 *
 *  🔹 OPPOSITE DIRECTION (CONVERGING):
 *     LC 1, 167, 15, 16, 18, 11, 42, 977, 344, 881, 948, 923, 1498, 2422
 *
 *  🔹 SAME DIRECTION (READER-WRITER):
 *     LC 26, 27, 80, 283, 88, 349, 350, 905, 922
 *
 *  🔹 FAST & SLOW (FLOYD'S CYCLE):
 *     LC 141, 142, 287, 202, 876, 19, 143, 457, 2095
 *
 *  🔹 DUTCH NATIONAL FLAG / PARTITION:
 *     LC 75, 905, 922, 2161
 *
 *  🔹 N-SUM (2SUM, 3SUM, 4SUM, KSUM):
 *     LC 1, 167, 15, 16, 259, 18, 454, 923, CSES 1640-1642
 *
 *  🔹 TRAPPING RAIN WATER:
 *     LC 42 (1D), LC 407 (2D)
 *
 *  🔹 FIXED SLIDING WINDOW (BASIC):
 *     LC 643, 1456, 1343, 2090, 1052, 1984, 2379, 2461
 *
 *  🔹 FIXED SLIDING WINDOW + DEQUE:
 *     LC 239, 1438, 480, CSES 1077, CSES 1076
 *
 *  🔹 FIXED SLIDING WINDOW + HASHING (ANAGRAM):
 *     LC 567, 438, 242, 187, 1876, 2156
 *
 *  🔹 VARIABLE WINDOW (EXPAND-SHRINK):
 *     LC 209, 1004, 1493, 487, 2024, 1658, 713
 *
 *  🔹 VARIABLE WINDOW (AT MOST K DISTINCT):
 *     LC 340, 159, 904, 992, 1695, 2958
 *
 *  🔹 VARIABLE WINDOW (EXACT K TRICK):
 *     LC 992, 930, 1248, 2962, 1358, 2537, 2799
 *
 *  🔹 VARIABLE WINDOW (ADVANCED / HARD):
 *     LC 76, 424, 3, 795, 862, 395, 1438, 2302, 2009, 2516, 1574
 *
 *  🔹 BINARY SEARCH + TWO POINTER:
 *     LC 719, 658, 2300, 2824, 532, 1679, 881, 1855
 *
 * ============================================================================
 */

// This file is a reference cheat sheet — no executable code.
// Open the individual module folders for theory and implementations.

int main() {
    // Track your progress above! Mark [ ] → [✅] as you solve each problem.
    return 0;
}

