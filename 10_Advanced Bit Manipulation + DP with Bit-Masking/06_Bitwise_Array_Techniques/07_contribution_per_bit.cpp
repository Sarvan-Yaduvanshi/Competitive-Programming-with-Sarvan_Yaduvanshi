/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 06.07 — CONTRIBUTION PER BIT                             ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TECHNIQUE: Instead of computing answer for entire numbers, compute per-bit independently.

FORMULA FOR SUM OF XOR/AND/OR OF ALL PAIRS:
════════════════════════════════════════════
    For each bit b (0 to 30):
        c₁ = count of numbers with bit b set
        c₀ = n - c₁

    Sum of (a_i AND a_j) over all pairs: Σ_b 2^b × C(c₁, 2)
    Sum of (a_i OR a_j) over all pairs:  Σ_b 2^b × (C(n,2) - C(c₀, 2))
    Sum of (a_i XOR a_j) over all pairs: Σ_b 2^b × c₁ × c₀

DRY RUN — Sum of XOR of all pairs, arr=[1,2,3]:
    Bit 0: c₁=2 (1,3 have bit 0), c₀=1 → contribution = 1 × 2 × 1 = 2
    Bit 1: c₁=2 (2,3 have bit 1), c₀=1 → contribution = 2 × 2 × 1 = 4
    Total = 2+4 = 6
    Verify: (1^2)+(1^3)+(2^3) = 3+2+1 = 6 ✓

TIME: O(n × 32)
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

long long sumXorAllPairs(vector<int>& arr) {
    int n = arr.size();
    long long total = 0;
    for (int b = 0; b < 31; b++) {
        int c1 = 0;
        for (int x : arr) if (x & (1 << b)) c1++;
        int c0 = n - c1;
        total += (long long)(1 << b) * c1 * c0;
    }
    return total;
}

long long sumAndAllPairs(vector<int>& arr) {
    int n = arr.size();
    long long total = 0;
    for (int b = 0; b < 31; b++) {
        long long c1 = 0;
        for (int x : arr) if (x & (1 << b)) c1++;
        total += (long long)(1 << b) * c1 * (c1 - 1) / 2;
    }
    return total;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   CONTRIBUTION PER BIT                          ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<int> arr = {1, 2, 3};

    // Brute force verification
    long long bruteXor = 0, bruteAnd = 0;
    int n = arr.size();
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++) {
            bruteXor += arr[i] ^ arr[j];
            bruteAnd += arr[i] & arr[j];
        }

    cout << "  Array: [1, 2, 3]" << endl;
    cout << "  Sum of XOR of all pairs: " << sumXorAllPairs(arr) << " (brute: " << bruteXor << ")" << endl;
    cout << "  Sum of AND of all pairs: " << sumAndAllPairs(arr) << " (brute: " << bruteAnd << ")" << endl;

    assert(sumXorAllPairs(arr) == bruteXor);
    assert(sumAndAllPairs(arr) == bruteAnd);

    cout << "\n✅ Contribution per bit verified!" << endl;
    return 0;
}

