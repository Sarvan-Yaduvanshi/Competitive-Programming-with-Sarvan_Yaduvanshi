/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Trapping Rain Water — ALL Versions (1D + 2D)
 *  Level   : Medium → Hard
 * ============================================================================
 *
 *  LC 42  — Trapping Rain Water (1D)
 *           https://leetcode.com/problems/trapping-rain-water/
 *  LC 407 — Trapping Rain Water II (2D / 3D)
 *           https://leetcode.com/problems/trapping-rain-water-ii/
 *  GFG    — https://practice.geeksforgeeks.org/problems/trapping-rain-water/
 *
 *  THREE APPROACHES FOR 1D:
 *  ────────────────────────
 *  Approach 1: Prefix Max Arrays → O(N) time, O(N) space
 *  Approach 2: Two Pointer       → O(N) time, O(1) space ⭐ BEST
 *  Approach 3: Stack-based       → O(N) time, O(N) space
 *
 *  CORE INSIGHT:
 *  Water at position i = min(leftMax[i], rightMax[i]) - height[i]
 *  Water is trapped by the SHORTER of the two tallest walls on each side.
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

// ============================================================================
// APPROACH 1: Prefix Max Arrays — O(N) time, O(N) space
// ============================================================================
/*
 * Precompute leftMax[i] = max height from 0..i
 * Precompute rightMax[i] = max height from i..N-1
 * Water at i = min(leftMax[i], rightMax[i]) - height[i]
 */
int trap_prefix(vector<int>& height) {
    int n = height.size();
    if (n == 0) return 0;

    vector<int> leftMax(n), rightMax(n);

    leftMax[0] = height[0];
    for (int i = 1; i < n; i++)
        leftMax[i] = max(leftMax[i-1], height[i]);

    rightMax[n-1] = height[n-1];
    for (int i = n-2; i >= 0; i--)
        rightMax[i] = max(rightMax[i+1], height[i]);

    int water = 0;
    for (int i = 0; i < n; i++)
        water += min(leftMax[i], rightMax[i]) - height[i];

    return water;
}

// ============================================================================
// APPROACH 2: Two Pointer — O(N) time, O(1) space ⭐ BEST
// ============================================================================
/*
 * KEY INSIGHT: We don't need the full prefix arrays!
 *
 * Maintain leftMax and rightMax as we go.
 * Process from the side with the SMALLER max:
 * - If leftMax < rightMax: water at left is determined by leftMax
 * - If rightMax ≤ leftMax: water at right is determined by rightMax
 *
 * WHY? The water level at any position is limited by the SHORTER wall.
 * If leftMax < rightMax, we know the left wall is the bottleneck,
 * so we can safely compute water at the left position.
 */
int trap_twoPointer(vector<int>& height) {
    int n = height.size();
    if (n == 0) return 0;

    int left = 0, right = n - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            // Left wall is the bottleneck
            if (height[left] >= leftMax)
                leftMax = height[left];  // Update max, no water
            else
                water += leftMax - height[left];  // Trap water
            left++;
        } else {
            // Right wall is the bottleneck
            if (height[right] >= rightMax)
                rightMax = height[right];
            else
                water += rightMax - height[right];
            right--;
        }
    }
    return water;
}

// ============================================================================
// APPROACH 3: Stack-Based — O(N) time, O(N) space
// ============================================================================
/*
 * Use a monotone decreasing stack (of indices).
 * When we find a height taller than stack top, water is trapped between
 * the current height and the new stack top (after popping).
 */
int trap_stack(vector<int>& height) {
    int n = height.size();
    stack<int> st;
    int water = 0;

    for (int i = 0; i < n; i++) {
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

// ============================================================================
// LC 407: Trapping Rain Water II (2D / 3D) — BFS + Min Heap
// ============================================================================
/*
 * Generalization to 2D grid. Use BFS from boundary with a min-heap.
 * Process cells from lowest boundary inward.
 *
 * IDEA: Water level at any cell is determined by the shortest path from
 * that cell to the boundary. Start from boundary (min-heap), expand inward.
 *
 * Time: O(M*N*log(M*N)), Space: O(M*N)
 */
int trapRainWater2D(vector<vector<int>>& heightMap) {
    int m = heightMap.size(), n = heightMap[0].size();
    if (m < 3 || n < 3) return 0;

    // Min-heap: (height, row, col)
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    // Add all boundary cells to heap
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || i == m-1 || j == 0 || j == n-1) {
                pq.push({heightMap[i][j], i, j});
                visited[i][j] = true;
            }
        }
    }

    int water = 0;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!pq.empty()) {
        auto [h, x, y] = pq.top(); pq.pop();

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || visited[nx][ny])
                continue;
            visited[nx][ny] = true;

            // Water trapped = max(0, boundary_height - cell_height)
            water += max(0, h - heightMap[nx][ny]);

            // Push with max(current_boundary, cell_height) — water level
            pq.push({max(h, heightMap[nx][ny]), nx, ny});
        }
    }
    return water;
}

int main() {
    // 1D Trapping Rain Water
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

    cout << "Trapping Rain Water 1D:\n";
    cout << "  Prefix Max: " << trap_prefix(height) << "\n";      // 6
    cout << "  Two Pointer: " << trap_twoPointer(height) << "\n";  // 6
    cout << "  Stack:       " << trap_stack(height) << "\n";        // 6

    // 2D Trapping Rain Water
    vector<vector<int>> grid = {
        {1, 4, 3, 1, 3, 2},
        {3, 2, 1, 3, 2, 4},
        {2, 3, 3, 2, 3, 1}
    };
    cout << "\nTrapping Rain Water 2D: " << trapRainWater2D(grid) << "\n"; // 4

    return 0;
}

