/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 07.06 — WINDOW OR ≥ K                                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Find shortest subarray with OR ≥ K.

KEY INSIGHT: OR is monotonically non-decreasing as we extend window.
    Expand right → OR increases. Shrink left → OR can decrease.

MAINTAINING WINDOW OR: Use bit frequency array.
    OR bit b = 1 ⟺ freq[b] > 0 (at least one element has that bit).

TIME: O(n × 32)
*/
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int shortestSubarrayOrGeqK(vector<int>& arr, int K) {
    int n = arr.size();
    int freq[32] = {};
    int best = INT_MAX;
    int left = 0;

    auto getOR = [&]() -> int {
        int val = 0;
        for (int b = 0; b < 32; b++)
            if (freq[b] > 0) val |= (1 << b);
        return val;
    };

    for (int right = 0; right < n; right++) {
        for (int b = 0; b < 32; b++)
            if (arr[right] & (1 << b)) freq[b]++;

        while (left <= right && getOR() >= K) {
            best = min(best, right - left + 1);
            for (int b = 0; b < 32; b++)
                if (arr[left] & (1 << b)) freq[b]--;
            left++;
        }
    }
    return best == INT_MAX ? -1 : best;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   WINDOW OR ≥ K                                 ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> arr = {1, 2, 4, 8};
    int K = 7;
    cout << "  [1,2,4,8], K=" << K << ": shortest = " << shortestSubarrayOrGeqK(arr, K) << endl;

    vector<int> arr2 = {1, 1, 1, 1, 7};
    K = 7;
    cout << "  [1,1,1,1,7], K=" << K << ": shortest = " << shortestSubarrayOrGeqK(arr2, K) << endl;

    cout << "\n✅ Window OR ≥ K demonstrated!" << endl;
    return 0;
}

