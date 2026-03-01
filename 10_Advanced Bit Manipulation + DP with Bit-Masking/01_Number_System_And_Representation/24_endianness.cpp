/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.24 — ENDIANNESS (Little vs Big Endian)                ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

DEFINITION:
═══════════
Endianness = the order in which bytes are stored in memory.

Consider 32-bit integer: 0x12345678

BIG ENDIAN (Network byte order):
═════════════════════════════════
    Address:  [0]   [1]   [2]   [3]
    Content:  0x12  0x34  0x56  0x78
    MSB first (most significant byte at lowest address)
    Used by: Network protocols, SPARC, some ARM

LITTLE ENDIAN:
══════════════
    Address:  [0]   [1]   [2]   [3]
    Content:  0x78  0x56  0x34  0x12
    LSB first (least significant byte at lowest address)
    Used by: x86, x86-64, most modern CPUs

WHY IT MATTERS:
═══════════════
    • Network programming: Must convert between host and network order
    • Binary file I/O: Different architectures may read differently
    • Bit manipulation: Usually doesn't matter (CPU handles it)
    • In CP: Almost never matters (same machine reads/writes)

MNEMONIC:
═════════
    Big Endian = Big end first (most significant)
    Little Endian = Little end first (least significant)
    Named from Gulliver's Travels (which end of an egg to crack!)
*/

#include <iostream>
#include <cstring>
#include <cstdint>
using namespace std;

bool isLittleEndian() {
    uint32_t x = 1;
    // If first byte is 1, then LSB is at lowest address → little endian
    return *((uint8_t*)&x) == 1;
}

void showByteOrder(uint32_t val) {
    uint8_t* bytes = (uint8_t*)&val;
    cout << "  Value: 0x" << hex << val << dec << endl;
    cout << "  Memory layout: ";
    for (int i = 0; i < 4; i++) {
        cout << "[" << i << "]=0x" << hex << (int)bytes[i] << dec << " ";
    }
    cout << endl;
}

// Swap endianness
uint32_t swapEndian32(uint32_t x) {
    return ((x >> 24) & 0xFF) |
           ((x >> 8)  & 0xFF00) |
           ((x << 8)  & 0xFF0000) |
           ((x << 24) & 0xFF000000);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   ENDIANNESS — LITTLE vs BIG ENDIAN             ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- System Endianness ---" << endl;
    cout << "  This system is: " << (isLittleEndian() ? "LITTLE ENDIAN" : "BIG ENDIAN") << endl;

    cout << "\n--- Byte Order of 0x12345678 ---" << endl;
    showByteOrder(0x12345678);
    if (isLittleEndian()) {
        cout << "  (LSB 0x78 is at lowest address → Little Endian)" << endl;
    }

    cout << "\n--- Endian Swap ---" << endl;
    uint32_t original = 0x12345678;
    uint32_t swapped = swapEndian32(original);
    cout << "  Original: 0x" << hex << original << endl;
    cout << "  Swapped:  0x" << swapped << dec << endl;
    showByteOrder(swapped);

    cout << "\n--- Practical: Does Endianness Affect Bit Ops? ---" << endl;
    uint32_t x = 0x12345678;
    cout << "  x & 0xFF      = 0x" << hex << (x & 0xFF) << " (always gets LSB byte)" << endl;
    cout << "  x >> 24       = 0x" << (x >> 24) << " (always gets MSB byte)" << endl;
    cout << "  Bit operations are ENDIAN-INDEPENDENT!" << dec << endl;

    cout << "\n✅ Endianness concepts demonstrated!" << endl;
    return 0;
}

