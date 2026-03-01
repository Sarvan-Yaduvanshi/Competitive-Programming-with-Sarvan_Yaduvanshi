/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — NEXT GREATER ELEMENT (NGE)                                    ║
║           From Zero to Grandmaster — Classical Stack Problems               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Problem Definition
 2. Brute Force O(n²)
 3. Monotonic Stack Solution O(n)
 4. Detailed Dry Run
 5. Right-to-Left vs Left-to-Right
 6. Variants & Applications

PROBLEM:
────────
  For each element in an array, find the NEXT element that is GREATER.
  If no greater element exists to the right, answer is -1.

  Input:  [4, 5, 2, 25, 7, 8]
  Output: [5, 25, 25, -1, 8, -1]

  Explanation:
    4  → next greater is 5
    5  → next greater is 25
    2  → next greater is 25
    25 → no greater element → -1
    7  → next greater is 8
    8  → no greater element → -1

BRUTE FORCE:
───────────
  For each i, scan right to find first element > arr[i]
  Time: O(n²)  Space: O(1)

MONOTONIC STACK APPROACH:
────────────────────────
  Key Insight: Use a stack that maintains DECREASING order from bottom to top.

  Process RIGHT to LEFT:
  For each element:
    1. Pop all elements from stack that are ≤ current element
    2. If stack not empty → top is the NGE
    3. If stack empty → no NGE, answer is -1
    4. Push current element onto stack

  Why does this work?
  The stack always contains potential "next greater" candidates in decreasing order.
  Elements that are smaller than current can never be NGE for anything to the left.

  Time: O(n) — each element pushed/popped at most once
  Space: O(n) for the stack

DETAILED DRY RUN:
────────────────
  Array: [4, 5, 2, 25, 7, 8]
  Process RIGHT to LEFT (i = 5 to 0):

  i=5, arr[5]=8:
    Stack: []
    No element in stack → NGE[5] = -1
    Push 8 → Stack: [8]

  i=4, arr[4]=7:
    Stack: [8]
    8 > 7 → NGE[4] = 8
    Push 7 → Stack: [8, 7]

  i=3, arr[3]=25:
    Stack: [8, 7]
    Pop 7 (7 ≤ 25)
    Pop 8 (8 ≤ 25)
    Stack empty → NGE[3] = -1
    Push 25 → Stack: [25]

  i=2, arr[2]=2:
    Stack: [25]
    25 > 2 → NGE[2] = 25
    Push 2 → Stack: [25, 2]

  i=1, arr[1]=5:
    Stack: [25, 2]
    Pop 2 (2 ≤ 5)
    25 > 5 → NGE[1] = 25
    Push 5 → Stack: [25, 5]

  i=0, arr[0]=4:
    Stack: [25, 5]
    5 > 4 → NGE[0] = 5
    Push 4 → Stack: [25, 5, 4]

  Result: [5, 25, 25, -1, 8, -1] ✅

  Stack state visualization:
  ┌─────────────────────────────────────────────────────────┐
  │ i=5: []        →  [8]           NGE[5]=-1              │
  │ i=4: [8]       →  [8,7]         NGE[4]=8               │
  │ i=3: [8,7]     →  [25]          NGE[3]=-1              │
  │ i=2: [25]      →  [25,2]        NGE[2]=25              │
  │ i=1: [25,2]    →  [25,5]        NGE[1]=25              │
  │ i=0: [25,5]    →  [25,5,4]      NGE[0]=5               │
  └─────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BRUTE FORCE O(n²)
// ═══════════════════════════════════════════════════════════════

vector<int> nge_brute(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[i]) {
                result[i] = arr[j];
                break;
            }
        }
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: MONOTONIC STACK — RIGHT TO LEFT
// ═══════════════════════════════════════════════════════════════

vector<int> nge_stack_rtl(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n);
    stack<int> st;  // Stores values (decreasing from bottom)

    for (int i = n - 1; i >= 0; i--) {
        // Pop all elements ≤ current
        while (!st.empty() && st.top() <= arr[i]) {
            st.pop();
        }

        // If stack not empty, top is NGE
        result[i] = st.empty() ? -1 : st.top();

        // Push current element
        st.push(arr[i]);
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: MONOTONIC STACK — LEFT TO RIGHT
// ═══════════════════════════════════════════════════════════════
/*
  Alternative: Process left to right, push INDICES.
  When arr[i] > stack.top(), we found NGE for stack.top().

  DRY RUN: [4, 5, 2, 25, 7, 8]
  Stack stores indices.

  i=0: push 0          stack=[0]
  i=1: arr[1]=5 > arr[0]=4 → NGE[0]=5, pop → push 1    stack=[1]
  i=2: arr[2]=2 < 5 → push 2                            stack=[1,2]
  i=3: arr[3]=25 > arr[2]=2 → NGE[2]=25, pop
       arr[3]=25 > arr[1]=5 → NGE[1]=25, pop → push 3   stack=[3]
  i=4: arr[4]=7 < 25 → push 4                           stack=[3,4]
  i=5: arr[5]=8 > arr[4]=7 → NGE[4]=8, pop → push 5    stack=[3,5]

  Remaining: NGE[3]=-1, NGE[5]=-1
*/

vector<int> nge_stack_ltr(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> st;  // Stores indices

    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] < arr[i]) {
            result[st.top()] = arr[i];
            st.pop();
        }
        st.push(i);
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: NGE WITH MAP (LC 496 — Next Greater Element I)
// ═══════════════════════════════════════════════════════════════
/*
  LC 496: Two arrays nums1 (subset of nums2).
  For each element in nums1, find its NGE in nums2.

  Strategy: Build NGE map for all of nums2, then look up nums1.
*/

vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    // Build NGE map from nums2
    stack<int> st;
    unordered_map<int, int> ngeMap;

    for (int i = nums2.size() - 1; i >= 0; i--) {
        while (!st.empty() && st.top() <= nums2[i]) st.pop();
        ngeMap[nums2[i]] = st.empty() ? -1 : st.top();
        st.push(nums2[i]);
    }

    // Look up results for nums1
    vector<int> result;
    for (int x : nums1) {
        result.push_back(ngeMap[x]);
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// DEMONSTRATION
// ═══════════════════════════════════════════════════════════════

void printVec(vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  NEXT GREATER ELEMENT (NGE) — MONOTONIC STACK           ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    vector<int> arr = {4, 5, 2, 25, 7, 8};

    cout << "Array: ";
    printVec(arr);

    auto r1 = nge_brute(arr);
    cout << "Brute force NGE: ";
    printVec(r1);

    auto r2 = nge_stack_rtl(arr);
    cout << "Stack (R→L) NGE: ";
    printVec(r2);

    auto r3 = nge_stack_ltr(arr);
    cout << "Stack (L→R) NGE: ";
    printVec(r3);

    // LC 496
    cout << "\n═══ LC 496: NEXT GREATER ELEMENT I ═══\n";
    vector<int> nums1 = {4, 1, 2};
    vector<int> nums2 = {1, 3, 4, 2};
    auto r4 = nextGreaterElement(nums1, nums2);
    cout << "nums1: "; printVec(nums1);
    cout << "nums2: "; printVec(nums2);
    cout << "NGE:   "; printVec(r4);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE PROBLEMS:\n";
    cout << "───────────────────\n";
    cout << "1. LC 496  — Next Greater Element I\n";
    cout << "2. LC 503  — Next Greater Element II (Circular)\n";
    cout << "3. LC 739  — Daily Temperatures\n";
    cout << "4. LC 901  — Online Stock Span\n";
    cout << "5. CSES 1645 — Nearest Smaller Values\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

