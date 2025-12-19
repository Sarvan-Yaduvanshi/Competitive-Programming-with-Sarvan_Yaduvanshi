//
// Created by Sarvan Yaduvanshi on 10/7/25.
//

#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
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

// Method 1 : Brute Force work for 10^6 but not work 10^12..
// Time Complexity O(N)
void factorization(i64 n) {
    vector<i64> factors;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) factors.push_back(i);
    }

    // print all factors
    for (auto factor : factors) cout << factor << " ";
    cout << endl;
}

// Method 2 : Optimized Sqrt work 10^12...
// Time Complexity O(Sqrt(N))
void opFactorization(i64 n) {
    // Execution Speed: The time complexity is O(Sqrt(N).
    // It's technically faster because it avoids the O(DlogD) sorting step
    vector<i64> front_factors;
    vector<i64> back_factors;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            front_factors.push_back(i);
            if (n / i != i) back_factors.push_back(n / i);
        }
    }

    // if avoid two vector than use single vector than sort all element
    // Execution Speed: The time complexity is O(Sqrt(N) +DlogD),
    // where D is the number of divisors.
    /*
    vector<i64> factors;
    for (i64 i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            if (n / i != i) factors.push_back(n / i);
        }
    }
    sort(all(factors));
    */

    // Print the first half
    for (i64 factor : front_factors) cout << factor << " ";
    // Print the second half in reverse
    for (int i = sz(back_factors) - 1; i >= 0; i--) {
        cout << back_factors[i] << " ";
    }
    cout << endl;

    // Both Method are Great But Generally CP Use Single Vector
}

// Method 3 :- print all factors using prime logic
// Calculates prime factorization of n in O(sqrt(N)).
// Returns a map where key is the prime and value is its exponent.
// Example: 72 -> { {2, 3}, {3, 2} } representing 2^3 * 3^2.
map<i64, int> getPrimeFactorization(i64 n) {
    map<i64, int> prime_factors;
    for (i64 i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            prime_factors[i]++;
            n /= i;
        }
    }
    if (n > 1) prime_factors[n]++;
    return prime_factors;
}

// Recursively generates all factors from a prime factorization.
// 'primes' is a vector of {prime, exponent} pairs. 'all_factors' is the output vector.
void generateFactors(int k, i64 current_factor, const vector<pii<i64, int>>& primes, vector<i64>& all_factors) {
    // Base case: all prime factors have been considered. A new factor is found.
    if (k == sz(primes)) {
        all_factors.push_back(current_factor);
        return;
    }

    i64 p = primes[k].fi; // The current prime base
    int a = primes[k].se; // Its maximum exponent
    i64 p_power = 1;

    // Recursive step: iterate through all possible powers of the current prime (from p^0 to p^a).
    for (int i = 0; i <= a; ++i) {
        generateFactors(k + 1, current_factor * p_power, primes, all_factors);
        p_power *= p;
    }
}
void solve() {
    i64 n; cin >> n;

    // Method 1 : simple brute force
    factorization(n);

    cout << "<----------------------->" << endl;
    // Method 2 : Optimized
    opFactorization(n);

    // Step 1: Get the prime factorization as a map.
    map<i64, int> prime_map = getPrimeFactorization(n);

    // Step 2: Convert map to a vector of pairs for easier iteration in the recursive function.
    vector<pii<i64, int>> primes(all(prime_map));

    // Step 3: Recursively generate all factors.
    vector<i64> all_factors;
    generateFactors(0, 1, primes, all_factors);

    // --- FIX WAS HERE ---
    // Step 4: The calculated factors must be sorted and printed.
    sort(all(all_factors));
    for (i64 factor : all_factors) {
        cout << factor << " ";
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    // int TC = 1;
    // cin >> TC;
    // while(TC--) {
    // solve();
    // }
    return 0;
}