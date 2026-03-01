/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.05 — DECIMAL TO BINARY CONVERSION                     ║
║           Bit Manipulation — Base Conversions                              ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

ALGORITHM — REPEATED DIVISION METHOD:
══════════════════════════════════════
    To convert decimal N to binary:
    1. Divide N by 2
    2. Record the remainder (0 or 1) — this is the next bit (from LSB)
    3. Replace N with quotient
    4. Repeat until N = 0
    5. Read remainders from BOTTOM to TOP

MATHEMATICAL PROOF:
═══════════════════
    N = b_(k-1) × 2^(k-1) + ... + b_1 × 2 + b_0

    N mod 2 = b_0          (all terms with 2^i for i≥1 vanish)
    N / 2   = b_(k-1) × 2^(k-2) + ... + b_1

    Repeating extracts each bit from LSB to MSB.

DRY RUN — CONVERT 25₁₀ TO BINARY:
═══════════════════════════════════
    Step  N      N÷2    N%2(bit)
    ─────────────────────────────
    1     25     12     1    (LSB = b₀)
    2     12      6     0         (b₁)
    3      6      3     0         (b₂)
    4      3      1     1         (b₃)
    5      1      0     1    (MSB = b₄)

    Read bottom→top: 11001₂

    Verify: 1×16 + 1×8 + 0×4 + 0×2 + 1×1 = 25 ✓

DRY RUN — CONVERT 100₁₀ TO BINARY:
════════════════════════════════════
    Step  N       N÷2    N%2
    ────────────────────────────
    1     100     50     0
    2      50     25     0
    3      25     12     1
    4      12      6     0
    5       6      3     0
    6       3      1     1
    7       1      0     1

    Read bottom→top: 1100100₂
    Verify: 64+32+4 = 100 ✓

METHOD 2 — SUBTRACTING POWERS OF 2:
════════════════════════════════════
    Find largest 2^k ≤ N, set bit k = 1, subtract, repeat.

    N = 25:  2⁴=16 ≤ 25  → bit 4 = 1, N = 9
             2³=8  ≤ 9   → bit 3 = 1, N = 1
             2²=4  > 1   → bit 2 = 0
             2¹=2  > 1   → bit 1 = 0
             2⁰=1  ≤ 1   → bit 0 = 1, N = 0
    Result: 11001₂ ✓

FRACTIONAL CONVERSION (Decimal 0.625 → Binary):
════════════════════════════════════════════════
    Multiply by 2, take integer part:
    0.625 × 2 = 1.25  → 1
    0.25  × 2 = 0.50  → 0
    0.50  × 2 = 1.00  → 1

    Read top→bottom: 0.101₂
    Verify: 1×(1/2) + 0×(1/4) + 1×(1/8) = 0.5 + 0.125 = 0.625 ✓

TIME COMPLEXITY: O(log₂ N) — number of bits
SPACE COMPLEXITY: O(log₂ N) — to store the result
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// METHOD 1: Repeated Division
// ═══════════════════════════════════════════════════════════════
string decimalToBinary_division(long long n) {
    if (n == 0) return "0";
    string result = "";
    cout << "  Step  N       N/2     N%2" << endl;
    cout << "  ─────────────────────────" << endl;
    int step = 1;
    while (n > 0) {
        long long q = n / 2;
        int r = n % 2;
        cout << "  " << step++ << "     " << n << "\t" << q << "\t" << r << endl;
        result = (char)('0' + r) + result;
        n = q;
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// METHOD 2: Subtracting Powers of 2
// ═══════════════════════════════════════════════════════════════
string decimalToBinary_subtraction(long long n) {
    if (n == 0) return "0";
    string result = "";
    // Find highest bit
    int highBit = 0;
    while ((1LL << (highBit + 1)) <= n) highBit++;

    for (int i = highBit; i >= 0; i--) {
        if (n >= (1LL << i)) {
            result += '1';
            n -= (1LL << i);
            cout << "  2^" << i << " = " << (1LL << i) << " ≤ N → bit " << i << " = 1, remaining = " << n << endl;
        } else {
            result += '0';
            cout << "  2^" << i << " = " << (1LL << i) << " > N → bit " << i << " = 0" << endl;
        }
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// METHOD 3: Fractional Conversion (double → binary fraction string)
// ═══════════════════════════════════════════════════════════════
string fractionalToBinary(double frac, int precision = 10) {
    string result = "0.";
    while (frac > 0 && precision-- > 0) {
        frac *= 2;
        if (frac >= 1.0) {
            result += '1';
            frac -= 1.0;
        } else {
            result += '0';
        }
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// METHOD 4: Using bit operations (most efficient)
// ═══════════════════════════════════════════════════════════════
string decimalToBinary_bitwise(long long n) {
    if (n == 0) return "0";
    string result = "";
    while (n > 0) {
        result = (char)('0' + (n & 1)) + result;  // n & 1 = LSB
        n >>= 1;                                    // right shift = divide by 2
    }
    return result;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   DECIMAL → BINARY CONVERSION                   ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Method 1: Repeated Division
    cout << "\n═══ METHOD 1: Repeated Division (25₁₀) ═══" << endl;
    string r1 = decimalToBinary_division(25);
    cout << "  Result: " << r1 << "₂" << endl;

    cout << "\n═══ METHOD 1: Repeated Division (100₁₀) ═══" << endl;
    string r2 = decimalToBinary_division(100);
    cout << "  Result: " << r2 << "₂" << endl;

    // Method 2: Subtracting Powers
    cout << "\n═══ METHOD 2: Subtract Powers of 2 (25₁₀) ═══" << endl;
    string r3 = decimalToBinary_subtraction(25);
    cout << "  Result: " << r3 << "₂" << endl;

    // Method 3: Fractional
    cout << "\n═══ METHOD 3: Fractional (0.625) ═══" << endl;
    cout << "  0.625₁₀ = " << fractionalToBinary(0.625) << "₂" << endl;
    cout << "  0.1₁₀   = " << fractionalToBinary(0.1) << "₂ (non-terminating!)" << endl;

    // Method 4: Bitwise
    cout << "\n═══ METHOD 4: Bitwise (25₁₀) ═══" << endl;
    cout << "  Result: " << decimalToBinary_bitwise(25) << "₂" << endl;

    // Assertions
    assert(r1 == "11001");
    assert(r2 == "1100100");
    assert(decimalToBinary_bitwise(25) == "11001");
    assert(decimalToBinary_bitwise(100) == "1100100");
    assert(decimalToBinary_bitwise(255) == "11111111");

    cout << "\n✅ All decimal to binary conversions verified!" << endl;
    return 0;
}

