/*
 * ============================================================================
 *     STRING AUTOMATON DP — DP ON AHO-CORASICK & SUFFIX STRUCTURES
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : String DP — DP on Aho-Corasick, String Automaton, KMP Automaton
 * Level   : ⭐⭐⭐⭐⭐ Grandmaster / ICPC
 * ============================================================================
 *
 * DP ON STRING AUTOMATONS:
 *   Build a finite automaton (DFA) from patterns, then do DP on its states.
 *   dp[i][state] = number of strings of length i ending in automaton state
 *
 * PROBLEMS SOLVED:
 * 1. Count strings of length N over alphabet that DON'T contain a pattern
 * 2. Count strings containing at least one of multiple patterns (Aho-Corasick)
 * 3. KMP automaton DP — count strings avoiding a single pattern
 * 4. Combine with Matrix Exponentiation for huge N
 *
 * APPLICATIONS:
 * - Virus detection (avoid bad patterns)
 * - DNA sequence counting
 * - Password policy checking
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

/*
 * 1. KMP AUTOMATON DP
 *    Count strings of length N over alphabet of size SIGMA
 *    that do NOT contain pattern P as substring.
 *
 *    Build KMP failure function → automaton.
 *    State = length of longest prefix of P that is a suffix of current string.
 *    If state reaches |P|, pattern is found → forbidden.
 *
 *    dp[i][j] = number of strings of length i with KMP state j
 *    dp[0][0] = 1
 *    For each state j and character c:
 *      next_state = KMP_transition(j, c)
 *      if next_state != |P|: dp[i+1][next_state] += dp[i][j]
 */
class KMPAutomatonDP {
    vector<int> fail;
    vector<vector<int>> transition;
    int m;  // Pattern length
    int sigma;  // Alphabet size

    void buildKMP(string& pattern) {
        m = pattern.size();
        fail.assign(m + 1, 0);

        // Build failure function
        for (int i = 1; i < m; i++) {
            int j = fail[i];
            while (j > 0 && pattern[j] != pattern[i]) j = fail[j];
            fail[i + 1] = (pattern[j] == pattern[i]) ? j + 1 : 0;
        }

        // Build transition table
        transition.assign(m, vector<int>(sigma, 0));
        for (int state = 0; state < m; state++) {
            for (int c = 0; c < sigma; c++) {
                int j = state;
                while (j > 0 && (pattern[j] - 'a') != c) j = fail[j];
                if ((pattern[j] - 'a') == c) j++;
                transition[state][c] = j;
            }
        }
    }

public:
    KMPAutomatonDP(int sigma = 26) : sigma(sigma) {}

    // Count strings of length N that DON'T contain pattern
    long long countAvoiding(string& pattern, int N) {
        buildKMP(pattern);

        vector<vector<long long>> dp(N + 1, vector<long long>(m, 0));
        dp[0][0] = 1;

        for (int i = 0; i < N; i++) {
            for (int state = 0; state < m; state++) {
                if (dp[i][state] == 0) continue;
                for (int c = 0; c < sigma; c++) {
                    int nxt = transition[state][c];
                    if (nxt < m) {  // Don't count if pattern fully matched
                        dp[i + 1][nxt] = (dp[i + 1][nxt] + dp[i][state]) % MOD;
                    }
                }
            }
        }

        long long ans = 0;
        for (int j = 0; j < m; j++)
            ans = (ans + dp[N][j]) % MOD;
        return ans;
    }

    // With Matrix Exponentiation for huge N
    long long countAvoidingMatExp(string& pattern, long long N) {
        buildKMP(pattern);

        typedef vector<vector<long long>> Matrix;
        int sz = m;

        // Build transition matrix
        Matrix T(sz, vector<long long>(sz, 0));
        for (int state = 0; state < sz; state++) {
            for (int c = 0; c < sigma; c++) {
                int nxt = transition[state][c];
                if (nxt < sz) {
                    T[nxt][state] = (T[nxt][state] + 1) % MOD;
                }
            }
        }

        // Matrix power
        auto matMul = [&](Matrix& A, Matrix& B) -> Matrix {
            Matrix C(sz, vector<long long>(sz, 0));
            for (int i = 0; i < sz; i++)
                for (int k = 0; k < sz; k++) {
                    if (A[i][k] == 0) continue;
                    for (int j = 0; j < sz; j++)
                        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            return C;
        };

        // T^N
        Matrix result(sz, vector<long long>(sz, 0));
        for (int i = 0; i < sz; i++) result[i][i] = 1;

        long long exp = N;
        while (exp > 0) {
            if (exp & 1) result = matMul(result, T);
            T = matMul(T, T);
            exp >>= 1;
        }

        long long ans = 0;
        for (int j = 0; j < sz; j++)
            ans = (ans + result[j][0]) % MOD;
        return ans;
    }
};

/*
 * 2. AHO-CORASICK DP
 *    Multiple patterns. Count strings of length N containing NONE of them.
 *
 *    Build Aho-Corasick automaton from all patterns.
 *    Mark "dangerous" states (where any pattern ends).
 *    DP on automaton avoiding dangerous states.
 */
class AhoCorasickDP {
    static const int SIGMA = 26;

    struct Node {
        int children[SIGMA];
        int fail;
        bool is_end;  // Any pattern ends here or at any suffix link ancestor
        Node() {
            memset(children, -1, sizeof(children));
            fail = 0;
            is_end = false;
        }
    };

    vector<Node> trie;

    void buildTrie(vector<string>& patterns) {
        trie.clear();
        trie.push_back(Node());

        for (auto& p : patterns) {
            int cur = 0;
            for (char c : p) {
                int idx = c - 'a';
                if (trie[cur].children[idx] == -1) {
                    trie[cur].children[idx] = trie.size();
                    trie.push_back(Node());
                }
                cur = trie[cur].children[idx];
            }
            trie[cur].is_end = true;
        }
    }

    void buildFailLinks() {
        queue<int> q;
        for (int c = 0; c < SIGMA; c++) {
            if (trie[0].children[c] == -1)
                trie[0].children[c] = 0;
            else {
                trie[trie[0].children[c]].fail = 0;
                q.push(trie[0].children[c]);
            }
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            trie[u].is_end = trie[u].is_end || trie[trie[u].fail].is_end;

            for (int c = 0; c < SIGMA; c++) {
                if (trie[u].children[c] == -1) {
                    trie[u].children[c] = trie[trie[u].fail].children[c];
                } else {
                    trie[trie[u].children[c]].fail = trie[trie[u].fail].children[c];
                    q.push(trie[u].children[c]);
                }
            }
        }
    }

public:
    // Count strings of length N over lowercase that contain NONE of the patterns
    long long countAvoiding(vector<string>& patterns, int N) {
        buildTrie(patterns);
        buildFailLinks();

        int states = trie.size();
        vector<vector<long long>> dp(N + 1, vector<long long>(states, 0));
        dp[0][0] = 1;

        for (int i = 0; i < N; i++) {
            for (int s = 0; s < states; s++) {
                if (dp[i][s] == 0) continue;
                if (trie[s].is_end) continue;  // Dangerous state

                for (int c = 0; c < SIGMA; c++) {
                    int nxt = trie[s].children[c];
                    if (!trie[nxt].is_end) {
                        dp[i + 1][nxt] = (dp[i + 1][nxt] + dp[i][s]) % MOD;
                    }
                }
            }
        }

        long long ans = 0;
        for (int s = 0; s < states; s++)
            if (!trie[s].is_end)
                ans = (ans + dp[N][s]) % MOD;
        return ans;
    }

    // Total strings of length N = 26^N
    // Strings containing at least one pattern = 26^N - countAvoiding
    long long countContaining(vector<string>& patterns, int N) {
        long long total = 1;
        for (int i = 0; i < N; i++) total = total * SIGMA % MOD;
        long long avoiding = countAvoiding(patterns, N);
        return (total - avoiding + MOD) % MOD;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== STRING AUTOMATON DP ===" << endl;

    // KMP Automaton DP — single pattern
    KMPAutomatonDP kmp(2);  // Binary alphabet
    string pattern = "aa";
    cout << "\n--- KMP Automaton DP ---" << endl;
    cout << "Binary strings of length N avoiding \"" << pattern << "\":" << endl;
    for (int n = 1; n <= 10; n++)
        cout << "N=" << n << ": " << kmp.countAvoiding(pattern, n) << " ";
    cout << endl;
    // Should be Fibonacci: 2, 3, 5, 8, 13, 21, ...

    // KMP with Matrix Expo for huge N
    cout << "N=10^18: " << kmp.countAvoidingMatExp(pattern, 1000000000000000000LL) << endl;

    // Aho-Corasick DP — multiple patterns
    AhoCorasickDP ac;
    vector<string> patterns = {"ab", "cd"};
    cout << "\n--- Aho-Corasick DP ---" << endl;
    cout << "Strings of length N over {a-z} avoiding {\"ab\", \"cd\"}:" << endl;
    for (int n = 1; n <= 5; n++)
        cout << "N=" << n << ": " << ac.countAvoiding(patterns, n) << endl;

    // Count containing at least one pattern
    cout << "\nStrings CONTAINING at least one of {\"ab\", \"cd\"}:" << endl;
    for (int n = 1; n <= 5; n++)
        cout << "N=" << n << ": " << ac.countContaining(patterns, n) << endl;

    cout << "\n============================================" << endl;
    cout << "  STRING AUTOMATON DP SUMMARY:" << endl;
    cout << "  1. Build automaton (KMP / Aho-Corasick)" << endl;
    cout << "  2. Mark dangerous states (pattern matches)" << endl;
    cout << "  3. DP on states: dp[len][state]" << endl;
    cout << "  4. For huge N: Matrix Exponentiation" << endl;
    cout << "============================================" << endl;

    return 0;
}

