/*
Author: Sarvan.DP.GrandMaster
Created : 2025-12-28 14:58:10
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

// --- Type Definitions ---
using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

// --- Constants ---
constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

// --- Random Number Generator ---
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// --- Macros ---
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

#define v1(v, n) vec<i64> v(n)
#define take(v) for(auto &x : v) cin >> x
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

inline i64 gcd(i64 a, i64 b) { return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b) { return (a / std::gcd(a, b)) * b; }

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}


// ==========================================
//      GM LEVEL: BITWISE OPERATORS GUIDE
// ==========================================
/*
 * PRECEDENCE WARNING (Crucial for GM):
 * Bitwise operators (&, |, ^) have LOWER precedence than (==, !=, <, >).
 * WRONG:   if (n & 1 == 0)   -> Calculates (1 == 0) first!
 * CORRECT: if ((n & 1) == 0) -> Calculates (n & 1) first.
 */

// ==========================================
//  1. AND (&) : INTERSECTION / SUBTRACTION
// ==========================================
/*
 * Logic: Returns 1 only if BOTH bits are 1.
 * Math:  Acts as subtraction in set theory.
 * n % (2^k) == n & ((2^k) - 1)
 */

void exploreAND(int n) {
    cout << "\n--- 1. AND (&) Tricks ---\n";

    // Trick 1: Check Odd/Even (Fastest)
    // Logic: LSB is 1 for odd, 0 for even.
    if (n & 1) cout << "Number is ODD\n";
    else       cout << "Number is EVEN\n";

    // Trick 2: Clear Last Set Bit (Brain Kernighan's Algorithm)
    // Logic: Used in Fenwick Trees (BIT). Removing the bottom-most '1'.
    int clearedLast = n & (n - 1);
    cout << "n & (n-1) -> " << clearedLast << " (Removed last 1)\n";

    // Trick 3: Isolate Last Set Bit (Lowbit)
    // Logic: x & (-x) gives ONLY the rightmost 1.
    // -x is (~x + 1) in 2's complement.
    int lowbit = n & (-n);
    cout << "n & (-n)  -> " << lowbit << " (Only the last 1 remains)\n";
}

// ==========================================
//  2. OR (|) : UNION / MERGE
// ==========================================
/*
 * Logic: Returns 1 if EITHER bit is 1.
 * Math:  Used to accumulate flags or fill bits.
 */

void exploreOR(int n) {
    cout << "\n--- 2. OR (|) Tricks ---\n";

    // Trick 1: Fill all trailing zeros with ones
    // Example: 1000 -> 1111.
    // Logic: n | (n-1) fills the gap created by subtraction.
    int filledTrailing = n | (n - 1);
    cout << "n | (n-1) -> " << filledTrailing << " (Filled trailing 0s)\n";

    // Trick 2: Char Lowercase Conversion
    // Logic: 'A' (65) | ' ' (32) = 'a' (97). Sets the 5th bit.
    char up = 'C';
    char low = (up | ' ');
    cout << "Upper '" << up << "' to Lower '" << low << "'\n";
}

// ==========================================
//  3. XOR (^) : DIFFERENCE / TOGGLE
// ==========================================
/*
 * Logic: Returns 1 if bits are DIFFERENT.
 * Math:  Addition without carry.
 * A + B = (A ^ B) + 2 * (A & B)
 */

void exploreXOR(int a, int b) {
    cout << "\n--- 3. XOR (^) Tricks ---\n";

    // Trick 1: Swap without Temp
    cout << "Before Swap: a=" << a << ", b=" << b << "\n";
    a ^= b;
    b ^= a;
    a ^= b;
    cout << "After Swap : a=" << a << ", b=" << b << "\n";

    // Trick 2: Detect Signs (Fast check if signs are different)
    // Logic: Sign bit is the MSB. If signs differ, MSB of XOR is 1 (negative).
    int x = -10, y = 20;
    bool oppositeSigns = ((x ^ y) < 0);
    cout << "Do " << x << " and " << y << " have opposite signs? " << oppositeSigns << "\n";
}

// ==========================================
//  4. NOT (~) : INVERSION
// ==========================================
/*
 * Logic: Flips every bit (0->1, 1->0).
 * Math:  ~n = -(n + 1) [Two's Complement Identity]
 */

void exploreNOT(int n) {
    cout << "\n--- 4. NOT (~) Tricks ---\n";

    cout << "~" << n << " = " << (~n) << " (Which is -(" << n << "+1))\n";

    // Trick: Get a sequence of all 1s
    // Useful for generating masks dynamically
    int allOnes = ~0;
    cout << "~0 is: " << allOnes << " (Binary: ...1111)\n";
}

// ==========================================
//  5. SHIFTS (<<, >>) : SCALING
// ==========================================
/*
 * Left Shift (<<): Multiply by 2.
 * Right Shift (>>): Divide by 2.
 * GM WARNING: Always use 1LL for shifts > 30 to avoid overflow.
 */

void exploreShifts(int n) {
    cout << "\n--- 5. Shift (<< >>) Tricks ---\n";

    // Trick 1: Fast Multiplication/Division
    cout << n << " * 2 = " << (n << 1) << "\n";
    cout << n << " / 2 = " << (n >> 1) << "\n";

    // Trick 2: The 1LL Rule (GM Mandatory)
    // 1 << 40 is overflow (undefined). 1LL << 40 is safe.
    long long safeShift = 1LL << 40;
    cout << "1LL << 40 gives large value safely.\n";
}

// ==========================================
//  6. GCC BUILT-IN FUNCTIONS (O(1) Speed)
// ==========================================
/*
 * These translate directly to hardware instructions.
 * Essential for Time Limit constraints in CP.
 */

void exploreBuiltins(int n) {
    cout << "\n--- 6. GCC Built-in Hacks ---\n";

    // 1. Population Count (Count set bits)
    // Complexity: O(1) on modern CPUs
    cout << "__builtin_popcount(" << n << "): " << __builtin_popcount(n) << "\n";

    // 2. Count Leading Zeros (clz)
    // Useful for calculating Log2(n) -> 31 - clz(n)
    if (n > 0)
        cout << "__builtin_clz(" << n << "): " << __builtin_clz(n) << "\n";

    // 3. Count Trailing Zeros (ctz)
    // Useful to find the index of the least significant bit
    if (n > 0)
        cout << "__builtin_ctz(" << n << "): " << __builtin_ctz(n) << "\n";

    // 4. Parity (1 if count of set bits is odd, 0 if even)
    cout << "__builtin_parity(" << n << "): " << __builtin_parity(n) << "\n";
}

// ==========================================
//           DRIVER CODE
// ==========================================

void solve() {
    int n;
    cout << "Enter a number to test (e.g. 10): ";
    cin >> n;

    // Visualization
    cout << "Binary of " << n << ": " << bitset<8>(n) << "\n";

    exploreAND(n);
    exploreOR(n);
    exploreXOR(5, 9);
    exploreNOT(n);
    exploreShifts(n);
    exploreBuiltins(n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);

    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();
    
    solve();
    return 0;
}

