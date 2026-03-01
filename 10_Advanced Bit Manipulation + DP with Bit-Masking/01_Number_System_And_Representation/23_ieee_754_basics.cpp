/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.23 — IEEE 754 BASICS                                  ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

IEEE 754 STANDARD:
══════════════════
    Value = (-1)^S × (1 + F) × 2^(E - bias)

    Format          Bits  Sign  Exponent  Mantissa  Bias
    ─────────────────────────────────────────────────────
    float (single)  32    1     8         23        127
    double          64    1     11        52        1023
    long double     80/128 varies

SPECIAL VALUES:
═══════════════
    +0:        S=0, E=0,   F=0
    -0:        S=1, E=0,   F=0     (+0 == -0 in comparisons)
    +∞:        S=0, E=255, F=0     (result of 1.0/0.0)
    -∞:        S=1, E=255, F=0
    NaN:       E=255, F≠0           (result of 0.0/0.0, sqrt(-1))
    Denormal:  E=0, F≠0             (tiny numbers near zero)

DENORMALIZED NUMBERS:
═════════════════════
    When E=0: Value = (-1)^S × (0 + F) × 2^(1 - bias)
    (No implicit leading 1, allows gradual underflow to 0)

    Smallest positive float:
        Normal: 2^(-126) ≈ 1.18 × 10^(-38)
        Denorm: 2^(-149) ≈ 1.4 × 10^(-45)

ROUNDING:
═════════
    Default: Round to nearest, ties to even
    This is why 0.1 + 0.2 ≠ 0.3 in binary floating point

DRY RUN — DECODING 0x41200000:
══════════════════════════════
    Hex:    4    1    2    0    0    0    0    0
    Binary: 0100 0001 0010 0000 0000 0000 0000 0000

    S = 0
    E = 10000010 = 130, actual = 130 - 127 = 3
    F = .01000000000000000000000

    Value = +1 × (1 + 0.25) × 2³ = 1.25 × 8 = 10.0 ✓
*/

#include <iostream>
#include <cstring>
#include <cmath>
#include <bitset>
#include <limits>
using namespace std;

void decodeIEEE754_float(float f) {
    unsigned int bits;
    memcpy(&bits, &f, sizeof(bits));

    int S = (bits >> 31) & 1;
    int E = (bits >> 23) & 0xFF;
    unsigned int F = bits & 0x7FFFFF;

    cout << "  Float: " << f << endl;
    cout << "  Bits:  " << bitset<32>(bits) << endl;
    cout << "  S=" << S << " E=" << E << " F=" << bitset<23>(F) << endl;

    if (E == 0 && F == 0) cout << "  → " << (S ? "-0" : "+0") << endl;
    else if (E == 255 && F == 0) cout << "  → " << (S ? "-∞" : "+∞") << endl;
    else if (E == 255) cout << "  → NaN" << endl;
    else if (E == 0) cout << "  → Denormalized: " << (S?"-":"+") << "0."
                          << " × 2^(-126)" << endl;
    else {
        double mantissa = 1.0;
        for (int i = 22; i >= 0; i--) {
            if (F & (1 << i)) mantissa += pow(2, i - 23);
        }
        cout << "  → " << (S?"-":"+") << mantissa << " × 2^" << (E-127)
             << " = " << f << endl;
    }
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   IEEE 754 BASICS                               ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- Normal Numbers ---" << endl;
    decodeIEEE754_float(10.0f);
    cout << endl;
    decodeIEEE754_float(6.5f);
    cout << endl;
    decodeIEEE754_float(-1.0f);

    cout << "\n--- Special Values ---" << endl;
    decodeIEEE754_float(0.0f);
    cout << endl;
    decodeIEEE754_float(-0.0f);
    cout << endl;
    decodeIEEE754_float(1.0f/0.0f);   // +inf
    cout << endl;
    decodeIEEE754_float(0.0f/0.0f);   // NaN

    cout << "\n--- Precision Limits ---" << endl;
    cout << "  float digits:  " << numeric_limits<float>::digits10 << endl;
    cout << "  double digits: " << numeric_limits<double>::digits10 << endl;
    cout << "  float epsilon: " << numeric_limits<float>::epsilon() << endl;
    cout << "  double epsilon:" << numeric_limits<double>::epsilon() << endl;
    cout << "  float min (normal):  " << numeric_limits<float>::min() << endl;
    cout << "  float min (denorm):  " << numeric_limits<float>::denorm_min() << endl;

    cout << "\n--- NaN Properties ---" << endl;
    float nan_val = 0.0f / 0.0f;
    cout << "  NaN == NaN? " << (nan_val == nan_val ? "true" : "FALSE (always!)") << endl;
    cout << "  isnan(NaN)? " << (isnan(nan_val) ? "YES" : "NO") << endl;
    cout << "  isinf(1/0)? " << (isinf(1.0f/0.0f) ? "YES" : "NO") << endl;

    cout << "\n✅ IEEE 754 basics demonstrated!" << endl;
    return 0;
}

