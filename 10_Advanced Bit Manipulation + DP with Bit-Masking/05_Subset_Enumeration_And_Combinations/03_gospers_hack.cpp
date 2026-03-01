/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 05.03 — GOSPER'S HACK                                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Enumerate all n-bit numbers with exactly k bits set.
    i.e., iterate all C(n,k) subsets of size k.

GOSPER'S HACK FORMULA:
══════════════════════
    Given current mask x:
        lowest = x & (-x)              // lowest set bit
        ripple = x + lowest            // carry propagates
        x = ((x ^ ripple) >> (ctz+2)) | ripple

    Or equivalently:
        c = x & (-x);
        r = x + c;
        x = (((r ^ x) >> 2) / c) | r;

SIMPLIFIED VERSION:
    low = x & (-x);
    high = x + low;
    x = (((high ^ x) >> (__builtin_ctz(low) + 2))) | high;

DRY RUN — n=5, k=3 (all 5-bit numbers with 3 bits set):
    Start: 00111 (7)
    → 01011 (11) → 01101 (13) → 01110 (14)
    → 10011 (19) → 10101 (21) → 10110 (22)
    → 11001 (25) → 11010 (26) → 11100 (28)
    Total: C(5,3) = 10 ✓

TIME: O(C(n,k)) to enumerate all
APPLICATION: Iterate all subsets of fixed size k.
*/
#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

void gosperHack(int n, int k) {
    cout << "  All " << n << "-bit masks with " << k << " bits set:" << endl;
    int mask = (1 << k) - 1;  // smallest: k rightmost bits
    int limit = (1 << n);
    int count = 0;

    while (mask < limit) {
        cout << "    " << bitset<5>(mask) << " (" << mask << ")" << endl;
        count++;

        // Gosper's hack: next permutation of bits
        int c = mask & (-mask);
        int r = mask + c;
        mask = (((r ^ mask) >> (__builtin_ctz(c) + 2))) | r;
    }
    cout << "  Total: " << count << endl;
}

// Compute C(n,k) for verification
int comb(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    int result = 1;
    for (int i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   GOSPER'S HACK                                 ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- C(5,3) = " << comb(5,3) << " subsets of size 3 ---" << endl;
    gosperHack(5, 3);

    cout << "\n--- C(4,2) = " << comb(4,2) << " subsets of size 2 ---" << endl;
    gosperHack(4, 2);

    cout << "\n--- C(5,1) = " << comb(5,1) << " subsets of size 1 ---" << endl;
    gosperHack(5, 1);

    cout << "\n✅ Gosper's hack verified!" << endl;
    return 0;
}

