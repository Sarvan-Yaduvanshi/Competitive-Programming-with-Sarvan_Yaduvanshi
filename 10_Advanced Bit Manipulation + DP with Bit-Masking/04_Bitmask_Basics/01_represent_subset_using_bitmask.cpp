/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 04.01 — REPRESENT SUBSET USING BITMASK                   ║
║           Bit Manipulation — Bitmask Basics                                ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

CORE CONCEPT:
═════════════
    A bitmask is an integer where each bit represents membership of an element.

    Universe U = {0, 1, 2, ..., n-1}
    Subset S ⊆ U is represented by an n-bit integer (mask):
        bit i is 1 ⟺ element i ∈ S

BIJECTION:
══════════
    There is a 1-to-1 mapping between subsets of {0,..,n-1} and integers [0, 2ⁿ-1].
    Total subsets = 2ⁿ.

EXAMPLE — n=4, U={0,1,2,3}:
════════════════════════════
    mask = 0  (0000) → {} (empty set)
    mask = 1  (0001) → {0}
    mask = 5  (0101) → {0, 2}
    mask = 9  (1001) → {0, 3}
    mask = 13 (1101) → {0, 2, 3}
    mask = 15 (1111) → {0, 1, 2, 3} (full set)

DRY RUN — SET {a, c, d} with elements {a=0, b=1, c=2, d=3}:
═══════════════════════════════════════════════════════════════
    a∈S → bit 0 = 1
    b∉S → bit 1 = 0
    c∈S → bit 2 = 1
    d∈S → bit 3 = 1
    mask = 1101₂ = 13

SET OPERATIONS ON BITMASKS:
═══════════════════════════
    Union:        A ∪ B  =  A | B
    Intersection: A ∩ B  =  A & B
    Difference:   A \ B  =  A & ~B
    Complement:   Ā      =  ~A & ((1<<n)-1)
    Symmetric diff: A △ B = A ^ B
    Subset check: A ⊆ B  ⟺  (A & B) == A  ⟺  (A | B) == B
    Size:         |A|    =  popcount(A)
    Empty check:  A = ∅  ⟺  A == 0

CONSTRAINTS:
════════════
    • n ≤ 20-23 for bitmask DP (2²⁰ ≈ 10⁶, 2²³ ≈ 8×10⁶)
    • Use int for n ≤ 30, long long for n ≤ 62
    • 1LL << i for i ≥ 31

PRACTICE PROBLEMS:
══════════════════
    CSES: Apple Division
    LeetCode 78: Subsets
    Codeforces: 550B
*/
#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>
using namespace std;

// Print subset represented by mask, given element names
void printSubset(int mask, int n, const vector<string>& names = {}) {
    cout << "{";
    bool first = true;
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            if (!first) cout << ", ";
            if (!names.empty()) cout << names[i];
            else cout << i;
            first = false;
        }
    }
    cout << "}";
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   REPRESENT SUBSET USING BITMASK                ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int n = 4;
    vector<string> names = {"a", "b", "c", "d"};

    // Show all 2^n subsets
    cout << "\n--- All Subsets of {a,b,c,d} ---" << endl;
    for (int mask = 0; mask < (1 << n); mask++) {
        cout << "  mask=" << mask << " (" << bitset<4>(mask) << ") → ";
        printSubset(mask, n, names);
        cout << endl;
    }

    // Set operations
    int A = 0b1101; // {a, c, d}
    int B = 0b0111; // {a, b, c}
    cout << "\n--- Set Operations ---" << endl;
    cout << "  A = "; printSubset(A, n, names); cout << endl;
    cout << "  B = "; printSubset(B, n, names); cout << endl;
    cout << "  A ∪ B = "; printSubset(A | B, n, names); cout << endl;
    cout << "  A ∩ B = "; printSubset(A & B, n, names); cout << endl;
    cout << "  A \\ B = "; printSubset(A & ~B, n, names); cout << endl;
    cout << "  A △ B = "; printSubset(A ^ B, n, names); cout << endl;
    cout << "  |A| = " << __builtin_popcount(A) << endl;
    cout << "  A ⊆ B? " << ((A & B) == A ? "YES" : "NO") << endl;

    // Assertions
    assert((A | B) == 0b1111);
    assert((A & B) == 0b0101);
    assert(__builtin_popcount(A) == 3);

    cout << "\n✅ Bitmask subset representation verified!" << endl;
    return 0;
}

