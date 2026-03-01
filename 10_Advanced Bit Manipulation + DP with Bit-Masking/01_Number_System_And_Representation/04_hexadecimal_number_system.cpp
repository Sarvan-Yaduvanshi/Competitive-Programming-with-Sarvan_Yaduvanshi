/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.04 — HEXADECIMAL NUMBER SYSTEM                        ║
║           Bit Manipulation — Number System Foundations                      ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

MATHEMATICAL DEFINITION:
════════════════════════
The Hexadecimal Number System (Base-16) uses 16 distinct symbols:
    H = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F}
    where A=10, B=11, C=12, D=13, E=14, F=15

Any hex number N with digits h_(k-1), ..., h_1, h_0 is:

    N = Σ (i = 0 to k-1) [ h_i × 16^i ]

EXAMPLE — POSITIONAL NOTATION:
══════════════════════════════
    Hex: 2F3₁₆

    Position:  2         F=15      3
    Weight:    16²=256   16¹=16    16⁰=1

    N = 2×256 + 15×16 + 3×1
      = 512   + 240   + 3
      = 755₁₀

DRY RUN — HEX 1A3F₁₆ TO DECIMAL:
══════════════════════════════════
    h₃=1, h₂=A=10, h₁=3, h₀=F=15

    N = 1×16³ + 10×16² + 3×16¹ + 15×16⁰
      = 4096  + 2560   + 48    + 15
      = 6719₁₀ ✓

WHY HEXADECIMAL MATTERS:
════════════════════════
    • Each hex digit = exactly 4 binary bits (nibble)
    • Compact representation of binary data
    • Memory addresses: 0x7FFE1234
    • Colors in RGB: #FF5733 = R:255 G:87 B:51
    • C/C++ hex literal prefix: 0x (e.g., 0x2F3 = 755₁₀)

NIBBLE MAPPING TABLE:
═════════════════════
    Hex  Binary   Decimal
    0    0000     0
    1    0001     1
    2    0010     2
    3    0011     3
    4    0100     4
    5    0101     5
    6    0110     6
    7    0111     7
    8    1000     8
    9    1001     9
    A    1010     10
    B    1011     11
    C    1100     12
    D    1101     13
    E    1110     14
    F    1111     15

PROPERTIES:
═══════════
    • Base (Radix) = 16 = 2⁴
    • k-digit range: [0, 16^k - 1]
    • 2 hex digits = 1 byte (0x00 to 0xFF = 0 to 255)
    • 8 hex digits = 32 bits, 16 hex digits = 64 bits
*/

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <cassert>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// Helper: Convert hex char to value
// ═══════════════════════════════════════════════════════════════
int hexCharToValue(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

char valueToHexChar(int v) {
    if (v < 10) return '0' + v;
    return 'A' + v - 10;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 1: Hex string to decimal
// Formula: N = Σ h_i × 16^i
// ═══════════════════════════════════════════════════════════════
long long hexToDecimal(const string& hex) {
    long long result = 0;
    for (char c : hex) {
        result = result * 16 + hexCharToValue(c);
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 2: Decimal to hex string
// Method: Repeated division by 16
// ═══════════════════════════════════════════════════════════════
string decimalToHex(long long n) {
    if (n == 0) return "0";
    string result = "";
    while (n > 0) {
        result = valueToHexChar(n % 16) + result;
        n /= 16;
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 3: Hex breakdown
// ═══════════════════════════════════════════════════════════════
void displayHexBreakdown(const string& hex) {
    int k = hex.size();
    cout << "Hex " << hex << "₁₆ breakdown:" << endl;

    long long sum = 0;
    for (int i = 0; i < k; i++) {
        int pos = k - 1 - i;
        int val = hexCharToValue(hex[i]);
        long long contribution = val * (long long)pow(16, pos);
        cout << "  h_" << pos << " = " << hex[i] << "=" << val
             << " × 16^" << pos << " = " << contribution << endl;
        sum += contribution;
    }
    cout << "  Total = " << sum << "₁₀" << endl;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 4: RGB Color parsing
// ═══════════════════════════════════════════════════════════════
void parseRGBColor(const string& hexColor) {
    // Format: RRGGBB (6 hex digits)
    int r = hexCharToValue(hexColor[0]) * 16 + hexCharToValue(hexColor[1]);
    int g = hexCharToValue(hexColor[2]) * 16 + hexCharToValue(hexColor[3]);
    int b = hexCharToValue(hexColor[4]) * 16 + hexCharToValue(hexColor[5]);

    cout << "Color #" << hexColor << " = RGB(" << r << ", " << g << ", " << b << ")" << endl;
}

// ═══════════════════════════════════════════════════════════════
// FUNCTION 5: Using C++ stream for hex I/O
// ═══════════════════════════════════════════════════════════════
void cppHexDemo() {
    int n = 755;
    cout << "Decimal " << n << " in hex: " << hex << uppercase << n << dec << endl;
    cout << "Using setfill: 0x" << hex << setfill('0') << setw(8) << n << dec << endl;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   HEXADECIMAL NUMBER SYSTEM — DEMONSTRATIONS    ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Demo 1: Hex to Decimal
    cout << "\n--- Hex to Decimal ---" << endl;
    cout << "2F3₁₆ = " << hexToDecimal("2F3") << "₁₀" << endl;       // 755
    cout << "1A3F₁₆ = " << hexToDecimal("1A3F") << "₁₀" << endl;     // 6719
    cout << "FF₁₆ = " << hexToDecimal("FF") << "₁₀" << endl;          // 255

    // Demo 2: Decimal to Hex
    cout << "\n--- Decimal to Hex ---" << endl;
    cout << "755₁₀ = " << decimalToHex(755) << "₁₆" << endl;
    cout << "6719₁₀ = " << decimalToHex(6719) << "₁₆" << endl;
    cout << "255₁₀ = " << decimalToHex(255) << "₁₆" << endl;

    // Demo 3: Breakdown
    cout << "\n--- Place Value Breakdown ---" << endl;
    displayHexBreakdown("2F3");
    cout << endl;
    displayHexBreakdown("1A3F");

    // Demo 4: RGB Colors
    cout << "\n--- RGB Color Parsing ---" << endl;
    parseRGBColor("FF5733");
    parseRGBColor("00FF00");
    parseRGBColor("0000FF");

    // Demo 5: C++ hex I/O
    cout << "\n--- C++ Hex I/O ---" << endl;
    cppHexDemo();

    // Assertions
    assert(hexToDecimal("2F3") == 755);
    assert(hexToDecimal("1A3F") == 6719);
    assert(hexToDecimal("FF") == 255);
    assert(decimalToHex(755) == "2F3");
    assert(decimalToHex(255) == "FF");

    cout << "\n✅ All hexadecimal number system concepts verified!" << endl;
    return 0;
}

