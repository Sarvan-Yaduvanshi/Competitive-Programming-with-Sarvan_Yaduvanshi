/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — LARGEST RECTANGLE IN HISTOGRAM (LC 84)                        ║
║           From Zero to Grandmaster — Monotonic Stack Patterns               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM:
────────
  Given array of bar heights, find the area of the largest rectangle
  that can be formed in the histogram.

  Heights: [2, 1, 5, 6, 2, 3]
  Answer: 10 (height=5, width=2, bars at index 2,3)

INTUITION:
─────────
  For each bar, find how far LEFT and RIGHT it can extend as the minimum.
  Width = right_boundary - left_boundary - 1
  Area = height × width

  left_boundary  = Previous Smaller Element (PSE) index
  right_boundary = Next Smaller Element (NSE) index

  If no PSE → left_boundary = -1
  If no NSE → right_boundary = n

APPROACH 1: PSE + NSE
─────────────────────
  1. Compute PSE indices for all bars
  2. Compute NSE indices for all bars
  3. For each bar: area = height[i] × (NSE[i] - PSE[i] - 1)

APPROACH 2: Single Stack (Optimized)
─────────────────────────────────────
  Use increasing monotonic stack of indices.
  When we pop bar at index j (because heights[j] > heights[i]):
    - The NSE for j is i
    - The PSE for j is the new stack.top() (or -1)
    - Width = i - stack.top() - 1
    - Area = heights[j] × width

DRY RUN (Approach 2): [2, 1, 5, 6, 2, 3]

  ┌──────┬────────┬──────────────────────────────────────────┬──────────┐
  │  i   │ h[i]   │ Action                                   │ maxArea  │
  ├──────┼────────┼──────────────────────────────────────────┼──────────┤
  │  0   │  2     │ push 0                                   │ 0        │
  │  1   │  1     │ pop 0: h=2, w=1-(-1)-1=1, a=2           │ 2        │
  │      │        │ push 1                                   │          │
  │  2   │  5     │ push 2                                   │ 2        │
  │  3   │  6     │ push 3                                   │ 2        │
  │  4   │  2     │ pop 3: h=6, w=4-2-1=1, a=6              │ 6        │
  │      │        │ pop 2: h=5, w=4-1-1=2, a=10             │ 10       │
  │      │        │ push 4                                   │          │
  │  5   │  3     │ push 5                                   │ 10       │
  │ END  │        │ pop 5: h=3, w=6-4-1=1, a=3              │ 10       │
  │      │        │ pop 4: h=2, w=6-1-1=4, a=8              │ 10       │
  │      │        │ pop 1: h=1, w=6-(-1)-1=6, a=6           │ 10       │
  └──────┴────────┴──────────────────────────────────────────┴──────────┘

  Answer: 10 ✅

  Visualization:
       ┌──┐
    ┌──┤  │
    │  │  │      ┌──┐
  ┌─┤  │  │  ┌──┤  │
  │ │  │  │  │  │  │
  │ │  │  │  │  │  │
  ──────────────────
  2  1  5  6  2  3
        ├────┤
        max area = 5 × 2 = 10

TIME: O(n)  SPACE: O(n)
*/

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// APPROACH 1: PSE + NSE (Easier to understand)
// ═══════════════════════════════════════════════════════════════

int largestRectanglePSENSE(vector<int>& heights) {
    int n = heights.size();
    vector<int> pse(n), nse(n);
    stack<int> st;

    // PSE (Previous Smaller Element Index)
    for (int i = 0; i < n; i++) {
        while (!st.empty() && heights[st.top()] >= heights[i]) st.pop();
        pse[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    // NSE (Next Smaller Element Index)
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && heights[st.top()] >= heights[i]) st.pop();
        nse[i] = st.empty() ? n : st.top();
        st.push(i);
    }

    // Calculate max area
    int maxArea = 0;
    for (int i = 0; i < n; i++) {
        int width = nse[i] - pse[i] - 1;
        maxArea = max(maxArea, heights[i] * width);
    }
    return maxArea;
}

// ═══════════════════════════════════════════════════════════════
// APPROACH 2: SINGLE STACK (Optimized, Competitive)
// ═══════════════════════════════════════════════════════════════

int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    stack<int> st;
    int maxArea = 0;

    for (int i = 0; i <= n; i++) {
        int currHeight = (i == n) ? 0 : heights[i];  // Sentinel at end

        while (!st.empty() && heights[st.top()] > currHeight) {
            int height = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : (i - st.top() - 1);
            maxArea = max(maxArea, height * width);
        }
        st.push(i);
    }
    return maxArea;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  LARGEST RECTANGLE IN HISTOGRAM (LC 84)                  ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    vector<int> h1 = {2, 1, 5, 6, 2, 3};
    cout << "Heights: [2,1,5,6,2,3]\n";
    cout << "PSE+NSE approach: " << largestRectanglePSENSE(h1) << "\n";
    cout << "Single stack:     " << largestRectangleArea(h1) << "\n\n";

    vector<int> h2 = {2, 4};
    cout << "Heights: [2,4] → " << largestRectangleArea(h2) << "\n";

    vector<int> h3 = {6, 2, 5, 4, 5, 1, 6};
    cout << "Heights: [6,2,5,4,5,1,6] → " << largestRectangleArea(h3) << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LC 84 — Largest Rectangle in Histogram\n";
    cout << "         LC 85 — Maximal Rectangle (2D version)\n";
    cout << "═══════════════════════════════════════════════════════════\n";
    return 0;
}

