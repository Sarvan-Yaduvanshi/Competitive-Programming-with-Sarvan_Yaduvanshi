/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.01 — DECIMAL NUMBER SYSTEM                              ║
║           Bit Manipulation — Number System Foundations                       ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

MATHEMATICAL DEFINITION:
════════════════════════
The Decimal Number System (Base-10) uses 10 distinct digits:
    D = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}

Any decimal number N with digits d_(k-1), d_(k-2), ..., d_1, d_0 is:

    N = Σ (i = 0 to k-1) [ d_i × 10^i ]

EXAMPLE — POSITIONAL NOTATION:
══════════════════════════════
    Number: 3754

    Position:  3        7        5        4
    Weight:    10³      10²      10¹      10⁰
    Value:     3×1000   7×100    5×10     4×1

    N = 3×10³ + 7×10² + 5×10¹ + 4×10⁰
      = 3000  + 700   + 50    + 4
      = 3754

DRY RUN — DECOMPOSING 2025:
════════════════════════════
    d₃ = 2, d₂ = 0, d₁ = 2, d₀ = 5

    N = 2×10³ + 0×10² + 2×10¹ + 5×10⁰
      = 2000  + 0     + 20    + 5
      = 2025 ✓

PROPERTIES:
═══════════
    • Base (Radix) = 10
    • k-digit number range: [0, 10^k - 1]
    • 3-digit range: [0, 999]  → 1000 possible values
    • Number of digits in N: k = ⌊log₁₀(N)⌋ + 1

FRACTIONAL NUMBERS:
═══════════════════
    23.45 = 2×10¹ + 3×10⁰ + 4×10⁻¹ + 5×10⁻²
          = 20    + 3     + 0.4    + 0.05
          = 23.45

TIME COMPLEXITY OF OPERATIONS:
══════════════════════════════
    • Digit extraction: O(1) per digit
    • Full decomposition: O(log₁₀(N)) = O(k)
    • Digit count: O(1) using log₁₀

PRACTICE PROBLEMS:
══════════════════
    • Count digits of a number
    • Sum of digits
    • Reverse a number
    • Check if number is palindrome in decimal
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// FUNCTION 1: Count digits using logarithm
// Formula: k = ⌊log₁₀(N)⌋ + 1
// ═══════════════════════════════════════════════════════════════
int countDigits(long long n) {
    if (n == 0) return 1;
    if (n < 0) n = -n;
    return (int)floor(log10(n)) + 1;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 2: Decompose number into positional values
// N = Σ d_i × 10^i
// ═══════════════════════════════════════════════════════════════
void decomposeDecimal(long long n) {
    cout << "Decomposition of " << n << ":" << endl;

    vector<int> digits;
    long long temp = n;
    while (temp > 0) {
        digits.push_back(temp % 10);
        temp /= 10;
    }

    // Print from MSB to LSB
    long long sum = 0;
    for (int i = digits.size() - 1; i >= 0; i--) {
        long long positionalValue = digits[i] * (long long)pow(10, i);
        cout << "  d_" << i << " = " << digits[i]
             << " × 10^" << i << " = " << positionalValue << endl;
        sum += positionalValue;
    }
    cout << "  Total = " << sum << endl;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 3: Sum of digits
// ═══════════════════════════════════════════════════════════════
int sumOfDigits(long long n) {
    if (n < 0) n = -n;
    int sum = 0;
    while (n > 0) {
        sum += n % 10;  // Extract last digit d₀
        n /= 10;        // Remove last digit (shift right in base 10)
    }
    return sum;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 4: Reverse a number
// ═══════════════════════════════════════════════════════════════
long long reverseNumber(long long n) {
    long long rev = 0;
    while (n > 0) {
        rev = rev * 10 + n % 10;  // Shift rev left, add last digit
        n /= 10;
    }
    return rev;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 5: Check palindrome in decimal
// ═══════════════════════════════════════════════════════════════
bool isPalindromeDecimal(long long n) {
    return n == reverseNumber(n);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   DECIMAL NUMBER SYSTEM — DEMONSTRATIONS        ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Demo 1: Count digits
    cout << "\n--- Count Digits ---" << endl;
    cout << "Digits in 3754: " << countDigits(3754) << endl;    // 4
    cout << "Digits in 0: " << countDigits(0) << endl;          // 1
    cout << "Digits in 100000: " << countDigits(100000) << endl; // 6

    // Demo 2: Decompose
    cout << "\n--- Positional Decomposition ---" << endl;
    decomposeDecimal(3754);
    cout << endl;
    decomposeDecimal(2025);

    // Demo 3: Sum of digits
    cout << "\n--- Sum of Digits ---" << endl;
    cout << "Sum of digits of 3754: " << sumOfDigits(3754) << endl; // 3+7+5+4 = 19

    // Demo 4: Reverse
    cout << "\n--- Reverse Number ---" << endl;
    cout << "Reverse of 3754: " << reverseNumber(3754) << endl; // 4573

    // Demo 5: Palindrome check
    cout << "\n--- Palindrome Check ---" << endl;
    cout << "12321 is palindrome: " << (isPalindromeDecimal(12321) ? "YES" : "NO") << endl;
    cout << "12345 is palindrome: " << (isPalindromeDecimal(12345) ? "YES" : "NO") << endl;

    // Assertions
    assert(countDigits(3754) == 4);
    assert(sumOfDigits(3754) == 19);
    assert(reverseNumber(3754) == 4573);
    assert(isPalindromeDecimal(12321) == true);

    cout << "\n✅ All decimal number system concepts verified!" << endl;
    return 0;
}

