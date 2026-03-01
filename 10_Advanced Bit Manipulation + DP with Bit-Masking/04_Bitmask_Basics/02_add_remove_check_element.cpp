/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 04.02 — ADD / REMOVE / CHECK ELEMENT IN BITMASK          ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

OPERATIONS (CRUD for bitmask sets):
════════════════════════════════════
    Add element i:      mask |= (1 << i)     // Set bit i to 1
    Remove element i:   mask &= ~(1 << i)    // Clear bit i to 0
    Check element i:    (mask >> i) & 1       // Returns 1 if present, 0 if not
    Toggle element i:   mask ^= (1 << i)     // Flip membership

DRY RUN — Starting with empty set, n=5 ({0,1,2,3,4}):
═══════════════════════════════════════════════════════
    mask = 0 (00000)
    Add 1:    mask |= (1<<1) → 00010 = {1}
    Add 3:    mask |= (1<<3) → 01010 = {1,3}
    Check 1:  (01010 >> 1) & 1 = 1 (present ✓)
    Check 2:  (01010 >> 2) & 1 = 0 (absent ✓)
    Remove 1: mask &= ~(1<<1) → 01000 = {3}
    Toggle 4: mask ^= (1<<4) → 11000 = {3,4}
    Toggle 3: mask ^= (1<<3) → 10000 = {4}

TIME: All operations O(1)
*/
#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   ADD / REMOVE / CHECK ELEMENT IN BITMASK       ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int mask = 0;
    int n = 5;

    cout << "\n--- Step-by-step Operations ---" << endl;

    // Add 1
    mask |= (1 << 1);
    cout << "  Add 1:    " << bitset<5>(mask) << " = {1}" << endl;

    // Add 3
    mask |= (1 << 3);
    cout << "  Add 3:    " << bitset<5>(mask) << " = {1,3}" << endl;

    // Check
    cout << "  Check 1:  " << ((mask >> 1) & 1) << " (present)" << endl;
    cout << "  Check 2:  " << ((mask >> 2) & 1) << " (absent)" << endl;

    // Remove 1
    mask &= ~(1 << 1);
    cout << "  Remove 1: " << bitset<5>(mask) << " = {3}" << endl;

    // Toggle 4
    mask ^= (1 << 4);
    cout << "  Toggle 4: " << bitset<5>(mask) << " = {3,4}" << endl;

    // Toggle 3
    mask ^= (1 << 3);
    cout << "  Toggle 3: " << bitset<5>(mask) << " = {4}" << endl;

    assert(mask == (1 << 4));
    assert(((mask >> 4) & 1) == 1);
    assert(((mask >> 3) & 1) == 0);

    // Bulk operations
    cout << "\n--- Bulk Operations ---" << endl;
    mask = 0;
    // Add multiple: {0, 2, 4}
    mask |= (1<<0) | (1<<2) | (1<<4);
    cout << "  Add {0,2,4}: " << bitset<5>(mask) << endl;

    // Remove multiple: {0, 4}
    mask &= ~((1<<0) | (1<<4));
    cout << "  Remove {0,4}: " << bitset<5>(mask) << " = {2}" << endl;

    cout << "\n✅ Bitmask CRUD operations verified!" << endl;
    return 0;
}

