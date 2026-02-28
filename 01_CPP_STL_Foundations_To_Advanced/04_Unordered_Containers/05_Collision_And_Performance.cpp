/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           05 — COLLISION AND PERFORMANCE PITFALLS                          ║
║           From Zero to Grandmaster — Avoiding TLE                          ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

  When to use unordered_map vs map:
  ┌──────────────────────┬──────────────────┬──────────────────┐
  │ Scenario             │ Use              │ Reason           │
  ├──────────────────────┼──────────────────┼──────────────────┤
  │ Pure lookup O(1)     │ unordered_map    │ Fastest avg      │
  │ Need sorted keys     │ map              │ O(log n) ordered │
  │ Need lower_bound     │ map              │ Not in unordered │
  │ CF hackable problem  │ map or custom_h  │ Safety           │
  │ Small N (< 1000)     │ Either           │ Doesn't matter   │
  │ Stress testing       │ unordered_map    │ Faster           │
  │ String keys          │ unordered_map    │ O(|s|) vs O(|s|logn) │
  └──────────────────────┴──────────────────┴──────────────────┘

  GM VERDICT: Use unordered_map + custom_hash for max speed & safety.
              Use map when you need order or lower_bound.
*/

#include <bits/stdc++.h>
using namespace std;

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "═══ PERFORMANCE COMPARISON ═══\n\n";

    const int N = 1000000;

    // Benchmark: map vs unordered_map vs unordered_map+custom_hash
    {
        auto start = chrono::steady_clock::now();
        map<int, int> m;
        for (int i = 0; i < N; i++) m[i] = i;
        for (int i = 0; i < N; i++) m.find(i);
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "map (10^6 insert+find):                  " << ms << " ms\n";
    }
    {
        auto start = chrono::steady_clock::now();
        unordered_map<int, int> m;
        m.reserve(N);
        for (int i = 0; i < N; i++) m[i] = i;
        for (int i = 0; i < N; i++) m.find(i);
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "unordered_map+reserve (10^6):             " << ms << " ms\n";
    }
    {
        auto start = chrono::steady_clock::now();
        unordered_map<int, int, custom_hash> m;
        m.reserve(N);
        for (int i = 0; i < N; i++) m[i] = i;
        for (int i = 0; i < N; i++) m.find(i);
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "unordered_map+custom_hash+reserve (10^6): " << ms << " ms\n";
    }
    cout << "\n";

    // Demonstrate adversarial case
    cout << "═══ ADVERSARIAL INPUT DEMO ═══\n\n";
    cout << "On GCC, hash(x) ≈ x for small integers.\n";
    cout << "If all keys hash to same bucket → O(n) per operation!\n\n";

    // Keys that collide in a 1024-bucket table
    // Multiples of bucket_count cause collisions
    {
        unordered_map<int, int> m;
        int bucket_count = m.bucket_count();
        cout << "Default bucket count: " << bucket_count << "\n";

        auto start = chrono::steady_clock::now();
        // Insert multiples of bucket_count (all same bucket!)
        for (int i = 0; i < 50000; i++) {
            m[i * bucket_count] = i;
        }
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Adversarial insert (50K collisions): " << ms << " ms\n";
    }
    {
        unordered_map<int, int, custom_hash> m;
        auto start = chrono::steady_clock::now();
        int bc = 1;  // Doesn't matter with custom hash
        for (int i = 0; i < 50000; i++) {
            m[i * bc] = i;
        }
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Custom hash (same keys, 50K):         " << ms << " ms\n";
    }
    cout << "\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. unordered_map is 2-5x faster than map on average\n";
    cout << "2. Without custom hash, adversarial inputs cause O(n²)\n";
    cout << "3. ALWAYS reserve() + custom_hash for safety\n";
    cout << "4. Use map when you need: order, lower_bound, or absolute safety\n";
    cout << "5. For string keys, unordered is especially beneficial\n";

    return 0;
}

