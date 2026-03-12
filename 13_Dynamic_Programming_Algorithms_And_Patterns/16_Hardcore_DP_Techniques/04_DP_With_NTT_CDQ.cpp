/*
 * ============================================================================
 *    DP WITH NTT/CONVOLUTION + CDQ DIVIDE AND CONQUER
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Hardcore DP — DP with Convolution/NTT, CDQ D&C
 * Level   : ⭐⭐⭐⭐⭐ Grandmaster / ICPC
 * ============================================================================
 *
 * DP WITH CONVOLUTION:
 *   When dp[n] = Σ dp[i] × dp[n-i] (convolution form),
 *   Use NTT/FFT to compute in O(n log n) instead of O(n²).
 *
 *   Examples:
 *   - Catalan recurrence: C(n) = Σ C(i)×C(n-1-i)
 *   - Partition function acceleration
 *   - Polynomial multiplication in DP transitions
 *
 * CDQ DIVIDE AND CONQUER:
 *   When dp[i] depends on dp[0..i-1] via some operation:
 *   dp[i] = f(dp[0], dp[1], ..., dp[i-1])
 *
 *   Split into halves: compute left half, use left to update right, then right.
 *   If update can be done with FFT/NTT: O(n log² n) total.
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;  // NTT-friendly prime: 998244353 = 119 × 2^23 + 1

long long power(long long base, long long exp, long long mod) {
    long long result = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

/*
 * NTT (Number Theoretic Transform) — Exact FFT over MOD
 */
void ntt(vector<long long>& a, bool inverse) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        long long w = inverse ? power(3, MOD - 1 - (MOD - 1) / len, MOD)
                              : power(3, (MOD - 1) / len, MOD);
        for (int i = 0; i < n; i += len) {
            long long wn = 1;
            for (int j = 0; j < len / 2; j++) {
                long long u = a[i + j];
                long long v = a[i + j + len/2] * wn % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len/2] = (u - v + MOD) % MOD;
                wn = wn * w % MOD;
            }
        }
    }

    if (inverse) {
        long long n_inv = power(n, MOD - 2, MOD);
        for (auto& x : a) x = x * n_inv % MOD;
    }
}

// Polynomial multiplication using NTT
vector<long long> multiply(vector<long long> a, vector<long long> b) {
    int result_size = a.size() + b.size() - 1;
    int n = 1;
    while (n < result_size) n <<= 1;
    a.resize(n); b.resize(n);

    ntt(a, false);
    ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % MOD;
    ntt(a, true);

    a.resize(result_size);
    return a;
}

/*
 * 1. CATALAN NUMBERS VIA CONVOLUTION
 *    C(n) = Σ_{i=0}^{n-1} C(i) × C(n-1-i)
 *    This is self-convolution of the Catalan sequence.
 *
 *    For computing all C(0..n), use CDQ + NTT:
 *    Process left half → convolve left into right → process right half.
 *    Time: O(n log² n)
 */
vector<long long> catalanCDQ(int n) {
    vector<long long> C(n + 1, 0);
    C[0] = 1;

    function<void(int, int)> solve = [&](int lo, int hi) {
        if (lo == hi) {
            if (lo > 0) {
                // C[lo] is already accumulated from previous contributions
                // (will be finalized)
            }
            return;
        }
        int mid = (lo + hi) / 2;
        solve(lo, mid);

        // Contribution of C[lo..mid] to C[mid+1..hi]
        // C[j] += Σ C[i] × C[j-1-i] for i in [lo..mid]
        // This is a convolution of C[lo..mid] with C[?]

        // For simplicity, use direct computation here
        // (Full CDQ+NTT is more complex to implement correctly)
        for (int j = mid + 1; j <= hi; j++) {
            for (int i = lo; i <= mid; i++) {
                int idx = j - 1 - i;
                if (idx >= 0 && idx <= n) {
                    C[j] = (C[j] + C[i] * C[idx]) % MOD;
                }
            }
        }

        solve(mid + 1, hi);
    };

    solve(0, n);
    return C;
}

/*
 * 2. CDQ DIVIDE AND CONQUER — General DP Optimization
 *    dp[i] = Σ_{j=0}^{i-1} dp[j] × f(j, i)
 *    where f(j, i) depends only on (i - j).
 *
 *    CDQ:
 *    1. solve(lo, mid) — compute dp[lo..mid]
 *    2. Contribution of dp[lo..mid] to dp[mid+1..hi] via convolution
 *    3. solve(mid+1, hi) — compute dp[mid+1..hi]
 *
 *    Time: O(n log² n) with NTT
 */

// Example: dp[0]=1, dp[n] = Σ dp[j] × a[n-j] for j=0..n-1
// Given array a[], compute dp[0..N]
vector<long long> cdqConvolutionDP(vector<long long>& a, int N) {
    vector<long long> dp(N + 1, 0);
    dp[0] = 1;

    function<void(int, int)> solve = [&](int lo, int hi) {
        if (lo == hi) return;
        int mid = (lo + hi) / 2;
        solve(lo, mid);

        // Contribution of dp[lo..mid] to dp[mid+1..hi]
        int lenL = mid - lo + 1;
        int lenR = hi - mid;

        vector<long long> polyA(lenL), polyB(hi - lo + 1);
        for (int i = 0; i < lenL; i++) polyA[i] = dp[lo + i];
        for (int i = 0; i < hi - lo + 1 && i <= N; i++) polyB[i] = (i < (int)a.size()) ? a[i] : 0;

        // Multiply
        if (lenL > 0 && polyB.size() > 0) {
            auto conv = multiply(polyA, polyB);
            for (int j = mid + 1; j <= hi; j++) {
                int idx = j - lo;
                if (idx < (int)conv.size()) {
                    dp[j] = (dp[j] + conv[idx]) % MOD;
                }
            }
        }

        solve(mid + 1, hi);
    };

    solve(0, N);
    return dp;
}

/*
 * 3. POLYNOMIAL KNAPSACK — Generating function approach
 *    For unbounded knapsack with item weights w1, w2, ..., wk:
 *    Generating function: Π (1/(1 - x^wi))
 *    Coefficient of x^W = number of ways.
 *
 *    For 0/1 knapsack:
 *    GF = Π (1 + x^wi)
 *    Evaluate using divide and conquer + NTT: O(n log² n × W)
 */
vector<long long> polyKnapsack01(vector<int>& weights, int maxW) {
    // Each item contributes polynomial (1 + x^w)
    // Multiply all polynomials using D&C

    function<vector<long long>(int, int)> solve = [&](int lo, int hi) -> vector<long long> {
        if (lo == hi) {
            vector<long long> poly(min(weights[lo], maxW) + 1, 0);
            poly[0] = 1;
            if (weights[lo] <= maxW) poly[weights[lo]] = 1;
            return poly;
        }
        int mid = (lo + hi) / 2;
        auto left = solve(lo, mid);
        auto right = solve(mid + 1, hi);
        auto result = multiply(left, right);
        if ((int)result.size() > maxW + 1) result.resize(maxW + 1);
        return result;
    };

    if (weights.empty()) return {1};
    return solve(0, weights.size() - 1);
}

/*
 * 4. PARTITION FUNCTION via Euler's Pentagonal Theorem
 *    p(n) - p(n-1) - p(n-2) + p(n-5) + p(n-7) - ... = 0
 *    Pentagonal numbers: k(3k-1)/2 for k = 1,-1,2,-2,...
 *    Signs: -, -, +, +, -, -, +, +, ...
 *    O(n√n) computation — much faster than O(n²)
 */
vector<long long> partitionPentagonal(int n) {
    vector<long long> p(n + 1, 0);
    p[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int k = 1; ; k++) {
            int pent1 = k * (3 * k - 1) / 2;  // Generalized pentagonal
            int pent2 = k * (3 * k + 1) / 2;

            if (pent1 > i) break;

            int sign = (k % 2 == 1) ? 1 : -1;
            p[i] = (p[i] + sign * p[i - pent1] % MOD + MOD) % MOD;

            if (pent2 <= i)
                p[i] = (p[i] + sign * p[i - pent2] % MOD + MOD) % MOD;
        }
    }
    return p;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== DP WITH NTT/CONVOLUTION ===" << endl;

    // NTT Polynomial Multiplication
    vector<long long> a = {1, 2, 3};  // 1 + 2x + 3x²
    vector<long long> b = {4, 5};     // 4 + 5x
    auto c = multiply(a, b);
    cout << "\n--- NTT Multiplication ---" << endl;
    cout << "(1+2x+3x²) × (4+5x) = ";
    for (int i = 0; i < (int)c.size(); i++) {
        if (i > 0) cout << " + ";
        cout << c[i] << "x^" << i;
    }
    cout << endl;

    // Catalan via CDQ
    auto cat = catalanCDQ(10);
    cout << "\n--- Catalan Numbers (CDQ) ---" << endl;
    for (int i = 0; i <= 10; i++) cout << "C(" << i << ")=" << cat[i] << " ";
    cout << endl;

    // Partition function
    auto part = partitionPentagonal(30);
    cout << "\n--- Partition Function (Pentagonal) ---" << endl;
    for (int i = 0; i <= 15; i++) cout << "p(" << i << ")=" << part[i] << " ";
    cout << endl;

    // Polynomial 0/1 Knapsack
    vector<int> weights = {2, 3, 5, 7};
    auto knap = polyKnapsack01(weights, 15);
    cout << "\n--- Polynomial 0/1 Knapsack ---" << endl;
    cout << "Weights: {2,3,5,7}, ways to make each sum:" << endl;
    for (int i = 0; i < min((int)knap.size(), 16); i++)
        cout << i << ":" << knap[i] << " ";
    cout << endl;

    cout << "\n============================================" << endl;
    cout << "  NTT/CONVOLUTION DP SUMMARY:" << endl;
    cout << "  • dp = self-convolution → CDQ + NTT" << endl;
    cout << "  • Knapsack counting → polynomial product" << endl;
    cout << "  • Partition function → Pentagonal theorem" << endl;
    cout << "  • Time: O(n log² n) for many DP problems" << endl;
    cout << "============================================" << endl;

    return 0;
}

