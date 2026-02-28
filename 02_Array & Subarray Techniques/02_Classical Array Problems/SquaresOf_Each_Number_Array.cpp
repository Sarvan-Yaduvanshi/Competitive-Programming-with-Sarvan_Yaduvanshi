/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-03 19:52:35
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

// Level 1: Basic (Implementation)
// The Task: You have an array A and you want to square every element and sorted in non-decreasing order.
// Logic : Just iterate and multiply. and Sort
// Time Complexity --> O(NlogN)
vector<int> sortedSquares(const vector<int> &arr){
    // Step 1 : Squares
    for (auto &a : arr) a *= a;

    // Step 2 : Sort --> NlogN
    sort(all(arr));

    return arr;
}

// Level 2: Expert (Two Pointers)
// The Task: You have a sorted array that contains negative numbers (e.g., [-4, -1, 0, 3, 10]).
// You need to return a sorted array of their squares.
// [-4, -1, 0, 3, 10] --> [0, 1, 9, 16, 100]
// Logic : The largest square will always be at either the start (very small negative) or the end (very large positive) of the original array.
//       : Compare the absolute values of left and right.
//       : Place the larger square at the end of your result array and move the pointer.
// Time Complexity --> O(N)
vector<int> sortedSqaresArray(vector<int> &arr){
    int n = arr.size();
    int L = 0;
    int R = n - 1;

    vector<int> res(n);

    // Fill result from the back (largest to smallest)
    for (int i = n - 1; i >= 0; i--){
       if (abs(arr[L]) > abs(arr[R])){
           res[i] = arr[L] * arr[L];
           L++;
       } else{
           res[i] = arr[R] * arr[R];
           R--;
       }
    }

    return res;
}

// Level 3: Grandmaster (Matrix Exponentiation)
// 1. Concept: Matrix Exponentiation
// Logic: Used to solve Linear Recurrences (like Fibonacci, tiling problems, graph paths of length K) when N is huge (up to 10^18).
// Core Idea: Convert the recurrence relation into a Transition Matrix T.
// The Power: To find the state at step $N$, we compute T^N.
// Optimization: Instead of multiplying T x T x...(N times),
// we use Binary Exponentiation (Squaring) to compute it in O(K^3log N) time, where K is the matrix size.

constexpr int SZ = 2; // Adjust size based on recurrence (e.g., Fib=2, Trib=3)

struct Matrix {
    i64 mat[SZ][SZ];
    Matrix() {
        // Init with 0 (Zero Matrix)
        for(int i=0; i<SZ; i++) for(int j=0; j<SZ; j++) mat[i][j] = 0;
    }
};

// [Operation: Multiplication]
// Standard Matrix Multiplication (Row * Column)
// Logic: C[i][j] = Sum(A[i][k] * B[k][j])
Matrix multiply(Matrix A, Matrix B) {
    Matrix C;
    for(int i=0; i<SZ; i++) {
        for(int j=0; j<SZ; j++) {
            for(int k=0; k<SZ; k++) {
                C.mat[i][j] = (C.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % MOD;
            }
        }
    }
    return C;
}

// [Operation: Exponentiation]
// Logic: Binary Exponentiation (Divide & Conquer)
// 1. If power is odd: Result = Result * A
// 2. Square the base: A = A * A
// 3. Divide power by 2
Matrix power(Matrix A, i64 p) {
    Matrix res;
    // Init 'res' as Identity Matrix (1s on diagonal, 0s elsewhere)
    // Identity Matrix acts like '1' in scalar multiplication
    for(int i=0; i<SZ; i++) res.mat[i][i] = 1;

    while(p > 0) {
        if(p & 1) res = multiply(res, A); // If bit is set, include current power
        A = multiply(A, A);               // Square the matrix for next bit
        p >>= 1;                          // Right shift to process next bit
    }
    return res;
}

// Practice Problems (Basic to GM)
// https://leetcode.com/problems/fibonacci-number/description/
// https://leetcode.com/problems/n-th-tribonacci-number/description/
// https://cses.fi/problemset/task/1722


void solve() {

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    // Multi-test case support (commented out for this demo)
    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();
    
    solve();
    return 0;
}

