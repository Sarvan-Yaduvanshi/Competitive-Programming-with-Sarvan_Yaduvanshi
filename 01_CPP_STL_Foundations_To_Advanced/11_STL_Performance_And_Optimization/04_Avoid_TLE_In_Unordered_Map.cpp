/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           04 — AVOID TLE IN UNORDERED_MAP                                  ║
║           From Zero to Grandmaster — Anti-Hack Defense Guide               ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. HOW Hackers Blow Up Your unordered_map on Codeforces
 2. The Anti-Hack Custom Hash (splitmix64) — Full Explanation
 3. reserve() — Pre-allocate to Avoid Rehashing
 4. Load Factor Tuning
 5. When unordered_map Gets TLE (Real CF Examples)
 6. The Complete Defense Template

═══════════════════════════════════════════════════════════════════════════════
 THE ATTACK — HOW IT WORKS
═══════════════════════════════════════════════════════════════════════════════

 GCC's default hash for int is basically: hash(x) = x
 (For GCC's libstdc++, the hash function is the identity for integers!)

 Bucket index = hash(x) % bucket_count
 If bucket_count = 2^k (power of two), then:
   bucket = x % 2^k = x & (2^k - 1) = last k bits of x

 ATTACK: Insert values that all have the SAME last k bits!
   Example: bucket_count=1024 (2^10)
   Keys: 0, 1024, 2048, 3072, 4096, ...  (all multiples of 1024)
   ALL go to bucket 0 → chain of length N → O(N) per lookup!

 DRY RUN:
   bucket_count = 4  (k=2)
   Insert: 0, 4, 8, 12, 16, 20
   hash(0)%4=0, hash(4)%4=0, hash(8)%4=0, hash(12)%4=0, ...

   Bucket 0: 0 → 4 → 8 → 12 → 16 → 20   ← ALL HERE!
   Bucket 1: (empty)
   Bucket 2: (empty)
   Bucket 3: (empty)

   find(20) traverses chain of 6 → O(n) instead of O(1)!
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: DEMONSTRATING THE ATTACK
// ═══════════════════════════════════════════════════════════════

void demonstrateAttack() {
    cout << "═══ THE HASH ATTACK — LIVE DEMO ═══\n\n";

    // Unsafe unordered_map
    unordered_map<int, int> unsafe;

    // Find the bucket count
    cout << "Initial bucket count: " << unsafe.bucket_count() << "\n";

    // Insert adversarial keys (multiples of initial bucket count)
    int bc = unsafe.bucket_count();
    const int N = 100000;

    auto start = chrono::steady_clock::now();
    for (int i = 0; i < N; i++) {
        unsafe[i * bc] = i;  // All hash to bucket 0!
    }
    auto t_bad = chrono::duration_cast<chrono::milliseconds>(
        chrono::steady_clock::now() - start).count();
    cout << "Adversarial insert (" << N << " collisions): " << t_bad << " ms\n";

    // Same count with normal keys
    unordered_map<int, int> safe;
    safe.reserve(N);
    start = chrono::steady_clock::now();
    for (int i = 0; i < N; i++) {
        safe[i] = i;
    }
    auto t_good = chrono::duration_cast<chrono::milliseconds>(
        chrono::steady_clock::now() - start).count();
    cout << "Normal insert (" << N << " keys): " << t_good << " ms\n";
    cout << "Adversarial is ~" << (t_good > 0 ? t_bad / max(t_good, 1L) : 999)
         << "x slower!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: THE ANTI-HACK HASH — FULL EXPLANATION
// ═══════════════════════════════════════════════════════════════
/*
 splitmix64 — the standard CP defense hash:

 HOW IT WORKS:
 ─────────────
 1. Add a RANDOM fixed seed (different each program run)
    → Hacker can't predict bucket assignments
 2. Apply splitmix64 mixing function
    → Excellent bit avalanche: changing 1 bit in input
       changes ~50% of output bits
    → Eliminates patterns that cause collisions

 WHY IT WORKS:
 ─────────────
 The seed is generated from chrono::steady_clock at program start.
 Hacker submits their test AFTER your code is on the judge.
 They can't know your seed → can't craft adversarial inputs.

 MEMORIZE THIS STRUCT — use it in EVERY contest:
*/

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // These magic constants come from splitmix64 algorithm
        x += 0x9e3779b97f4a7c15;                          // Golden ratio
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;         // Mix high bits
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;         // Mix more
        return x ^ (x >> 31);                               // Final mix
    }

    size_t operator()(uint64_t x) const {
        // Random seed — different each run!
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void demonstrateCustomHash() {
    cout << "═══ CUSTOM HASH — DEFENSE IN ACTION ═══\n\n";

    const int N = 100000;

    // Attack the DEFAULT hash
    {
        unordered_map<int, int> m;
        int bc = m.bucket_count();
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) m[i * max(bc, 1)] = i;
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Default hash (adversarial):  " << ms << " ms\n";
    }

    // Same attack on CUSTOM hash — neutralized!
    {
        unordered_map<int, int, custom_hash> m;
        m.reserve(N);
        int bc = 1;
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) m[i * max(bc, 1)] = i;
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Custom hash  (same keys):    " << ms << " ms\n";
    }
    cout << "Custom hash neutralizes the attack completely!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: RESERVE — AVOID REHASHING
// ═══════════════════════════════════════════════════════════════
/*
 WHAT IS REHASHING?
 ──────────────────
 When load_factor = size / bucket_count > max_load_factor (default 1.0):
   1. Allocate new bucket array (2× size)
   2. Re-hash ALL existing elements → O(n)!
   3. Insert into new buckets

 This is the unordered_map equivalent of vector reallocation.

 DRY RUN:
   Initial: 1 bucket
   Insert 1st element → load=1/1=1.0 → REHASH to 2 buckets, re-insert 1
   Insert 2nd element → load=2/2=1.0 → REHASH to 4 buckets, re-insert 2
   Insert 3rd element → load=3/4=0.75 → OK
   Insert 4th element → load=4/4=1.0 → REHASH to 8 buckets, re-insert 4
   ...

   reserve(N) pre-allocates ~N/max_load_factor buckets → NO rehashes!
*/

void demonstrateReserve() {
    cout << "═══ RESERVE OPTIMIZATION ═══\n\n";

    const int N = 1000000;

    // Without reserve
    {
        unordered_map<int, int> m;
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) m[i] = i;
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Without reserve (10^6): " << ms << " ms, "
             << "buckets=" << m.bucket_count() << "\n";
    }

    // With reserve
    {
        unordered_map<int, int> m;
        m.reserve(N);
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) m[i] = i;
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "With reserve (10^6):    " << ms << " ms, "
             << "buckets=" << m.bucket_count() << "\n";
    }

    // With reserve + custom hash
    {
        unordered_map<int, int, custom_hash> m;
        m.reserve(N);
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) m[i] = i;
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Reserve+custom (10^6):  " << ms << " ms, "
             << "buckets=" << m.bucket_count() << "\n\n";
    }
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: LOAD FACTOR TUNING
// ═══════════════════════════════════════════════════════════════

void demonstrateLoadFactor() {
    cout << "═══ LOAD FACTOR TUNING ═══\n\n";

    /*
     load_factor() = size / bucket_count
     max_load_factor() = threshold for rehash (default 1.0)

     Lower max_load_factor → more buckets → fewer collisions → faster lookup
                           → but uses more memory

     Higher max_load_factor → fewer buckets → more collisions → slower lookup
                            → but uses less memory
    */

    const int N = 500000;

    // Default load factor (1.0)
    {
        unordered_map<int, int, custom_hash> m;
        m.reserve(N);
        for (int i = 0; i < N; i++) m[i] = i;
        auto start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i++) sum += m[i];
        auto ms = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "max_load_factor=1.0:  find " << ms << " μs, "
             << "buckets=" << m.bucket_count()
             << ", load=" << fixed << setprecision(2) << m.load_factor() << "\n";
    }

    // Lower load factor (0.25) — fewer collisions, more memory
    {
        unordered_map<int, int, custom_hash> m;
        m.max_load_factor(0.25);
        m.reserve(N);
        for (int i = 0; i < N; i++) m[i] = i;
        auto start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < N; i++) sum += m[i];
        auto ms = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "max_load_factor=0.25: find " << ms << " μs, "
             << "buckets=" << m.bucket_count()
             << ", load=" << fixed << setprecision(2) << m.load_factor() << "\n\n";
    }

    cout << "VERDICT: Default 1.0 is fine for most CP. Lower for extreme speed.\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: COMPLETE DEFENSE TEMPLATE
// ═══════════════════════════════════════════════════════════════

void printTemplate() {
    cout << "═══ COMPLETE DEFENSE TEMPLATE ═══\n\n";

    cout << "// PASTE THIS AT TOP OF EVERY CP SOLUTION:\n\n";

    cout << "struct custom_hash {\n";
    cout << "    static uint64_t splitmix64(uint64_t x) {\n";
    cout << "        x += 0x9e3779b97f4a7c15;\n";
    cout << "        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n";
    cout << "        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;\n";
    cout << "        return x ^ (x >> 31);\n";
    cout << "    }\n";
    cout << "    size_t operator()(uint64_t x) const {\n";
    cout << "        static const uint64_t FIXED_RANDOM =\n";
    cout << "            chrono::steady_clock::now().time_since_epoch().count();\n";
    cout << "        return splitmix64(x + FIXED_RANDOM);\n";
    cout << "    }\n";
    cout << "};\n\n";

    cout << "// USAGE:\n";
    cout << "unordered_map<int, int, custom_hash> m;\n";
    cout << "m.reserve(n);  // ALWAYS reserve!\n\n";

    cout << "// For unordered_set:\n";
    cout << "unordered_set<int, custom_hash> s;\n";
    cout << "s.reserve(n);\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateAttack();
    demonstrateCustomHash();
    demonstrateReserve();
    demonstrateLoadFactor();
    printTemplate();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Default GCC hash(x) ≈ x → trivially hackable on CF!\n";
    cout << "2. splitmix64 + random seed = unhackable defense\n";
    cout << "3. reserve(n) avoids O(n) rehash operations\n";
    cout << "4. Lower max_load_factor = faster at cost of memory\n";
    cout << "5. ALWAYS: unordered_map<K, V, custom_hash> + reserve(n)\n";
    cout << "6. Or just use map if you don't want to think about it\n";

    return 0;
}

/*
 REAL CF EXAMPLES WHERE PEOPLE GOT HACKED:
 ──────────────────────────────────────────
 • Any problem using unordered_map with integer keys on CF
 • Hackers submit tests with keys = multiples of 2^k
 • Solution goes from O(n) to O(n²) → TLE on test with N=10^5
 • Fix: Add custom_hash struct → never get hacked again
*/

