/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 07.05 — WINDOW AND ≥ K                                   ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Find shortest/longest subarray with AND ≥ K.

KEY INSIGHT: AND is monotonically non-increasing as we extend window.
    So we can use TWO POINTERS / sliding window.
    Expand right to get more elements → AND decreases.
    Shrink left to remove elements → AND can increase.

MAINTAINING WINDOW AND: Use bit frequency array (see 06.06).
    freq[b] = count of elements with bit b set in the window.
    AND bit b = 1 ⟺ freq[b] == window_size.

TIME: O(n × 32)
*/
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int shortestSubarrayAndGeqK(vector<int>& arr, int K) {
    int n = arr.size();
    int freq[32] = {};
    int best = INT_MAX;
    int left = 0;

    auto getAND = [&](int windowSize) -> int {
        int val = 0;
        for (int b = 0; b < 32; b++)
            if (freq[b] == windowSize) val |= (1 << b);
        return val;
    };

    for (int right = 0; right < n; right++) {
        // Add arr[right]
        for (int b = 0; b < 32; b++)
            if (arr[right] & (1 << b)) freq[b]++;

        // Shrink from left while AND ≥ K
        while (left <= right && getAND(right - left + 1) >= K) {
            best = min(best, right - left + 1);
            // Remove arr[left]
            for (int b = 0; b < 32; b++)
                if (arr[left] & (1 << b)) freq[b]--;
            left++;
        }
    }
    return best == INT_MAX ? -1 : best;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   WINDOW AND ≥ K                                ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> arr = {7, 6, 5, 4, 3};
    int K = 4;
    cout << "  [7,6,5,4,3], K=" << K << ": shortest = " << shortestSubarrayAndGeqK(arr, K) << endl;

    vector<int> arr2 = {15, 14, 13, 12};
    K = 12;
    cout << "  [15,14,13,12], K=" << K << ": shortest = " << shortestSubarrayAndGeqK(arr2, K) << endl;

    cout << "\n✅ Window AND ≥ K demonstrated!" << endl;
    return 0;
}

