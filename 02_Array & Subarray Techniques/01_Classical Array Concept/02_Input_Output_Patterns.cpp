/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-28 10:15:00
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
#include <sstream>

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

// =============================================================================
//  MODULE 02: INPUT / OUTPUT PATTERNS
//  Level: ⭐ Beginner
//  Topics: Fast I/O, reading arrays, output formatting, edge cases
// =============================================================================

// =============================================================================
// FAST I/O FUNDAMENTALS
// =============================================================================
/*
 * WHY Fast I/O matters in CP:
 * ───────────────────────────────────────────────────────────────
 * Default cin/cout is synchronized with C stdio (printf/scanf).
 * This synchronization makes them SLOW.
 *
 * THE FIX (put in main()):
 *   ios::sync_with_stdio(false);  // Unsync C++ streams from C streams
 *   cin.tie(nullptr);             // Untie cin from cout (no auto-flush)
 *
 * GOLDEN RULES after enabling fast I/O:
 *   1. NEVER mix cin/cout with scanf/printf in the same program
 *   2. Use '\n' instead of endl (endl forces a flush = SLOW)
 *   3. For massive output (10^6+ lines), consider printf
 *
 * Speed comparison for reading 10^6 integers:
 *   scanf         : ~0.15s
 *   cin (fast IO) : ~0.18s
 *   cin (default) : ~1.50s  ← 10x slower!
 */

// -------------------------------------------------------------
// 1. BASIC READING PATTERNS
// -------------------------------------------------------------

// Pattern 1: Read N, then N elements (MOST COMMON in CP)
void pattern_read_n_then_array() {
    cout << "--- Pattern: Read N then Array ---" << nl;

    int n;
    cin >> n;
    vec<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    // Or using our template helper:
    // vec<int> arr(n); read(arr);

    cout << "Read " << n << " elements" << nl;
}

// Pattern 2: Read until EOF (common in UVa Online Judge, some CF)
void pattern_read_until_eof() {
    cout << "--- Pattern: Read Until EOF ---" << nl;

    // Method 1: while(cin >> x)
    /*
    int x;
    while (cin >> x) {
        // process x
    }
    */

    // Method 2: Read lines until EOF
    /*
    string line;
    while (getline(cin, line)) {
        // process line
    }
    */

    // Method 3: Check for EOF explicitly
    /*
    int x;
    while (cin >> x && !cin.eof()) {
        // process x
    }
    */
}

// Pattern 3: Read T test cases, each with N elements
void pattern_multi_test_case() {
    cout << "--- Pattern: Multiple Test Cases ---" << nl;

    /*
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vec<int> arr(n);
        read(arr);
        // solve and output for this test case
    }
    */
}

// Pattern 4: Read pairs / tuples
void pattern_read_pairs() {
    cout << "--- Pattern: Read Pairs ---" << nl;

    /*
    int n;
    cin >> n;
    vec<pii> pairs(n);
    for (auto& [a, b] : pairs) cin >> a >> b;  // C++17 structured bindings
    */

    // Or classic style:
    /*
    for (int i = 0; i < n; i++) {
        cin >> pairs[i].first >> pairs[i].second;
    }
    */
}

// Pattern 5: Read 2D grid / matrix
void pattern_read_2d_grid() {
    cout << "--- Pattern: Read 2D Grid ---" << nl;

    /*
    int n, m;
    cin >> n >> m;
    vvec<int> grid(n, vec<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> grid[i][j];
    */

    // For character grid:
    /*
    int n, m;
    cin >> n >> m;
    vec<string> grid(n);
    for (auto& row : grid) cin >> row;
    */
}

// Pattern 6: Read entire line (with spaces)
void pattern_read_line() {
    cout << "--- Pattern: Read Full Line ---" << nl;

    /*
    // IMPORTANT: After reading an integer with cin >>, there's a leftover '\n'
    // You MUST consume it before getline!

    int n;
    cin >> n;
    cin.ignore();  // Consume the leftover newline

    string line;
    getline(cin, line);  // Now this reads the actual next line
    */
}

// Pattern 7: Read space-separated integers from a single line (unknown count)
void pattern_read_line_of_ints() {
    cout << "--- Pattern: Read Line of Ints ---" << nl;

    /*
    string line;
    getline(cin, line);
    istringstream iss(line);

    vec<int> nums;
    int x;
    while (iss >> x) {
        nums.pb(x);
    }
    */
}

// -------------------------------------------------------------
// 2. OUTPUT PATTERNS
// -------------------------------------------------------------

// Pattern 1: Print array with space separator (NO trailing space)
void print_array_clean(const vec<int>& arr) {
    // GM Standard: No trailing space, newline at end
    for (int i = 0; i < sz(arr); i++) {
        if (i > 0) cout << ' ';
        cout << arr[i];
    }
    cout << nl;
    // For input  {1, 2, 3, 4, 5}
    // Output: "1 2 3 4 5\n"
}

// Pattern 2: Print with trailing space (simpler, usually accepted)
void print_array_simple(const vec<int>& arr) {
    for (int x : arr) cout << x << ' ';
    cout << nl;
    // Output: "1 2 3 4 5 \n"  (trailing space — usually OK in CP)
}

// Pattern 3: Print with custom separator
void print_array_sep(const vec<int>& arr, const string& sep = " ") {
    for (int i = 0; i < sz(arr); i++) {
        if (i > 0) cout << sep;
        cout << arr[i];
    }
    cout << nl;
}

// Pattern 4: Print YES/NO or "Yes"/"No" (case-sensitive!)
void print_yes_no(bool condition) {
    // Some problems want "YES"/"NO", others want "Yes"/"No"
    // ALWAYS check the problem statement!

    // Our macros handle the common case:
    if (condition) { YES; }
    else { NO; }
}

// Pattern 5: Print 2D grid
void print_2d_grid(const vvec<int>& grid) {
    for (auto& row : grid) {
        for (int i = 0; i < sz(row); i++) {
            if (i > 0) cout << ' ';
            cout << row[i];
        }
        cout << nl;
    }
}

// Pattern 6: Print with fixed precision (for floating point)
void print_float_precision() {
    ld val = 3.141592653589793;

    // Method 1: fixed + setprecision (in main usually)
    cout << fixed << setprecision(10) << val << nl;
    // Output: 3.1415926536

    // Method 2: printf-style (guaranteed formatting)
    printf("%.10Lf\n", val);
}

// Pattern 7: Print answer for each test case on new line
void print_multi_answers(const vec<i64>& answers) {
    // Pre-build entire output string for FAST output
    // GM Tip: For 10^5+ test cases, building string first is faster
    string out;
    out.reserve(answers.size() * 12); // Pre-allocate
    for (i64 ans : answers) {
        out += to_string(ans);
        out += '\n';
    }
    cout << out;
}

// -------------------------------------------------------------
// 3. ULTRA-FAST I/O (GM Level — for TLE-prone problems)
// -------------------------------------------------------------

// Method 1: Custom fast reader (reads character by character)
// Use when cin is too slow even with fast I/O flags
namespace FastIO {
    inline int readInt() {
        int x = 0;
        bool neg = false;
        char c = getchar_unlocked();
        while (c < '0' || c > '9') {
            if (c == '-') neg = true;
            c = getchar_unlocked();
        }
        while (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            c = getchar_unlocked();
        }
        return neg ? -x : x;
    }

    inline void writeInt(int x) {
        if (x < 0) {
            putchar_unlocked('-');
            x = -x;
        }
        if (x > 9) writeInt(x / 10);
        putchar_unlocked('0' + x % 10);
    }
}

// Method 2: Read entire input at once (for massive I/O)
/*
void read_entire_input() {
    // Read all of stdin into a string
    string input(istreambuf_iterator<char>(cin), {});
    istringstream iss(input);

    int n;
    iss >> n;
    vec<int> arr(n);
    for (auto& x : arr) iss >> x;
}
*/

// -------------------------------------------------------------
// 4. COMMON I/O PITFALLS (GM MUST-KNOW)
// -------------------------------------------------------------
/*
 * PITFALL 1: Mixing cin and scanf
 *   → After ios::sync_with_stdio(false), NEVER use scanf/printf
 *
 * PITFALL 2: Using endl instead of '\n'
 *   → endl = '\n' + flush. Flush is O(write_buffer) and SLOW.
 *   → For 10^5 lines, endl can add 0.5s!
 *
 * PITFALL 3: Forgetting cin.ignore() before getline
 *   → After cin >> n, the newline '\n' stays in buffer
 *   → getline reads an empty string instead of the next line
 *
 * PITFALL 4: Integer overflow in input
 *   → If values can be > 2×10^9, use long long
 *   → cin >> (long long) x;
 *
 * PITFALL 5: Not clearing data between test cases
 *   → vec<int> arr; // declared outside the loop
 *   → MUST clear or re-initialize for each test case!
 *
 * PITFALL 6: Trailing whitespace in output
 *   → Most CP judges accept trailing space, but some don't
 *   → Use the "if (i > 0) cout << ' '" pattern to be safe
 */

void solve() {
    cout << "╔════════════════════════════════════════╗" << nl;
    cout << "║  MODULE 02: Input / Output Patterns    ║" << nl;
    cout << "╚════════════════════════════════════════╝" << nl;

    // Demo output patterns with sample data
    vec<int> sample = {1, 2, 3, 4, 5};

    cout << nl << "Clean print: ";
    print_array_clean(sample);

    cout << "Simple print: ";
    print_array_simple(sample);

    cout << "Comma-separated: ";
    print_array_sep(sample, ", ");

    cout << "2D grid:" << nl;
    vvec<int> grid = {{1,2,3},{4,5,6},{7,8,9}};
    print_2d_grid(grid);

    cout << nl << "Float precision: ";
    print_float_precision();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    solve();

    return 0;
}

