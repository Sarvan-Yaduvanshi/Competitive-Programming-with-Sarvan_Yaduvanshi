/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Container With Most Water
 *  Level   : Medium
 * ============================================================================
 *
 *  LC 11: Container With Most Water
 *  https://leetcode.com/problems/container-with-most-water/
 *
 *  PROBLEM:
 *  Given array of heights, find two lines that form a container holding
 *  the most water. Area = min(h[left], h[right]) * (right - left).
 *
 *  APPROACH: Converging Two Pointer
 *  ────────────────────────────────
 *  Start with widest container (left=0, right=N-1).
 *  Always move the pointer with SMALLER height.
 *
 *  WHY? Moving the taller pointer can only decrease width without
 *  guaranteed height increase. Moving the shorter one might find a
 *  taller line that increases the area.
 *
 *  PROOF (Exchange Argument):
 *  If h[left] < h[right], then for ANY right' < right:
 *  area(left, right') ≤ h[left] * (right'-left) < h[left] * (right-left) = current area
 *  So we can safely skip all (left, right') pairs → move left++.
 *
 *  Time: O(N), Space: O(1)
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxArea(vector<int>& height) {
    int left = 0, right = (int)height.size() - 1;
    int best = 0;

    while (left < right) {
        int w = right - left;
        int h = min(height[left], height[right]);
        best = max(best, w * h);

        // Move the bottleneck (shorter line)
        if (height[left] < height[right])
            left++;
        else
            right--;
    }
    return best;
}

int main() {
    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "Max Area: " << maxArea(height) << "\n";  // 49

    vector<int> h2 = {1, 1};
    cout << "Max Area: " << maxArea(h2) << "\n";  // 1

    return 0;
}

