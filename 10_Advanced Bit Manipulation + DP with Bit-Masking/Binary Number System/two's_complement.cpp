/*
Author: Sarvan.DP.GrandMaster
Created : 2025-12-28 15:04:27
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

//Method 1 : manually implement (Two's Complement Decimal ---> Binary)
// --- Helper: Invert Bits (Step 3 in your image) ---
string invertBits(string str) {
    for (char &ch : str) {
        if (ch == '0') ch = '1';
        else ch = '0';
    }

    return str;
}

// --- Helper: Add 1 (Step 4 in your image) ---
string addOne(string str) {
    const int n = str.size();
    bool carry = true; // We start wanting to add 1

    // Iterate from Right (LSB) to Left (MSB)
    for (int i = n - 1; i >= 0; i--) {
        if (carry) {
            if (str[i] == '0') {
                str[i] = '1';
                carry = false;  // Added 1, done. No more carry.
            } else {
                str[i] = '0';  // 1 + 1 becomes 0
                carry = true; // Carry moves to the next left bit
            }
        } else break; // Optimization: If no carry, we are done
    }

    return str;
}

// Two's Complement (Decimal ---> Binary)
void solve() {
    cout << "Enter a decimal number : ";
    int n; cin >> n; // eg : n = 10

    // Step 1: Get Basic Binary (Absolute Value)
    // We use 8 bits to match the "prefix 0" concept easily
    const string bin = bitset<8>(n).to_string();
    cout << "Original (+10): " << bin << nl;; // 00001010

    // Step 2 & 3: Invert (1's Complement)
    const string onesComp = invertBits(bin);
    cout << "1's Complement: " << onesComp << "\n"; // 11110101

    // Step 4: Add 1 (2's Complement)
    const string twosComp = addOne(onesComp);
    cout << "2's Complement: " << twosComp << " (Represents -10)\n";

    cout << "<----------Method 2 : ----------->" << nl;

    // Method 2 : The "Grand Master" Approach (The One-Liner)
    n = 10;
    // 1. Direct Negation
    // The compiler automatically does (~n + 1) logic here
    const int negativeN = -n;

    // 2. Visualizing it
    // bitset prints the raw bits exactly how they are in memory
    cout << "Binary of -10: " << bitset<8>(negativeN) << "\n";
    // Output: 11110110

    // 3. The Math Trick (Bitwise Formula)
    // If you need to manually calculate -n without the minus sign:
    const int manualCalc = (~n) + 1;
    cout << "Manual Logic:  " << bitset<8>(manualCalc) << "\n";
}

// Two's Complement (Binary ---> Decimal)
// Logic:
// 1. Check the first bit (Significant Bit --> Sign Bit)
// 2. if 0 --> It's positive. Convert normally.
// 3. If 1 --> It's negative. Apply Two's Complement Reverse (Invert + Add 1) to find the magnitude, then put a - sign.
void binaryToDecimalSigned(const string& s) {
    // Check Sign Bit (First character)
    if (s[0] == '0') {
        cout << "Positive: " << stoll(s, nullptr, 2) << "\n";
    } else {
        // It's Negative!
        // Apply "Invert + Add 1" to find positive magnitude
        const string inverted = invertBits(s);
        const string magnitudeBin = addOne(inverted);

        const i64 val = stoll(magnitudeBin, nullptr, 2);
        cout << "Negative: -" << val << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Two's Complement (Decimal ---> Binary)" << nl;
    cout << "<----------------------------------->" << nl;
    solve();

    cout << "<----------------------------------------->" << nl;
    cout << "Two's Complement (Binary ---> Decimal)" << nl;

    // Fun Call Binary --> Decimal (Two's Complement)
    cout << "enter a binary number : ";
    string str; cin >> str;
    binaryToDecimalSigned(str);

    return 0;
}

