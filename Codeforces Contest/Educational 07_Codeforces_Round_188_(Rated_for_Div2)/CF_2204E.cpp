// Author: sarvan.dp.grandmaster
// Created: 2026-03-16 21:10:21
// Problem: E. Sum of Digits (and Again)
// Contest: Codeforces - Educational Codeforces Round 188 (Rated for Div. 2)
// URL: https://codeforces.com/contest/2204/problem/E
// Memory Limit: 512 MB
// Time Limit: 2000 ms

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

// Input helper
template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}
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

int sum_of_digits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

void solve() {
    string s; cin >> s;


    if (sz(s) == 1) {
        cout << s << "\n";
        return;
    }

    int tot = 0;
    vec<int> freq(10, 0);
    
    for (char c : s) {
        int d = c - '0';
        freq[d]++;
        tot += d;
    }


    int start_guess = max(1, tot - 200); 
    
    for (int i = start_guess; i <= tot; i++) {
        int curr = i;
        vec<int> seq;
        vec<int> seq_freq(10, 0);
        int seq_sum = 0;

        // Generate the tail sequence: x2, x3, ..., xk
        while (true) {
            seq.pb(curr);
            seq_sum += curr;

            int temp = curr;
            while (temp > 0) {
                seq_freq[temp % 10]++;
                temp /= 10;
            }

            if (curr <= 9) {
                seq_sum += curr; 
                break;
            }
            curr = sum_of_digits(curr);
        }

        // If the math formula holds up
        if (seq_sum == tot) {
            bool has_enough_digits = true;
            for (int d = 0; d < 10; ++d) {
                if (seq_freq[d] > freq[d]) {
                    has_enough_digits = false;
                    break;
                }
            }

            if (has_enough_digits) {
                vector<int> rem_freq = freq;
                for (int d = 0; d < 10; ++d) {
                    rem_freq[d] -= seq_freq[d];
                }

                string x1 = "";

                for (int d = 1; d < 10; ++d) {
                    if (rem_freq[d] > 0) {
                        x1 += to_string(d);
                        rem_freq[d]--;
                        break;
                    }
                }

                // Append all remaining digits to x1
                for (int d = 0; d < 10; ++d) {
                    while (rem_freq[d] > 0) {
                        x1 += to_string(d);
                        rem_freq[d]--;
                    }
                }

                // Append the rest of the sequence (x2, x3, ...)
                string ans = x1;
                for (int num : seq) {
                    ans += to_string(num);
                }

                cout << ans << nl;
                return; 
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    
    return 0;
}