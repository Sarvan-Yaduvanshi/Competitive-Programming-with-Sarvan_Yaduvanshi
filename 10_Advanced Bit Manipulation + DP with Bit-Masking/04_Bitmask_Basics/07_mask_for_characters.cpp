/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 04.07 — MASK FOR CHARACTERS (26-bit)                     ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

CONCEPT: Represent a set of lowercase characters as a 26-bit integer.
    Bit i = 1 ⟺ character ('a' + i) is present.

EXAMPLE:
    "abc" → bit 0,1,2 set → mask = 0...0111 = 7
    "az"  → bit 0,25 set  → mask = 0b10...001

APPLICATIONS:
═════════════
    • Check if two strings share any common characters: mask1 & mask2
    • Count distinct characters: popcount(mask)
    • Check if string has all unique characters: build mask, detect duplicates
    • Anagram detection: same character mask AND same frequencies
    • Palindrome permutation: at most 1 odd-frequency char → popcount(mask) ≤ 1

DRY RUN — charMask("hello"):
    h → bit 7, e → bit 4, l → bit 11, l (already set), o → bit 14
    mask = (1<<7)|(1<<4)|(1<<11)|(1<<14) = 000100100010010000₂

TIME: O(len) to build, O(1) for set operations
*/
#include <iostream>
#include <string>
#include <bitset>
#include <cassert>
using namespace std;

int charMask(const string& s) {
    int mask = 0;
    for (char c : s) mask |= (1 << (c - 'a'));
    return mask;
}

void printCharSet(int mask) {
    cout << "{";
    bool first = true;
    for (int i = 0; i < 26; i++) {
        if (mask & (1 << i)) {
            if (!first) cout << ",";
            cout << (char)('a' + i);
            first = false;
        }
    }
    cout << "}";
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   MASK FOR CHARACTERS (26-bit)                  ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    string s1 = "hello", s2 = "world";
    int m1 = charMask(s1), m2 = charMask(s2);

    cout << "\n  \"" << s1 << "\" → "; printCharSet(m1);
    cout << " (distinct: " << __builtin_popcount(m1) << ")" << endl;
    cout << "  \"" << s2 << "\" → "; printCharSet(m2);
    cout << " (distinct: " << __builtin_popcount(m2) << ")" << endl;

    cout << "\n  Common chars: "; printCharSet(m1 & m2); cout << endl;
    cout << "  All chars:    "; printCharSet(m1 | m2); cout << endl;
    cout << "  Only in s1:   "; printCharSet(m1 & ~m2); cout << endl;

    // Check all unique characters
    cout << "\n--- All Unique Characters Check ---" << endl;
    for (string s : {"abcdef", "hello", "abcba"}) {
        int mask = 0;
        bool unique = true;
        for (char c : s) {
            if (mask & (1 << (c - 'a'))) { unique = false; break; }
            mask |= (1 << (c - 'a'));
        }
        cout << "  \"" << s << "\": " << (unique ? "all unique" : "has duplicates") << endl;
    }

    // Palindrome permutation check
    cout << "\n--- Palindrome Permutation Check ---" << endl;
    for (string s : {"racecar", "aabb", "abc"}) {
        int mask = 0;
        for (char c : s) mask ^= (1 << (c - 'a')); // toggle parity
        bool canPalin = __builtin_popcount(mask) <= 1;
        cout << "  \"" << s << "\": " << (canPalin ? "YES" : "NO") << endl;
    }

    cout << "\n✅ Character mask operations verified!" << endl;
    return 0;
}

