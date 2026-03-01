/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.03 — OCTAL NUMBER SYSTEM                              ║
║           Bit Manipulation — Number System Foundations                      ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

MATHEMATICAL DEFINITION:
════════════════════════
The Octal Number System (Base-8) uses 8 distinct digits:
    O = {0, 1, 2, 3, 4, 5, 6, 7}

Any octal number N with digits o_(k-1), ..., o_1, o_0 is:

    N = Σ (i = 0 to k-1) [ o_i × 8^i ]

EXAMPLE — POSITIONAL NOTATION:
══════════════════════════════
    Octal: 357₈

    Position:  3        5        7
    Weight:    8²=64    8¹=8     8⁰=1

    N = 3×64 + 5×8 + 7×1
      = 192  + 40  + 7
      = 239₁₀

DRY RUN — OCTAL 754₈ TO DECIMAL:
═════════════════════════════════
    o₂=7, o₁=5, o₀=4

    N = 7×8² + 5×8¹ + 4×8⁰
      = 7×64 + 5×8  + 4×1
      = 448  + 40   + 4
      = 492₁₀ ✓

WHY OCTAL MATTERS:
══════════════════
    • Each octal digit = exactly 3 binary bits
    • Used in Unix file permissions: 755₈ = rwxr-xr-x
    • Easy conversion to/from binary
    • Mapping: 0→000, 1→001, 2→010, 3→011, 4→100, 5→101, 6→110, 7→111

PROPERTIES:
═══════════
    • Base (Radix) = 8 = 2³
    • k-digit range: [0, 8^k - 1]
    • 3-digit range: [0, 511]
    • Number of digits: k = ⌊log₈(N)⌋ + 1
    • C/C++ octal literal prefix: 0  (e.g., 0357 = 239₁₀)
*/

#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// FUNCTION 1: Octal string to decimal
// Formula: N = Σ o_i × 8^i
// ═══════════════════════════════════════════════════════════════
long long octalToDecimal(const string& octal) {
    long long result = 0;
    int n = octal.size();
    for (int i = 0; i < n; i++) {
        result += (octal[i] - '0') * (long long)pow(8, n - 1 - i);
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 2: Decimal to octal string
// Method: Repeated division by 8
// ═══════════════════════════════════════════════════════════════
string decimalToOctal(long long n) {
    if (n == 0) return "0";
    string result = "";
    while (n > 0) {
        result = (char)('0' + n % 8) + result;
        n /= 8;
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 3: Display octal breakdown with place values
// ═══════════════════════════════════════════════════════════════
void displayOctalBreakdown(const string& octal) {
    int k = octal.size();
    cout << "Octal " << octal << "₈ breakdown:" << endl;

    long long sum = 0;
    for (int i = 0; i < k; i++) {
        int pos = k - 1 - i;
        int digit = octal[i] - '0';
        long long val = digit * (long long)pow(8, pos);
        cout << "  o_" << pos << " = " << digit
             << " × 8^" << pos << " = " << val << endl;
        sum += val;
    }
    cout << "  Total = " << sum << "₁₀" << endl;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 4: Unix file permissions octal demo
// ═══════════════════════════════════════════════════════════════
void unixPermissions(int octalPerm) {
    // Each octal digit: r(4) w(2) x(1)
    string labels[] = {"Owner", "Group", "Other"};
    int digits[3];
    digits[2] = octalPerm % 10; octalPerm /= 10;
    digits[1] = octalPerm % 10; octalPerm /= 10;
    digits[0] = octalPerm % 10;

    cout << "Unix Permissions:" << endl;
    for (int i = 0; i < 3; i++) {
        string perm = "";
        perm += (digits[i] & 4) ? "r" : "-";
        perm += (digits[i] & 2) ? "w" : "-";
        perm += (digits[i] & 1) ? "x" : "-";
        cout << "  " << labels[i] << ": " << digits[i] << " = " << perm << endl;
    }
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   OCTAL NUMBER SYSTEM — DEMONSTRATIONS          ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Demo 1: Octal to Decimal
    cout << "\n--- Octal to Decimal ---" << endl;
    cout << "357₈ = " << octalToDecimal("357") << "₁₀" << endl;   // 239
    cout << "754₈ = " << octalToDecimal("754") << "₁₀" << endl;   // 492

    // Demo 2: Decimal to Octal
    cout << "\n--- Decimal to Octal ---" << endl;
    cout << "239₁₀ = " << decimalToOctal(239) << "₈" << endl;     // 357
    cout << "492₁₀ = " << decimalToOctal(492) << "₈" << endl;     // 754

    // Demo 3: Breakdown
    cout << "\n--- Place Value Breakdown ---" << endl;
    displayOctalBreakdown("357");
    cout << endl;
    displayOctalBreakdown("754");

    // Demo 4: Unix Permissions
    cout << "\n--- Unix File Permissions ---" << endl;
    unixPermissions(755);
    cout << endl;
    unixPermissions(644);

    // Assertions
    assert(octalToDecimal("357") == 239);
    assert(octalToDecimal("754") == 492);
    assert(decimalToOctal(239) == "357");
    assert(decimalToOctal(492) == "754");

    cout << "\n✅ All octal number system concepts verified!" << endl;
    return 0;
}

