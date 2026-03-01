/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Greedy Interactive Problems
 *  Level   : Grandmaster
 * ============================================================================
 *
 *  ▶ WHAT ARE INTERACTIVE PROBLEMS?
 *  ────────────────────────────────
 *  In interactive problems, you DON'T get the full input upfront.
 *  Instead, you ASK QUERIES to a judge and receive answers.
 *  You must find the answer using a LIMITED number of queries.
 *
 *  ▶ GREEDY STRATEGIES FOR INTERACTIVE:
 *  ────────────────────────────────────
 *  1. BINARY SEARCH INTERACTIVE: Narrow down the answer space with each query
 *  2. ELIMINATION: Each query eliminates at least half the candidates
 *  3. INFORMATION GAIN: Each query maximizes information gained
 *  4. ADAPTIVE GREEDY: Adjust strategy based on judge responses
 *
 *  ▶ COMMON PATTERNS (Codeforces):
 *  ───────────────────────────────
 *  - "Guess the number" → binary search (log N queries)
 *  - "Find the hidden permutation" → comparison-based greedy
 *  - "GCD queries" → use GCD properties to narrow candidates
 *  - "Find the special element" → tournament-style elimination
 *
 *  ▶ IMPORTANT RULES:
 *  ──────────────────
 *  1. Always flush output after each query: cout << endl; or cout.flush();
 *  2. Read the judge's response before making the next query
 *  3. Stay within the query limit!
 *  4. Handle edge cases carefully (judge is adversarial)
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================================
// TEMPLATE: Interactive Binary Search (Guess the Number)
// ============================================================================
/*
 * Problem: Judge has a number X in [1, N]. You can ask "? Y" and judge
 * responds "1" if X > Y, "0" if X == Y, "-1" if X < Y.
 * Find X in at most ceil(log2(N)) queries.
 */
void interactiveBinarySearch(int n) {
    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        cout << "? " << mid << endl; // Query
        cout.flush();

        int response;
        cin >> response;

        if (response == 0) {
            cout << "! " << mid << endl;
            return;
        } else if (response == 1) {
            lo = mid + 1; // X > mid
        } else {
            hi = mid - 1; // X < mid
        }
    }
    cout << "! " << lo << endl;
    cout.flush();
}

// ============================================================================
// CF 1762D Style: GCD Queries — Find element using GCD
// ============================================================================
/*
 * Problem sketch: Hidden permutation of [1..N]. You can query "? i j"
 * which returns gcd(p[i], p[j]). Find the index of element 1.
 *
 * Key insight: gcd(1, x) = 1 for all x. So if gcd query returns 1,
 * at least one of the two elements is 1 (or they're coprime).
 *
 * Greedy strategy: Tournament-style elimination.
 * - Start with candidate = index 1
 * - For each index i from 2 to N:
 *   Query gcd(candidate, i)
 *   If result != 1, the value at 'candidate' is NOT 1 → candidate = i
 *   If result == 1, one of them could be 1 → keep current candidate
 *     (but need second check)
 *
 * After tournament, verify the winner with a few more queries.
 * Total queries: ~2N (within typical limits)
 */

// ============================================================================
// Template: Interactive Problem with Adaptive Greedy
// ============================================================================
/*
 * General template for interactive CF problems:
 *
 * int main() {
 *     int t;
 *     cin >> t;
 *     while (t--) {
 *         int n;
 *         cin >> n;
 *
 *         // Phase 1: Gather information with queries
 *         int candidate = 0;
 *         for (int i = 1; i < n; i++) {
 *             cout << "? " << candidate + 1 << " " << i + 1 << endl;
 *             cout.flush();
 *             int response;
 *             cin >> response;
 *
 *             // Greedy: update candidate based on response
 *             if (shouldSwitch(response)) {
 *                 candidate = i;
 *             }
 *         }
 *
 *         // Phase 2: Output answer
 *         cout << "! " << candidate + 1 << endl;
 *         cout.flush();
 *
 *         // Read verdict (some problems require this)
 *         int verdict;
 *         cin >> verdict;
 *         if (verdict == -1) return 0; // Wrong answer
 *     }
 *     return 0;
 * }
 */

int main() {
    // This is a template file — actual interactive problems
    // must be run against a judge.
    cout << "=== Interactive Greedy Templates ===" << endl;
    cout << "1. Binary Search Interactive: O(log N) queries" << endl;
    cout << "2. Tournament Elimination: O(N) queries" << endl;
    cout << "3. GCD-based: O(N) queries with GCD properties" << endl;
    cout << "4. Adaptive Greedy: Adjust based on responses" << endl;
    cout << endl;
    cout << "KEY RULE: Always flush output!" << endl;
    cout << "  cout << endl;  // This flushes" << endl;
    cout << "  cout.flush();  // Or this" << endl;
    return 0;
}

