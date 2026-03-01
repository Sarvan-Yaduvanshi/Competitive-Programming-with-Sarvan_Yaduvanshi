/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — NEXT GREATER ELEMENT II — CIRCULAR ARRAY (LC 503)             ║
║           From Zero to Grandmaster — Monotonic Stack Patterns               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM:
────────
  Given a CIRCULAR array, find Next Greater Element for each position.
  Circular means: after the last element, we wrap to the first.

  Input:  [1, 2, 1]
  Output: [2, -1, 2]  (for index 2, wrap around to find 2 at index 1)

TRICK: Iterate 2*n times using index i % n
───────────────────────────────────────────
  This simulates the circular nature without actually duplicating the array.

  DRY RUN: [1, 2, 3, 1]  (n=4, iterate 0..7)

  Process RIGHT to LEFT (i = 2n-1 to 0):

  i=7 (7%4=3, arr=1): stack=[] → push 1                    stack=[1]
  i=6 (6%4=2, arr=3): pop 1(≤3), stack=[] → push 3         stack=[3]
  i=5 (5%4=1, arr=2): 3>2 → push 2                         stack=[3,2]
  i=4 (4%4=0, arr=1): 2>1 → push 1                         stack=[3,2,1]
  --- Now we start recording results ---
  i=3 (3%4=3, arr=1): pop 1(≤1), 2>1 → result[3]=2        stack=[3,2,1]
  i=2 (2%4=2, arr=3): pop 1,2(≤3) → result[2]=-1          stack=[3,3]
  i=1 (1%4=1, arr=2): 3>2 → result[1]=3                    stack=[3,3,2]
  i=0 (0%4=0, arr=1): 2>1 → result[0]=2                    stack=[3,3,2,1]

  Result: [2, 3, -1, 2] ✅

TIME: O(n)  SPACE: O(n)
*/

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st;  // Stores values

    // Iterate 2n times (right to left)
    for (int i = 2 * n - 1; i >= 0; i--) {
        int idx = i % n;

        while (!st.empty() && st.top() <= nums[idx]) {
            st.pop();
        }

        if (i < n) {  // Only record for first pass
            result[idx] = st.empty() ? -1 : st.top();
        }

        st.push(nums[idx]);
    }
    return result;
}

// Alternative: Left-to-right with index stack
vector<int> nextGreaterElementsV2(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st;  // Stores indices

    for (int i = 0; i < 2 * n; i++) {
        int idx = i % n;
        while (!st.empty() && nums[st.top()] < nums[idx]) {
            result[st.top()] = nums[idx];
            st.pop();
        }
        if (i < n) st.push(idx);  // Only push in first pass
    }
    return result;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  NGE II — CIRCULAR ARRAY (LC 503)                        ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    vector<int> v1 = {1, 2, 1};
    auto r1 = nextGreaterElements(v1);
    cout << "Array: [1,2,1] → NGE: [";
    for (int i = 0; i < (int)r1.size(); i++) cout << r1[i] << (i+1<(int)r1.size()?",":"");
    cout << "]\n";

    vector<int> v2 = {1, 2, 3, 4, 3};
    auto r2 = nextGreaterElements(v2);
    cout << "Array: [1,2,3,4,3] → NGE: [";
    for (int i = 0; i < (int)r2.size(); i++) cout << r2[i] << (i+1<(int)r2.size()?",":"");
    cout << "]\n";

    vector<int> v3 = {5, 4, 3, 2, 1};
    auto r3 = nextGreaterElements(v3);
    cout << "Array: [5,4,3,2,1] → NGE: [";
    for (int i = 0; i < (int)r3.size(); i++) cout << r3[i] << (i+1<(int)r3.size()?",":"");
    cout << "]\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "KEY INSIGHT: Iterate 2*n times, use i%n for circular access.\n";
    cout << "PRACTICE: LC 503 — Next Greater Element II\n";
    cout << "═══════════════════════════════════════════════════════════\n";
    return 0;
}

