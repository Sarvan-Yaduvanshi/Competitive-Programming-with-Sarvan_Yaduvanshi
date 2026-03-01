/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 06.09 — SUM OF OR OF ALL SUBARRAYS                       ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Compute Σ (over all subarrays) OR(subarray).

TECHNIQUE: Contribution per bit.
    For bit b, count subarrays where AT LEAST ONE element has bit b set.
    Total subarrays = n(n+1)/2. Subtract subarrays where NO element has bit b.

    For bit b: find lengths of consecutive runs of elements WITHOUT bit b.
    If a run has length L, it contributes L(L+1)/2 "bad" subarrays.
    Good subarrays for bit b = n(n+1)/2 - Σ L_i(L_i+1)/2
    Contribution = 2^b × good_count.

DRY RUN — arr=[1,2,3]:
    n=3, total subarrays = 6
    Bit 0 (set in 1,3): runs without bit 0: [2] (length 1) → bad=1 → good=5 → 1×5=5
    Bit 1 (set in 2,3): runs without bit 1: [1] (length 1) → bad=1 → good=5 → 2×5=10
    Total = 5+10 = 15
    Verify: OR([1])=1, OR([2])=2, OR([3])=3, OR([1,2])=3, OR([2,3])=3, OR([1,2,3])=3
    = 1+2+3+3+3+3 = 15 ✓

TIME: O(n × 32)
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

long long sumOrAllSubarrays(vector<int>& arr) {
    int n = arr.size();
    long long totalSub = (long long)n * (n + 1) / 2;
    long long total = 0;

    for (int b = 0; b < 30; b++) {
        // Count subarrays where no element has bit b
        long long bad = 0;
        int run = 0;
        for (int i = 0; i < n; i++) {
            if (!((arr[i] >> b) & 1)) {
                run++;
            } else {
                bad += (long long)run * (run + 1) / 2;
                run = 0;
            }
        }
        bad += (long long)run * (run + 1) / 2;
        total += (1LL << b) * (totalSub - bad);
    }
    return total;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   SUM OF OR OF ALL SUBARRAYS                    ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> arr = {1, 2, 3};
    cout << "  [1,2,3]: " << sumOrAllSubarrays(arr) << endl;

    // Brute force
    long long brute = 0;
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        int orVal = 0;
        for (int j = i; j < n; j++) { orVal |= arr[j]; brute += orVal; }
    }
    cout << "  Brute force: " << brute << endl;
    assert(sumOrAllSubarrays(arr) == brute);

    cout << "\n✅ Sum of OR of all subarrays verified!" << endl;
    return 0;
}

