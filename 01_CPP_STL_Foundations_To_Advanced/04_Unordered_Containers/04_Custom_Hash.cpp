/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           04 — CUSTOM HASH FOR COMPETITIVE PROGRAMMING                     ║
║           From Zero to Grandmaster — Anti-Hack Defense                     ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Why Custom Hash? (Anti-hack attacks on Codeforces)
 2. Splitmix64 Anti-Hack Hash (THE GM template)
 3. Hash for pair<int,int>
 4. Hash for vector<int>
 5. Hash for custom structs

CRITICAL FOR CP:
────────────────
  The default hash for integers on GCC is basically the IDENTITY function!
  Hackers on Codeforces can craft inputs that cause ALL elements to collide
  in the same bucket → O(n²) instead of O(n) → TLE!

  SOLUTION: Use a custom hash that's hard to attack.
  The splitmix64 hash is the GOLD STANDARD for CP.
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: THE SPLITMIX64 ANTI-HACK HASH (MEMORIZE THIS!)
// ═══════════════════════════════════════════════════════════════
/*
 This hash:
 1. Uses a fixed random seed (changes each run → can't be predicted)
 2. Applies splitmix64 mixing (excellent distribution)
 3. Resists Codeforces anti-hash attacks

 USE THIS IN EVERY CP SOLUTION USING unordered_map/set!
*/

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// Usage: unordered_map<int, int, custom_hash> safe_map;
// Usage: unordered_set<int, custom_hash> safe_set;

void demonstrateAntiHack() {
    cout << "═══ ANTI-HACK HASH ═══\n\n";

    // Unsafe (default hash)
    unordered_map<int, int> unsafe_map;

    // Safe (custom hash)
    unordered_map<int, int, custom_hash> safe_map;

    // Insert same elements into both
    const int N = 100000;

    {
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) safe_map[i] = i;
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Safe map (10^5):   " << ms << " ms\n";
    }
    {
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) unsafe_map[i] = i;
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Unsafe map (10^5): " << ms << " ms\n";
    }
    cout << "(Both fast with random data, but unsafe fails with adversarial input)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: HASH FOR pair<int,int>
// ═══════════════════════════════════════════════════════════════
/*
 std::hash doesn't support pairs by default!
 You need a custom hash to use pair as unordered_map key.
*/

struct pair_hash {
    size_t operator()(const pair<int, int>& p) const {
        auto h1 = custom_hash{}(p.first);
        auto h2 = custom_hash{}(p.second);
        return h1 ^ (h2 << 32);  // Combine hashes
    }
};

void demonstratePairHash() {
    cout << "═══ HASH FOR PAIRS ═══\n\n";

    // Count frequency of coordinate pairs
    unordered_map<pair<int, int>, int, pair_hash> freq;
    vector<pair<int, int>> points = {{1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}, {1, 2}};

    for (auto& p : points) freq[p]++;

    cout << "Point frequencies:\n";
    for (auto& [p, cnt] : freq) {
        cout << "  (" << p.first << "," << p.second << ") → " << cnt << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: HASH FOR vector<int>
// ═══════════════════════════════════════════════════════════════

struct vector_hash {
    size_t operator()(const vector<int>& v) const {
        size_t seed = v.size();
        for (auto& x : v) {
            seed ^= custom_hash{}(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

void demonstrateVectorHash() {
    cout << "═══ HASH FOR VECTORS ═══\n\n";

    // Group arrays by sorted version (like group anagrams)
    unordered_map<vector<int>, vector<vector<int>>, vector_hash> groups;

    vector<vector<int>> arrays = {
        {1, 2, 3}, {3, 2, 1}, {4, 5, 6}, {2, 1, 3}, {6, 5, 4}
    };

    for (auto& arr : arrays) {
        vector<int> key = arr;
        sort(key.begin(), key.end());
        groups[key].push_back(arr);
    }

    cout << "Groups by sorted version:\n";
    for (auto& [key, group] : groups) {
        cout << "  Key [";
        for (int x : key) cout << x << " ";
        cout << "]: ";
        for (auto& arr : group) {
            cout << "[";
            for (int x : arr) cout << x;
            cout << "] ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: HASH FOR CUSTOM STRUCTS
// ═══════════════════════════════════════════════════════════════

struct Point {
    int x, y, z;
    bool operator==(const Point& o) const {
        return x == o.x && y == o.y && z == o.z;
    }
};

struct PointHash {
    size_t operator()(const Point& p) const {
        size_t h = 0;
        h ^= custom_hash{}(p.x) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= custom_hash{}(p.y) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= custom_hash{}(p.z) + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }
};

void demonstrateStructHash() {
    cout << "═══ HASH FOR CUSTOM STRUCTS ═══\n\n";

    unordered_map<Point, string, PointHash> pointNames;
    pointNames[{0, 0, 0}] = "origin";
    pointNames[{1, 0, 0}] = "x-axis";
    pointNames[{0, 1, 0}] = "y-axis";

    cout << "Point names:\n";
    for (auto& [p, name] : pointNames) {
        cout << "  (" << p.x << "," << p.y << "," << p.z << ") = " << name << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: THE COMPLETE SAFE TEMPLATE
// ═══════════════════════════════════════════════════════════════

void demonstrateTemplate() {
    cout << "═══ COMPLETE SAFE TEMPLATE ═══\n\n";

    cout << "// Paste this at the top of your CP solutions:\n\n";
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
    cout << "// Usage: unordered_map<int, int, custom_hash> m;\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateAntiHack();
    demonstratePairHash();
    demonstrateVectorHash();
    demonstrateStructHash();
    demonstrateTemplate();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Default hash is HACKABLE on Codeforces!\n";
    cout << "2. Use splitmix64 custom hash for safety\n";
    cout << "3. pair/vector/struct need custom hash functors\n";
    cout << "4. Combine hashes with XOR + golden ratio constant\n";
    cout << "5. MEMORIZE the custom_hash template — use in every contest\n";

    return 0;
}

