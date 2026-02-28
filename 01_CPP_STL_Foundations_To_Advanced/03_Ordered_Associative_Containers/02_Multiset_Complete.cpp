/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — MULTISET COMPLETE GUIDE                                     ║
║           From Zero to Grandmaster — Sorted with Duplicates                ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. multiset vs set — Key Differences
 2. Erase-One Trick (CRITICAL BUG TO AVOID)
 3. count(), equal_range()
 4. Sliding Window Median (GM-Level Pattern)
 5. CP Problem: Towers (CSES)

MULTISET:
─────────
  Like set, but ALLOWS DUPLICATES.
  multiset<int> ms = {3, 1, 4, 1, 5, 1} → {1, 1, 1, 3, 4, 5}

  CRITICAL DIFFERENCE:
    ms.erase(1)         → Removes ALL 1s!      {3, 4, 5}
    ms.erase(ms.find(1)) → Removes ONE 1!      {1, 1, 3, 4, 5}

  This is the #1 bug in multiset usage. NEVER FORGET!
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC OPERATIONS
// ═══════════════════════════════════════════════════════════════

void demonstrateBasicOps() {
    cout << "═══ MULTISET BASICS ═══\n\n";

    multiset<int> ms;
    ms.insert(5);
    ms.insert(3);
    ms.insert(5);  // Duplicate ALLOWED!
    ms.insert(1);
    ms.insert(5);  // Third copy!
    ms.insert(3);

    cout << "multiset: ";
    for (int x : ms) cout << x << " ";
    cout << "\n";
    cout << "size: " << ms.size() << "\n";
    cout << "count(5): " << ms.count(5) << "\n";
    cout << "count(3): " << ms.count(3) << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: ERASE-ONE TRICK (THE #1 BUG)
// ═══════════════════════════════════════════════════════════════
/*
 DRY RUN:
   ms = {1, 1, 1, 3, 3, 5, 5, 5}

   ms.erase(5)           → {1, 1, 1, 3, 3}  (ALL 5s gone!)
   ms.erase(ms.find(5))  → {1, 1, 1, 3, 3, 5, 5}  (ONE 5 gone!)

 THIS IS THE MOST COMMON BUG IN CP WITH MULTISET.
*/

void demonstrateEraseTrick() {
    cout << "═══ ERASE-ONE TRICK ═══\n\n";

    // WRONG: erase by value removes ALL
    multiset<int> ms1 = {1, 2, 2, 3, 3, 3};
    cout << "Before: ";
    for (int x : ms1) cout << x << " ";
    cout << "\n";

    ms1.erase(3);  // Removes ALL 3s!
    cout << "erase(3) [WRONG if you want one]: ";
    for (int x : ms1) cout << x << " ";
    cout << " (all 3s gone!)\n\n";

    // CORRECT: erase by iterator removes ONE
    multiset<int> ms2 = {1, 2, 2, 3, 3, 3};
    cout << "Before: ";
    for (int x : ms2) cout << x << " ";
    cout << "\n";

    ms2.erase(ms2.find(3));  // Removes ONE 3!
    cout << "erase(find(3)) [CORRECT]: ";
    for (int x : ms2) cout << x << " ";
    cout << " (one 3 gone)\n\n";

    // equal_range — get all copies of a value
    multiset<int> ms3 = {1, 2, 2, 3, 3, 3, 4, 5};
    auto [lo, hi] = ms3.equal_range(3);
    cout << "equal_range(3): ";
    for (auto it = lo; it != hi; ++it) cout << *it << " ";
    cout << "(count = " << distance(lo, hi) << ")\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: SLIDING WINDOW MEDIAN (GM-LEVEL)
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Maintain median of a sliding window of size K.

 APPROACH: Two multisets — lower half and upper half.
   lower: contains smaller half (max-oriented)
   upper: contains larger half (min-oriented)
   Median = max of lower half (or avg for even size)

 DRY RUN: arr = [1, 3, -1, -3, 5, 3, 6, 7], K = 3
   Window [1,3,-1]: sorted = [-1,1,3] → median = 1
   Window [3,-1,-3]: sorted = [-3,-1,3] → median = -1
   Window [-1,-3,5]: sorted = [-3,-1,5] → median = -1
   ...
*/

void slidingWindowMedian() {
    cout << "═══ SLIDING WINDOW MEDIAN ═══\n\n";

    vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    multiset<int> lower, upper;  // lower ≤ upper

    auto balance = [&]() {
        while (lower.size() > upper.size() + 1) {
            upper.insert(*prev(lower.end()));
            lower.erase(prev(lower.end()));
        }
        while (upper.size() > lower.size()) {
            lower.insert(*upper.begin());
            upper.erase(upper.begin());
        }
    };

    auto addNum = [&](int x) {
        if (lower.empty() || x <= *prev(lower.end()))
            lower.insert(x);
        else
            upper.insert(x);
        balance();
    };

    auto removeNum = [&](int x) {
        auto it = lower.find(x);
        if (it != lower.end())
            lower.erase(it);
        else
            upper.erase(upper.find(x));
        balance();
    };

    auto getMedian = [&]() -> double {
        if (k % 2 == 1) return *prev(lower.end());
        return ((double)*prev(lower.end()) + *upper.begin()) / 2.0;
    };

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nK = " << k << "\n\n";

    vector<double> medians;
    for (int i = 0; i < (int)arr.size(); i++) {
        addNum(arr[i]);
        if (i >= k) removeNum(arr[i - k]);
        if (i >= k - 1) {
            medians.push_back(getMedian());
            cout << "Window [" << i - k + 1 << ".." << i << "]: median = "
                 << getMedian() << "\n";
        }
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: CP PROBLEM — TOWERS (CSES)
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Stack cubes on towers. Each new cube goes on the tower
          with the smallest top that's still >= cube size. If no
          such tower, create new one. Minimize towers.

 This is a MULTISET problem!
 Use upper_bound to find smallest tower top > cube size.

 DRY RUN: cubes = [3, 6, 2, 8, 1, 4]
   cube=3: no tower → new tower {3}
   cube=6: no tower with top > 6 → new tower {3, 6}
   cube=2: tower with top 3 > 2, place → replace 3 with 2 → {2, 6}
   cube=8: no tower > 8 → {2, 6, 8}
   cube=1: tower 2 > 1, place → {1, 6, 8}
   cube=4: tower 6 > 4, place → {1, 4, 8}
   Answer: 3 towers
*/

void towersProblem() {
    cout << "═══ CP PROBLEM: TOWERS ═══\n\n";

    vector<int> cubes = {3, 6, 2, 8, 1, 4};
    multiset<int> tops;  // Top values of all towers

    cout << "Cubes: ";
    for (int x : cubes) cout << x << " ";
    cout << "\n\n";

    for (int cube : cubes) {
        auto it = tops.upper_bound(cube);  // Smallest top > cube
        if (it != tops.end()) {
            tops.erase(it);  // Remove that tower's top
        }
        tops.insert(cube);  // Add new top (either new tower or replaced)

        cout << "Place cube " << cube << " → towers: ";
        for (int t : tops) cout << t << " ";
        cout << "\n";
    }

    cout << "\nMinimum towers needed: " << tops.size() << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateBasicOps();
    demonstrateEraseTrick();
    slidingWindowMedian();
    towersProblem();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. multiset allows duplicates, still sorted O(log n)\n";
    cout << "2. erase(val) removes ALL, erase(find(val)) removes ONE!\n";
    cout << "3. equal_range gives range of equal elements\n";
    cout << "4. Two multisets for sliding window median\n";
    cout << "5. upper_bound in multiset for greedy tower/scheduling problems\n";

    return 0;
}

/*
 PRACTICE PROBLEMS:
 ──────────────────
 1. [CSES Towers]               https://cses.fi/problemset/task/1073
 2. [LC Sliding Window Median]   https://leetcode.com/problems/sliding-window-median/
 3. [CF Multiset]               https://codeforces.com/problemset/problem/1354/D
*/

