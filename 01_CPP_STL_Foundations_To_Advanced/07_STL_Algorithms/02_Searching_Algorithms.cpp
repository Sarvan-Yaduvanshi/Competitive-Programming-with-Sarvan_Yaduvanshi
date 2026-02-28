/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — SEARCHING ALGORITHMS IN STL                                 ║
║           From Zero to Grandmaster                                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

 KEY FUNCTIONS:
   find()           → O(N), linear search
   binary_search()  → O(log N), requires sorted range
   lower_bound()    → First element >= value
   upper_bound()    → First element > value
   equal_range()    → {lower_bound, upper_bound}
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> v = {1, 3, 3, 5, 5, 5, 7, 9, 11};

    // ── find() — Linear O(N) ──
    cout << "═══ find() ═══\n";
    auto it = find(v.begin(), v.end(), 5);
    if (it != v.end())
        cout << "Found 5 at index " << (it - v.begin()) << "\n";
    it = find(v.begin(), v.end(), 6);
    cout << "Found 6? " << (it != v.end() ? "Yes" : "No") << "\n\n";

    // ── binary_search() — O(log N), needs sorted ──
    cout << "═══ binary_search() ═══\n";
    cout << "5 exists? " << binary_search(v.begin(), v.end(), 5) << "\n";
    cout << "6 exists? " << binary_search(v.begin(), v.end(), 6) << "\n\n";

    // ── lower_bound / upper_bound ──
    cout << "═══ lower_bound / upper_bound ═══\n";
    /*
     v = {1, 3, 3, 5, 5, 5, 7, 9, 11}
          0  1  2  3  4  5  6  7   8

     lower_bound(5) → index 3 (first >= 5)
     upper_bound(5) → index 6 (first > 5)
     Count of 5s = upper_bound - lower_bound = 6 - 3 = 3
    */
    auto lb = lower_bound(v.begin(), v.end(), 5);
    auto ub = upper_bound(v.begin(), v.end(), 5);
    cout << "lower_bound(5) at index: " << (lb - v.begin()) << " (value " << *lb << ")\n";
    cout << "upper_bound(5) at index: " << (ub - v.begin()) << " (value " << *ub << ")\n";
    cout << "Count of 5: " << (ub - lb) << "\n";

    // lower_bound for non-existing value
    lb = lower_bound(v.begin(), v.end(), 4);
    cout << "lower_bound(4) at index: " << (lb - v.begin()) << " (value " << *lb << ")\n";
    cout << "(first element >= 4 is 5)\n\n";

    // ── equal_range ──
    cout << "═══ equal_range() ═══\n";
    auto [lo, hi] = equal_range(v.begin(), v.end(), 3);
    cout << "equal_range(3): indices [" << (lo - v.begin()) << ", " << (hi - v.begin()) << ")\n";
    cout << "Count of 3: " << (hi - lo) << "\n\n";

    // ── PRACTICAL PATTERNS ──
    cout << "═══ PRACTICAL CP PATTERNS ═══\n\n";

    // Pattern 1: Count elements in range [a, b]
    int a = 3, b = 7;
    int cnt = upper_bound(v.begin(), v.end(), b) - lower_bound(v.begin(), v.end(), a);
    cout << "Elements in [" << a << "," << b << "]: " << cnt << "\n";

    // Pattern 2: Find insert position
    int val = 6;
    int pos = lower_bound(v.begin(), v.end(), val) - v.begin();
    cout << "Insert position for " << val << ": index " << pos << "\n";

    // Pattern 3: Count elements strictly less than X
    int X = 5;
    int less_count = lower_bound(v.begin(), v.end(), X) - v.begin();
    cout << "Elements < " << X << ": " << less_count << "\n";

    // Pattern 4: Count elements strictly greater than X
    int greater_count = v.end() - upper_bound(v.begin(), v.end(), X);
    cout << "Elements > " << X << ": " << greater_count << "\n";

    // Pattern 5: Binary search on answer
    cout << "\n═══ BINARY SEARCH ON ANSWER ═══\n";
    // "Is there a valid solution with parameter = mid?"
    // If monotonic: binary search on the answer space
    auto canAchieve = [](int target) -> bool {
        // Example: can we divide array into groups with max sum ≤ target?
        return target >= 10;  // Dummy: anything >= 10 works
    };

    int lo2 = 1, hi2 = 100, ans = -1;
    while (lo2 <= hi2) {
        int mid = (lo2 + hi2) / 2;
        if (canAchieve(mid)) {
            ans = mid;
            hi2 = mid - 1;
        } else {
            lo2 = mid + 1;
        }
    }
    cout << "Minimum valid answer: " << ans << "\n\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. lower_bound: first >=, upper_bound: first >\n";
    cout << "2. Count of x = upper_bound - lower_bound\n";
    cout << "3. Elements in [a,b] = upper_bound(b) - lower_bound(a)\n";
    cout << "4. binary_search returns bool, use lower_bound for position\n";
    cout << "5. All require SORTED range!\n";

    return 0;
}

