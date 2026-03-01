/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 12 — SEARCHING WITH DATA STRUCTURES                      ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1.  Binary Search on Prefix Sum
 2.  Binary Search on Segment Tree
 3.  Binary Search with Fenwick Tree (BIT)
 4.  Searching with Hash Map
 5.  Searching with Set / Multiset
 6.  PBDS order_of_key

OVERVIEW:
─────────
Combining binary search with data structures unlocks powerful techniques
for range queries, dynamic order statistics, and online algorithms.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <climits>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<pair<int,int>, null_type, less<pair<int,int>>,
             rb_tree_tag, tree_order_statistics_node_update> ordered_set;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BINARY SEARCH ON PREFIX SUM
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 If array has non-negative elements, prefix sum is monotonically increasing.
 This means we can binary search on the prefix sum array!

 APPLICATIONS:
   1. Find minimum prefix of length that sums to ≥ target
   2. Random weighted selection (weighted random)
   3. Find subarray with sum closest to target
   4. Count subarrays with sum in [lo, hi]

 KEY: Prefix sum of non-negative array is sorted → BS applicable!
*/

// Find shortest prefix with sum ≥ target
int shortestPrefixWithSum(vector<int>& arr, int target) {
    int n = arr.size();
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + arr[i];

    // Binary search for first prefix ≥ target
    auto it = lower_bound(prefix.begin(), prefix.end(), (long long)target);
    if (it == prefix.end()) return -1;
    return (int)(it - prefix.begin());
}

// Weighted Random Selection: Given weights, pick index with probability proportional to weight
int weightedRandomPick(vector<int>& weights, int random_val) {
    int n = weights.size();
    vector<int> prefix(n);
    prefix[0] = weights[0];
    for (int i = 1; i < n; i++) prefix[i] = prefix[i - 1] + weights[i];

    // random_val in [1, total_weight]
    // Find first index where prefix >= random_val
    return (int)(lower_bound(prefix.begin(), prefix.end(), random_val) - prefix.begin());
}

// Find minimum length subarray with sum ≥ target (positive elements)
// Using prefix sum + binary search: O(n log n)
int minSubarrayLen_bs(int target, vector<int>& nums) {
    int n = nums.size();
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + nums[i];

    int minLen = INT_MAX;
    for (int i = 0; i <= n; i++) {
        // Find smallest j > i such that prefix[j] - prefix[i] >= target
        // → prefix[j] >= prefix[i] + target
        long long need = prefix[i] + target;
        auto it = lower_bound(prefix.begin() + i + 1, prefix.end(), need);
        if (it != prefix.end()) {
            int j = (int)(it - prefix.begin());
            minLen = min(minLen, j - i);
        }
    }
    return minLen == INT_MAX ? 0 : minLen;
}

void demo_prefix_bs() {
    cout << "=== SECTION 1: BS ON PREFIX SUM ===" << endl;

    vector<int> arr = {2, 3, 1, 2, 4, 3};
    cout << "Shortest prefix sum ≥ 7: " << shortestPrefixWithSum(arr, 7) << " elements" << endl;

    vector<int> weights = {1, 3, 2, 4};
    cout << "Weighted pick (random=5): index " << weightedRandomPick(weights, 5) << endl;

    int target = 7;
    cout << "Min subarray len with sum ≥ " << target << ": "
         << minSubarrayLen_bs(target, arr) << endl; // 2 (4+3)

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: BINARY SEARCH ON SEGMENT TREE
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Segment trees can answer "walk down" queries that are essentially
 binary search within the tree structure.

 EXAMPLES:
   1. Find first element ≥ X in range
   2. Find kth element in range (with persistence or merge sort tree)
   3. Kth zero/one in a range
   4. First position from left where prefix sum ≥ X

 TECHNIQUE: Descend the segment tree:
   At each node, check left child's aggregate:
   - If left child satisfies condition → go left
   - Else → subtract left's contribution, go right
*/

// Segment Tree with "find kth 1" (kth set bit in BIT-like structure)
class SegTree {
    vector<int> tree;
    int n;

    void build(int node, int start, int end, vector<int>& arr) {
        if (start == end) { tree[node] = arr[start]; return; }
        int mid = (start + end) / 2;
        build(2 * node, start, mid, arr);
        build(2 * node + 1, mid + 1, end, arr);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) { tree[node] = val; return; }
        int mid = (start + end) / 2;
        if (idx <= mid) update(2 * node, start, mid, idx, val);
        else update(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) +
               query(2 * node + 1, mid + 1, end, l, r);
    }

    // Find kth one (1-indexed k) — "walk down" binary search
    int findKth(int node, int start, int end, int k) {
        if (start == end) return start;
        int mid = (start + end) / 2;
        int leftSum = tree[2 * node];
        if (leftSum >= k) return findKth(2 * node, start, mid, k);
        else return findKth(2 * node + 1, mid + 1, end, k - leftSum);
    }

public:
    SegTree(int _n) : n(_n), tree(4 * _n, 0) {}

    void build(vector<int>& arr) { build(1, 0, n - 1, arr); }
    void update(int idx, int val) { update(1, 0, n - 1, idx, val); }
    int query(int l, int r) { return query(1, 0, n - 1, l, r); }
    int findKth(int k) { return findKth(1, 0, n - 1, k); }
};

void demo_segtree_bs() {
    cout << "=== SECTION 2: BS ON SEGMENT TREE ===" << endl;

    // Example: Array of 0s and 1s, find kth 1
    int n = 10;
    vector<int> arr = {0, 1, 0, 1, 1, 0, 0, 1, 0, 1}; // 1s at indices 1,3,4,7,9
    SegTree st(n);
    st.build(arr);

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    cout << "1st one at index: " << st.findKth(1) << endl; // 1
    cout << "3rd one at index: " << st.findKth(3) << endl; // 4
    cout << "5th one at index: " << st.findKth(5) << endl; // 9

    // Josephus problem simulation using segment tree
    cout << "\nJosephus simulation (n=5, k=2):" << endl;
    int n2 = 5, k = 2;
    vector<int> alive(n2, 1);
    SegTree st2(n2);
    st2.build(alive);

    int current = 0;
    int remaining = n2;
    cout << "Elimination order: ";
    while (remaining > 0) {
        current = (current + k - 1) % remaining;
        int pos = st2.findKth(current + 1); // 1-indexed
        cout << pos + 1 << " "; // 1-indexed output
        st2.update(pos, 0);
        remaining--;
        current = current % max(remaining, 1);
    }
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: BINARY SEARCH WITH FENWICK TREE (BIT)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Fenwick Tree (Binary Indexed Tree) supports:
   • Point update: O(log n)
   • Prefix sum query: O(log n)
   • Find kth element: O(log² n) or O(log n) with technique

 FIND KTH IN FENWICK TREE:
   Method 1: Binary search on prefix sum → O(log² n)
     BS on index i: find smallest i where prefixSum(i) >= k

   Method 2: Bit manipulation walk → O(log n)
     Start from highest power of 2, walk down like in segment tree

 APPLICATIONS:
   • Dynamic order statistics (insert/delete + kth query)
   • Count inversions with coordinate compression
   • Range frequency queries
*/

class BIT {
    vector<int> bit;
    int n;

public:
    BIT(int _n) : n(_n), bit(_n + 1, 0) {}

    void update(int i, int delta) {
        for (++i; i <= n; i += i & (-i))
            bit[i] += delta;
    }

    int query(int i) {
        int sum = 0;
        for (++i; i > 0; i -= i & (-i))
            sum += bit[i];
        return sum;
    }

    int query(int l, int r) {
        return query(r) - (l > 0 ? query(l - 1) : 0);
    }

    // Find kth element (0-indexed) — O(log² n) using binary search
    int findKth_bs(int k) {
        int lo = 0, hi = n - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (query(mid) >= k) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    // Find kth element — O(log n) using bit walking
    int findKth(int k) {
        int pos = 0;
        int bitMask = 1;
        while (bitMask <= n) bitMask <<= 1;
        bitMask >>= 1;

        for (; bitMask > 0; bitMask >>= 1) {
            int next = pos + bitMask;
            if (next <= n && bit[next] < k) {
                k -= bit[next];
                pos = next;
            }
        }
        return pos; // 0-indexed
    }
};

void demo_bit_bs() {
    cout << "=== SECTION 3: BS ON FENWICK TREE ===" << endl;

    // Count inversions using BIT + coordinate compression
    vector<int> arr = {5, 3, 4, 1, 2};
    int n = arr.size();

    // Coordinate compression
    vector<int> sorted_arr = arr;
    sort(sorted_arr.begin(), sorted_arr.end());
    sorted_arr.erase(unique(sorted_arr.begin(), sorted_arr.end()), sorted_arr.end());
    int m = sorted_arr.size();

    BIT bit(m);
    long long inversions = 0;
    for (int i = 0; i < n; i++) {
        int compressed = lower_bound(sorted_arr.begin(), sorted_arr.end(), arr[i])
                        - sorted_arr.begin();
        // Count elements already inserted that are > arr[i]
        inversions += i - bit.query(compressed);
        bit.update(compressed, 1);
    }
    cout << "Inversions in [5,3,4,1,2]: " << inversions << endl; // 7

    // Dynamic kth using BIT
    BIT bit2(10); // Values 0-9
    for (int x : {3, 1, 4, 1, 5, 9, 2, 6}) {
        bit2.update(x, 1);
    }
    cout << "1st smallest: " << bit2.findKth(1) << endl; // 1
    cout << "3rd smallest: " << bit2.findKth(3) << endl; // 2
    cout << "5th smallest: " << bit2.findKth(5) << endl; // 4

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: SEARCHING WITH HASH MAP
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Hash maps provide O(1) average lookup, enabling powerful search patterns.

 PATTERNS:
   1. Two Sum: Store complement, search in O(1)
   2. Subarray Sum = K: prefix sum + hash map
   3. Longest subarray with sum K
   4. Count subarrays with sum K
   5. Check if subset sum exists (meet-in-middle with hash)
   6. Group Anagrams: Sort string as key
*/

// Two Sum (unsorted) — O(n)
pair<int, int> twoSum_hash(vector<int>& nums, int target) {
    unordered_map<int, int> seen;
    for (int i = 0; i < (int)nums.size(); i++) {
        int complement = target - nums[i];
        if (seen.count(complement)) return {seen[complement], i};
        seen[nums[i]] = i;
    }
    return {-1, -1};
}

// Count subarrays with sum = K
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixCount;
    prefixCount[0] = 1;
    int sum = 0, count = 0;
    for (int x : nums) {
        sum += x;
        count += prefixCount[sum - k];
        prefixCount[sum]++;
    }
    return count;
}

// Longest subarray with sum = K
int longestSubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> firstOccurrence;
    firstOccurrence[0] = -1;
    int sum = 0, maxLen = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        sum += nums[i];
        if (firstOccurrence.count(sum - k))
            maxLen = max(maxLen, i - firstOccurrence[sum - k]);
        if (!firstOccurrence.count(sum))
            firstOccurrence[sum] = i;
    }
    return maxLen;
}

// Check if any two elements have difference = K
bool hasPairWithDiff(vector<int>& nums, int k) {
    unordered_set<int> seen;
    for (int x : nums) {
        if (seen.count(x + k) || seen.count(x - k)) return true;
        seen.insert(x);
    }
    return false;
}

void demo_hashmap_search() {
    cout << "=== SECTION 4: HASH MAP SEARCH ===" << endl;

    vector<int> nums = {2, 7, 11, 15};
    auto [a, b] = twoSum_hash(nums, 9);
    cout << "Two Sum (target=9): indices " << a << ", " << b << endl;

    vector<int> nums2 = {1, 1, 1};
    cout << "Subarrays sum=2: " << subarraySum(nums2, 2) << endl; // 2

    vector<int> nums3 = {1, -1, 5, -2, 3};
    cout << "Longest subarray sum=3: " << longestSubarraySum(nums3, 3) << endl; // 4

    cout << "Has pair diff=3: " << hasPairWithDiff(nums, 3) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: SEARCHING WITH SET / MULTISET
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 std::set and std::multiset are balanced BSTs (Red-Black trees).
 They support O(log n) search, insert, delete, and bound queries.

 KEY OPERATIONS:
   s.lower_bound(x): First element ≥ x — O(log n)
   s.upper_bound(x): First element > x — O(log n)
   s.find(x): Find exact element — O(log n)
   s.count(x): Count of x — O(log n + count)

 IMPORTANT: Use MEMBER lower_bound, not std::lower_bound!
   s.lower_bound(x)     → O(log n) ✓
   lower_bound(s.begin(), s.end(), x) → O(n) ✗ (forward iterator!)

 APPLICATIONS:
   • Sliding window with set (maintain sorted window)
   • Closest element to target
   • Floor/ceil queries
   • Contains Duplicate III (LC 220)
*/

// Closest element to target in set
int closestInSet(set<int>& s, int target) {
    auto it = s.lower_bound(target);
    int closest = INT_MAX;
    if (it != s.end()) closest = *it;
    if (it != s.begin()) {
        --it;
        if (abs(*it - target) < abs(closest - target)) closest = *it;
    }
    return closest;
}

// Contains Duplicate III (LC 220): Check if |nums[i]-nums[j]| ≤ t and |i-j| ≤ k
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    set<long long> window;
    for (int i = 0; i < (int)nums.size(); i++) {
        auto it = window.lower_bound((long long)nums[i] - t);
        if (it != window.end() && *it <= (long long)nums[i] + t) return true;
        window.insert(nums[i]);
        if ((int)window.size() > k) window.erase(nums[i - k]);
    }
    return false;
}

// Sliding window median using two multisets
double slidingWindowMedian(vector<int>& nums, int k) {
    multiset<int> lo, hi; // lo = lower half, hi = upper half
    for (int i = 0; i < k; i++) {
        lo.insert(nums[i]);
        hi.insert(*lo.rbegin());
        lo.erase(prev(lo.end()));
        if (lo.size() < hi.size()) {
            lo.insert(*hi.begin());
            hi.erase(hi.begin());
        }
    }
    if (k % 2) return *lo.rbegin();
    return ((double)*lo.rbegin() + *hi.begin()) / 2.0;
}

void demo_set_search() {
    cout << "=== SECTION 5: SET / MULTISET SEARCH ===" << endl;

    set<int> s = {1, 3, 5, 7, 9};
    cout << "Closest to 4: " << closestInSet(s, 4) << endl; // 3 or 5

    // Floor and Ceil
    auto it = s.lower_bound(4);
    if (it != s.end()) cout << "Ceil(4) = " << *it << endl; // 5
    if (it != s.begin()) { --it; cout << "Floor(4) = " << *it << endl; } // 3

    // Contains Nearby Almost Duplicate
    vector<int> nums = {1, 2, 3, 1};
    cout << "Contains nearby dup (k=3,t=0): " << containsNearbyAlmostDuplicate(nums, 3, 0) << endl;

    // Sliding window median
    vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    cout << "First window (k=3) median: " << slidingWindowMedian(arr, 3) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: PBDS ORDER_OF_KEY
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 The Policy-Based Data Structure (PBDS) ordered set provides:
   find_by_order(k): Iterator to kth element (0-indexed) — O(log n)
   order_of_key(x): Count of elements strictly < x — O(log n)

 COMBINED WITH BS:
   • Dynamic rank queries
   • Count elements in range [lo, hi]:
     order_of_key(hi+1) - order_of_key(lo)
   • Online inversion counting
   • Sliding window rank queries

 HANDLING DUPLICATES:
   Use pair<value, unique_id> to allow duplicate values.
*/

void demo_pbds() {
    cout << "=== SECTION 6: PBDS ORDER_OF_KEY ===" << endl;

    ordered_set os;
    int id = 0;

    // Insert elements
    for (int x : {5, 1, 3, 2, 4}) os.insert({x, id++});

    // Rank queries
    cout << "Rank of 3 (elements < 3): " << os.order_of_key({3, 0}) << endl; // 2
    cout << "Rank of 5 (elements < 5): " << os.order_of_key({5, 0}) << endl; // 4

    // Kth element
    cout << "2nd element (0-indexed): " << os.find_by_order(2)->first << endl; // 3

    // Count elements in range [2, 4]
    int lo = 2, hi = 4;
    int count = os.order_of_key({hi + 1, 0}) - os.order_of_key({lo, 0});
    cout << "Count in [2,4]: " << count << endl; // 3

    // Dynamic: insert and query
    os.insert({6, id++});
    os.insert({0, id++});
    cout << "After inserting 6,0: rank of 3 = " << os.order_of_key({3, 0}) << endl; // 3

    // Erase and query
    auto it = os.find_by_order(0); // Smallest element
    cout << "Erasing smallest: " << it->first << endl;
    os.erase(it);
    cout << "New 0th element: " << os.find_by_order(0)->first << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   CHAPTER 12: SEARCHING WITH DATA STRUCTURES                ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    demo_prefix_bs();
    demo_segtree_bs();
    demo_bit_bs();
    demo_hashmap_search();
    demo_set_search();
    demo_pbds();

    cout << "═══════════════════════════════════════════════════════════════" << endl;
    cout << "All Chapter 12 demos completed successfully!" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                         PRACTICE PROBLEMS                                  ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                            ║
║  🟢 EASY:                                                                  ║
║  1. Two Sum (LC 1) — Hash map                                              ║
║  2. Contains Duplicate II (LC 219) — Set window                            ║
║  3. Random Pick with Weight (LC 528) — Prefix sum BS                       ║
║                                                                            ║
║  🟡 MEDIUM:                                                                ║
║  4. Subarray Sum Equals K (LC 560) — Prefix + Hash                         ║
║  5. Contains Duplicate III (LC 220) — Set window                           ║
║  6. Min Size Subarray Sum (LC 209) — Prefix BS                             ║
║  7. CSES — Josephus Problem II (Segment tree BS)                           ║
║  8. CSES — List Removals (BIT/Seg tree BS)                                 ║
║  9. Count inversions (BIT + compression)                                   ║
║                                                                            ║
║  🔴 HARD:                                                                  ║
║ 10. Sliding Window Median (LC 480) — Two multisets                         ║
║ 11. Count of Range Sum (LC 327) — Merge sort / BIT                         ║
║ 12. CF 1042D — Petya and Array (PBDS/BIT)                                  ║
║ 13. Max Sum of Rectangle No Larger Than K (LC 363)                         ║
║                                                                            ║
║  🔵 GRANDMASTER:                                                           ║
║ 14. CF 1515E — Dynamic order stats                                         ║
║ 15. Kth smallest in range using persistent seg tree                        ║
║ 16. CF 1208E — Let Them Slide (deque + seg tree)                           ║
║ 17. Merge Sort Tree — kth in range                                         ║
║                                                                            ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

