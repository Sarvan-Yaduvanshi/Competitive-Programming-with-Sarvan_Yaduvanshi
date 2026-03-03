/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — POLICY-BASED DATA STRUCTURES (PBDS)                           ║
║           From Zero to Grandmaster — K-th Smallest in O(log n)               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What is PBDS?
 2. Ordered Set — find_by_order, order_of_key
 3. PBDS as Sorted Array with O(log n) Operations
 4. PBDS with Multiset Behavior (Handling Duplicates)
 5. CP Problem: K-th Smallest Queries

WHAT IS PBDS?
─────────────
  PBDS (Policy-Based Data Structures) are GCC extensions that provide
  additional functionality beyond standard STL.

  The KILLER feature: ordered_set
    • find_by_order(k) → iterator to k-th element (0-indexed) → O(log n)
    • order_of_key(x)  → number of elements strictly less than x → O(log n)

  Standard set CAN'T do these in O(log n)!
  set needs O(n) for rank/k-th queries, PBDS does it in O(log n).

  ⚠️ GCC-only! Works on Codeforces, AtCoder, CSES. NOT on MSVC.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

// PBDS includes
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// THE TEMPLATE (memorize this!)
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,
                         tree_order_statistics_node_update>;

// For multiset behavior (allow duplicates)
template<class T>
using ordered_multiset = tree<pair<T, int>, null_type, less<pair<T, int>>,
                              rb_tree_tag, tree_order_statistics_node_update>;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC PBDS OPERATIONS
// ═══════════════════════════════════════════════════════════════

void demonstrateBasicPBDS() {
    cout << "═══ PBDS ORDERED SET BASICS ═══\n\n";

    ordered_set<int> os;
    os.insert(10);
    os.insert(30);
    os.insert(20);
    os.insert(50);
    os.insert(40);

    cout << "Ordered set: ";
    for (int x : os) cout << x << " ";
    cout << "\n\n";

    // find_by_order(k) — iterator to k-th element (0-indexed)
    cout << "find_by_order(0) = " << *os.find_by_order(0) << " (smallest)\n";
    cout << "find_by_order(1) = " << *os.find_by_order(1) << "\n";
    cout << "find_by_order(2) = " << *os.find_by_order(2) << " (median)\n";
    cout << "find_by_order(4) = " << *os.find_by_order(4) << " (largest)\n\n";

    // order_of_key(x) — count of elements strictly less than x
    cout << "order_of_key(10) = " << os.order_of_key(10) << " (rank of 10)\n";
    cout << "order_of_key(25) = " << os.order_of_key(25) << " (elements < 25)\n";
    cout << "order_of_key(50) = " << os.order_of_key(50) << " (elements < 50)\n";
    cout << "order_of_key(51) = " << os.order_of_key(51) << " (all < 51 = size)\n\n";

    // Standard set operations still work
    os.erase(30);
    cout << "After erase(30): ";
    for (int x : os) cout << x << " ";
    cout << "\n";

    auto it = os.find(20);
    if (it != os.end()) cout << "Found 20 ✓\n";
    cout << "Size: " << os.size() << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: PBDS AS SORTED ARRAY REPLACEMENT
// ═══════════════════════════════════════════════════════════════
/*
 COMPARISON:
 ┌─────────────────────┬──────────────┬──────────────┬──────────────┐
 │ Operation           │ sorted array │ set          │ PBDS         │
 ├─────────────────────┼──────────────┼──────────────┼──────────────┤
 │ Insert              │ O(n)         │ O(log n)     │ O(log n) ✓   │
 │ Delete              │ O(n)         │ O(log n)     │ O(log n) ✓   │
 │ Find                │ O(log n)     │ O(log n)     │ O(log n) ✓   │
 │ K-th smallest       │ O(1)         │ O(n) ✗       │ O(log n) ✓   │
 │ Rank of element     │ O(log n)     │ O(n) ✗       │ O(log n) ✓   │
 │ Lower/upper bound   │ O(log n)     │ O(log n)     │ O(log n) ✓   │
 └─────────────────────┴──────────────┴──────────────┴──────────────┘

 PBDS is the BEST of both worlds!
*/

// ═══════════════════════════════════════════════════════════════
// SECTION 3: HANDLING DUPLICATES (MULTISET BEHAVIOR)
// ═══════════════════════════════════════════════════════════════
/*
 PBDS doesn't support duplicates directly.
 TRICK: Use pair<value, unique_id> to make each element unique.
*/

void demonstrateMultisetPBDS() {
    cout << "═══ PBDS WITH DUPLICATES ═══\n\n";

    ordered_multiset<int> oms;
    int uid = 0;  // Unique ID counter

    auto insert = [&](int val) { oms.insert({val, uid++}); };
    auto erase = [&](int val) { oms.erase(oms.lower_bound({val, 0})); };
    auto kth = [&](int k) { return oms.find_by_order(k)->first; };
    auto rank = [&](int val) { return (int)oms.order_of_key({val, 0}); };

    insert(5);
    insert(3);
    insert(5);  // Duplicate!
    insert(1);
    insert(5);  // Another duplicate!
    insert(3);

    cout << "Elements: ";
    for (auto& [val, id] : oms) cout << val << " ";
    cout << "\n";
    cout << "Size: " << oms.size() << "\n";

    cout << "0th element: " << kth(0) << "\n";
    cout << "2nd element: " << kth(2) << "\n";
    cout << "4th element: " << kth(4) << "\n";
    cout << "Rank of 5: " << rank(5) << " (elements < 5)\n\n";

    erase(5);  // Remove ONE 5
    cout << "After erase one 5: ";
    for (auto& [val, id] : oms) cout << val << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: CP PROBLEM — K-TH SMALLEST QUERIES
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Given a set, support:
   1. Insert x
   2. Delete x
   3. Find k-th smallest
   4. Find rank of x

 DRY RUN:
   Insert 5, 3, 8, 1, 7
   Set: {1, 3, 5, 7, 8}
   K-th(0) = 1, K-th(2) = 5, K-th(4) = 8
   Rank(5) = 2 (two elements < 5)
   Delete 3 → {1, 5, 7, 8}
   K-th(1) = 5, Rank(5) = 1
*/

void kthSmallestQueries() {
    cout << "═══ CP PROBLEM: K-TH SMALLEST QUERIES ═══\n\n";

    ordered_set<int> os;

    // Insert
    for (int x : {5, 3, 8, 1, 7}) {
        os.insert(x);
        cout << "Insert " << x << " → set: ";
        for (int v : os) cout << v << " ";
        cout << "\n";
    }
    cout << "\n";

    // Queries
    cout << "K-th smallest (0-indexed):\n";
    for (int k = 0; k < (int)os.size(); k++) {
        cout << "  k=" << k << " → " << *os.find_by_order(k) << "\n";
    }
    cout << "\n";

    cout << "Rank queries:\n";
    for (int x : {1, 3, 5, 6, 7, 8, 10}) {
        cout << "  rank(" << x << ") = " << os.order_of_key(x)
             << " (elements < " << x << ")\n";
    }
    cout << "\n";

    // Delete
    os.erase(3);
    cout << "After erase(3): ";
    for (int v : os) cout << v << " ";
    cout << "\n";
    cout << "K-th(1) = " << *os.find_by_order(1) << "\n";
    cout << "Rank(5) = " << os.order_of_key(5) << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: COUNTING INVERSIONS WITH PBDS
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Count inversions in array (pairs where i < j but a[i] > a[j]).

 APPROACH: For each element, count how many previously inserted elements
           are GREATER than it. Use order_of_key to find rank.
           Inversions from a[i] = (elements already inserted) - rank(a[i])

 DRY RUN: [3, 1, 2]
   i=0: insert 3, rank=0, inversions += 0 - 0 = 0
   i=1: insert 1, elements=1, rank(1)=0, inversions += 1 - 0 = 1
   i=2: insert 2, elements=2, rank(2)=1, inversions += 2 - 1 = 1
   Total: 2 inversions → (3,1) and (3,2) ✓
*/

void countInversions() {
    cout << "═══ COUNT INVERSIONS WITH PBDS ═══\n\n";

    vector<int> arr = {5, 3, 8, 1, 7, 2, 4, 6};
    ordered_set<int> os;
    long long inversions = 0;

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n";

    for (int i = 0; i < (int)arr.size(); i++) {
        int greater_count = (int)os.size() - (int)os.order_of_key(arr[i]);
        inversions += greater_count;
        os.insert(arr[i]);
        cout << "  Insert " << arr[i] << ": " << greater_count
             << " elements greater (inversions so far: " << inversions << ")\n";
    }
    cout << "\nTotal inversions: " << inversions << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateBasicPBDS();
    demonstrateMultisetPBDS();
    kthSmallestQueries();
    countInversions();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. PBDS = set + O(log n) rank and k-th queries\n";
    cout << "2. find_by_order(k): k-th smallest element\n";
    cout << "3. order_of_key(x): count of elements < x\n";
    cout << "4. For duplicates: use pair<value, unique_id>\n";
    cout << "5. Count inversions: size - order_of_key per element\n";
    cout << "6. GCC-only! Works on CF, AtCoder, CSES\n";
    cout << "7. MEMORIZE the template: tree<T, null_type, less<T>, ...>\n";

    return 0;
}

/*
 PRACTICE PROBLEMS:
 ──────────────────
 1. [CSES Josephus Problem]   https://cses.fi/problemset/task/2162
 2. [CSES Salary Queries]     https://cses.fi/problemset/task/1144
 3. [SPOJ MKTHNUM]            K-th number in range
 4. [CF Inversions]            Count inversions with PBDS
*/

