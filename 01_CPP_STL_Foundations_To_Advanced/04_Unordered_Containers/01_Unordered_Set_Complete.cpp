/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — UNORDERED_SET COMPLETE GUIDE                                ║
║           From Zero to Grandmaster — O(1) Hash Set                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

  unordered_set = hash table storing UNIQUE elements.
  O(1) average insert/find/erase.
  NOT sorted (unlike set).

  Internal: hash table with chaining (linked lists in buckets)
  ┌─────┐
  │  0  │ → [10] → [20]
  │  1  │ → [31]
  │  2  │ →  ∅
  │  3  │ → [3] → [13]
  │  4  │ → [44]
  └─────┘
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ── SECTION 1: BASIC OPERATIONS ──
    cout << "═══ UNORDERED_SET BASICS ═══\n\n";

    unordered_set<int> us;
    us.insert(5);
    us.insert(3);
    us.insert(8);
    us.insert(1);
    us.insert(5);  // Duplicate ignored

    cout << "Elements (unordered!): ";
    for (int x : us) cout << x << " ";
    cout << "\nSize: " << us.size() << "\n";

    // find — O(1) average
    if (us.find(3) != us.end()) cout << "Found 3 ✓\n";
    if (us.count(8)) cout << "8 exists ✓\n";

    // erase
    us.erase(3);
    cout << "After erase(3): ";
    for (int x : us) cout << x << " ";
    cout << "\n\n";

    // ── SECTION 2: BUCKET INTERFACE ──
    cout << "═══ BUCKET INTERFACE ═══\n\n";

    unordered_set<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Bucket count: " << s.bucket_count() << "\n";
    cout << "Load factor: " << s.load_factor() << "\n";
    cout << "Max load factor: " << s.max_load_factor() << "\n\n";

    // Which bucket is each element in?
    for (int x : {1, 5, 10}) {
        cout << "Element " << x << " is in bucket " << s.bucket(x) << "\n";
    }
    cout << "\n";

    // ── SECTION 3: RESERVE AND REHASH ──
    cout << "═══ RESERVE AND REHASH ═══\n\n";
    /*
     reserve(n) — pre-allocate buckets for n elements
     rehash(n)  — set bucket count to at least n

     GM TIP: reserve() avoids rehashing, which can cause TLE!
    */
    unordered_set<int> big;
    big.reserve(1000000);  // Pre-allocate for 10^6 elements
    cout << "After reserve(10^6): bucket_count = " << big.bucket_count() << "\n\n";

    // ── SECTION 4: PERFORMANCE COMPARISON ──
    cout << "═══ SET vs UNORDERED_SET ═══\n\n";
    const int N = 1000000;

    {
        auto start = chrono::steady_clock::now();
        unordered_set<int> us;
        us.reserve(N);
        for (int i = 0; i < N; i++) us.insert(i);
        for (int i = 0; i < N; i++) us.find(i);
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "unordered_set (10^6 insert+find): " << ms << " ms\n";
    }
    {
        auto start = chrono::steady_clock::now();
        set<int> os;
        for (int i = 0; i < N; i++) os.insert(i);
        for (int i = 0; i < N; i++) os.find(i);
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "set (10^6 insert+find):           " << ms << " ms\n";
    }
    cout << "\n";

    // ── SECTION 5: CP PATTERN — DISTINCT ELEMENTS ──
    cout << "═══ CP: COUNT DISTINCT ═══\n\n";
    vector<int> arr = {1, 2, 3, 2, 1, 4, 5, 4, 3, 2, 1};
    unordered_set<int> distinct(arr.begin(), arr.end());
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nDistinct count: " << distinct.size() << "\n\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. unordered_set: O(1) avg, O(n) worst for all ops\n";
    cout << "2. NOT sorted — use set if you need order\n";
    cout << "3. reserve() to avoid rehashing (performance!)\n";
    cout << "4. ~2-5x faster than set for pure lookup\n";
    cout << "5. Vulnerable to hash attacks on CF — use custom hash!\n";

    return 0;
}

