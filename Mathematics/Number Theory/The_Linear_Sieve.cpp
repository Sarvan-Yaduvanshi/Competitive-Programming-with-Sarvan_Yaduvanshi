//
// Created by Sarvan Yaduvanshi on 10/12/25.
//

#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using i128 = __int128_t;
using ld  = long double;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD  = 1'000'000'007LL;
constexpr i64 MOD1 = 1'000'000'007LL;
constexpr i64 MOD2 = 998'244'353LL;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) int((x).size())
#define pb push_back
#define fi first
#define se second

template<class T> using vec = vector<T>;
template<class A, class B> using pii = pair<A,B>;

// ---------------- Toolbox ----------------
inline i64 gcdll(i64 a, i64 b) { while(b){ a %= b; swap(a,b);} return abs(a);}
inline i64 lcmll(i64 a, i64 b) { return a / gcdll(a,b) * b;}
inline i64 modpow(i64 a, i64 e, i64 mod = MOD) {
    i64 r = 1;
    while(e) {
        if(e & 1) r = r * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return r;
}

void solve() {
    i64 n; cin >> n;

    // Space Complexity: O(N)
    vector<i64> primes; // store all list prime
    vector<bool> is_composite(n + 1, false); // marks all composite

    // Time Complexity O(N) + O(N) --> O(N)
    for (i64 i = 2; i <= n; i++) {
        if (!is_composite[i]) {
            primes.pb(i); // 'i' is a prime number
        }
        // Time Complexity O(N)
        for (i64 p : primes) {
            if (i * p > n) break; // 1. Bounds Check

            is_composite[i * p] = true; // 2. Mark as Composite

            if (i % p == 0) break; // 3. The "Magic" Break
        }
    }

    // print all prime number
    for (i64 p : primes) cout << p << " ";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    cin >> TC;
    while(TC--) {
        solve();
    }
    return 0;
}

/*
Input:
1
20

Output:
2 3 5 7 11 13 17 19
*/

/*
Explanation:
- All primes ≤ 20:
  2,3,5,7,11,13,17,19
- Covers small primes, composites, odd/even numbers.
- Useful for validation in contests.
*/
