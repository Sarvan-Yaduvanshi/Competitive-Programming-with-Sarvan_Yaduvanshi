/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 09.04 — INCLUSION-EXCLUSION WITH BITMASK                 ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

INCLUSION-EXCLUSION PRINCIPLE:
══════════════════════════════
    |A₁ ∪ A₂ ∪ ... ∪ Aₙ| = Σ|Aᵢ| - Σ|Aᵢ∩Aⱼ| + Σ|Aᵢ∩Aⱼ∩Aₖ| - ...

    With bitmask: for each subset S ⊆ {1..n}:
        coefficient = (-1)^(|S|+1)

    Σ_{S≠∅} (-1)^(|S|+1) × f(∩_{i∈S} Aᵢ)

CLASSIC PROBLEM: Count integers in [1,N] not divisible by any prime in a given set.
    f(S) = N / lcm(primes in S)  (using floor division)
    answer = N - Σ_{S≠∅} (-1)^(|S|+1) × f(S)

DRY RUN — N=30, primes={2,3,5}:
    |A₂|=15, |A₃|=10, |A₅|=6
    |A₂∩A₃|=5, |A₂∩A₅|=3, |A₃∩A₅|=2
    |A₂∩A₃∩A₅|=1
    |A₂∪A₃∪A₅| = 15+10+6 - 5-3-2 + 1 = 22
    Not divisible by any: 30-22 = 8 → {1,7,11,13,17,19,23,29} ✓

TIME: O(2ⁿ) where n = number of sets

PRACTICE PROBLEMS:
══════════════════
    Codeforces: 451E (Devu and Flowers)
    CSES: Counting Coprime Pairs
*/
#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>
using namespace std;

long long countNotDivisible(long long N, vector<long long>& primes) {
    int n = primes.size();
    long long bad = 0; // count of numbers divisible by at least one prime

    for (int mask = 1; mask < (1 << n); mask++) {
        long long lcm_val = 1;
        int bits = __builtin_popcount(mask);
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                lcm_val = lcm(lcm_val, primes[i]);
                if (lcm_val > N) break; // overflow protection
            }
        }
        long long count = N / lcm_val;
        if (bits & 1) bad += count;  // odd: add
        else bad -= count;           // even: subtract
    }
    return N - bad;
}

// Euler's totient using inclusion-exclusion
long long eulerTotient(long long n) {
    // Find prime factors
    vector<long long> primes;
    long long temp = n;
    for (long long p = 2; p * p <= temp; p++) {
        if (temp % p == 0) {
            primes.push_back(p);
            while (temp % p == 0) temp /= p;
        }
    }
    if (temp > 1) primes.push_back(temp);
    return countNotDivisible(n, primes);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   INCLUSION-EXCLUSION WITH BITMASK              ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<long long> primes = {2, 3, 5};
    long long N = 30;
    long long result = countNotDivisible(N, primes);
    cout << "\n  N=" << N << ", primes={2,3,5}" << endl;
    cout << "  Numbers not divisible by 2,3,5: " << result << endl;
    assert(result == 8);

    cout << "\n--- Euler's Totient via Inclusion-Exclusion ---" << endl;
    for (long long n : {12, 30, 100}) {
        cout << "  φ(" << n << ") = " << eulerTotient(n) << endl;
    }
    assert(eulerTotient(12) == 4);  // {1,5,7,11}
    assert(eulerTotient(30) == 8);

    cout << "\n✅ Inclusion-Exclusion verified!" << endl;
    return 0;
}

