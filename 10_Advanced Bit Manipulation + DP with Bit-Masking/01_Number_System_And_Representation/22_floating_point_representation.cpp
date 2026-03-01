/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.22 — FLOATING POINT REPRESENTATION (Basic Idea)       ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

SCIENTIFIC NOTATION IN BINARY:
══════════════════════════════
    Just like decimal: 6.022 × 10²³
    Binary uses:       1.mantissa × 2^exponent

    Any floating point number = (-1)^sign × (1 + fraction) × 2^(exponent - bias)

STRUCTURE (32-bit float):
═════════════════════════
    [S][EEEEEEEE][MMMMMMMMMMMMMMMMMMMMMMM]
     1    8 bits        23 bits
    Sign  Exponent      Mantissa (fraction)

    Total = 1 + 8 + 23 = 32 bits

STRUCTURE (64-bit double):
══════════════════════════
    [S][EEEEEEEEEEE][MMMM...M]
     1    11 bits     52 bits

    Total = 1 + 11 + 52 = 64 bits

DRY RUN — REPRESENT 6.5 IN FLOAT:
══════════════════════════════════
    Step 1: 6.5₁₀ = 110.1₂
    Step 2: Normalize: 1.101 × 2²
    Step 3: Sign = 0 (positive)
    Step 4: Exponent = 2 + 127(bias) = 129 = 10000001₂
    Step 5: Mantissa = 10100000000000000000000 (23 bits, drop leading 1)

    Result: 0 10000001 10100000000000000000000
          = 0x40D00000

PRECISION LIMITS:
═════════════════
    float:  ~7 significant decimal digits
    double: ~15-16 significant decimal digits

    NEVER compare floats with ==
    Use: abs(a - b) < epsilon (typically 1e-9)

CP IMPLICATIONS:
════════════════
    • Use double for floating point in CP (not float)
    • Binary search on answer → use 100 iterations or eps = 1e-9
    • Integer answers → avoid floating point entirely if possible
*/

#include <iostream>
#include <cstring>
#include <bitset>
#include <cmath>
#include <iomanip>
using namespace std;

void showFloatBits(float f) {
    unsigned int bits;
    memcpy(&bits, &f, sizeof(bits));

    int sign = (bits >> 31) & 1;
    int exponent = (bits >> 23) & 0xFF;
    int mantissa = bits & 0x7FFFFF;

    cout << "  " << f << " = ";
    cout << sign << " ";
    cout << bitset<8>(exponent) << " ";
    cout << bitset<23>(mantissa) << endl;
    cout << "    Sign=" << sign << ", Exp=" << exponent << " (bias 127, actual="
         << exponent-127 << "), Mantissa=1." << bitset<23>(mantissa) << endl;
}

void showDoubleBits(double d) {
    unsigned long long bits;
    memcpy(&bits, &d, sizeof(bits));

    int sign = (bits >> 63) & 1;
    int exponent = (bits >> 52) & 0x7FF;
    long long mantissa = bits & 0xFFFFFFFFFFFFF;

    cout << "  " << d << " → Sign=" << sign
         << ", Exp=" << exponent << " (actual=" << exponent-1023 << ")" << endl;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   FLOATING POINT REPRESENTATION                 ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- Float Bit Layout (32-bit) ---" << endl;
    showFloatBits(6.5f);
    showFloatBits(1.0f);
    showFloatBits(-1.0f);
    showFloatBits(0.1f);

    cout << "\n--- Double Bit Layout (64-bit) ---" << endl;
    showDoubleBits(6.5);
    showDoubleBits(0.1);

    cout << "\n--- Precision Limits ---" << endl;
    cout << fixed;
    cout << "  float precision:  " << setprecision(20) << 0.1f << endl;
    cout << "  double precision: " << setprecision(20) << 0.1 << endl;
    cout << "  Neither is exactly 0.1!" << endl;

    cout << "\n--- Never Compare Floats with == ---" << endl;
    double a = 0.1 + 0.2;
    double b = 0.3;
    cout << "  0.1 + 0.2 == 0.3? " << (a == b ? "true" : "FALSE!") << endl;
    cout << "  |diff| = " << scientific << abs(a - b) << endl;
    cout << "  Use eps comparison: |a-b| < 1e-9? "
         << (abs(a-b) < 1e-9 ? "YES" : "NO") << endl;

    cout << "\n✅ Floating point representation demonstrated!" << endl;
    return 0;
}

