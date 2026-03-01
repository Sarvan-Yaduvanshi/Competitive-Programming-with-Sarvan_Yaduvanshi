/*
 * ============================================================================
 *                    🏆 GREEDY ALGORITHMS — MASTER PROBLEM CHEAT SHEET
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Level   : Zero to Grandmaster (GM)
 *  Total   : 120+ Curated Problems
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
 * ║                   MODULE 01: GREEDY FUNDAMENTALS                       ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 455   - Assign Cookies                | E  | Basic Greedy       ║
 * ║     https://leetcode.com/problems/assign-cookies/                      ║
 * ║                                                                        ║
 * ║ [ ] LC 860   - Lemonade Change                | E  | Greedy Simulation ║
 * ║     https://leetcode.com/problems/lemonade-change/                     ║
 * ║                                                                        ║
 * ║ [ ] LC 2224  - Min Operations Convert Time    | E  | Greedy Coins      ║
 * ║     https://leetcode.com/problems/minimum-number-of-operations-to-convert-time/ ║
 * ║                                                                        ║
 * ║ [ ] GFG      - Greedy Intro (Activity Select) | E  | Activity Selection║
 * ║     https://practice.geeksforgeeks.org/problems/activity-selection/    ║
 * ║                                                                        ║
 * ║ [ ] CF 1350A - Orac and Factors               | E  (800)  | Basic     ║
 * ║     https://codeforces.com/problemset/problem/1350/A                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1399A - Remove Smallest                | E  (800)  | Basic     ║
 * ║     https://codeforces.com/problemset/problem/1399/A                   ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                   MODULE 02: BASIC GREEDY PATTERNS                     ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] GFG      - Fractional Knapsack            | E  | Value/Weight Sort ║
 * ║     https://practice.geeksforgeeks.org/problems/fractional-knapsack/   ║
 * ║                                                                        ║
 * ║ [ ] GFG      - Job Sequencing Problem         | M  | Deadline Greedy   ║
 * ║     https://practice.geeksforgeeks.org/problems/job-sequencing-problem/║
 * ║                                                                        ║
 * ║ [ ] GFG      - Huffman Encoding               | M  | Priority Queue    ║
 * ║     https://practice.geeksforgeeks.org/problems/huffman-encoding/      ║
 * ║                                                                        ║
 * ║ [ ] LC 1710  - Max Units on a Truck           | E  | Sort by unit      ║
 * ║     https://leetcode.com/problems/maximum-units-on-a-truck/            ║
 * ║                                                                        ║
 * ║ [ ] CSES 1074 - Stick Lengths                 | E  | Median Greedy     ║
 * ║     https://cses.fi/problemset/task/1074                               ║
 * ║                                                                        ║
 * ║ [ ] LC 2037  - Min Moves to Seat Everyone     | E  | Sort Both Arrays  ║
 * ║     https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone/ ║
 * ║                                                                        ║
 * ║ [ ] CF 1525A - Potion-making                  | E  (800)  | GCD       ║
 * ║     https://codeforces.com/problemset/problem/1525/A                   ║
 * ║                                                                        ║
 * ║ [ ] LC 1005  - Max Sum After K Negations      | E  | Sort + Greedy     ║
 * ║     https://leetcode.com/problems/maximize-sum-of-array-after-k-negations/ ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                   MODULE 03: SORTING-BASED GREEDY                      ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 435   - Non-overlapping Intervals      | M  | Earliest End Sort ║
 * ║     https://leetcode.com/problems/non-overlapping-intervals/           ║
 * ║                                                                        ║
 * ║ [ ] LC 452   - Min Arrows to Burst Balloons   | M  | Interval Greedy   ║
 * ║     https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/ ║
 * ║                                                                        ║
 * ║ [ ] LC 1029  - Two City Scheduling             | M  | Cost Difference   ║
 * ║     https://leetcode.com/problems/two-city-scheduling/                 ║
 * ║                                                                        ║
 * ║ [ ] LC 253   - Meeting Rooms II                | M  | Min Heap / Sweep  ║
 * ║     https://leetcode.com/problems/meeting-rooms-ii/                    ║
 * ║                                                                        ║
 * ║ [ ] GFG      - Minimum Platforms               | M  | Sweep Line       ║
 * ║     https://practice.geeksforgeeks.org/problems/minimum-platforms/     ║
 * ║                                                                        ║
 * ║ [ ] CSES 1629 - Movie Festival                 | M  | Activity Select   ║
 * ║     https://cses.fi/problemset/task/1629                               ║
 * ║                                                                        ║
 * ║ [ ] CSES 1630 - Tasks and Deadlines            | M  | SJF Scheduling    ║
 * ║     https://cses.fi/problemset/task/1630                               ║
 * ║                                                                        ║
 * ║ [ ] CF 1353D - Constructing the Array          | M  (1600) | PQ Sort   ║
 * ║     https://codeforces.com/problemset/problem/1353/D                   ║
 * ║                                                                        ║
 * ║ [ ] LC 2580  - Count Ways Group Overlapping    | M  | Interval Merge    ║
 * ║     https://leetcode.com/problems/count-ways-to-group-overlapping-ranges/ ║
 * ║                                                                        ║
 * ║ [ ] LC 948   - Bag of Tokens                   | M  | Sort + 2 Pointer  ║
 * ║     https://leetcode.com/problems/bag-of-tokens/                       ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                   MODULE 04: TWO POINTER + GREEDY HYBRIDS              ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 56    - Merge Intervals                 | M  | Sort + Merge      ║
 * ║     https://leetcode.com/problems/merge-intervals/                     ║
 * ║                                                                        ║
 * ║ [ ] LC 986   - Interval List Intersections     | M  | Two Pointer       ║
 * ║     https://leetcode.com/problems/interval-list-intersections/         ║
 * ║                                                                        ║
 * ║ [ ] LC 252   - Meeting Rooms                   | E  | Sort + Check      ║
 * ║     https://leetcode.com/problems/meeting-rooms/                       ║
 * ║                                                                        ║
 * ║ [ ] LC 763   - Partition Labels                | M  | Last Occurrence   ║
 * ║     https://leetcode.com/problems/partition-labels/                    ║
 * ║                                                                        ║
 * ║ [ ] LC 2410  - Max Matching Players+Trainers   | M  | Sort + 2 Pointer  ║
 * ║     https://leetcode.com/problems/maximum-matching-of-players-with-trainers/ ║
 * ║                                                                        ║
 * ║ [ ] CSES 1640 - Sum of Two Values              | M  | Two Pointer/Map   ║
 * ║     https://cses.fi/problemset/task/1640                               ║
 * ║                                                                        ║
 * ║ [ ] CF 1462C - Unique Number                   | M  (1100) | Greedy    ║
 * ║     https://codeforces.com/problemset/problem/1462/C                   ║
 * ║                                                                        ║
 * ║ [ ] LC 881   - Boats to Save People            | M  | Two Pointer       ║
 * ║     https://leetcode.com/problems/boats-to-save-people/                ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                   MODULE 05: GREEDY ON ARRAYS                          ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 55    - Jump Game                       | M  | Farthest Reach    ║
 * ║     https://leetcode.com/problems/jump-game/                           ║
 * ║                                                                        ║
 * ║ [ ] LC 45    - Jump Game II                    | M  | BFS / Greedy      ║
 * ║     https://leetcode.com/problems/jump-game-ii/                        ║
 * ║                                                                        ║
 * ║ [ ] LC 1306  - Jump Game III                   | M  | BFS + Greedy      ║
 * ║     https://leetcode.com/problems/jump-game-iii/                       ║
 * ║                                                                        ║
 * ║ [ ] LC 1345  - Jump Game IV                    | H  | BFS + Map         ║
 * ║     https://leetcode.com/problems/jump-game-iv/                        ║
 * ║                                                                        ║
 * ║ [ ] LC 134   - Gas Station                     | M  | Circular Greedy   ║
 * ║     https://leetcode.com/problems/gas-station/                         ║
 * ║                                                                        ║
 * ║ [ ] LC 135   - Candy                           | H  | Two-Pass Greedy   ║
 * ║     https://leetcode.com/problems/candy/                               ║
 * ║                                                                        ║
 * ║ [ ] LC 561   - Array Partition                 | E  | Sort + Pair       ║
 * ║     https://leetcode.com/problems/array-partition/                     ║
 * ║                                                                        ║
 * ║ [ ] LC 846   - Hand of Straights               | M  | Map + Greedy      ║
 * ║     https://leetcode.com/problems/hand-of-straights/                   ║
 * ║                                                                        ║
 * ║ [ ] CSES 2216 - Collecting Numbers             | M  | Inversion Count   ║
 * ║     https://cses.fi/problemset/task/2216                               ║
 * ║                                                                        ║
 * ║ [ ] CF 1472D - Even-Odd Game                   | M  (1200) | Sort Desc ║
 * ║     https://codeforces.com/problemset/problem/1472/D                   ║
 * ║                                                                        ║
 * ║ [ ] LC 1509  - Min Diff Between Max & Min      | M  | Sort + Window     ║
 * ║     https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/ ║
 * ║                                                                        ║
 * ║ [ ] LC 1899  - Merge Triplets to Form Target   | M  | Greedy Filter     ║
 * ║     https://leetcode.com/problems/merge-triplets-to-form-target-triplet/ ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                   MODULE 06: GREEDY ON STRINGS                         ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 402   - Remove K Digits                 | M  | Monotone Stack    ║
 * ║     https://leetcode.com/problems/remove-k-digits/                     ║
 * ║                                                                        ║
 * ║ [ ] LC 316   - Remove Duplicate Letters         | M  | Stack + Greedy   ║
 * ║     https://leetcode.com/problems/remove-duplicate-letters/            ║
 * ║                                                                        ║
 * ║ [ ] LC 1081  - Smallest Subsequence of Distinct | M  | Same as LC 316   ║
 * ║     https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/ ║
 * ║                                                                        ║
 * ║ [ ] LC 767   - Reorganize String               | M  | Max-Heap Greedy   ║
 * ║     https://leetcode.com/problems/reorganize-string/                   ║
 * ║                                                                        ║
 * ║ [ ] LC 984   - String Without AAA or BBB       | M  | Balanced Greedy   ║
 * ║     https://leetcode.com/problems/string-without-aaa-or-bbb/          ║
 * ║                                                                        ║
 * ║ [ ] LC 1663  - Smallest String Numeric Value    | M  | Fill from End    ║
 * ║     https://leetcode.com/problems/smallest-string-with-a-given-numeric-value/ ║
 * ║                                                                        ║
 * ║ [ ] LC 649   - Dota2 Senate                    | M  | Queue Greedy      ║
 * ║     https://leetcode.com/problems/dota2-senate/                        ║
 * ║                                                                        ║
 * ║ [ ] LC 1405  - Longest Happy String             | M  | PQ Greedy        ║
 * ║     https://leetcode.com/problems/longest-happy-string/                ║
 * ║                                                                        ║
 * ║ [ ] CF 1681B - Card Game                       | M  (1100) | String    ║
 * ║     https://codeforces.com/problemset/problem/1681/B                   ║
 * ║                                                                        ║
 * ║ [ ] LC 2182  - Construct String Repeat Limit    | M  | PQ + Greedy      ║
 * ║     https://leetcode.com/problems/construct-string-with-repeat-limit/  ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                   MODULE 07: GREEDY ON GRAPHS                          ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] CSES 1675 - Road Reparation (MST)          | M  | Kruskal's MST    ║
 * ║     https://cses.fi/problemset/task/1675                               ║
 * ║                                                                        ║
 * ║ [ ] CSES 1671 - Shortest Routes I (Dijkstra)   | M  | Dijkstra         ║
 * ║     https://cses.fi/problemset/task/1671                               ║
 * ║                                                                        ║
 * ║ [ ] LC 1584  - Min Cost Connect All Points     | M  | Prim's / Kruskal ║
 * ║     https://leetcode.com/problems/min-cost-to-connect-all-points/      ║
 * ║                                                                        ║
 * ║ [ ] LC 743   - Network Delay Time              | M  | Dijkstra         ║
 * ║     https://leetcode.com/problems/network-delay-time/                  ║
 * ║                                                                        ║
 * ║ [ ] LC 1135  - Connecting Cities Min Cost       | M  | MST              ║
 * ║     https://leetcode.com/problems/connecting-cities-with-minimum-cost/ ║
 * ║                                                                        ║
 * ║ [ ] CF 1095F - Make It Connected               | H  (2100) | MST      ║
 * ║     https://codeforces.com/problemset/problem/1095/F                   ║
 * ║                                                                        ║
 * ║ [ ] GFG      - Prim's MST                      | M  | Prim's Algorithm ║
 * ║     https://practice.geeksforgeeks.org/problems/minimum-spanning-tree/ ║
 * ║                                                                        ║
 * ║ [ ] GFG      - Dijkstra's Algorithm             | M  | Dijkstra        ║
 * ║     https://practice.geeksforgeeks.org/problems/implementing-dijkstra/ ║
 * ║                                                                        ║
 * ║ [ ] LC 787   - Cheapest Flights K Stops         | M  | Modified Dijkstra║
 * ║     https://leetcode.com/problems/cheapest-flights-within-k-stops/     ║
 * ║                                                                        ║
 * ║ [ ] CSES 1676 - Road Construction               | M  | DSU             ║
 * ║     https://cses.fi/problemset/task/1676                               ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                   MODULE 08: GREEDY + DATA STRUCTURES                  ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 621   - Task Scheduler                  | M  | Greedy + Math     ║
 * ║     https://leetcode.com/problems/task-scheduler/                      ║
 * ║                                                                        ║
 * ║ [ ] LC 1353  - Max Number of Events Attended    | M  | PQ + Sort        ║
 * ║     https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/ ║
 * ║                                                                        ║
 * ║ [ ] LC 502   - IPO                             | H  | Two PQ Greedy     ║
 * ║     https://leetcode.com/problems/ipo/                                 ║
 * ║                                                                        ║
 * ║ [ ] LC 871   - Min Refueling Stops             | H  | Max-Heap Greedy   ║
 * ║     https://leetcode.com/problems/minimum-number-of-refueling-stops/   ║
 * ║                                                                        ║
 * ║ [ ] LC 630   - Course Schedule III             | H  | PQ + Sort         ║
 * ║     https://leetcode.com/problems/course-schedule-iii/                 ║
 * ║                                                                        ║
 * ║ [ ] CSES 1164 - Room Allocation                 | M  | Multiset / PQ   ║
 * ║     https://cses.fi/problemset/task/1164                               ║
 * ║                                                                        ║
 * ║ [ ] LC 1834  - Single Threaded CPU             | M  | PQ Simulation     ║
 * ║     https://leetcode.com/problems/single-threaded-cpu/                 ║
 * ║                                                                        ║
 * ║ [ ] LC 1046  - Last Stone Weight                | E  | Max-Heap         ║
 * ║     https://leetcode.com/problems/last-stone-weight/                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1700C - Helping the Nature              | M  (1700) | PQ       ║
 * ║     https://codeforces.com/problemset/problem/1700/C                   ║
 * ║                                                                        ║
 * ║ [ ] LC 295   - Find Median from Data Stream     | H  | Two Heaps       ║
 * ║     https://leetcode.com/problems/find-median-from-data-stream/        ║
 * ║                                                                        ║
 * ║ [ ] LC 1675  - Minimize Deviation in Array      | H  | PQ Greedy       ║
 * ║     https://leetcode.com/problems/minimize-deviation-in-array/         ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                   MODULE 09: GREEDY + BINARY SEARCH                    ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 410   - Split Array Largest Sum          | H  | BS + Greedy Chk  ║
 * ║     https://leetcode.com/problems/split-array-largest-sum/             ║
 * ║                                                                        ║
 * ║ [ ] LC 1011  - Capacity to Ship Packages        | M  | BS + Greedy Chk  ║
 * ║     https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/ ║
 * ║                                                                        ║
 * ║ [ ] LC 875   - Koko Eating Bananas              | M  | BS on Answer     ║
 * ║     https://leetcode.com/problems/koko-eating-bananas/                 ║
 * ║                                                                        ║
 * ║ [ ] CSES 1620 - Factory Machines                | M  | BS + Greedy      ║
 * ║     https://cses.fi/problemset/task/1620                               ║
 * ║                                                                        ║
 * ║ [ ] CF 1623C - Balanced Stone Heaps             | H  (1800) | BS+Grdy  ║
 * ║     https://codeforces.com/problemset/problem/1623/C                   ║
 * ║                                                                        ║
 * ║ [ ] LC 2064  - Minimized Maximum Products       | M  | BS + Greedy      ║
 * ║     https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/ ║
 * ║                                                                        ║
 * ║ [ ] LC 1482  - Min Days to Make Bouquets        | M  | BS + Greedy Chk  ║
 * ║     https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/ ║
 * ║                                                                        ║
 * ║ [ ] LC 2226  - Max Candies Allocated             | M  | BS on Answer    ║
 * ║     https://leetcode.com/problems/maximum-candies-allocated-to-k-children/ ║
 * ║                                                                        ║
 * ║ [ ] CF 1579E2- Array Optimization               | H  (2100) | BS+BIT  ║
 * ║     https://codeforces.com/problemset/problem/1579/E2                  ║
 * ║                                                                        ║
 * ║ [ ] LC 774   - Minimize Max Distance Gas Station | H  | BS + Greedy    ║
 * ║     https://leetcode.com/problems/minimize-max-distance-to-gas-station/║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                   MODULE 10: INTERVAL GREEDY PROBLEMS                  ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 57    - Insert Interval                  | M  | Interval Merge   ║
 * ║     https://leetcode.com/problems/insert-interval/                     ║
 * ║                                                                        ║
 * ║ [ ] LC 1235  - Max Profit Job Scheduling        | H  | DP + BS (Bridge) ║
 * ║     https://leetcode.com/problems/maximum-profit-in-job-scheduling/    ║
 * ║                                                                        ║
 * ║ [ ] LC 646   - Max Length of Pair Chain          | M  | Interval Greedy  ║
 * ║     https://leetcode.com/problems/maximum-length-of-pair-chain/        ║
 * ║                                                                        ║
 * ║ [ ] LC 759   - Employee Free Time               | H  | Merge + Sweep    ║
 * ║     https://leetcode.com/problems/employee-free-time/                  ║
 * ║                                                                        ║
 * ║ [ ] CSES 1632 - Movie Festival II               | H  | Multiset Greedy  ║
 * ║     https://cses.fi/problemset/task/1632                               ║
 * ║                                                                        ║
 * ║ [ ] CF 1472E - Correct Placement                | M  (1700) | Sort+BS  ║
 * ║     https://codeforces.com/problemset/problem/1472/E                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1141F2- Same Sum Blocks (Hard)           | H  (1900) | Sweep   ║
 * ║     https://codeforces.com/problemset/problem/1141/F2                  ║
 * ║                                                                        ║
 * ║ [ ] LC 1288  - Remove Covered Intervals          | M  | Sort + Count   ║
 * ║     https://leetcode.com/problems/remove-covered-intervals/            ║
 * ║                                                                        ║
 * ║ [ ] LC 352   - Data Stream as Disjoint Intervals | H  | TreeMap/Set    ║
 * ║     https://leetcode.com/problems/data-stream-as-disjoint-intervals/   ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                   MODULE 11: GREEDY ON TREES                           ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] LC 968   - Binary Tree Cameras              | H  | Leaf-Up Greedy   ║
 * ║     https://leetcode.com/problems/binary-tree-cameras/                 ║
 * ║                                                                        ║
 * ║ [ ] LC 310   - Minimum Height Trees              | M  | Leaf Pruning    ║
 * ║     https://leetcode.com/problems/minimum-height-trees/                ║
 * ║                                                                        ║
 * ║ [ ] LC 834   - Sum of Distances in Tree          | H  | Re-rooting     ║
 * ║     https://leetcode.com/problems/sum-of-distances-in-tree/            ║
 * ║                                                                        ║
 * ║ [ ] CSES 1130 - Tree Matching                    | M  | DP on Tree     ║
 * ║     https://cses.fi/problemset/task/1130                               ║
 * ║                                                                        ║
 * ║ [ ] LC 2246  - Longest Path Diff Adjacent        | H  | DFS + Greedy   ║
 * ║     https://leetcode.com/problems/longest-path-with-different-adjacent-characters/ ║
 * ║                                                                        ║
 * ║ [ ] LC 1325  - Delete Leaves with Given Value    | M  | Post-order     ║
 * ║     https://leetcode.com/problems/delete-leaves-with-a-given-value/    ║
 * ║                                                                        ║
 * ║ [ ] CF 1092F - Tree with Maximum Cost            | H  (2200) | Reroot ║
 * ║     https://codeforces.com/problemset/problem/1092/F                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1182D - Complete Mirror                   | EX (2400) | Tree   ║
 * ║     https://codeforces.com/problemset/problem/1182/D                   ║
 * ║                                                                        ║
 * ║ [ ] LC 124   - Binary Tree Max Path Sum          | H  | DFS Greedy     ║
 * ║     https://leetcode.com/problems/binary-tree-maximum-path-sum/        ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                   MODULE 12: MATROID THEORY & EXCHANGE ARGUMENTS       ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] CF 1428C - ABBB                             | M  (1400) | Stack    ║
 * ║     https://codeforces.com/problemset/problem/1428/C                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1579D - Productive Meeting                | M  (1400) | PQ      ║
 * ║     https://codeforces.com/problemset/problem/1579/D                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1363C - Game on Leaves                    | M  (1600) | Tree    ║
 * ║     https://codeforces.com/problemset/problem/1363/C                   ║
 * ║                                                                        ║
 * ║ [ ] CSES 1666 - Building Roads                   | M  | DSU/BFS        ║
 * ║     https://cses.fi/problemset/task/1666                               ║
 * ║                                                                        ║
 * ║ [ ] LC 948   - Bag of Tokens                     | M  | Exchange Arg    ║
 * ║     https://leetcode.com/problems/bag-of-tokens/                       ║
 * ║                                                                        ║
 * ║ [ ] CF 1154D - Walking Robot                     | M  (1500) | Greedy  ║
 * ║     https://codeforces.com/problemset/problem/1154/D                   ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                   MODULE 13: ADVANCED GREEDY                           ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] CF 865D  - Buy Low Sell High                | EX (2200) | Regret   ║
 * ║     https://codeforces.com/problemset/problem/865/D                    ║
 * ║                                                                        ║
 * ║ [ ] CF 1348C - Phoenix and Distribution          | M  (1600) | Greedy  ║
 * ║     https://codeforces.com/problemset/problem/1348/C                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1700D - River Locks                       | H  (1900) | Greedy  ║
 * ║     https://codeforces.com/problemset/problem/1700/D                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1657D - Painting the Array                | H  (1800) | Greedy  ║
 * ║     https://codeforces.com/problemset/problem/1657/D                   ║
 * ║                                                                        ║
 * ║ [ ] CSES 2169 - Nested Ranges Count              | H  | BIT + Sort    ║
 * ║     https://cses.fi/problemset/task/2169                               ║
 * ║                                                                        ║
 * ║ [ ] LC 871   - Min Refueling Stops (Regret)      | H  | Regret Greedy  ║
 * ║     https://leetcode.com/problems/minimum-number-of-refueling-stops/   ║
 * ║                                                                        ║
 * ║ [ ] LC 630   - Course Schedule III (Regret)      | H  | Regret PQ      ║
 * ║     https://leetcode.com/problems/course-schedule-iii/                 ║
 * ║                                                                        ║
 * ║ [ ] CF 1491D - Zookeeper and the Infinite Zoo    | H  (1800) | Bits   ║
 * ║     https://codeforces.com/problemset/problem/1491/D                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1515C - Phoenix and Towers               | M  (1600) | Balance  ║
 * ║     https://codeforces.com/problemset/problem/1515/C                   ║
 * ║                                                                        ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║              MODULE 14: CODEFORCES GM-LEVEL GREEDY                     ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║                                                                        ║
 * ║ [ ] CF 1559D2- Mocha and Diana (Hard)           | GM (2500) | DSU+Grdy ║
 * ║     https://codeforces.com/problemset/problem/1559/D2                  ║
 * ║                                                                        ║
 * ║ [ ] CF 1637D - Yet Another Sorting Problem       | EX (2100) | Parity ║
 * ║     https://codeforces.com/problemset/problem/1637/D                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1706D - Chopping Carrots                  | EX (2100) | BS+Grdy║
 * ║     https://codeforces.com/problemset/problem/1706/D                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1918D - Blocking Elements                 | GM (2400) | BS+Stk ║
 * ║     https://codeforces.com/problemset/problem/1918/D                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1842D - Tenzing and Animal Friends        | EX (2200) | Graph  ║
 * ║     https://codeforces.com/problemset/problem/1842/D                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1799D2- Hot Start (Hard)                  | GM (2400) | DP+Grdy║
 * ║     https://codeforces.com/problemset/problem/1799/D2                  ║
 * ║                                                                        ║
 * ║ [ ] CF 1762D - GCD Queries                       | EX (2200) | Intrctv║
 * ║     https://codeforces.com/problemset/problem/1762/D                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1667B - Optimal Partition                  | EX (2100) | SegTree║
 * ║     https://codeforces.com/problemset/problem/1667/B                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1793D - Moscow Gorillas                    | H  (1900) | Math  ║
 * ║     https://codeforces.com/problemset/problem/1793/D                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1810D - Climbing the Tree                  | EX (2100) | Intrctv║
 * ║     https://codeforces.com/problemset/problem/1810/D                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1927E - Klever Permutation                 | H  (1900) | Constr║
 * ║     https://codeforces.com/problemset/problem/1927/E                   ║
 * ║                                                                        ║
 * ║ [ ] CF 1872E - Data Structures Fan               | EX (2100) | XOR    ║
 * ║     https://codeforces.com/problemset/problem/1872/E                   ║
 * ║                                                                        ║
 * ╚══════════════════════════════════════════════════════════════════════════╝
 *
 * ============================================================================
 *                         QUICK REFERENCE BY TECHNIQUE
 * ============================================================================
 *
 *  🔹 SORT + GREEDY:
 *     LC 455, 435, 452, 1029, 253, 1710, 948, 561, 881
 *
 *  🔹 PRIORITY QUEUE GREEDY:
 *     LC 621, 502, 871, 630, 1353, 1046, 767, 1834, 295, 1675
 *
 *  🔹 INTERVAL GREEDY:
 *     LC 56, 57, 435, 452, 253, 986, 763, 646, 759, 1288, 352
 *
 *  🔹 BINARY SEARCH + GREEDY:
 *     LC 410, 1011, 875, 2064, 1482, 2226, 774
 *
 *  🔹 STACK-BASED GREEDY:
 *     LC 402, 316, 1081, 2182
 *
 *  🔹 TWO-POINTER GREEDY:
 *     LC 455, 881, 948, 2410
 *
 *  🔹 REGRET-BASED GREEDY:
 *     CF 865D, LC 871, LC 630
 *
 *  🔹 CONSTRUCTION GREEDY:
 *     CF 1927E, CF 1348C, LC 984, LC 1405
 *
 *  🔹 MST / GRAPH GREEDY:
 *     CSES 1675, CSES 1671, LC 1584, LC 743, CF 1095F
 *
 *  🔹 TREE GREEDY:
 *     LC 968, LC 310, LC 834, CSES 1130, LC 2246, LC 124
 *
 * ============================================================================
 */

// This file is a reference cheat sheet — no executable code.
// Open the individual module folders for theory and implementations.

int main() {
    // Track your progress above! Mark [ ] → [✅] as you solve each problem.
    return 0;
}

