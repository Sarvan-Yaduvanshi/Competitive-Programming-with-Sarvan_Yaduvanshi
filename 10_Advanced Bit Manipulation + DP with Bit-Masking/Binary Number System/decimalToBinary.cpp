/*
Author: Sarvan.DP.GrandMaster
Created : 2025-12-28 15:01:09
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

// Method 1 : Beginner Level Implement (Never Use only learning purpose)
i64 DecToBinary(i64 n) {
    i64 ans = 0, powOf10 = 1;

    while (n > 0) {
        const i64 rem = n % 2;
        n /= 2;
        ans += rem * powOf10;
        powOf10 *= 10; // rev order store (update power position eg : 10, 100,1000,.....)
    }

    return ans;
}

// --- Method 2: The General Purpose String (Best for Logic) ---
string getBinaryString(i64 n) {
    // Handle 0 explicitly
    if (n == 0) return "0";

    string binaryStr;
    while (n > 0) {
        // (n & 1) gets the last bit (equivalent to n % 2)
        binaryStr += (n & 1) + '0'; //  // GM Trick: Direct char conversion
        n >>= 1;
    }

    reverse(all(binaryStr));
    return binaryStr;
}

// --- Method 3: The STL Shortcut (Best for Printing Fixed Width) ---
void printBitset(i64 n) {
    // Uses 64 bits to cover all 'long long' values
    string s = bitset<64>(n).to_string();

    // GM Trick: Remove leading zeros manually if needed
    // Finds the first '1'. If not found (n=0), returns specific index.
    const auto firstOne = s.find('1');
    if(firstOne != string::npos) {
        cout << s.substr(firstOne) << "\n";
    } else {
        cout << "0\n";
    }
}

void solve() {
    cout << "Enter a Decimal Number : ";
    i64 n;
    cin >> n;

    // Use Method 1:
    cout << "Beginner : " << DecToBinary(n) << "\n";

    // Use Method 2:
    const string s = getBinaryString(n);
    cout << "String Method: " << s << "\n";

    // Use Method B when you just need to print it fast
    cout << "Bitset Method: ";
    printBitset(n);
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

