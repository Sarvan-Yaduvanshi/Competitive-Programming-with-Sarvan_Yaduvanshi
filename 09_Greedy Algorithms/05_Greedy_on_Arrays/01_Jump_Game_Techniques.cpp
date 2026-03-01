/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Jump Game Techniques — Farthest Reach Greedy
 *  Level   : Intermediate
 * ============================================================================
 *
 *  ▶ JUMP GAME I (LC 55): Can you reach the last index?
 *     Greedy: Track farthest reachable index. If current > farthest, stuck.
 *
 *  ▶ JUMP GAME II (LC 45): Minimum jumps to reach last index.
 *     Greedy (BFS-like): Track current range end. When you exhaust the range, jump.
 *
 *  ▶ JUMP GAME III (LC 1306): Can you reach index with value 0?
 *     BFS/DFS from starting index.
 *
 *  ▶ KEY INSIGHT:
 *     "Farthest reach" is the core greedy idea for jump problems.
 *     At each position, update the farthest you can ever reach.
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ============================================================================
// JUMP GAME I (LC 55) — Can reach last index? O(N)
// ============================================================================
bool canJump(vector<int>& nums) {
    int farthest = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (i > farthest) return false;  // Can't reach this position
        farthest = max(farthest, i + nums[i]);
        if (farthest >= (int)nums.size() - 1) return true;
    }
    return true;
}

// ============================================================================
// JUMP GAME II (LC 45) — Minimum jumps. O(N)
// ============================================================================
/*
 * Greedy BFS approach:
 * Think of it as BFS where "level" = number of jumps.
 * At each level, find the farthest position reachable.
 * When current position exceeds current level's end, we must jump.
 */
int minJumps(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return 0;

    int jumps = 0, currentEnd = 0, farthest = 0;

    for (int i = 0; i < n - 1; i++) {
        farthest = max(farthest, i + nums[i]);
        if (i == currentEnd) {
            jumps++;
            currentEnd = farthest;
            if (currentEnd >= n - 1) break;
        }
    }
    return jumps;
}

// ============================================================================
// JUMP GAME III (LC 1306) — BFS to reach index with value 0
// ============================================================================
bool canReachZero(vector<int>& arr, int start) {
    int n = arr.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int idx = q.front(); q.pop();
        if (arr[idx] == 0) return true;

        for (int next : {idx + arr[idx], idx - arr[idx]}) {
            if (next >= 0 && next < n && !visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
    return false;
}

int main() {
    // Jump Game I
    vector<int> nums1 = {2, 3, 1, 1, 4};
    cout << "Can jump: " << (canJump(nums1) ? "YES" : "NO") << endl; // YES

    vector<int> nums2 = {3, 2, 1, 0, 4};
    cout << "Can jump: " << (canJump(nums2) ? "YES" : "NO") << endl; // NO

    // Jump Game II
    vector<int> nums3 = {2, 3, 1, 1, 4};
    cout << "Min jumps: " << minJumps(nums3) << endl; // 2

    // Jump Game III
    vector<int> arr = {4, 2, 3, 0, 3, 1, 2};
    cout << "Can reach 0: " << (canReachZero(arr, 5) ? "YES" : "NO") << endl; // YES

    return 0;
}

