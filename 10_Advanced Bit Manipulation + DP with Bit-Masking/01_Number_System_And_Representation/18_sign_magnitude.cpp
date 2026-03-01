/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.18 — SIGN MAGNITUDE REPRESENTATION                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

DEFINITION:
═══════════
MSB = sign bit (0 = +, 1 = -), remaining (n-1) bits = magnitude.
Range for n bits: [-(2^(n-1) - 1), 2^(n-1) - 1]

DRY RUN (8-bit):
    +5  = 0|0000101   (sign=0, magnitude=5)
    -5  = 1|0000101   (sign=1, magnitude=5)
    +0  = 0|0000000
    -0  = 1|0000000   ← Two zeros! Problem same as one's complement.

COMPARISON OF ALL THREE:
════════════════════════
    Number  Sign-Mag    One's Comp   Two's Comp
    +5      00000101    00000101     00000101
    -5      10000101    11111010     11111011
    +0      00000000    00000000     00000000
    -0      10000000    11111111     (no -0!)

    Two's complement is the clear winner for hardware!

WHY SIGN-MAGNITUDE IS USED:
═══════════════════════════
    • IEEE 754 floating point uses sign-magnitude for the significand
    • Human-intuitive (we naturally think of sign + magnitude)
    • Not used for integers in modern CPUs
*/

#include <iostream>
#include <bitset>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   SIGN MAGNITUDE REPRESENTATION                 ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- Sign-Magnitude 8-bit Examples ---" << endl;
    // Simulate sign-magnitude
    auto toSignMag = [](int x) -> unsigned char {
        if (x >= 0) return (unsigned char)x;
        return 0x80 | (unsigned char)(-x);  // set bit 7 + magnitude
    };

    for (int x : {5, -5, 0, 127, -127, -0}) {
        unsigned char sm = toSignMag(x);
        char sign = (sm & 0x80) ? '-' : '+';
        int mag = sm & 0x7F;
        cout << "  " << x << "\t= " << bitset<8>(sm)
             << " (sign=" << sign << ", magnitude=" << mag << ")" << endl;
    }

    cout << "\n--- Comparison Table (8-bit) ---" << endl;
    cout << "  Value\tSign-Mag\tOne's Comp\tTwo's Comp" << endl;
    for (int x : {5, -5, 0, 127, -127, -128}) {
        unsigned char sm = (x == -128) ? 0 : toSignMag(x);  // -128 doesn't fit sign-mag
        unsigned char oc = (x >= 0) ? x : ~((unsigned char)(-x));
        signed char tc = (signed char)x;
        if (x == -128)
            cout << "  " << x << "\tN/A\t\t\tN/A\t\t\t" << bitset<8>((unsigned char)tc) << endl;
        else
            cout << "  " << x << "\t" << bitset<8>(sm) << "\t" << bitset<8>(oc) << "\t" << bitset<8>((unsigned char)tc) << endl;
    }

    cout << "\n✅ Sign magnitude concept demonstrated!" << endl;
    return 0;
}

