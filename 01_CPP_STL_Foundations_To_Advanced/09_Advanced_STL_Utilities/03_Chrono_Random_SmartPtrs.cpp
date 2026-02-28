/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — CHRONO & RANDOM — Timing and Random for CP                  ║
║           04 — SMART POINTERS (basic overview)                             ║
║           From Zero to Grandmaster                                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ═══ CHRONO — Timing Code ═══
    cout << "═══ CHRONO — TIMING ═══\n\n";
    /*
     chrono is essential for:
       1. Benchmarking solutions locally
       2. Stress testing (run until time limit)
       3. Seeding random generators
    */

    auto start = chrono::steady_clock::now();

    // Some work to time
    long long sum = 0;
    for (int i = 0; i < 10000000; i++) sum += i;

    auto end = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    auto us = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "10^7 iterations: " << ms << " ms (" << us << " μs)\n";
    cout << "Sum (prevent optimize away): " << sum << "\n\n";

    // Time limit checking in stress test
    auto timeLimit = chrono::steady_clock::now() + chrono::seconds(2);
    int iterations = 0;
    while (chrono::steady_clock::now() < timeLimit) {
        iterations++;
        // Do some work
        volatile int x = iterations * 2;
        (void)x;
    }
    cout << "Iterations in 2 seconds: " << iterations << "\n\n";

    // ═══ RANDOM — mt19937 ═══
    cout << "═══ RANDOM — mt19937 ═══\n\n";
    /*
     mt19937 = Mersenne Twister random generator.
     MUCH better than rand()!

     Seed with chrono for different values each run.
     Seed with fixed value for reproducible results.
    */

    // Seed with time
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    // Random integers
    cout << "Random ints: ";
    for (int i = 0; i < 10; i++) cout << rng() % 100 << " ";
    cout << "\n";

    // Random in range [a, b]
    uniform_int_distribution<int> dist(1, 6);  // Dice roll
    cout << "Dice rolls: ";
    for (int i = 0; i < 10; i++) cout << dist(rng) << " ";
    cout << "\n";

    // Random doubles
    uniform_real_distribution<double> ddist(0.0, 1.0);
    cout << "Random doubles: ";
    for (int i = 0; i < 5; i++) cout << fixed << setprecision(3) << ddist(rng) << " ";
    cout << "\n";

    // Shuffle array
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    shuffle(v.begin(), v.end(), rng);
    cout << "Shuffled: ";
    for (int x : v) cout << x << " ";
    cout << "\n\n";

    // ═══ STRESS TESTING TEMPLATE ═══
    cout << "═══ STRESS TESTING TEMPLATE ═══\n\n";
    /*
     STRESS TEST = generate random inputs, compare brute force vs optimized.

     Template:
     while (true) {
         auto input = generate_random(rng);
         auto brute = brute_force(input);
         auto fast = optimized(input);
         if (brute != fast) {
             print(input);  // Found counterexample!
             break;
         }
     }
    */

    // Example: Test if custom sort matches std::sort
    auto bruteSort = [](vector<int> v) {
        for (int i = 0; i < (int)v.size(); i++)
            for (int j = i + 1; j < (int)v.size(); j++)
                if (v[i] > v[j]) swap(v[i], v[j]);
        return v;
    };

    bool allPassed = true;
    for (int test = 0; test < 1000; test++) {
        int n = rng() % 10 + 1;
        vector<int> arr(n);
        for (int& x : arr) x = rng() % 100;

        auto r1 = bruteSort(arr);
        auto r2 = arr;
        sort(r2.begin(), r2.end());

        if (r1 != r2) {
            cout << "MISMATCH on test " << test << "!\n";
            allPassed = false;
            break;
        }
    }
    if (allPassed) cout << "All 1000 stress tests passed! ✓\n\n";

    // ═══ SMART POINTERS (Brief Overview) ═══
    cout << "═══ SMART POINTERS ═══\n\n";
    /*
     Smart pointers manage memory automatically (RAII).
     Rarely needed in CP, but good to know.

     unique_ptr<T> — sole ownership, can't copy, can move
     shared_ptr<T> — shared ownership, reference counted
     weak_ptr<T>   — non-owning observer of shared_ptr
    */

    // unique_ptr
    auto up = make_unique<int>(42);
    cout << "unique_ptr: " << *up << "\n";
    // auto up2 = up;  // ERROR: can't copy!
    auto up2 = move(up);  // OK: transfer ownership
    cout << "After move: " << *up2 << "\n";

    // shared_ptr
    auto sp1 = make_shared<int>(100);
    auto sp2 = sp1;  // OK: shared ownership
    cout << "shared_ptr: " << *sp1 << ", count=" << sp1.use_count() << "\n";
    sp2.reset();
    cout << "After reset: count=" << sp1.use_count() << "\n\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. chrono for timing: steady_clock::now(), duration_cast\n";
    cout << "2. mt19937 for random: seed with chrono, use distributions\n";
    cout << "3. Stress test: generate random → compare brute vs fast\n";
    cout << "4. shuffle(v.begin(), v.end(), rng) for random permutation\n";
    cout << "5. Smart pointers: unique_ptr (sole), shared_ptr (shared)\n";
    cout << "6. In CP: chrono + mt19937 are essential, smart ptrs are rare\n";

    return 0;
}

