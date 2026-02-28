/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — HASHING FUNDAMENTALS                                        ║
║           From Zero to Grandmaster — How Hash Tables Work                  ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What is a Hash Function?
 2. How Hash Tables Work (Chaining vs Open Addressing)
 3. std::hash and Built-in Hashing
 4. Collision Resolution
 5. Load Factor and Rehashing
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: WHAT IS HASHING?
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A hash function maps data of arbitrary size to a fixed-size value.
   hash("hello") → 2348762  (some integer)
   hash("world") → 9847231
   hash(42)      → 42       (identity for small ints)

 PROPERTIES OF GOOD HASH:
   1. Deterministic: same input → always same output
   2. Uniform: distributes values evenly across buckets
   3. Fast: O(1) computation
   4. Low collisions: different inputs → different outputs (ideally)

 HASH TABLE STRUCTURE:
   bucket[hash(key) % num_buckets] → chain of (key, value) pairs

   Example: 5 buckets, insert keys 3, 8, 13, 18, 23
   hash(k) = k % 5
   bucket[0]: ∅
   bucket[1]: ∅
   bucket[2]: ∅
   bucket[3]: 3 → 8 → 13 → 18 → 23  ← ALL COLLIDE! O(n)!
   bucket[4]: ∅

   This is why a GOOD hash function matters!
*/

void demonstrateHashing() {
    cout << "═══ HASHING FUNDAMENTALS ═══\n\n";

    // std::hash for built-in types
    hash<int> intHash;
    hash<string> strHash;
    hash<double> dblHash;

    cout << "hash(42) = " << intHash(42) << "\n";
    cout << "hash(43) = " << intHash(43) << "\n";
    cout << "hash(\"hello\") = " << strHash("hello") << "\n";
    cout << "hash(\"world\") = " << strHash("world") << "\n";
    cout << "hash(3.14) = " << dblHash(3.14) << "\n\n";

    // Bucket distribution demo
    const int NUM_BUCKETS = 10;
    vector<int> data = {5, 15, 25, 35, 3, 13, 23, 33, 7, 17};

    vector<vector<int>> buckets(NUM_BUCKETS);
    for (int x : data) {
        buckets[x % NUM_BUCKETS].push_back(x);
    }

    cout << "Simple hash (x % 10), " << data.size() << " elements:\n";
    for (int i = 0; i < NUM_BUCKETS; i++) {
        cout << "  bucket[" << i << "]: ";
        for (int x : buckets[i]) cout << x << " ";
        if (buckets[i].empty()) cout << "∅";
        cout << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: CHAINING vs OPEN ADDRESSING
// ═══════════════════════════════════════════════════════════════
/*
 CHAINING (what C++ unordered containers use):
 ──────────────────────────────────────────────
 Each bucket is a linked list. Collisions → append to list.

 bucket[0]: ∅
 bucket[1]: 11 → 21 → 31
 bucket[2]: 2
 bucket[3]: 3 → 13

 Pros: Simple, no clustering
 Cons: Extra memory for pointers, cache-unfriendly

 OPEN ADDRESSING (Python dicts use this):
 ────────────────────────────────────────
 On collision, probe to next empty slot.
 Linear probing: try bucket+1, bucket+2, ...

 Pros: Cache-friendly, no extra pointers
 Cons: Clustering, harder deletion

 FOR CP: You don't choose — C++ uses chaining internally.
         Just understand WHY collisions cause O(n) worst case.
*/

// ═══════════════════════════════════════════════════════════════
// SECTION 3: LOAD FACTOR AND REHASHING
// ═══════════════════════════════════════════════════════════════

void demonstrateLoadFactor() {
    cout << "═══ LOAD FACTOR & REHASHING ═══\n\n";

    /*
     Load Factor = num_elements / num_buckets
     When load factor > max_load_factor (default 1.0),
     the table REHASHES: doubles buckets, re-inserts everything → O(n)!
    */

    unordered_set<int> us;
    cout << "Initial: buckets=" << us.bucket_count()
         << ", load=" << us.load_factor() << "\n";

    for (int i = 0; i < 20; i++) {
        us.insert(i);
        if (i % 5 == 4) {
            cout << "After " << (i + 1) << " inserts: buckets="
                 << us.bucket_count() << ", load="
                 << fixed << setprecision(2) << us.load_factor() << "\n";
        }
    }

    cout << "\nWith reserve(100):\n";
    unordered_set<int> us2;
    us2.reserve(100);
    cout << "  buckets=" << us2.bucket_count() << " (no rehash needed for 100 elements)\n\n";

    // Max load factor can be adjusted
    unordered_set<int> us3;
    us3.max_load_factor(0.5);  // More buckets, fewer collisions
    cout << "Custom max_load_factor=0.5: fewer collisions but more memory\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: SIMPLE HASH TABLE IMPLEMENTATION
// ═══════════════════════════════════════════════════════════════

class SimpleHashSet {
    static const int BUCKETS = 1009;  // Prime number!
    vector<list<int>> table;

    int hash(int key) { return ((key % BUCKETS) + BUCKETS) % BUCKETS; }

public:
    SimpleHashSet() : table(BUCKETS) {}

    void insert(int key) {
        int h = hash(key);
        for (int x : table[h]) if (x == key) return;
        table[h].push_back(key);
    }

    bool find(int key) {
        int h = hash(key);
        for (int x : table[h]) if (x == key) return true;
        return false;
    }

    void erase(int key) {
        int h = hash(key);
        table[h].remove(key);
    }
};

void demonstrateSimpleHashSet() {
    cout << "═══ SIMPLE HASH TABLE IMPLEMENTATION ═══\n\n";

    SimpleHashSet hs;
    hs.insert(10);
    hs.insert(20);
    hs.insert(1019);  // Same bucket as 10! (1019 % 1009 = 10)

    cout << "find(10) = " << hs.find(10) << "\n";
    cout << "find(20) = " << hs.find(20) << "\n";
    cout << "find(30) = " << hs.find(30) << "\n";

    hs.erase(10);
    cout << "After erase(10), find(10) = " << hs.find(10) << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateHashing();
    demonstrateLoadFactor();
    demonstrateSimpleHashSet();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Hash function maps keys to bucket indices\n";
    cout << "2. C++ uses chaining (linked lists in buckets)\n";
    cout << "3. Load factor > 1.0 triggers rehash (costly!)\n";
    cout << "4. reserve() avoids rehashing — always use it!\n";
    cout << "5. Collisions cause O(n) worst case — use custom hash\n";
    cout << "6. Prime bucket counts reduce collision patterns\n";

    return 0;
}

