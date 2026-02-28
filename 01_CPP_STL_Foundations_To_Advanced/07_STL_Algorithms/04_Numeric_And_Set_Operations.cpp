/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           04 — NUMERIC ALGORITHMS                                          ║
║           05 — SET OPERATIONS                                              ║
║           From Zero to Grandmaster                                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ═══════════════════════════════════════════════
    // NUMERIC ALGORITHMS (<numeric>)
    // ═══════════════════════════════════════════════

    // ── accumulate ──
    cout << "═══ accumulate() ═══\n";
    vector<int> v = {1, 2, 3, 4, 5};
    int sum = accumulate(v.begin(), v.end(), 0);
    long long sumLL = accumulate(v.begin(), v.end(), 0LL);  // Use 0LL for long long!
    cout << "Sum: " << sum << "\n";

    // Custom accumulate (product)
    int product = accumulate(v.begin(), v.end(), 1, multiplies<int>());
    cout << "Product: " << product << "\n";

    // String concatenation
    vector<string> words = {"Hello", " ", "World"};
    string concat = accumulate(words.begin(), words.end(), string(""));
    cout << "Concat: " << concat << "\n\n";

    // ── partial_sum (prefix sum!) ──
    cout << "═══ partial_sum() — PREFIX SUM ═══\n";
    v = {1, 2, 3, 4, 5};
    vector<int> prefix(v.size());
    partial_sum(v.begin(), v.end(), prefix.begin());
    cout << "Array:      "; for (int x : v) cout << x << " "; cout << "\n";
    cout << "Prefix sum: "; for (int x : prefix) cout << x << " "; cout << "\n";
    // Range sum [l,r] = prefix[r] - (l > 0 ? prefix[l-1] : 0)
    int l = 1, r = 3;
    int range_sum = prefix[r] - (l > 0 ? prefix[l - 1] : 0);
    cout << "Sum [1,3] = " << range_sum << "\n\n";

    // ── adjacent_difference ──
    cout << "═══ adjacent_difference() ═══\n";
    vector<int> diff(v.size());
    adjacent_difference(v.begin(), v.end(), diff.begin());
    cout << "Adj diff: "; for (int x : diff) cout << x << " "; cout << "\n\n";

    // ── iota ──
    cout << "═══ iota() ═══\n";
    vector<int> indices(10);
    iota(indices.begin(), indices.end(), 0);  // {0, 1, 2, ..., 9}
    cout << "iota(0): "; for (int x : indices) cout << x << " "; cout << "\n";

    iota(indices.begin(), indices.end(), 100);  // {100, 101, ..., 109}
    cout << "iota(100): "; for (int x : indices) cout << x << " "; cout << "\n\n";

    // ── inner_product (dot product) ──
    cout << "═══ inner_product() ═══\n";
    vector<int> a = {1, 2, 3}, b = {4, 5, 6};
    int dot = inner_product(a.begin(), a.end(), b.begin(), 0);
    cout << "{1,2,3} · {4,5,6} = " << dot << " (1*4+2*5+3*6=32)\n\n";

    // ── gcd, lcm (C++17) ──
    cout << "═══ gcd() / lcm() ═══\n";
    cout << "gcd(12, 18) = " << __gcd(12, 18) << "\n";
    cout << "lcm(12, 18) = " << lcm(12, 18) << "\n";
    // GCD of array
    vector<int> nums = {12, 18, 24, 36};
    int g = nums[0];
    for (int x : nums) g = __gcd(g, x);
    cout << "GCD of {12,18,24,36} = " << g << "\n\n";

    // ═══════════════════════════════════════════════
    // SET OPERATIONS (on sorted ranges!)
    // ═══════════════════════════════════════════════

    cout << "═══ SET OPERATIONS ═══\n\n";
    vector<int> s1 = {1, 2, 3, 4, 5};
    vector<int> s2 = {3, 4, 5, 6, 7};

    cout << "S1: "; for (int x : s1) cout << x << " "; cout << "\n";
    cout << "S2: "; for (int x : s2) cout << x << " "; cout << "\n\n";

    // set_union — elements in either
    vector<int> result;
    set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(result));
    cout << "Union:        "; for (int x : result) cout << x << " "; cout << "\n";

    // set_intersection — elements in both
    result.clear();
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(result));
    cout << "Intersection: "; for (int x : result) cout << x << " "; cout << "\n";

    // set_difference — in S1 but not S2
    result.clear();
    set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(result));
    cout << "S1 - S2:      "; for (int x : result) cout << x << " "; cout << "\n";

    // set_symmetric_difference — in one but not both
    result.clear();
    set_symmetric_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(result));
    cout << "Symmetric:    "; for (int x : result) cout << x << " "; cout << "\n";

    // includes — check if S1 is subset of S2
    vector<int> subset = {3, 4, 5};
    cout << "\n{3,4,5} ⊆ S1? " << includes(s1.begin(), s1.end(), subset.begin(), subset.end()) << "\n";

    // merge — merge two sorted ranges
    result.clear();
    merge(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(result));
    cout << "Merge: "; for (int x : result) cout << x << " "; cout << "\n\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. accumulate for sum/product (use 0LL for long long!)\n";
    cout << "2. partial_sum = prefix sum in one line\n";
    cout << "3. iota for generating sequential indices\n";
    cout << "4. Set operations need SORTED ranges\n";
    cout << "5. __gcd() and lcm() for number theory\n";

    return 0;
}

