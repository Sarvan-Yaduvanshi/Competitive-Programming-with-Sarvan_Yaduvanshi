/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 06.08 — SUM OF XOR OF ALL SUBARRAYS                      ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Compute Σ (over all subarrays) XOR(subarray).

TECHNIQUE: Contribution per bit.
    For bit b, count how many subarrays have an ODD number of elements with bit b set.
    If bit b contributes to a subarray's XOR, that adds 2^b to the total.

METHOD: Use prefix XOR. Subarray [L..R] has bit b set in XOR ⟺ prefix[L] and prefix[R+1]
differ at bit b. Count prefix values with bit b = 0 (call it c₀) and bit b = 1 (c₁).
Contribution of bit b = 2^b × c₀ × c₁.

DRY RUN — arr=[1,2]:
    prefix = [0, 1, 3]
    Bit 0: prefix values {0,1,3} → bit 0: {0,1,1} → c₀=1, c₁=2 → contrib = 1×1×2 = 2
    Bit 1: prefix values → bit 1: {0,0,1} → c₀=2, c₁=1 → contrib = 2×2×1 = 4
    Total = 2+4 = 6
    Verify: XOR([1])=1, XOR([2])=2, XOR([1,2])=3 → 1+2+3=6 ✓

TIME: O(n × 32)
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

long long sumXorAllSubarrays(vector<int>& arr) {
    int n = arr.size();
    // Build prefix XOR
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] ^ arr[i];

    long long total = 0;
    for (int b = 0; b < 30; b++) {
        int c0 = 0, c1 = 0;
        for (int i = 0; i <= n; i++) {
            if ((prefix[i] >> b) & 1) c1++;
            else c0++;
        }
        total += (1LL << b) * c0 * c1;
    }
    return total;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   SUM OF XOR OF ALL SUBARRAYS                   ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> arr = {1, 2};
    cout << "  [1,2]: " << sumXorAllSubarrays(arr) << endl;
    assert(sumXorAllSubarrays(arr) == 6); // 1+2+3

    vector<int> arr2 = {1, 2, 3};
    long long brute = 0;
    for (int i = 0; i < 3; i++) {
        int x = 0;
        for (int j = i; j < 3; j++) { x ^= arr2[j]; brute += x; }
    }
    cout << "  [1,2,3]: " << sumXorAllSubarrays(arr2) << " (brute: " << brute << ")" << endl;
    assert(sumXorAllSubarrays(arr2) == brute);

    cout << "\n✅ Sum of XOR of all subarrays verified!" << endl;
    return 0;
}

