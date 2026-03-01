/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.02 — BINARY NUMBER SYSTEM                               ║
║           Bit Manipulation — Number System Foundations                       ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

MATHEMATICAL DEFINITION:
════════════════════════
The Binary Number System (Base-2) uses 2 distinct digits:
    B = {0, 1}

Each digit is called a "bit" (binary digit).

Any binary number N with bits b_(k-1), b_(k-2), ..., b_1, b_0 is:

    N = Σ (i = 0 to k-1) [ b_i × 2^i ]

EXAMPLE — POSITIONAL NOTATION:
══════════════════════════════
    Binary: 1101₂

    Position:  1        1        0        1
    Bit index: 3        2        1        0
    Weight:    2³=8     2²=4     2¹=2     2⁰=1

    N = 1×2³ + 1×2² + 0×2¹ + 1×2⁰
      = 8    + 4    + 0    + 1
      = 13₁₀

DRY RUN — BINARY 10110₂ TO DECIMAL:
════════════════════════════════════
    b₄=1, b₃=0, b₂=1, b₁=1, b₀=0

    N = 1×2⁴ + 0×2³ + 1×2² + 1×2¹ + 0×2⁰
      = 16   + 0    + 4    + 2    + 0
      = 22₁₀ ✓

POWERS OF 2 — MUST MEMORIZE:
═════════════════════════════
    2⁰  = 1         2⁸  = 256
    2¹  = 2         2⁹  = 512
    2²  = 4         2¹⁰ = 1024  (≈ 1K)
    2³  = 8         2¹⁶ = 65536 (≈ 64K)
    2⁴  = 16        2²⁰ = 1048576 (≈ 1M)
    2⁵  = 32        2³⁰ ≈ 10⁹
    2⁶  = 64        2³² ≈ 4.3 × 10⁹
    2⁷  = 128       2⁶⁴ ≈ 1.8 × 10¹⁹

KEY PROPERTIES:
═══════════════
    • Base (Radix) = 2
    • k-bit number range: [0, 2^k - 1]
    • 8-bit (byte): [0, 255]
    • Number of bits in N: k = ⌊log₂(N)⌋ + 1
    • MSB = Most Significant Bit (leftmost 1)
    • LSB = Least Significant Bit (rightmost bit, index 0)

WHY BINARY?
═══════════
    • Hardware uses voltage levels: HIGH(1) / LOW(0)
    • All data in computers is stored in binary
    • Boolean algebra maps directly to binary
    • Fast operations: shift = multiply/divide by 2

PLACE VALUE TABLE FOR 8 BITS:
═════════════════════════════
    Bit position:  7    6    5    4    3    2    1    0
    Place value:  128   64   32   16    8    4    2    1

    Example: 10110011₂ = 128+32+16+2+1 = 179₁₀
*/

#include <iostream>
#include <string>
#include <cmath>
#include <bitset>
#include <cassert>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// FUNCTION 1: Binary string to decimal (manual positional sum)
// Formula: N = Σ b_i × 2^i
// ═══════════════════════════════════════════════════════════════
long long binaryToDecimal(const string& binary) {
    long long result = 0;
    int n = binary.size();
    for (int i = 0; i < n; i++) {
        // binary[0] is MSB, binary[n-1] is LSB
        // Bit at position (n-1-i) has value binary[i]
        if (binary[i] == '1') {
            result += (1LL << (n - 1 - i));
        }
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 2: Decimal to binary string
// Method: Repeatedly divide by 2, collect remainders
// ═══════════════════════════════════════════════════════════════
string decimalToBinary(long long n) {
    if (n == 0) return "0";
    string result = "";
    while (n > 0) {
        result = (char)('0' + n % 2) + result;
        n /= 2;
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 3: Count number of bits
// Formula: k = ⌊log₂(N)⌋ + 1
// ═══════════════════════════════════════════════════════════════
int countBits(long long n) {
    if (n == 0) return 1;
    return (int)floor(log2(n)) + 1;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 4: Display binary with place values (educational)
// ═══════════════════════════════════════════════════════════════
void displayBinaryBreakdown(long long n) {
    string bin = decimalToBinary(n);
    int k = bin.size();

    cout << "Number: " << n << " = " << bin << "₂" << endl;
    cout << "Breakdown:" << endl;

    long long sum = 0;
    for (int i = 0; i < k; i++) {
        int bitPos = k - 1 - i;
        int bitVal = bin[i] - '0';
        long long contribution = bitVal * (1LL << bitPos);
        cout << "  b_" << bitPos << " = " << bitVal
             << " × 2^" << bitPos << " = " << contribution << endl;
        sum += contribution;
    }
    cout << "  Total = " << sum << endl;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 5: Print using C++ bitset
// ═══════════════════════════════════════════════════════════════
void showBitset(int n) {
    cout << "bitset<8>(" << n << ")  = " << bitset<8>(n) << endl;
    cout << "bitset<16>(" << n << ") = " << bitset<16>(n) << endl;
    cout << "bitset<32>(" << n << ") = " << bitset<32>(n) << endl;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   BINARY NUMBER SYSTEM — DEMONSTRATIONS          ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Demo 1: Binary to Decimal
    cout << "\n--- Binary to Decimal ---" << endl;
    cout << "1101₂ = " << binaryToDecimal("1101") << "₁₀" << endl;     // 13
    cout << "10110₂ = " << binaryToDecimal("10110") << "₁₀" << endl;   // 22
    cout << "11111111₂ = " << binaryToDecimal("11111111") << "₁₀" << endl; // 255

    // Demo 2: Decimal to Binary
    cout << "\n--- Decimal to Binary ---" << endl;
    cout << "13₁₀ = " << decimalToBinary(13) << "₂" << endl;
    cout << "22₁₀ = " << decimalToBinary(22) << "₂" << endl;
    cout << "255₁₀ = " << decimalToBinary(255) << "₂" << endl;

    // Demo 3: Bit count
    cout << "\n--- Number of Bits ---" << endl;
    cout << "Bits in 13: " << countBits(13) << endl;   // 4
    cout << "Bits in 255: " << countBits(255) << endl;  // 8
    cout << "Bits in 1024: " << countBits(1024) << endl; // 11

    // Demo 4: Breakdown
    cout << "\n--- Place Value Breakdown ---" << endl;
    displayBinaryBreakdown(179);

    // Demo 5: C++ bitset
    cout << "\n--- C++ Bitset Display ---" << endl;
    showBitset(13);
    showBitset(179);

    // Assertions
    assert(binaryToDecimal("1101") == 13);
    assert(binaryToDecimal("10110") == 22);
    assert(decimalToBinary(13) == "1101");
    assert(decimalToBinary(22) == "10110");
    assert(countBits(13) == 4);
    assert(countBits(255) == 8);

    cout << "\n✅ All binary number system concepts verified!" << endl;
    return 0;
}

