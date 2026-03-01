/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — TRAPPING RAIN WATER (STACK APPROACH) — LC 42                  ║
║           From Zero to Grandmaster — Monotonic Stack Patterns               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Given elevation map, compute trapped water after rain.
  Heights: [0,1,0,2,1,0,1,3,2,1,2,1]  Answer: 6

STACK APPROACH:
  Use stack to find "valleys" (trapped water between walls).
  Stack maintains decreasing heights.
  When we find a height > stack.top(), we have a valley.

DRY RUN: [0,1,0,2,1,0,1,3,2,1,2,1]

  Key pops that trap water:
  i=3 (h=2): pop idx=2(h=0), bounded by idx=1(h=1)
    water_height = min(2,1)-0 = 1, width = 3-1-1 = 1, area = 1
  i=3 (h=2): pop idx=1(h=1), bounded by nothing → stack empty, skip
  ...continuing through gives total = 6

  ┌──────────────────────────────────────┐
  │        █                             │
  │    █≈≈≈██≈█                          │
  │    █≈█≈██≈██≈█                       │
  │  ──────────────                      │
  │  0 1 0 2 1 0 1 3 2 1 2 1            │
  │    ≈ = trapped water (total 6)       │
  └──────────────────────────────────────┘

TIME: O(n)  SPACE: O(n)
*/

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Stack approach
int trapStack(vector<int>& height) {
    stack<int> st;
    int water = 0;

    for (int i = 0; i < (int)height.size(); i++) {
        while (!st.empty() && height[i] > height[st.top()]) {
            int bottom = st.top(); st.pop();
            if (st.empty()) break;

            int width = i - st.top() - 1;
            int h = min(height[i], height[st.top()]) - height[bottom];
            water += width * h;
        }
        st.push(i);
    }
    return water;
}

// Two-pointer approach (O(1) space, for comparison)
int trapTwoPointer(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int leftMax = 0, rightMax = 0, water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            leftMax = max(leftMax, height[left]);
            water += leftMax - height[left];
            left++;
        } else {
            rightMax = max(rightMax, height[right]);
            water += rightMax - height[right];
            right--;
        }
    }
    return water;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  TRAPPING RAIN WATER (LC 42) — STACK APPROACH            ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    vector<int> h1 = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << "Heights: [0,1,0,2,1,0,1,3,2,1,2,1]\n";
    cout << "Stack approach:       " << trapStack(h1) << "\n";
    cout << "Two-pointer approach: " << trapTwoPointer(h1) << "\n\n";

    vector<int> h2 = {4,2,0,3,2,5};
    cout << "Heights: [4,2,0,3,2,5]\n";
    cout << "Stack approach:       " << trapStack(h2) << "\n";
    cout << "Two-pointer approach: " << trapTwoPointer(h2) << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LC 42 — Trapping Rain Water\n";
    cout << "         LC 407 — Trapping Rain Water II (3D)\n";
    cout << "═══════════════════════════════════════════════════════════\n";
    return 0;
}

