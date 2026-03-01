/*
╔══════════════════════════════════════════════════════════════╗
║  06. BACKTRACKING FUNDAMENTALS — Permutations & N-Queens     ║
║  Level 3 — Backtracking & State Space Search                 ║
╚══════════════════════════════════════════════════════════════╝

════════════════════════════════════════════════════════════════
📖 WHAT IS BACKTRACKING?
════════════════════════════════════════════════════════════════

Backtracking = Recursion + UNDO (go back and try other options)

Pattern:
    1. CHOOSE  — pick an option
    2. EXPLORE — recurse with that option
    3. UN-CHOOSE — undo the option (backtrack)
    4. Try next option

════════════════════════════════════════════════════════════════
🏗️ BACKTRACKING TEMPLATE
════════════════════════════════════════════════════════════════

    void backtrack(state, choices) {
        if (goal_reached) {
            add to results;
            return;
        }

        for (each choice in choices) {
            if (isValid(choice)) {
                make(choice);                    // CHOOSE
                backtrack(updated_state);         // EXPLORE
                undo(choice);                     // UN-CHOOSE
            }
        }
    }

════════════════════════════════════════════════════════════════
💡 BACKTRACKING vs BRUTE FORCE
════════════════════════════════════════════════════════════════

Brute force: Generate ALL possibilities, then filter valid ones
Backtracking: PRUNE invalid branches EARLY (much faster!)

                    root
                   / | \
                  a   b   c
                 /|   |   |\
                b  c  ✗   a  b    ← if 'b' is invalid, DON'T go deeper
               /       \
              c         ✗

════════════════════════════════════════════════════════════════

🎯 Problems:
   1. Permutations — LC 46
   2. Permutations II (with duplicates) — LC 47
   3. N-Queens — LC 51
   4. Sudoku Solver — LC 37
   5. Palindrome Partitioning — LC 131
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

using i64 = long long;
template<class T> using vec = vector<T>;

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}


// ═══════════════════════════════════════════════════════════
// 1️⃣ PERMUTATIONS — LC 46
// ═══════════════════════════════════════════════════════════
/*
   Given distinct integers, return all possible permutations.

   [1,2,3] → [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

   Total permutations = n!

   ═══ METHOD 1: Using visited array ═══

   At each position, try every element that hasn't been used yet.

   Recursion tree for [1,2,3]:
                          []
                    /      |      \
                [1]       [2]      [3]
               /   \     /   \    /   \
           [1,2] [1,3] [2,1][2,3][3,1][3,2]
            |     |     |    |    |    |
         [1,2,3][1,3,2][2,1,3]...

   Time: O(n! * n), Space: O(n)
*/

// Method 1: Visited array
void permute_v1(vec<int>& nums, vec<bool>& visited,
                vec<int>& current, vec<vec<int>>& result) {
    if (sz(current) == sz(nums)) {
        result.pb(current);
        return;
    }

    for (int i = 0; i < sz(nums); i++) {
        if (visited[i]) continue;  // Already used

        visited[i] = true;         // CHOOSE
        current.pb(nums[i]);
        permute_v1(nums, visited, current, result);  // EXPLORE
        current.pop_back();         // UN-CHOOSE
        visited[i] = false;
    }
}

/*
   ═══ METHOD 2: Swap-based (more efficient, in-place) ═══

   Idea: Fix element at position `index` by swapping with each
         element from index to n-1.

   No extra visited array needed!
*/
void permute_v2(vec<int>& nums, int index, vec<vec<int>>& result) {
    if (index == sz(nums)) {
        result.pb(nums);
        return;
    }

    for (int i = index; i < sz(nums); i++) {
        swap(nums[index], nums[i]);       // CHOOSE (fix nums[i] at position index)
        permute_v2(nums, index + 1, result);  // EXPLORE
        swap(nums[index], nums[i]);       // UN-CHOOSE (backtrack)
    }
}


// ═══════════════════════════════════════════════════════════
// 2️⃣ PERMUTATIONS II (with duplicates) — LC 47
// ═══════════════════════════════════════════════════════════
/*
   Input may have duplicates. Return unique permutations.

   [1,1,2] → [[1,1,2], [1,2,1], [2,1,1]]

   🧠 KEY: Sort + skip rule
   At each level, don't place the same value twice at the same position.

   Rule: if nums[i] == nums[i-1] AND visited[i-1] == false, SKIP
   (This means the previous duplicate was NOT used at an earlier
    position in the current branch, so we'd create a duplicate branch)
*/
void permuteUnique(vec<int>& nums, vec<bool>& visited,
                   vec<int>& current, vec<vec<int>>& result) {
    if (sz(current) == sz(nums)) {
        result.pb(current);
        return;
    }

    for (int i = 0; i < sz(nums); i++) {
        if (visited[i]) continue;

        // Skip duplicates: same value AND previous duplicate not used
        if (i > 0 && nums[i] == nums[i - 1] && !visited[i - 1]) continue;

        visited[i] = true;
        current.pb(nums[i]);
        permuteUnique(nums, visited, current, result);
        current.pop_back();
        visited[i] = false;
    }
}


// ═══════════════════════════════════════════════════════════
// 3️⃣ N-QUEENS — LC 51
// ═══════════════════════════════════════════════════════════
/*
   Place N queens on an NxN board such that no two queens attack
   each other (no same row, column, or diagonal).

   🧠 Approach: Place one queen per ROW. For each row, try every column.

   Validity check: for position (row, col), check:
   - Column: no queen in same column above
   - Left diagonal: (row-1, col-1), (row-2, col-2), ...
   - Right diagonal: (row-1, col+1), (row-2, col+2), ...

   ═══ OPTIMIZATION: Use 3 boolean arrays ═══
   - col[c]    = true if column c has a queen
   - diag1[d]  = true if left-diagonal d has a queen  (d = row - col + n - 1)
   - diag2[d]  = true if right-diagonal d has a queen (d = row + col)

   This makes isSafe() O(1) instead of O(n)!

   Time: O(n!), Space: O(n^2) for the board
*/

class NQueens {
    int n;
    vec<string> board;
    vec<bool> colUsed, diag1Used, diag2Used;
    vec<vec<string>> results;

public:
    vec<vec<string>> solveNQueens(int _n) {
        n = _n;
        board.assign(n, string(n, '.'));
        colUsed.assign(n, false);
        diag1Used.assign(2 * n, false);
        diag2Used.assign(2 * n, false);
        results.clear();

        backtrack(0);
        return results;
    }

private:
    void backtrack(int row) {
        if (row == n) {
            results.pb(board);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (colUsed[col] || diag1Used[row - col + n - 1] || diag2Used[row + col])
                continue;  // Not safe → PRUNE

            // CHOOSE
            board[row][col] = 'Q';
            colUsed[col] = diag1Used[row - col + n - 1] = diag2Used[row + col] = true;

            // EXPLORE
            backtrack(row + 1);

            // UN-CHOOSE (backtrack)
            board[row][col] = '.';
            colUsed[col] = diag1Used[row - col + n - 1] = diag2Used[row + col] = false;
        }
    }
};


// ═══════════════════════════════════════════════════════════
// 4️⃣ SUDOKU SOLVER — LC 37
// ═══════════════════════════════════════════════════════════
/*
   Fill a 9x9 grid so that each row, column, and 3x3 box
   contains digits 1-9 exactly once.

   🧠 Approach: Find first empty cell, try digits 1-9,
   check validity, recurse, backtrack.

   Time: O(9^(empty_cells)), but with pruning it's much faster
*/

class SudokuSolver {
    bool rowUsed[9][10], colUsed[9][10], boxUsed[9][10];

    int boxIndex(int r, int c) { return (r / 3) * 3 + c / 3; }

    bool isValid(int r, int c, int num) {
        return !rowUsed[r][num] && !colUsed[c][num] && !boxUsed[boxIndex(r, c)][num];
    }

    bool solve(vec<vec<char>>& board) {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (board[r][c] != '.') continue;

                for (int num = 1; num <= 9; num++) {
                    if (!isValid(r, c, num)) continue;

                    // CHOOSE
                    board[r][c] = '0' + num;
                    rowUsed[r][num] = colUsed[c][num] = boxUsed[boxIndex(r, c)][num] = true;

                    // EXPLORE
                    if (solve(board)) return true;  // Found solution!

                    // UN-CHOOSE
                    board[r][c] = '.';
                    rowUsed[r][num] = colUsed[c][num] = boxUsed[boxIndex(r, c)][num] = false;
                }

                return false;  // No valid digit for this cell
            }
        }
        return true;  // All cells filled!
    }

public:
    void solveSudoku(vec<vec<char>>& board) {
        memset(rowUsed, 0, sizeof(rowUsed));
        memset(colUsed, 0, sizeof(colUsed));
        memset(boxUsed, 0, sizeof(boxUsed));

        // Initialize used arrays from existing board
        for (int r = 0; r < 9; r++)
            for (int c = 0; c < 9; c++)
                if (board[r][c] != '.') {
                    int num = board[r][c] - '0';
                    rowUsed[r][num] = colUsed[c][num] = boxUsed[boxIndex(r, c)][num] = true;
                }

        solve(board);
    }
};


// ═══════════════════════════════════════════════════════════
// 5️⃣ PALINDROME PARTITIONING — LC 131
// ═══════════════════════════════════════════════════════════
/*
   Partition string s such that every substring is a palindrome.
   Return all possible partitions.

   "aab" → [["a","a","b"], ["aa","b"]]

   🧠 Approach: At each position, try every possible substring
   starting from that position. If it's a palindrome, recurse
   for the rest.
*/
bool isPalin(const string& s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}

void palindromePartition(const string& s, int start,
                         vec<string>& current, vec<vec<string>>& result) {
    if (start == sz(s)) {
        result.pb(current);
        return;
    }

    for (int end = start; end < sz(s); end++) {
        if (isPalin(s, start, end)) {           // Only if palindrome
            current.pb(s.substr(start, end - start + 1));  // CHOOSE
            palindromePartition(s, end + 1, current, result);  // EXPLORE
            current.pop_back();                                 // UN-CHOOSE
        }
    }
}


// ═══════════════════════════════════════════════════════════
// 6️⃣ WORD SEARCH — LC 79
// ═══════════════════════════════════════════════════════════
/*
   Given 2D board of chars and a word, check if word exists
   by moving horizontally/vertically (adjacent cells).
   Each cell used at most once.

   🧠 DFS + Backtracking on a grid
*/
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool wordSearchDFS(vec<vec<char>>& board, const string& word,
                   int r, int c, int idx) {
    if (idx == sz(word)) return true;  // Found entire word
    if (r < 0 || r >= sz(board) || c < 0 || c >= sz(board[0])) return false;
    if (board[r][c] != word[idx]) return false;

    char temp = board[r][c];
    board[r][c] = '#';  // Mark visited (CHOOSE)

    for (int d = 0; d < 4; d++) {
        if (wordSearchDFS(board, word, r + dx[d], c + dy[d], idx + 1))
            return true;
    }

    board[r][c] = temp;  // Restore (UN-CHOOSE / backtrack)
    return false;
}

bool wordSearch(vec<vec<char>>& board, const string& word) {
    for (int i = 0; i < sz(board); i++)
        for (int j = 0; j < sz(board[0]); j++)
            if (wordSearchDFS(board, word, i, j, 0))
                return true;
    return false;
}


// ═══════════════════════════════════════════════════════════
// 7️⃣ LETTER COMBINATIONS OF A PHONE NUMBER — LC 17
// ═══════════════════════════════════════════════════════════
/*
   digits = "23" → ["ad","ae","af","bd","be","bf","cd","ce","cf"]

   Each digit maps to letters. Explore all combinations.
*/
string phoneMap[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

void letterCombinations(const string& digits, int index,
                        string& current, vec<string>& result) {
    if (index == sz(digits)) {
        if (!current.empty()) result.pb(current);
        return;
    }

    string& letters = phoneMap[digits[index] - '0'];
    for (char c : letters) {
        current.pb(c);                                      // CHOOSE
        letterCombinations(digits, index + 1, current, result);  // EXPLORE
        current.pop_back();                                  // UN-CHOOSE
    }
}


// ═══════════════════════════════════════════════════════════
// 🧪 TEST
// ═══════════════════════════════════════════════════════════

void solve() {
    // 1. Permutations
    {
        cout << "=== PERMUTATIONS of [1,2,3] ===" << nl;
        vec<int> nums = {1, 2, 3};
        vec<vec<int>> res;
        permute_v2(nums, 0, res);
        for (auto& p : res) {
            cout << "[";
            for (int i = 0; i < sz(p); i++) cout << p[i] << (i+1<sz(p)?",":"");
            cout << "]" << nl;
        }
    }

    // 2. Permutations with duplicates
    {
        cout << nl << "=== UNIQUE PERMUTATIONS of [1,1,2] ===" << nl;
        vec<int> nums = {1, 1, 2};
        sort(all(nums));  // MUST SORT!
        vec<bool> vis(sz(nums), false);
        vec<int> cur;
        vec<vec<int>> res;
        permuteUnique(nums, vis, cur, res);
        for (auto& p : res) {
            cout << "[";
            for (int i = 0; i < sz(p); i++) cout << p[i] << (i+1<sz(p)?",":"");
            cout << "]" << nl;
        }
    }

    // 3. N-Queens
    {
        cout << nl << "=== N-QUEENS (N=4) ===" << nl;
        NQueens nq;
        auto solutions = nq.solveNQueens(4);
        cout << "Number of solutions: " << sz(solutions) << nl;
        for (auto& sol : solutions) {
            for (auto& row : sol) cout << row << nl;
            cout << "---" << nl;
        }
    }

    // 4. Palindrome Partitioning
    {
        cout << nl << "=== PALINDROME PARTITIONING of 'aab' ===" << nl;
        vec<string> cur;
        vec<vec<string>> res;
        palindromePartition("aab", 0, cur, res);
        for (auto& p : res) {
            cout << "[";
            for (int i = 0; i < sz(p); i++) cout << "\"" << p[i] << "\"" << (i+1<sz(p)?",":"");
            cout << "]" << nl;
        }
    }

    // 5. Letter Combinations
    {
        cout << nl << "=== LETTER COMBINATIONS of '23' ===" << nl;
        string cur;
        vec<string> res;
        letterCombinations("23", 0, cur, res);
        for (auto& s : res) cout << "\"" << s << "\" ";
        cout << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    while (TC--) solve();

    return 0;
}

