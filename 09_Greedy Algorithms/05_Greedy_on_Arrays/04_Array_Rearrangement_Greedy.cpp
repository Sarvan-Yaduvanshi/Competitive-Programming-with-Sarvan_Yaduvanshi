/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Array Rearrangement Greedy
 *  Level   : Intermediate
 * ============================================================================
 *
 *  PATTERNS:
 *  1. WIGGLE SORT: Rearrange so a[0]<a[1]>a[2]<a[3]>...
 *  2. HAND OF STRAIGHTS: Group into consecutive groups of size k
 *  3. MERGE TRIPLETS: Check if target triplet is achievable
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

// ============================================================================
// Wiggle Sort II (LC 324) — O(N log N) with sort
// ============================================================================
void wiggleSort(vector<int>& nums) {
    vector<int> sorted_nums = nums;
    sort(sorted_nums.begin(), sorted_nums.end());
    int n = nums.size();
    int mid = (n - 1) / 2, right = n - 1;
    // Place smaller half at even indices (reversed), larger half at odd (reversed)
    for (int i = 0; i < n; i++) {
        nums[i] = (i % 2 == 0) ? sorted_nums[mid--] : sorted_nums[right--];
    }
}

// ============================================================================
// Hand of Straights (LC 846) — Group into consecutive groups of size k
// ============================================================================
bool isNStraightHand(vector<int>& hand, int groupSize) {
    if (hand.size() % groupSize != 0) return false;

    map<int, int> freq;
    for (int h : hand) freq[h]++;

    for (auto& [card, cnt] : freq) {
        if (cnt > 0) {
            for (int i = groupSize - 1; i >= 0; i--) {
                freq[card + i] -= cnt;
                if (freq[card + i] < 0) return false;
            }
        }
    }
    return true;
}

// ============================================================================
// Merge Triplets (LC 1899) — Can we form target triplet?
// ============================================================================
bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
    // Greedy: Only use triplets where all values ≤ corresponding target values
    vector<int> best(3, 0);
    for (auto& t : triplets) {
        if (t[0] <= target[0] && t[1] <= target[1] && t[2] <= target[2]) {
            best[0] = max(best[0], t[0]);
            best[1] = max(best[1], t[1]);
            best[2] = max(best[2], t[2]);
        }
    }
    return best == target;
}

int main() {
    // Wiggle Sort
    vector<int> nums = {1, 5, 1, 1, 6, 4};
    wiggleSort(nums);
    cout << "Wiggle: ";
    for (int n : nums) cout << n << " ";
    cout << endl;

    // Hand of Straights
    vector<int> hand = {1, 2, 3, 6, 2, 3, 4, 7, 8};
    cout << "Hand: " << (isNStraightHand(hand, 3) ? "YES" : "NO") << endl; // YES

    return 0;
}

