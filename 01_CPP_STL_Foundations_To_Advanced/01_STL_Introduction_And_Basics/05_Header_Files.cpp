/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           05 — HEADER FILES IN C++ FOR CP                                  ║
║           From Zero to Grandmaster — Smart Includes                        ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Individual Header Files
 2. bits/stdc++.h — The CP Secret Weapon
 3. Pragma Optimizations
 4. Precompiled Headers
 5. When NOT to Use bits/stdc++.h

CORE IDEA:
──────────
  In competitive programming, we use #include <bits/stdc++.h>
  to include EVERYTHING. In production code, use individual headers.

GM TIP: bits/stdc++.h is GCC-only. It works on Codeforces, AtCoder,
        CSES, and most judges. It does NOT work on MSVC (Visual Studio).
*/

// ═══════════════════════════════════════════════════════════════
// METHOD 1: Individual Headers (Production Style)
// ═══════════════════════════════════════════════════════════════
/*
 COMMON HEADERS:
 ───────────────
 #include <iostream>        // cin, cout
 #include <vector>          // vector
 #include <algorithm>       // sort, find, binary_search
 #include <string>          // string
 #include <set>             // set, multiset
 #include <map>             // map, multimap
 #include <unordered_set>   // unordered_set
 #include <unordered_map>   // unordered_map
 #include <queue>           // queue, priority_queue
 #include <stack>           // stack
 #include <deque>           // deque
 #include <list>            // list
 #include <numeric>         // accumulate, iota, gcd
 #include <cmath>           // sqrt, pow, abs, ceil, floor
 #include <climits>         // INT_MAX, INT_MIN, LLONG_MAX
 #include <cassert>         // assert
 #include <bitset>          // bitset
 #include <tuple>           // tuple, tie
 #include <functional>      // greater<>, function<>
 #include <array>           // array
 #include <chrono>          // timing
 #include <random>          // mt19937, random
 #include <iomanip>         // setprecision, fixed
*/

// ═══════════════════════════════════════════════════════════════
// METHOD 2: bits/stdc++.h — Include EVERYTHING (CP Style)
// ═══════════════════════════════════════════════════════════════
/*
 #include <bits/stdc++.h>

 This single header includes ALL C++ standard library headers.

 PROS:
   ✓ One line instead of 20+ includes
   ✓ Never forget a header
   ✓ Saves precious contest time

 CONS:
   ✗ GCC-only (not standard C++)
   ✗ Slower compilation (includes everything)
   ✗ Not portable to MSVC
   ✗ Bad practice for production code

 VERDICT: USE IT for CP. Period. Time saved > compilation overhead.
*/

#include <bits/stdc++.h>  // THE CP WAY
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 3: PRAGMA OPTIMIZATIONS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Pragmas are compiler directives that optimize your code.
 They can make the difference between AC and TLE!

 COMMON PRAGMAS FOR CP:

 #pragma GCC optimize("O2")
   → Standard optimization level (safe, always use)

 #pragma GCC optimize("O3")
   → Aggressive optimization (faster, very rare issues)

 #pragma GCC optimize("Ofast")
   → Maximum speed (may break strict floating-point)
   → Enables -ffast-math (dangerous for precision problems!)

 #pragma GCC optimize("unroll-loops")
   → Unrolls loops (good for tight loops)

 #pragma GCC target("avx2,bmi,bmi2,popcnt")
   → Enable SIMD instructions (hardware-level speedup)
   → __builtin_popcount becomes a single CPU instruction!

 GM TEMPLATE:
   #pragma GCC optimize("O2,unroll-loops")
   #pragma GCC target("avx2,bmi,bmi2,popcnt")
   #include <bits/stdc++.h>
   using namespace std;

 WARNING: Don't use Ofast for problems requiring exact floating-point!
*/

// ═══════════════════════════════════════════════════════════════
// SECTION 4: THE COMPLETE CP TEMPLATE
// ═══════════════════════════════════════════════════════════════

/*
 THE GRANDMASTER TEMPLATE:
 ─────────────────────────

 #pragma GCC optimize("O2,unroll-loops")
 #pragma GCC target("avx2,bmi,bmi2,popcnt")
 #include <bits/stdc++.h>
 using namespace std;

 #define ll long long
 #define vi vector<int>
 #define vll vector<long long>
 #define pii pair<int,int>
 #define all(x) (x).begin(), (x).end()
 #define sz(x) (int)(x).size()
 #define pb push_back
 #define F first
 #define S second

 const int MOD = 1e9 + 7;
 const int INF = 1e9;
 const ll LINF = 1e18;

 void solve() {
     // Solution here
 }

 int main() {
     ios::sync_with_stdio(false);
     cin.tie(nullptr);

     int t = 1;
     cin >> t;
     while (t--) solve();

     return 0;
 }
*/

void demonstrateHeaders() {
    cout << "═══ HEADER FILES DEMO ═══\n\n";

    // All of these work because of bits/stdc++.h:
    vector<int> v = {5, 3, 1, 4, 2};
    sort(v.begin(), v.end());
    cout << "sort works (from <algorithm>): ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    set<int> s(v.begin(), v.end());
    cout << "set works (from <set>): ";
    for (int x : s) cout << x << " ";
    cout << "\n";

    cout << "accumulate works (from <numeric>): sum = "
         << accumulate(v.begin(), v.end(), 0) << "\n";

    cout << "sqrt works (from <cmath>): sqrt(144) = "
         << sqrt(144) << "\n";

    cout << "INT_MAX works (from <climits>): " << INT_MAX << "\n";

    cout << "\nAll included with ONE line: #include <bits/stdc++.h>\n\n";
}

void demonstratePragmaEffect() {
    cout << "═══ PRAGMA EFFECT DEMO ═══\n\n";

    const int N = 10000000;
    vector<int> v(N);
    iota(v.begin(), v.end(), 0);

    auto start = chrono::steady_clock::now();
    long long sum = 0;
    for (int i = 0; i < N; i++) {
        sum += v[i];
        sum ^= (v[i] * 3 + 1);  // Some work to prevent optimization away
    }
    auto end = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Loop (10^7 iterations): " << ms << " ms\n";
    cout << "(With pragmas, this would be even faster)\n";
    cout << "Result (prevent optimize away): " << sum << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateHeaders();
    demonstratePragmaEffect();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Use #include <bits/stdc++.h> in contests\n";
    cout << "2. Use individual headers in production code\n";
    cout << "3. #pragma GCC optimize(\"O2\") is almost always safe\n";
    cout << "4. Avoid Ofast for floating-point precision problems\n";
    cout << "5. Always add ios::sync_with_stdio(false); cin.tie(nullptr);\n";

    return 0;
}

/*
 PRACTICE:
 ─────────
 1. Try compiling with and without pragmas, compare speed
 2. Try removing bits/stdc++.h and add individual headers one by one
 3. Test on Codeforces Custom Invocation with different pragma levels
*/

