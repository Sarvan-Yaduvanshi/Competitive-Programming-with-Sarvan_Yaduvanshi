/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — SORTING ALGORITHMS IN STL                                   ║
║           From Zero to Grandmaster                                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

 ┌──────────────────┬──────────┬───────────────────────────────────────┐
 │ Function         │ Time     │ Use Case                              │
 ├──────────────────┼──────────┼───────────────────────────────────────┤
 │ sort()           │ O(NlogN) │ General sorting (IntroSort)           │
 │ stable_sort()    │ O(NlogN) │ Preserve relative order of equal      │
 │ partial_sort(k)  │ O(NlogK) │ Only sort first K elements            │
 │ nth_element()    │ O(N) avg │ Find k-th element (no full sort!)     │
 │ is_sorted()      │ O(N)     │ Check if already sorted               │
 └──────────────────┴──────────┴───────────────────────────────────────┘
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ── sort() ──
    cout << "═══ sort() ═══\n";
    vector<int> v = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    sort(v.begin(), v.end());
    cout << "Ascending: "; for (int x : v) cout << x << " "; cout << "\n";

    sort(v.begin(), v.end(), greater<int>());
    cout << "Descending: "; for (int x : v) cout << x << " "; cout << "\n";

    // Custom: sort by last digit
    vector<int> v2 = {23, 15, 42, 37, 11};
    sort(v2.begin(), v2.end(), [](int a, int b) { return a % 10 < b % 10; });
    cout << "By last digit: "; for (int x : v2) cout << x << " "; cout << "\n\n";

    // ── stable_sort() — preserves relative order of equal elements ──
    cout << "═══ stable_sort() ═══\n";
    vector<pair<int, string>> students = {{3, "Alice"}, {1, "Bob"}, {3, "Charlie"}, {1, "David"}};
    stable_sort(students.begin(), students.end(),
                [](const auto& a, const auto& b) { return a.first < b.first; });
    cout << "Stable (by grade): ";
    for (auto& [g, n] : students) cout << n << "(" << g << ") ";
    cout << "\n(Alice before Charlie, Bob before David — order preserved!)\n\n";

    // ── partial_sort() — sort only first K elements ──
    cout << "═══ partial_sort() ═══\n";
    vector<int> v3 = {9, 3, 7, 1, 5, 8, 2, 6, 4};
    partial_sort(v3.begin(), v3.begin() + 3, v3.end());
    cout << "First 3 smallest: "; for (int x : v3) cout << x << " "; cout << "\n";
    cout << "(Only first 3 are sorted, rest undefined)\n\n";

    // ── nth_element() — O(N) average! ──
    cout << "═══ nth_element() — THE GM TRICK ═══\n";
    /*
     nth_element rearranges so that:
       element at nth position = what would be there if sorted
       all before nth ≤ nth, all after nth ≥ nth
     BUT elements are NOT fully sorted!
     Time: O(N) average — MUCH faster than sort for finding median/k-th!
    */
    vector<int> v4 = {9, 3, 7, 1, 5, 8, 2, 6, 4};
    int k = 4;  // Find 5th smallest (0-indexed)
    nth_element(v4.begin(), v4.begin() + k, v4.end());
    cout << k << "-th element (0-indexed): " << v4[k] << "\n";
    cout << "Array: "; for (int x : v4) cout << x << " "; cout << "\n";
    cout << "(Elements partitioned around " << v4[k] << " but NOT sorted)\n\n";

    // Find median in O(N)
    vector<int> v5 = {7, 3, 1, 9, 5};
    int mid = v5.size() / 2;
    nth_element(v5.begin(), v5.begin() + mid, v5.end());
    cout << "Median of {7,3,1,9,5}: " << v5[mid] << "\n\n";

    // ── is_sorted() ──
    cout << "═══ is_sorted() ═══\n";
    vector<int> sorted_v = {1, 2, 3, 4, 5};
    vector<int> unsorted_v = {1, 3, 2, 4, 5};
    cout << "{1,2,3,4,5} sorted? " << is_sorted(sorted_v.begin(), sorted_v.end()) << "\n";
    cout << "{1,3,2,4,5} sorted? " << is_sorted(unsorted_v.begin(), unsorted_v.end()) << "\n\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. sort() = IntroSort, O(N log N), NOT stable\n";
    cout << "2. stable_sort() preserves order of equal elements\n";
    cout << "3. partial_sort() for top-K: O(N log K)\n";
    cout << "4. nth_element() for k-th/median: O(N) average!\n";
    cout << "5. Custom comparator lambda for flexible sorting\n";

    return 0;
}

