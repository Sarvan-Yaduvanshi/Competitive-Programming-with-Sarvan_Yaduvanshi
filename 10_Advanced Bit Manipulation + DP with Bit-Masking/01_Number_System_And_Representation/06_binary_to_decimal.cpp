/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.06 — BINARY TO DECIMAL CONVERSION                       ║
║           Bit Manipulation — Base Conversions                                ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

ALGORITHM — POSITIONAL WEIGHT SUM:
═══════════════════════════════════
    Given binary number B = b_(k-1) b_(k-2) ... b_1 b_0

    Decimal value N = Σ (i = 0 to k-1) [ b_i × 2^i ]

    Equivalently (Horner's method — more efficient):
    N = (...((b_(k-1) × 2 + b_(k-2)) × 2 + b_(k-3)) × 2 + ...) × 2 + b_0

DRY RUN — 11001₂ TO DECIMAL (Method 1: Positional Weights):
═════════════════════════════════════════════════════════════
    b₄=1  b₃=1  b₂=0  b₁=0  b₀=1

    N = 1×2⁴ + 1×2³ + 0×2² + 0×2¹ + 1×2⁰
      = 16   + 8    + 0    + 0    + 1
      = 25₁₀ ✓

DRY RUN — 11001₂ TO DECIMAL (Method 2: Horner's Method):
══════════════════════════════════════════════════════════
    Process left to right: 1 → 1 → 0 → 0 → 1

    Step 1: result = 1
    Step 2: result = 1×2 + 1 = 3
    Step 3: result = 3×2 + 0 = 6
    Step 4: result = 6×2 + 0 = 12
    Step 5: result = 12×2 + 1 = 25 ✓

    Horner's is O(k) with no exponentiation needed!

DRY RUN — 10110111₂ TO DECIMAL:
════════════════════════════════
    Positional:
    1×128 + 0×64 + 1×32 + 1×16 + 0×8 + 1×4 + 1×2 + 1×1
    = 128 + 0 + 32 + 16 + 0 + 4 + 2 + 1
    = 183₁₀

    Horner's: 1→2→5→11→22→45→91→183 ✓

TIME COMPLEXITY: O(k) where k = number of bits
SPACE COMPLEXITY: O(1) for Horner's method
*/

#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// METHOD 1: Positional Weights (Educational, with trace)
// N = Σ b_i × 2^i
// ═══════════════════════════════════════════════════════════════
long long binaryToDecimal_positional(const string& bin) {
    int k = bin.size();
    long long result = 0;

    cout << "  Positional weight expansion:" << endl;
    for (int i = 0; i < k; i++) {
        int bitPos = k - 1 - i;
        int bitVal = bin[i] - '0';
        long long contribution = bitVal * (1LL << bitPos);
        if (bitVal) {
            cout << "  + " << bitVal << " × 2^" << bitPos << " = " << contribution << endl;
        }
        result += contribution;
    }
    cout << "  = " << result << "₁₀" << endl;
    return result;
}

// ═══════════════════════════════════════════════════════════════
// METHOD 2: Horner's Method (Most efficient, no exponentiation)
// Process left→right: result = result × 2 + current_bit
// ═══════════════════════════════════════════════════════════════
long long binaryToDecimal_horner(const string& bin) {
    long long result = 0;

    cout << "  Horner's method trace:" << endl;
    for (int i = 0; i < (int)bin.size(); i++) {
        int bit = bin[i] - '0';
        result = result * 2 + bit;
        cout << "  Step " << i+1 << ": result = " << result
             << " (processed bit '" << bit << "')" << endl;
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// METHOD 3: Bit shift method (C++ optimized)
// ═══════════════════════════════════════════════════════════════
long long binaryToDecimal_bitshift(const string& bin) {
    long long result = 0;
    for (char c : bin) {
        result = (result << 1) | (c - '0');  // shift left + OR with bit
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// METHOD 4: Using stoll with base 2
// ═══════════════════════════════════════════════════════════════
long long binaryToDecimal_stl(const string& bin) {
    return stoll(bin, nullptr, 2);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   BINARY → DECIMAL CONVERSION                    ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Method 1: Positional
    cout << "\n═══ METHOD 1: Positional Weights (11001₂) ═══" << endl;
    long long r1 = binaryToDecimal_positional("11001");

    // Method 2: Horner's
    cout << "\n═══ METHOD 2: Horner's Method (11001₂) ═══" << endl;
    long long r2 = binaryToDecimal_horner("11001");
    cout << "  Result: " << r2 << "₁₀" << endl;

    cout << "\n═══ METHOD 2: Horner's Method (10110111₂) ═══" << endl;
    long long r3 = binaryToDecimal_horner("10110111");
    cout << "  Result: " << r3 << "₁₀" << endl;

    // Method 3: Bitshift
    cout << "\n═══ METHOD 3: Bitshift (11111111₂) ═══" << endl;
    cout << "  Result: " << binaryToDecimal_bitshift("11111111") << "₁₀" << endl;

    // Method 4: STL
    cout << "\n═══ METHOD 4: STL stoll (1100100₂) ═══" << endl;
    cout << "  Result: " << binaryToDecimal_stl("1100100") << "₁₀" << endl;

    // Assertions
    assert(r1 == 25);
    assert(r2 == 25);
    assert(r3 == 183);
    assert(binaryToDecimal_bitshift("11111111") == 255);
    assert(binaryToDecimal_stl("1100100") == 100);

    cout << "\n✅ All binary to decimal conversions verified!" << endl;
    return 0;
}

