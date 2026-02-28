/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           10 — THE COMPLETE GRANDMASTER CP TEMPLATE                        ║
║           Copy-paste this at the start of EVERY contest solution            ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt")
#include <bits/stdc++.h>
using namespace std;

// PBDS (uncomment when needed)
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template<class T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,
//                          tree_order_statistics_node_update>;

// ─── TYPE ALIASES ───
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
using vpii = vector<pii>;

// ─── MACROS ───
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define pb push_back
#define eb emplace_back
#define F first
#define S second
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); i--)
#define each(x, v) for (auto& x : v)

// ─── CONSTANTS ───
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const double EPS = 1e-9;
const double PI = acos(-1.0);

// ─── UTILITIES ───
template<class T> bool chmin(T& a, T b) { return a > b ? a = b, true : false; }
template<class T> bool chmax(T& a, T b) { return a < b ? a = b, true : false; }

ll power(ll base, ll exp, ll mod = MOD) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

ll modinv(ll a, ll mod = MOD) { return power(a, mod - 2, mod); }

// ─── ANTI-HACK HASH ───
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// ─── RANDOM ───
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// ─── DEBUG ───
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << x << "\n"
#else
#define dbg(x)
#endif

// ═══════════════════════════════════════════════════════════════
// SOLUTION
// ═══════════════════════════════════════════════════════════════

void solve() {
    // Your solution here
    int n;
    cin >> n;
    vi a(n);
    each(x, a) cin >> x;

    // Example: print sorted array
    sort(all(a));
    each(x, a) cout << x << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

/*
 TEMPLATE USAGE GUIDE:
 ─────────────────────
 • Copy this template at the start of every contest
 • Uncomment PBDS section when you need ordered_set
 • Use vi, vll, pii for shorter code
 • chmin/chmax for DP transitions
 • power() for modular exponentiation
 • custom_hash with unordered_map for safety
 • dbg() for local debugging (won't print on judge)
 • #define LOCAL when testing locally

 CONTEST STRATEGY:
 1. Read ALL problems first (5 min)
 2. Solve easiest → hardest
 3. Don't debug for > 15 min — move on
 4. Use stress testing for tricky problems
 5. Check edge cases: n=1, n=0, all same, sorted, reverse sorted
*/

