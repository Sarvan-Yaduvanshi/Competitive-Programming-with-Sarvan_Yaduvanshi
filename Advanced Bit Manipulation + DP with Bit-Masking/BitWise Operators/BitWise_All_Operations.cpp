/*
Author: Sarvan.DP.GrandMaster
Created : 2025-12-28 14:53:25
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
//      GM LEVEL: BIT MANIPULATION LIBRARY
// ==========================================

/**
 * 1. Check if the i-th bit is set (1) or unset (0).
 * Logic: Create a mask with only i-th bit as 1. AND it with n.
 * If result > 0, the bit was 1.
 */
bool getBit(int n, int i) {
    return (n & (1 << i)) != 0;
}

/**
 * 2. Set the i-th bit to 1 (Turn ON).
 * Logic: OR (|) preserves existing 1s and forces the i-th bit to 1.
 */
int setBit(int n, int i) {
    return (n | (1 << i));
}

/**
 * 3. Clear the i-th bit to 0 (Turn OFF).
 * Logic: We need a mask like 111101111 (0 at index i).
 * We get this by taking ~(1 << i). Then we AND (&) it.
 */
int clearBit(int n, int i) {
    int mask = ~(1 << i);
    return (n & mask);
}

/**
 * 4. Toggle the i-th bit (Flip 0->1 or 1->0).
 * Logic: XOR (^) flips the bit if the mask has a 1 at that position.
 */
int toggleBit(int n, int i) {
    return (n ^ (1 << i));
}

/**
 * 5. Update the i-th bit to a specific value (target: 0 or 1).
 * Logic: First CLEAR the spot to make it 0 (clean slate).
 * Then OR it with the target value shifted to position i.
 */
int updateBit(int n, int i, int target) {
    // Step 1: Clear the bit (Make it 0)
    int mask = ~(1 << i);
    n = n & mask;

    // Step 2: Set the bit to target
    return (n | (target << i));
}

/**
 * 6. Clear the last 'i' bits (from index 0 to i-1).
 * Example: n = 15 (1111), i = 2 -> Result = 12 (1100)
 */
int clearLastIBits(int n, int i) {
    // (~0) is all 1s (-1). Shift left by i puts 0s in the last i positions.
    int bitmask = (~0) << i;
    return n & bitmask;
}

/**
 * 7. Clear a range of bits from index i to j (inclusive).
 * Example: n = 31 (11111), i = 1, j = 3 -> Result = 17 (10001)
 * Logic: Create a mask like 111100011.
 */
int clearRangeOfBits(int n, int i, int j) {
    int a = (~0) << (j + 1); // 1s on the left of j
    int b = (1 << i) - 1;    // 1s on the right of i
    int bitmask = a | b;
    return n & bitmask;
}

/**
 * 8. Check if a number is a Power of 2.
 * Logic: Powers of 2 have only one bit set (e.g., 1000).
 * n & (n-1) removes the last set bit. If result is 0, it was a power of 2.
 */
bool isPowerOfTwo(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

/**
 * 9. Count set bits (Population Count).
 * Logic: Uses GCC builtin for O(1) speed.
 */
int countSetBits(int n) {
    return __builtin_popcount(n);
}

// ==========================================
//               DRIVER CODE
// ==========================================

void solve() {
    int n;
    cout << "Enter a number (n): ";
    cin >> n;

    int i, j;
    cout << "Enter bit index (i) to modify: ";
    cin >> i;

    // Visualize the input
    cout << "Original Binary: " << bitset<8>(n) << " (Decimal: " << n << ")\n";
    cout << "------------------------------------------------\n";

    // 1. Get Bit
    bool isSet = getBit(n, i);
    cout << "[GET] Is bit " << i << " set? : " << (isSet ? "YES (1)" : "NO (0)") << "\n";

    // 2. Set Bit
    cout << "[SET] Making bit " << i << " ON : " << setBit(n, i) << "\n";

    // 3. Clear Bit
    cout << "[CLR] Making bit " << i << " OFF: " << clearBit(n, i) << "\n";

    // 4. Toggle Bit (Bonus GM Function)
    cout << "[TGL] Flipping bit " << i << "    : " << toggleBit(n, i) << "\n";

    // 5. Update Bit
    int target;
    cout << "------------------------------------------------\n";
    cout << "Enter target value (0 or 1) for update: ";
    cin >> target;
    cout << "[UPD] Updating bit " << i << " to " << target << " : " << updateBit(n, i, target) << "\n";

    // --- TEST: Clear Last i Bits ---
    cout << "Enter i to clear last i bits: ";
    cin >> i;
    int resLast = clearLastIBits(n, i);
    cout << "[CLR LAST " << i << "] Result: " << bitset<8>(resLast) << " (" << resLast << ")\n";

    // --- TEST: Clear Range ---
    cout << "Enter range [i, j] to clear (e.g., 1 3): ";
    cin >> i >> j;
    int resRange = clearRangeOfBits(n, i, j);
    cout << "[CLR RNG " << i << "-" << j << "] Result: " << bitset<8>(resRange) << " (" << resRange << ")\n";

    // --- TEST: Power of 2 ---
    cout << "------------------------------------------------\n";
    cout << "[CHK] Is " << n << " a Power of 2? : " << (isPowerOfTwo(n) ? "YES" : "NO") << "\n";

    // --- TEST: Count Bits ---
    cout << "[CNT] Number of set bits : " << countSetBits(n) << "\n";
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

