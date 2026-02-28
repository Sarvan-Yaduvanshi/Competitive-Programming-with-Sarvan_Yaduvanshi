/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-22 00:00:00

========================================================================
    ZERO TO GRAND MASTER (GM) — TWO POINTER TECHNIQUE TEMPLATES
========================================================================

TABLE OF CONTENTS:
===================
 PART 1: OPPOSITE DIRECTION (Converging) Two Pointers
    Template 1A — Basic Converging Framework
    Template 1B — Two Sum on Sorted Array
    Template 1C — Container With Most Water / Trapping Rain Water Style
    Template 1D — Palindrome Check
    Template 1E — Three Sum (Extension)
    Template 1F — Partitioning / Dutch National Flag (3-Way Partition)

 PART 2: SAME DIRECTION Two Pointers
    Template 2A — Reader-Writer (Compaction / Remove Duplicates)
    Template 2B — Merge Two Sorted Arrays
    Template 2C — Intersection of Two Sorted Arrays

 PART 3: FAST & SLOW Pointers (Floyd's / Tortoise & Hare)
    Template 3A — Linked List Cycle Detection
    Template 3B — Find Cycle Start Node
    Template 3C — Find Middle of Linked List
    Template 3D — Happy Number Detection (Array/Math Variant)

 PART 4: SLIDING WINDOW (Two Pointer Variant)
    Template 4A — Variable Size Window (Expand + Shrink)
    Template 4B — Longest Subarray/Substring with Condition
    Template 4C — Shortest/Minimum Subarray with Condition
    Template 4D — At Most K Distinct (Count Subarrays Trick)

 PART 5: BINARY SEARCH + TWO POINTER (GM Level)
    Template 5A — Count Pairs with Condition
    Template 5B — Kth Smallest Pair Distance

 PART 6: MULTI-POINTER / N-SUM (GM Level)
    Template 6A — 4Sum Framework
    Template 6B — General K-Sum Recursive Framework

 GM TIPS & PATTERN RECOGNITION GUIDE (at the bottom)
========================================================================
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
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

using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define nl '\n'

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }

// =====================================================================
// ██████╗  █████╗ ██████╗ ████████╗     ██╗
// ██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝    ███║
// ██████╔╝███████║██████╔╝   ██║       ╚══█║
// ██╔═══╝ ██╔══██║██╔══██╗   ██║          █║
// ██║     ██║  ██║██║  ██║   ██║          █║
// ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝          ╚═╝
//   OPPOSITE DIRECTION (CONVERGING) TWO POINTERS
// =====================================================================

/*
 * ==========================================
 * TEMPLATE 1A: BASIC CONVERGING FRAMEWORK
 * ==========================================
 *
 * WHEN TO USE:
 *   - Array is SORTED (or symmetry-based like palindrome)
 *   - You need to find a PAIR satisfying some condition
 *   - You want to NARROW the search space from both ends
 *
 * TIME: O(N)   SPACE: O(1)
 *
 * PROBLEMS:
 *   - Two Sum II (Sorted)
 *   - Valid Palindrome
 *   - Container With Most Water
 *   - Trapping Rain Water
 *   - Squares of a Sorted Array
 */

/*
void template_1A_converging(vec<int>& arr) {
    int left = 0;
    int right = sz(arr) - 1;

    while (left < right) {   // use left <= right if single element matters
        // --- DECISION LOGIC ---
        // Compute something using arr[left] and arr[right]

        if ( condition_to_move_left_forward ) {
            left++;
        }
        else if ( condition_to_move_right_backward ) {
            right--;
        }
        else {
            // Found the answer or process the pair
            // ...
            left++;   // or right-- or both
            right--;
        }
    }
}
*/


/*
 * ==========================================
 * TEMPLATE 1B: TWO SUM ON SORTED ARRAY
 * ==========================================
 *
 * WHEN TO USE:
 *   - Array is SORTED
 *   - Find pair (a, b) where a + b == target
 *
 * KEY INSIGHT:
 *   If sum < target → we need a bigger sum → move left++
 *   If sum > target → we need a smaller sum → move right--
 *
 * TIME: O(N)   SPACE: O(1)
 *
 * PROBLEMS:
 *   LC 167: Two Sum II
 *   LC 15 : 3Sum (use this inside a loop)
 *   LC 16 : 3Sum Closest
 *   LC 18 : 4Sum
 */

pair<int,int> template_1B_twoSum_sorted(vec<int>& arr, int target) {
    int left = 0, right = sz(arr) - 1;

    while (left < right) {
        int sum = arr[left] + arr[right];

        if (sum == target) {
            return {left, right};  // Found!
        }
        else if (sum < target) {
            left++;    // Need bigger sum → move left forward
        }
        else {
            right--;   // Need smaller sum → move right backward
        }
    }
    return {-1, -1}; // Not found
}


/*
 * ==========================================
 * TEMPLATE 1C: CONTAINER WITH MOST WATER STYLE
 * ==========================================
 *
 * WHEN TO USE:
 *   - You need to MAXIMIZE or MINIMIZE some expression
 *     involving arr[left] and arr[right] and (right - left)
 *   - The key insight: always move the pointer that is the "bottleneck"
 *
 * KEY INSIGHT:
 *   Move the pointer that points to the SMALLER value because:
 *   - Keeping the smaller value and shrinking the width can never help
 *   - Only by replacing the smaller value do we have a chance to improve
 *
 * TIME: O(N)   SPACE: O(1)
 *
 * PROBLEMS:
 *   LC 11 : Container With Most Water
 *   LC 42 : Trapping Rain Water (variation with prefix max)
 */

int template_1C_container_water(vec<int>& height) {
    int left = 0, right = sz(height) - 1;
    int maxArea = 0;

    while (left < right) {
        int width = right - left;
        int h = min(height[left], height[right]);
        maxArea = max(maxArea, width * h);

        // Move the bottleneck (smaller height) pointer
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    return maxArea;
}


/*
 * ==========================================
 * TEMPLATE 1D: PALINDROME CHECK
 * ==========================================
 *
 * WHEN TO USE:
 *   - Check if string/array reads the same forwards and backwards
 *   - "Valid Palindrome" with optional skip/tolerance
 *
 * KEY INSIGHT:
 *   Compare from both ends. If mismatch found:
 *   - For basic palindrome: return false
 *   - For "at most K removals": try skipping left OR right (recursion/greedy)
 *
 * TIME: O(N)   SPACE: O(1)
 *
 * PROBLEMS:
 *   LC 125: Valid Palindrome
 *   LC 680: Valid Palindrome II (can remove at most 1 char)
 *   LC 1216: Valid Palindrome III (can remove at most k chars → DP)
 */

bool template_1D_palindrome(const string& s) {
    int left = 0, right = sz(s) - 1;

    while (left < right) {
        // Optional: skip non-alphanumeric characters
        // while (left < right && !isalnum(s[left])) left++;
        // while (left < right && !isalnum(s[right])) right--;

        if (tolower(s[left]) != tolower(s[right])) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// Valid Palindrome II — can remove at most 1 character
bool isPalindromeRange(const string& s, int lo, int hi) {
    while (lo < hi) {
        if (s[lo] != s[hi]) return false;
        lo++; hi--;
    }
    return true;
}

bool template_1D_palindrome_II(const string& s) {
    int left = 0, right = sz(s) - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            // Try skipping left OR skipping right
            return isPalindromeRange(s, left + 1, right) ||
                   isPalindromeRange(s, left, right - 1);
        }
        left++;
        right--;
    }
    return true;
}


/*
 * ==========================================
 * TEMPLATE 1E: THREE SUM (EXTENSION OF TWO SUM)
 * ==========================================
 *
 * WHEN TO USE:
 *   - Find all TRIPLETS (a, b, c) with a + b + c == target
 *   - This is just: fix one element, then run Two Sum on the rest
 *
 * KEY INSIGHT (GM Level):
 *   - SORT the array first
 *   - Fix arr[i], then run converging two pointers on [i+1 .. n-1]
 *   - Skip duplicates at ALL three levels to avoid duplicate triplets
 *
 * TIME: O(N²)   SPACE: O(1) extra (ignoring output)
 *
 * PROBLEMS:
 *   LC 15 : 3Sum
 *   LC 16 : 3Sum Closest
 *   LC 259: 3Sum Smaller
 */

vvec<int> template_1E_threeSum(vec<int>& nums, int target = 0) {
    sort(all(nums));
    vvec<int> result;
    int n = sz(nums);

    for (int i = 0; i < n - 2; i++) {
        // Skip duplicate for the first element
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        // Early termination (GM optimization)
        if ((i64)nums[i] + nums[i + 1] + nums[i + 2] > target) break;        // smallest possible sum > target
        if ((i64)nums[i] + nums[n - 2] + nums[n - 1] < target) continue;     // largest possible sum < target

        int left = i + 1, right = n - 1;
        int need = target - nums[i];

        while (left < right) {
            int sum = nums[left] + nums[right];

            if (sum == need) {
                result.push_back({nums[i], nums[left], nums[right]});

                // Skip duplicates for second and third elements
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                left++;
                right--;
            }
            else if (sum < need) {
                left++;
            }
            else {
                right--;
            }
        }
    }
    return result;
}


/*
 * ============================================================
 * TEMPLATE 1F: DUTCH NATIONAL FLAG / 3-WAY PARTITION
 * ============================================================
 *
 * WHEN TO USE:
 *   - Partition array into 3 groups (low, mid, high)
 *   - Sort an array with only 3 distinct values (like 0, 1, 2)
 *   - "Sort Colors" problem
 *
 * KEY INSIGHT:
 *   3 pointers: lo, mid, hi
 *   - [0..lo-1]   = group 0 (low values)
 *   - [lo..mid-1]  = group 1 (mid values)
 *   - [mid..hi]    = unexplored
 *   - [hi+1..n-1]  = group 2 (high values)
 *
 * TIME: O(N)   SPACE: O(1)
 *
 * PROBLEMS:
 *   LC 75: Sort Colors
 *   Partition around pivot (QuickSort variant)
 */

void template_1F_dutch_flag(vec<int>& nums) {
    int lo = 0, mid = 0, hi = sz(nums) - 1;

    while (mid <= hi) {
        if (nums[mid] == 0) {
            swap(nums[lo], nums[mid]);
            lo++;
            mid++;
        }
        else if (nums[mid] == 1) {
            mid++;
        }
        else { // nums[mid] == 2
            swap(nums[mid], nums[hi]);
            hi--;
            // DON'T increment mid — the swapped-in element needs to be checked
        }
    }
}


// =====================================================================
// ██████╗  █████╗ ██████╗ ████████╗    ██████╗
// ██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝         ██╗
// ██████╔╝███████║██████╔╝   ██║        █████╔╝
// ██╔═══╝ ██╔══██║██╔══██╗   ██║       ██╔═══╝
// ██║     ██║  ██║██║  ██║   ██║       ███████╗
// ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝       ╚══════╝
//   SAME DIRECTION TWO POINTERS
// =====================================================================

/*
 * ==========================================
 * TEMPLATE 2A: READER-WRITER (COMPACTION)
 * ==========================================
 *
 * WHEN TO USE:
 *   - Remove elements in-place
 *   - Remove duplicates from sorted array
 *   - Compact / filter array in O(1) space
 *
 * KEY INSIGHT:
 *   Two pointers move in the SAME direction (left to right):
 *   - 'reader' (fast) scans every element
 *   - 'writer' (slow) marks where the next valid element goes
 *   - Writer ONLY advances when we place a valid element
 *
 * TIME: O(N)   SPACE: O(1)
 *
 * PROBLEMS:
 *   LC 26 : Remove Duplicates from Sorted Array
 *   LC 27 : Remove Element
 *   LC 80 : Remove Duplicates from Sorted Array II (allow at most 2)
 *   LC 283: Move Zeroes
 */

// Remove all occurrences of 'val'
int template_2A_remove_element(vec<int>& nums, int val) {
    int writer = 0;
    for (int reader = 0; reader < sz(nums); reader++) {
        if (nums[reader] != val) {
            nums[writer] = nums[reader];
            writer++;
        }
    }
    return writer;  // new size
}

// Remove duplicates from sorted array (keep at most 1 of each)
int template_2A_remove_duplicates(vec<int>& nums) {
    if (nums.empty()) return 0;
    int writer = 1;  // first element is always valid
    for (int reader = 1; reader < sz(nums); reader++) {
        if (nums[reader] != nums[reader - 1]) {
            nums[writer] = nums[reader];
            writer++;
        }
    }
    return writer;
}

// Remove duplicates — keep at most K of each (GM Generalization)
int template_2A_remove_duplicates_K(vec<int>& nums, int k) {
    if (sz(nums) <= k) return sz(nums);
    int writer = k;  // first k elements are always valid
    for (int reader = k; reader < sz(nums); reader++) {
        // Compare with the element k positions behind the writer
        if (nums[reader] != nums[writer - k]) {
            nums[writer] = nums[reader];
            writer++;
        }
    }
    return writer;
}

// Move Zeroes to end (keep relative order of non-zero elements)
void template_2A_move_zeroes(vec<int>& nums) {
    int writer = 0;
    for (int reader = 0; reader < sz(nums); reader++) {
        if (nums[reader] != 0) {
            swap(nums[writer], nums[reader]); // swap to maintain order
            writer++;
        }
    }
}


/*
 * ==========================================
 * TEMPLATE 2B: MERGE TWO SORTED ARRAYS
 * ==========================================
 *
 * WHEN TO USE:
 *   - Merge two sorted sequences into one sorted sequence
 *   - Part of Merge Sort
 *
 * KEY INSIGHT:
 *   Two pointers, one on each array. Compare and pick the smaller.
 *   After one exhausts, copy the rest of the other.
 *
 * TIME: O(N + M)   SPACE: O(N + M) for output
 *
 * PROBLEMS:
 *   LC 88 : Merge Sorted Array (in-place, merge from the back)
 *   LC 21 : Merge Two Sorted Lists (Linked List version)
 *   LC 23 : Merge k Sorted Lists (use priority queue)
 */

vec<int> template_2B_merge_sorted(const vec<int>& a, const vec<int>& b) {
    vec<int> result;
    int i = 0, j = 0;

    while (i < sz(a) && j < sz(b)) {
        if (a[i] <= b[j]) {
            result.push_back(a[i++]);
        } else {
            result.push_back(b[j++]);
        }
    }

    // Copy remaining
    while (i < sz(a)) result.push_back(a[i++]);
    while (j < sz(b)) result.push_back(b[j++]);

    return result;
}

// LC 88: Merge Sorted Array IN-PLACE (merge from back — GM trick)
void template_2B_merge_inplace(vec<int>& nums1, int m, vec<int>& nums2, int n) {
    int i = m - 1, j = n - 1, write = m + n - 1;

    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[write--] = nums1[i--];
        } else {
            nums1[write--] = nums2[j--];
        }
    }
    // Copy remaining from nums2 (nums1 remaining are already in place)
    while (j >= 0) {
        nums1[write--] = nums2[j--];
    }
}


/*
 * ==========================================
 * TEMPLATE 2C: INTERSECTION OF TWO SORTED ARRAYS
 * ==========================================
 *
 * WHEN TO USE:
 *   - Find common elements between two sorted arrays
 *   - Find elements in one but not the other (difference)
 *
 * TIME: O(N + M)   SPACE: O(min(N, M)) for output
 *
 * PROBLEMS:
 *   LC 349: Intersection of Two Arrays
 *   LC 350: Intersection of Two Arrays II
 */

vec<int> template_2C_intersection(vec<int>& a, vec<int>& b) {
    // Assumes both are sorted
    vec<int> result;
    int i = 0, j = 0;

    while (i < sz(a) && j < sz(b)) {
        if (a[i] == b[j]) {
            result.push_back(a[i]);
            i++;
            j++;
        }
        else if (a[i] < b[j]) {
            i++;   // a[i] is too small, advance it
        }
        else {
            j++;   // b[j] is too small, advance it
        }
    }
    return result;
}


// =====================================================================
// ██████╗  █████╗ ██████╗ ████████╗    ██████╗
// ██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝         ██╗
// ██████╔╝███████║██████╔╝   ██║        █████╔╝
// ██╔═══╝ ██╔══██║██╔══██╗   ██║             ██╗
// ██║     ██║  ██║██║  ██║   ██║       ██████╔╝
// ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝       ╚═════╝
//   FAST & SLOW POINTERS (FLOYD'S / TORTOISE & HARE)
// =====================================================================

/*
 * ==========================================
 * TEMPLATE 3A: LINKED LIST CYCLE DETECTION
 * ==========================================
 *
 * WHEN TO USE:
 *   - Detect if a linked list has a cycle
 *   - Detect if a sequence enters a cycle (functional graph)
 *
 * KEY INSIGHT:
 *   - Slow moves 1 step, Fast moves 2 steps
 *   - If there is a cycle, they WILL meet inside the cycle
 *   - If no cycle, fast reaches nullptr
 *
 * WHY IT WORKS (GM Level Math):
 *   Let cycle length = C. When slow enters cycle, fast is already
 *   some distance ahead. The gap reduces by 1 each step.
 *   So they meet in at most C steps after slow enters the cycle.
 *
 * TIME: O(N)   SPACE: O(1)
 *
 * PROBLEMS:
 *   LC 141: Linked List Cycle
 *   LC 142: Linked List Cycle II (find start)
 *   LC 287: Find the Duplicate Number
 *   LC 202: Happy Number
 */

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

bool template_3A_hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;         // 1 step
        fast = fast->next->next;   // 2 steps

        if (slow == fast) {
            return true;  // Cycle detected!
        }
    }
    return false;  // fast reached end → no cycle
}


/*
 * ==========================================
 * TEMPLATE 3B: FIND CYCLE START NODE
 * ==========================================
 *
 * WHEN TO USE:
 *   - Find WHERE the cycle begins in a linked list
 *   - Find the duplicate number in [1..n] array
 *
 * KEY INSIGHT (Floyd's Algorithm Phase 2):
 *   After slow and fast meet inside the cycle:
 *   - Reset one pointer to head
 *   - Move BOTH pointers 1 step at a time
 *   - They will meet at the CYCLE START
 *
 * WHY (GM Level Proof):
 *   Let distance from head to cycle start = A
 *   Let distance from cycle start to meeting point = B
 *   Let cycle length = C
 *   At meeting: slow traveled A+B, fast traveled A+B+kC (for some k)
 *   Since fast = 2*slow: A+B+kC = 2(A+B) → kC = A+B → A = kC-B
 *   So if we start from head and meeting point simultaneously (1 step each),
 *   they meet after A steps — which is exactly the cycle start.
 *
 * TIME: O(N)   SPACE: O(1)
 *
 * PROBLEMS:
 *   LC 142: Linked List Cycle II
 *   LC 287: Find the Duplicate Number
 */

ListNode* template_3B_cycleStart(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    // Phase 1: Detect cycle (find meeting point)
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }

    // No cycle
    if (!fast || !fast->next) return nullptr;

    // Phase 2: Find cycle start
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;  // Both move 1 step now
    }
    return slow;  // This is the cycle start
}

// LC 287: Find the Duplicate Number (Array treated as linked list)
int template_3B_findDuplicate(vec<int>& nums) {
    // Treat array as linked list: index → value → next index
    int slow = nums[0], fast = nums[0];

    // Phase 1: Find intersection
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);

    // Phase 2: Find cycle start (= duplicate number)
    slow = nums[0];
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;
}


/*
 * ==========================================
 * TEMPLATE 3C: FIND MIDDLE OF LINKED LIST
 * ==========================================
 *
 * WHEN TO USE:
 *   - Find middle node of linked list
 *   - Split linked list into two halves (for merge sort, palindrome check, etc.)
 *
 * KEY INSIGHT:
 *   When fast reaches end, slow is at the middle.
 *   - For even length: "left < right" gives first middle, "<= right" gives second
 *
 * TIME: O(N)   SPACE: O(1)
 *
 * PROBLEMS:
 *   LC 876: Middle of the Linked List
 *   LC 234: Palindrome Linked List (find mid → reverse second half → compare)
 *   LC 143: Reorder List
 *   LC 148: Sort List (merge sort on linked list)
 */

ListNode* template_3C_findMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    // For SECOND middle (even length): fast && fast->next
    // For FIRST middle (even length):  fast->next && fast->next->next
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;  // slow is at middle
}


/*
 * ==========================================
 * TEMPLATE 3D: HAPPY NUMBER (ARRAY/MATH VARIANT)
 * ==========================================
 *
 * WHEN TO USE:
 *   - Any problem where you repeatedly apply a function f(x)
 *     and need to detect if you enter a cycle or reach a target
 *   - Happy Number, Digital Root, etc.
 *
 * KEY INSIGHT:
 *   Treat the sequence x, f(x), f(f(x)), ... as a "virtual linked list"
 *   Apply Floyd's cycle detection on this sequence.
 *
 * TIME: O(log N) for Happy Number   SPACE: O(1)
 *
 * PROBLEMS:
 *   LC 202: Happy Number
 */

int sumOfSquares(int n) {
    int sum = 0;
    while (n > 0) {
        int d = n % 10;
        sum += d * d;
        n /= 10;
    }
    return sum;
}

bool template_3D_isHappy(int n) {
    int slow = n;
    int fast = n;

    do {
        slow = sumOfSquares(slow);               // 1 step
        fast = sumOfSquares(sumOfSquares(fast));   // 2 steps
    } while (slow != fast);

    return slow == 1;  // If they meet at 1, it's happy
}


// =====================================================================
// ██████╗  █████╗ ██████╗ ████████╗    ██╗  ██╗
// ██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝    ██║  ██║
// ██████╔╝███████║██████╔╝   ██║       ███████║
// ██╔═══╝ ██╔══██║██╔══██╗   ██║       ╚════██║
// ██║     ██║  ██║██║  ██║   ██║            ██║
// ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝            ╚═╝
//   SLIDING WINDOW (TWO POINTER VARIANT)
// =====================================================================

/*
 * ==========================================
 * TEMPLATE 4A: VARIABLE SIZE WINDOW (EXPAND + SHRINK)
 * ==========================================
 *
 * WHEN TO USE:
 *   - Find longest/shortest subarray with some property
 *   - Count subarrays with some property
 *   - The window property has MONOTONIC behavior:
 *     expanding can only make it "worse" (or stay same)
 *     shrinking can only make it "better" (or stay same)
 *
 * KEY INSIGHT:
 *   This is the MASTER TEMPLATE for sliding window.
 *   - 'left' and 'right' move in the SAME direction (left to right)
 *   - 'right' EXPANDS the window (include more elements)
 *   - 'left' SHRINKS the window (exclude elements until valid)
 *
 * TIME: O(N) — each element enters and leaves the window at most once
 * SPACE: O(1) or O(K) depending on auxiliary data
 */

/*
// --- LONGEST subarray/substring with condition ---
int template_4A_longest(vec<int>& arr) {
    int n = sz(arr);
    int left = 0;
    int ans = 0;

    // State variables for the window (e.g., sum, count map, etc.)
    // int windowSum = 0;
    // unordered_map<int,int> freq;

    for (int right = 0; right < n; right++) {
        // --- EXPAND: Add arr[right] to window state ---
        // windowSum += arr[right];
        // freq[arr[right]]++;

        // --- SHRINK: While window is INVALID, shrink from left ---
        while ( window_is_invalid ) {
            // Remove arr[left] from window state
            // windowSum -= arr[left];
            // freq[arr[left]]--; if (freq[arr[left]] == 0) freq.erase(arr[left]);
            left++;
        }

        // --- UPDATE answer: window [left..right] is valid ---
        ans = max(ans, right - left + 1);
    }
    return ans;
}
*/


/*
 * ==========================================
 * TEMPLATE 4B: LONGEST SUBARRAY/SUBSTRING WITH CONDITION
 * ==========================================
 *
 * Concrete Examples:
 *
 * PROBLEMS:
 *   LC 3   : Longest Substring Without Repeating Characters
 *   LC 159 : Longest Substring with At Most 2 Distinct Characters
 *   LC 340 : Longest Substring with At Most K Distinct Characters
 *   LC 424 : Longest Repeating Character Replacement
 *   LC 1004: Max Consecutive Ones III (can flip at most K zeros)
 *   LC 1695: Maximum Erasure Value
 */

// LC 3: Longest Substring Without Repeating Characters
int template_4B_longest_unique_substr(const string& s) {
    int freq[128] = {};  // ASCII frequency
    int left = 0, ans = 0;

    for (int right = 0; right < sz(s); right++) {
        freq[(int)s[right]]++;

        // Shrink while we have a duplicate
        while (freq[(int)s[right]] > 1) {
            freq[(int)s[left]]--;
            left++;
        }

        ans = max(ans, right - left + 1);
    }
    return ans;
}

// LC 1004: Max Consecutive Ones III (can flip at most K zeros)
int template_4B_max_ones(vec<int>& nums, int k) {
    int left = 0, ans = 0;
    int zeroCount = 0;

    for (int right = 0; right < sz(nums); right++) {
        if (nums[right] == 0) zeroCount++;

        while (zeroCount > k) {
            if (nums[left] == 0) zeroCount--;
            left++;
        }

        ans = max(ans, right - left + 1);
    }
    return ans;
}

// LC 424: Longest Repeating Character Replacement
int template_4B_char_replacement(const string& s, int k) {
    int freq[26] = {};
    int left = 0, maxFreq = 0, ans = 0;

    for (int right = 0; right < sz(s); right++) {
        freq[s[right] - 'A']++;
        maxFreq = max(maxFreq, freq[s[right] - 'A']);

        // Window size - maxFreq = number of chars to replace
        // If that exceeds k, shrink
        while ((right - left + 1) - maxFreq > k) {
            freq[s[left] - 'A']--;
            left++;
        }

        ans = max(ans, right - left + 1);
    }
    return ans;
}


/*
 * ==========================================
 * TEMPLATE 4C: SHORTEST/MINIMUM SUBARRAY WITH CONDITION
 * ==========================================
 *
 * WHEN TO USE:
 *   - Find SHORTEST subarray satisfying some condition
 *   - Minimum window that contains all required elements
 *
 * KEY DIFFERENCE from Longest:
 *   - Update answer WHILE the window is valid (before shrinking)
 *   - Keep shrinking to find the minimum valid window
 *
 * PROBLEMS:
 *   LC 209 : Minimum Size Subarray Sum
 *   LC 76  : Minimum Window Substring
 *   LC 862 : Shortest Subarray with Sum at Least K (needs deque for negative values)
 */

// LC 209: Minimum Size Subarray Sum (sum >= target)
int template_4C_min_subarray_sum(vec<int>& nums, int target) {
    int left = 0, windowSum = 0;
    int ans = INT_MAX;

    for (int right = 0; right < sz(nums); right++) {
        windowSum += nums[right];

        // While window is VALID, try to shrink and update answer
        while (windowSum >= target) {
            ans = min(ans, right - left + 1);
            windowSum -= nums[left];
            left++;
        }
    }
    return ans == INT_MAX ? 0 : ans;
}

// LC 76: Minimum Window Substring
string template_4C_min_window(const string& s, const string& t) {
    int need[128] = {}, have[128] = {};
    int required = 0, formed = 0;

    for (char c : t) {
        if (need[(int)c] == 0) required++;
        need[(int)c]++;
    }

    int left = 0, minLen = INT_MAX, minStart = 0;

    for (int right = 0; right < sz(s); right++) {
        char c = s[right];
        have[(int)c]++;

        if (need[(int)c] > 0 && have[(int)c] == need[(int)c]) {
            formed++;
        }

        // Shrink while valid
        while (formed == required) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minStart = left;
            }
            char d = s[left];
            have[(int)d]--;
            if (need[(int)d] > 0 && have[(int)d] < need[(int)d]) {
                formed--;
            }
            left++;
        }
    }

    return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
}


/*
 * ============================================================
 * TEMPLATE 4D: AT MOST K — COUNT SUBARRAYS TRICK (GM Level)
 * ============================================================
 *
 * WHEN TO USE:
 *   - Count number of subarrays with EXACTLY K distinct elements
 *   - Count subarrays with property == K
 *
 * KEY INSIGHT (BRILLIANT TRICK):
 *   exactly(K) = atMost(K) - atMost(K - 1)
 *
 *   atMost(K): For each 'right', count subarrays ending at 'right'
 *   with at most K distinct elements = (right - left + 1)
 *
 * WHY (right - left + 1)?
 *   Subarrays ending at 'right' that start at left, left+1, ..., right
 *   → that's (right - left + 1) subarrays
 *
 * TIME: O(N)   SPACE: O(K)
 *
 * PROBLEMS:
 *   LC 992 : Subarrays with K Different Integers
 *   LC 1248: Count Number of Nice Subarrays (exactly K odd)
 *   LC 930 : Binary Subarrays With Sum
 *   LC 2444: Count Subarrays With Fixed Bounds
 */

i64 atMostKDistinct(vec<int>& nums, int k) {
    if (k < 0) return 0;

    unordered_map<int, int> freq;
    int left = 0;
    i64 count = 0;

    for (int right = 0; right < sz(nums); right++) {
        freq[nums[right]]++;

        while (sz(freq) > k) {
            freq[nums[left]]--;
            if (freq[nums[left]] == 0) freq.erase(nums[left]);
            left++;
        }

        // All subarrays [left..right], [left+1..right], ..., [right..right] are valid
        count += (right - left + 1);
    }
    return count;
}

i64 template_4D_exactly_K_distinct(vec<int>& nums, int k) {
    return atMostKDistinct(nums, k) - atMostKDistinct(nums, k - 1);
}


// =====================================================================
// ██████╗  █████╗ ██████╗ ████████╗    ███████╗
// ██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝    ██╔════╝
// ██████╔╝███████║██████╔╝   ██║       ███████╗
// ██╔═══╝ ██╔══██║██╔══██╗   ██║       ╚════██║
// ██║     ██║  ██║██║  ██║   ██║       ███████║
// ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝       ╚══════╝
//   BINARY SEARCH + TWO POINTER (GM LEVEL)
// =====================================================================

/*
 * ==========================================
 * TEMPLATE 5A: COUNT PAIRS WITH CONDITION
 * ==========================================
 *
 * WHEN TO USE:
 *   - Count pairs (i, j) where i < j and some condition on arr[i], arr[j]
 *   - Usually on a SORTED array
 *   - Conditions like: sum < target, sum >= target, diff <= d, etc.
 *
 * KEY INSIGHT:
 *   For sorted array:
 *   - Fix left. Binary search (or use right pointer) for the boundary.
 *   - All elements between give valid pairs.
 *
 * TIME: O(N log N) or O(N)   SPACE: O(1)
 *
 * PROBLEMS:
 *   LC 611 : Valid Triangle Number
 *   LC 259 : 3Sum Smaller
 *   LC 881 : Boats to Save People
 */

// Count pairs with sum < target (sorted array)
i64 template_5A_count_pairs_sum_less(vec<int>& arr, int target) {
    sort(all(arr));
    int left = 0, right = sz(arr) - 1;
    i64 count = 0;

    while (left < right) {
        if (arr[left] + arr[right] < target) {
            // All pairs (left, left+1), (left, left+2), ..., (left, right) are valid
            count += (right - left);
            left++;
        } else {
            right--;
        }
    }
    return count;
}

// LC 881: Boats to Save People
int template_5A_boats(vec<int>& people, int limit) {
    sort(all(people));
    int left = 0, right = sz(people) - 1;
    int boats = 0;

    while (left <= right) {
        if (people[left] + people[right] <= limit) {
            left++;   // Pair them together
        }
        right--;      // Heaviest person always gets on a boat
        boats++;
    }
    return boats;
}


/*
 * ==========================================
 * TEMPLATE 5B: KTH SMALLEST PAIR DISTANCE
 * ==========================================
 *
 * WHEN TO USE:
 *   - Find the Kth smallest pair distance/sum
 *   - Binary search on the ANSWER + two pointer to COUNT
 *
 * KEY INSIGHT:
 *   Binary search on the answer 'mid'. For each candidate 'mid',
 *   use two pointers to count how many pairs have distance <= mid.
 *   If count >= k → answer is at most mid → search left half.
 *
 * TIME: O(N log N + N log W) where W = max distance   SPACE: O(1)
 *
 * PROBLEMS:
 *   LC 719: Find K-th Smallest Pair Distance
 *   LC 378: Kth Smallest Element in a Sorted Matrix (similar idea)
 */

int template_5B_kth_smallest_pair_distance(vec<int>& nums, int k) {
    sort(all(nums));
    int n = sz(nums);
    int lo = 0, hi = nums[n - 1] - nums[0];

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        // Count pairs with distance <= mid using two pointers
        int count = 0;
        int left = 0;
        for (int right = 0; right < n; right++) {
            while (nums[right] - nums[left] > mid) {
                left++;
            }
            count += (right - left);  // pairs (left, right), (left+1, right), ...
        }

        if (count >= k) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}


// =====================================================================
// ██████╗  █████╗ ██████╗ ████████╗     ██████╗
// ██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝    ██╔════╝
// ██████╔╝███████║██████╔╝   ██║       ███████╗
// ██╔═══╝ ██╔══██║██╔══██╗   ██║       ██╔═══██╗
// ██║     ██║  ██║██║  ██║   ██║       ╚██████╔╝
// ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝        ╚═════╝
//   MULTI-POINTER / N-SUM (GM LEVEL)
// =====================================================================

/*
 * ==========================================
 * TEMPLATE 6A: 4SUM
 * ==========================================
 *
 * WHEN TO USE:
 *   - Find all quadruplets that sum to target
 *   - Extension of 3Sum: fix 2 elements, run 2Sum on the rest
 *
 * KEY INSIGHT:
 *   - Sort first
 *   - 2 outer loops (fix a and b)
 *   - Inner two pointer (find c and d)
 *   - Skip duplicates at every level
 *   - Use early termination (GM optimization)
 *
 * TIME: O(N³)   SPACE: O(1) extra
 *
 * PROBLEMS:
 *   LC 18: 4Sum
 */

vvec<int> template_6A_fourSum(vec<int>& nums, i64 target) {
    sort(all(nums));
    vvec<int> result;
    int n = sz(nums);

    for (int a = 0; a < n - 3; a++) {
        if (a > 0 && nums[a] == nums[a - 1]) continue;

        // Early termination
        if ((i64)nums[a] + nums[a+1] + nums[a+2] + nums[a+3] > target) break;
        if ((i64)nums[a] + nums[n-3] + nums[n-2] + nums[n-1] < target) continue;

        for (int b = a + 1; b < n - 2; b++) {
            if (b > a + 1 && nums[b] == nums[b - 1]) continue;

            // Early termination
            if ((i64)nums[a] + nums[b] + nums[b+1] + nums[b+2] > target) break;
            if ((i64)nums[a] + nums[b] + nums[n-2] + nums[n-1] < target) continue;

            int c = b + 1, d = n - 1;
            i64 need = target - nums[a] - nums[b];

            while (c < d) {
                i64 sum = (i64)nums[c] + nums[d];
                if (sum == need) {
                    result.push_back({nums[a], nums[b], nums[c], nums[d]});
                    while (c < d && nums[c] == nums[c + 1]) c++;
                    while (c < d && nums[d] == nums[d - 1]) d--;
                    c++; d--;
                }
                else if (sum < need) c++;
                else d--;
            }
        }
    }
    return result;
}


/*
 * ==========================================
 * TEMPLATE 6B: GENERAL K-SUM (RECURSIVE GM FRAMEWORK)
 * ==========================================
 *
 * WHEN TO USE:
 *   - Generalization: find K numbers that sum to target
 *   - Works for 2Sum, 3Sum, 4Sum, 5Sum, ... any K
 *
 * KEY INSIGHT:
 *   Recursive decomposition:
 *   - K-Sum → fix one element → solve (K-1)-Sum on remaining
 *   - Base case: K == 2 → use two pointer
 *
 * TIME: O(N^(K-1))   SPACE: O(K) recursion depth
 */

vvec<int> kSumHelper(vec<int>& nums, int start, int k, i64 target) {
    vvec<int> result;
    int n = sz(nums);

    if (k == 2) {
        // Base case: Two Sum with two pointers
        int lo = start, hi = n - 1;
        while (lo < hi) {
            i64 sum = (i64)nums[lo] + nums[hi];
            if (sum == target) {
                result.push_back({nums[lo], nums[hi]});
                while (lo < hi && nums[lo] == nums[lo + 1]) lo++;
                while (lo < hi && nums[hi] == nums[hi - 1]) hi--;
                lo++; hi--;
            }
            else if (sum < target) lo++;
            else hi--;
        }
        return result;
    }

    // Recursive case: fix nums[i], solve (k-1)-Sum
    for (int i = start; i <= n - k; i++) {
        if (i > start && nums[i] == nums[i - 1]) continue; // skip duplicates

        // Early termination
        i64 minSum = 0, maxSum = 0;
        for (int j = 0; j < k; j++) minSum += nums[i + j];
        for (int j = 0; j < k; j++) maxSum += nums[n - 1 - j];
        if (minSum > target) break;
        if (maxSum < target) continue;

        auto sub = kSumHelper(nums, i + 1, k - 1, target - nums[i]);
        for (auto& v : sub) {
            v.insert(v.begin(), nums[i]);
            result.push_back(v);
        }
    }
    return result;
}

vvec<int> template_6B_kSum(vec<int>& nums, int k, i64 target) {
    sort(all(nums));
    return kSumHelper(nums, 0, k, target);
}


// =====================================================================
//
//   ██████╗ ███╗   ███╗    ████████╗██╗██████╗ ███████╗
//  ██╔════╝ ████╗ ████║    ╚══██╔══╝██║██╔══██╗██╔════╝
//  ██║  ███╗██╔████╔██║       ██║   ██║██████╔╝███████╗
//  ██║   ██║██║╚██╔╝██║       ██║   ██║██╔═══╝ ╚════██║
//  ╚██████╔╝██║ ╚═╝ ██║       ██║   ██║██║     ███████║
//   ╚═════╝ ╚═╝     ╚═╝       ╚═╝   ╚═╝╚═╝     ╚══════╝
//
//   PATTERN RECOGNITION & TIPS — WHEN TO USE WHICH TEMPLATE
//
// =====================================================================

/*
 ╔══════════════════════════════════════════════════════════════════════════╗
 ║                    MASTER DECISION FLOWCHART                            ║
 ╠══════════════════════════════════════════════════════════════════════════╣
 ║                                                                         ║
 ║  Q1: Is the data a LINKED LIST?                                         ║
 ║    YES → Q1a: Detect cycle?              → Template 3A (Fast & Slow)    ║
 ║          Q1b: Find cycle start?          → Template 3B (Floyd Phase 2)  ║
 ║          Q1c: Find middle?               → Template 3C (Fast & Slow)    ║
 ║          Q1d: Merge two sorted lists?    → Template 2B (Same Direction) ║
 ║                                                                         ║
 ║  Q2: Is the array SORTED (or can you sort it)?                          ║
 ║    YES → Q2a: Find pair with target sum? → Template 1B (Converging)     ║
 ║          Q2b: Find triplet?              → Template 1E (3Sum)           ║
 ║          Q2c: Find K-tuple?              → Template 6B (K-Sum)          ║
 ║          Q2d: Count pairs w/ condition?  → Template 5A (Count Pairs)    ║
 ║          Q2e: Kth smallest pair?         → Template 5B (BS + 2P)        ║
 ║          Q2f: Merge two sorted arrays?   → Template 2B (Merge)          ║
 ║          Q2g: Intersection/difference?   → Template 2C (Intersection)   ║
 ║          Q2h: Pair boats/people?         → Template 5A (Boats)          ║
 ║                                                                         ║
 ║  Q3: Is it about a SUBARRAY or SUBSTRING?                               ║
 ║    YES → Q3a: Longest with condition?    → Template 4B (Sliding Window) ║
 ║          Q3b: Shortest with condition?   → Template 4C (Min Window)     ║
 ║          Q3c: Count subarrays exactly K? → Template 4D (atMost trick)   ║
 ║          Q3d: Fixed size window?         → Fixed Sliding Window (basic) ║
 ║                                                                         ║
 ║  Q4: Is it about IN-PLACE modification?                                 ║
 ║    YES → Q4a: Remove elements/duplicates → Template 2A (Reader-Writer)  ║
 ║          Q4b: Partition into groups?      → Template 1F (Dutch Flag)    ║
 ║          Q4c: Move elements?              → Template 2A (Move Zeroes)   ║
 ║                                                                         ║
 ║  Q5: Is it about PALINDROME?                                            ║
 ║    YES → Template 1D (Converging)                                       ║
 ║                                                                         ║
 ║  Q6: Is it about MAXIMIZE area/distance?                                ║
 ║    YES → Template 1C (Container Water / Move the bottleneck)            ║
 ║                                                                         ║
 ║  Q7: Detect CYCLE in number sequence?                                   ║
 ║    YES → Template 3D (Floyd on virtual linked list)                     ║
 ║                                                                         ║
 ╚══════════════════════════════════════════════════════════════════════════╝


 ╔══════════════════════════════════════════════════════════════════════════╗
 ║                         GM LEVEL TIPS                                   ║
 ╠══════════════════════════════════════════════════════════════════════════╣
 ║                                                                         ║
 ║  TIP 1: SORT FIRST                                                     ║
 ║    80% of two-pointer problems require sorting first.                   ║
 ║    If the problem says "order doesn't matter" → SORT IT.                ║
 ║                                                                         ║
 ║  TIP 2: KNOW YOUR INVARIANT                                            ║
 ║    Before coding, write down what is TRUE about the window/range        ║
 ║    at every step. E.g., "All elements in [left..right] are valid."      ║
 ║                                                                         ║
 ║  TIP 3: EXACTLY K = ATMOST(K) - ATMOST(K-1)                            ║
 ║    This is the single most powerful trick for counting subarrays.       ║
 ║    If you see "exactly K" → think this decomposition.                   ║
 ║                                                                         ║
 ║  TIP 4: SHRINK vs EXPAND                                               ║
 ║    For LONGEST → expand as much as possible, shrink when invalid.       ║
 ║    For SHORTEST → expand until valid, then shrink while still valid.    ║
 ║                                                                         ║
 ║  TIP 5: DON'T RESET LEFT                                               ║
 ║    In sliding window, 'left' NEVER moves backward. This is what        ║
 ║    gives O(N) time. If you find yourself resetting left = 0,            ║
 ║    you're probably doing it wrong.                                      ║
 ║                                                                         ║
 ║  TIP 6: SKIP DUPLICATES (N-Sum)                                        ║
 ║    When finding unique tuples, skip duplicates at EVERY pointer level.  ║
 ║    Pattern: if (i > start && nums[i] == nums[i-1]) continue;           ║
 ║                                                                         ║
 ║  TIP 7: EARLY TERMINATION (GM Optimization)                            ║
 ║    In N-Sum: if minimum possible sum > target → break.                  ║
 ║              if maximum possible sum < target → continue.               ║
 ║    This gives huge constant factor improvement.                         ║
 ║                                                                         ║
 ║  TIP 8: TWO POINTER ON ANSWER (Binary Search + Two Pointer)            ║
 ║    If the answer is monotonic (e.g., if distance D works, D+1 works),  ║
 ║    binary search on the answer, and use two pointers to verify.         ║
 ║                                                                         ║
 ║  TIP 9: WHEN TO USE DEQUE INSTEAD OF TWO POINTERS                     ║
 ║    If the array has NEGATIVE numbers and you need subarray sum          ║
 ║    conditions, two pointers won't work (no monotonicity).              ║
 ║    Use monotonic deque or prefix sum + binary search instead.           ║
 ║    Example: LC 862 (Shortest Subarray with Sum at Least K)             ║
 ║                                                                         ║
 ║  TIP 10: VIRTUAL LINKED LIST (GM Trick)                                ║
 ║    Any function f(x) that maps a finite set to itself creates a         ║
 ║    "virtual linked list" (functional graph). You can use Floyd's        ║
 ║    cycle detection on it. Example: LC 287 (Find Duplicate Number).     ║
 ║                                                                         ║
 ╚══════════════════════════════════════════════════════════════════════════╝


 ╔══════════════════════════════════════════════════════════════════════════╗
 ║              COMPLEXITY SUMMARY FOR ALL TEMPLATES                       ║
 ╠═══════════════════════════════════════════╦═══════════╦═════════════════╣
 ║  Template                                 ║   Time    ║     Space      ║
 ╠═══════════════════════════════════════════╬═══════════╬═════════════════╣
 ║  1A: Converging Basic                     ║   O(N)    ║     O(1)       ║
 ║  1B: Two Sum Sorted                       ║   O(N)    ║     O(1)       ║
 ║  1C: Container Water                      ║   O(N)    ║     O(1)       ║
 ║  1D: Palindrome                           ║   O(N)    ║     O(1)       ║
 ║  1E: Three Sum                            ║   O(N²)   ║     O(1)       ║
 ║  1F: Dutch National Flag                  ║   O(N)    ║     O(1)       ║
 ║  2A: Reader-Writer                        ║   O(N)    ║     O(1)       ║
 ║  2B: Merge Sorted                         ║   O(N+M)  ║     O(N+M)    ║
 ║  2C: Intersection                         ║   O(N+M)  ║     O(min)    ║
 ║  3A: Cycle Detection                      ║   O(N)    ║     O(1)       ║
 ║  3B: Cycle Start                          ║   O(N)    ║     O(1)       ║
 ║  3C: Find Middle                          ║   O(N)    ║     O(1)       ║
 ║  3D: Happy Number                         ║   O(logN) ║     O(1)       ║
 ║  4A-4B: Longest Window                    ║   O(N)    ║     O(K)       ║
 ║  4C: Shortest Window                      ║   O(N)    ║     O(K)       ║
 ║  4D: AtMost K (Count)                     ║   O(N)    ║     O(K)       ║
 ║  5A: Count Pairs                          ║  O(NlogN) ║     O(1)       ║
 ║  5B: Kth Pair Distance                    ║  O(NlogW) ║     O(1)       ║
 ║  6A: 4Sum                                 ║   O(N³)   ║     O(1)       ║
 ║  6B: K-Sum General                        ║  O(N^K-1) ║     O(K)       ║
 ╚═══════════════════════════════════════════╩═══════════╩═════════════════╝


 ╔══════════════════════════════════════════════════════════════════════════╗
 ║                    PRACTICE PROBLEMS ROADMAP                            ║
 ╠══════════════════════════════════════════════════════════════════════════╣
 ║                                                                         ║
 ║  LEVEL 1 — BEGINNER (Learn the patterns):                               ║
 ║    LC 167: Two Sum II                       [Template 1B]               ║
 ║    LC 125: Valid Palindrome                 [Template 1D]               ║
 ║    LC 283: Move Zeroes                      [Template 2A]               ║
 ║    LC 27 : Remove Element                   [Template 2A]               ║
 ║    LC 26 : Remove Duplicates Sorted Array   [Template 2A]               ║
 ║    LC 88 : Merge Sorted Array               [Template 2B]               ║
 ║    LC 876: Middle of Linked List            [Template 3C]               ║
 ║    LC 141: Linked List Cycle                [Template 3A]               ║
 ║                                                                         ║
 ║  LEVEL 2 — INTERMEDIATE (Apply patterns):                                ║
 ║    LC 11 : Container With Most Water        [Template 1C]               ║
 ║    LC 15 : 3Sum                             [Template 1E]               ║
 ║    LC 75 : Sort Colors                      [Template 1F]               ║
 ║    LC 80 : Remove Duplicates II             [Template 2A]               ║
 ║    LC 142: Linked List Cycle II             [Template 3B]               ║
 ║    LC 202: Happy Number                     [Template 3D]               ║
 ║    LC 209: Minimum Size Subarray Sum        [Template 4C]               ║
 ║    LC 3  : Longest Substring No Repeat      [Template 4B]               ║
 ║    LC 680: Valid Palindrome II              [Template 1D]               ║
 ║    LC 881: Boats to Save People             [Template 5A]               ║
 ║                                                                         ║
 ║  LEVEL 3 — ADVANCED (Combine patterns):                                  ║
 ║    LC 16 : 3Sum Closest                     [Template 1E variant]       ║
 ║    LC 18 : 4Sum                             [Template 6A]               ║
 ║    LC 42 : Trapping Rain Water              [Template 1C variant]       ║
 ║    LC 76 : Minimum Window Substring         [Template 4C]               ║
 ║    LC 287: Find the Duplicate Number        [Template 3B]               ║
 ║    LC 424: Longest Repeating Char Replace   [Template 4B]               ║
 ║    LC 611: Valid Triangle Number             [Template 5A]               ║
 ║    LC 1004: Max Consecutive Ones III        [Template 4B]               ║
 ║                                                                         ║
 ║  LEVEL 4 — GM LEVEL (Master the tricks):                                 ║
 ║    LC 340: Longest Substr At Most K Distinct [Template 4B]              ║
 ║    LC 719: Kth Smallest Pair Distance        [Template 5B]              ║
 ║    LC 862: Shortest Subarray Sum >= K        [Deque, see Tip 9]         ║
 ║    LC 930: Binary Subarrays With Sum         [Template 4D]              ║
 ║    LC 992: Subarrays K Different Integers    [Template 4D]              ║
 ║    LC 1248: Count Nice Subarrays             [Template 4D]              ║
 ║    LC 2444: Count Subarrays Fixed Bounds     [Advanced Window]          ║
 ║    CF 1462D: Add to Neighbour and Remove     [Two Pointer + Greedy]     ║
 ║    CF 1555C: Coin Rows                       [Prefix + Two Pointer]     ║
 ║    CF 1829D: Gold Rush                       [Two Pointer + Simulation] ║
 ║                                                                         ║
 ╚══════════════════════════════════════════════════════════════════════════╝
*/

// =====================================================================
//  DEMO: Uncomment to test any template
// =====================================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // --- DEMO: Two Sum on Sorted Array ---
    // vec<int> arr = {2, 7, 11, 15};
    // auto [i, j] = template_1B_twoSum_sorted(arr, 9);
    // cout << "Indices: " << i << ", " << j << nl;

    // --- DEMO: 3Sum ---
    // vec<int> nums = {-1, 0, 1, 2, -1, -4};
    // auto triplets = template_1E_threeSum(nums);
    // for (auto& t : triplets) {
    //     cout << t[0] << " " << t[1] << " " << t[2] << nl;
    // }

    // --- DEMO: Longest Substring Without Repeating Characters ---
    // string s = "abcabcbb";
    // cout << template_4B_longest_unique_substr(s) << nl;  // 3

    // --- DEMO: Happy Number ---
    // cout << (template_3D_isHappy(19) ? "Happy" : "Not Happy") << nl;

    // --- DEMO: Find Duplicate ---
    // vec<int> nums = {1, 3, 4, 2, 2};
    // cout << template_3B_findDuplicate(nums) << nl;  // 2

    // --- DEMO: Exactly K Distinct Subarrays ---
    // vec<int> nums = {1, 2, 1, 2, 3};
    // cout << template_4D_exactly_K_distinct(nums, 2) << nl;  // 7

    cout << "All Two Pointer Templates Loaded Successfully!" << nl;
    return 0;
}

