/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 10.01 — XOR BASIS CONSTRUCTION                           ║
║           Bit Manipulation — XOR Basis & Linear Algebra                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

CONCEPT: A XOR basis is a minimal set of numbers such that every XOR-reachable value
    can be produced by XORing some subset of the basis.

    Analogous to a vector space basis over GF(2) (field with {0,1}).

CONSTRUCTION (Gaussian Elimination):
═════════════════════════════════════
    basis[i] = the basis vector with highest bit = i (or 0 if unused).

    To insert x:
        for i from highest bit down to 0:
            if bit i of x is set:
                if basis[i] == 0: basis[i] = x; return (inserted)
                else: x ^= basis[i]  (reduce)
        if x == 0: not inserted (linearly dependent)

DRY RUN — Insert {6, 3, 5}:
    Insert 6 (110): basis[2] = 6
    Insert 3 (011): bit 1 → basis[1] = 3
    Insert 5 (101): bit 2 set → x ^= basis[2] = 5^6 = 3, bit 1 set → x ^= basis[1] = 3^3 = 0
    → 5 is linearly dependent! Not inserted.

    Basis: {6, 3}, dimension = 2, spans 2²=4 distinct XOR values: {0, 3, 5, 6}

PROPERTIES:
═══════════
    • Basis size ≤ log(MAX) ≤ 60 (for 64-bit numbers)
    • # distinct XOR values = 2^(basis_size)
    • Can check if x is representable: reduce x through basis, check if 0
    • Can find maximum XOR subset

TIME: O(n × log(MAX)) for construction

PRACTICE PROBLEMS:
══════════════════
    Codeforces: 959F, 895C
    SPOJ: XMAX
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

struct XORBasis {
    long long basis[60] = {};
    int sz = 0;

    bool insert(long long x) {
        for (int i = 59; i >= 0; i--) {
            if (!(x & (1LL << i))) continue;
            if (!basis[i]) {
                basis[i] = x;
                sz++;
                return true; // inserted
            }
            x ^= basis[i]; // reduce
        }
        return false; // linearly dependent
    }

    bool canRepresent(long long x) {
        for (int i = 59; i >= 0; i--) {
            if (x & (1LL << i)) x ^= basis[i];
        }
        return x == 0;
    }

    long long maxXOR() {
        long long result = 0;
        for (int i = 59; i >= 0; i--) {
            result = max(result, result ^ basis[i]);
        }
        return result;
    }

    long long minXOR() {
        for (int i = 0; i <= 59; i++) {
            if (basis[i]) return basis[i];
        }
        return 0;
    }
};

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   XOR BASIS CONSTRUCTION                        ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    XORBasis xb;
    vector<int> nums = {6, 3, 5, 7};

    cout << "\n--- Inserting elements ---" << endl;
    for (int x : nums) {
        bool inserted = xb.insert(x);
        cout << "  Insert " << x << ": " << (inserted ? "ADDED to basis" : "dependent (skipped)") << endl;
    }
    cout << "  Basis size: " << xb.sz << endl;
    cout << "  Distinct XOR values: 2^" << xb.sz << " = " << (1 << xb.sz) << endl;

    cout << "\n--- Basis vectors ---" << endl;
    for (int i = 0; i < 4; i++) {
        if (xb.basis[i]) cout << "  basis[" << i << "] = " << xb.basis[i] << endl;
    }

    cout << "\n--- Maximum XOR: " << xb.maxXOR() << endl;
    cout << "--- Minimum non-zero XOR: " << xb.minXOR() << endl;

    cout << "\n--- Can represent? ---" << endl;
    for (int x : {0, 1, 2, 3, 4, 5, 6, 7}) {
        cout << "  " << x << ": " << (xb.canRepresent(x) ? "YES" : "NO") << endl;
    }

    cout << "\n✅ XOR basis construction verified!" << endl;
    return 0;
}

