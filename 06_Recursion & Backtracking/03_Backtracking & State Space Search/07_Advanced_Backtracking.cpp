/*
╔══════════════════════════════════════════════════════════════╗
║  07. ADVANCED BACKTRACKING — Rat in Maze, M-Coloring, etc.   ║
║  Level 3 — Backtracking & State Space Search                 ║
╚══════════════════════════════════════════════════════════════╝

🎯 Problems:
   1. Rat in a Maze — All Paths (GFG)
   2. M-Coloring Problem (Graph Coloring)
   3. Knight's Tour
   4. Generate Valid Parentheses — LC 22
   5. Unique Paths with Obstacles (Recursive)
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
template<class T> using vvec = vector<vector<T>>;

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'


// ═══════════════════════════════════════════════════════════
// 1️⃣ RAT IN A MAZE — All Paths
// ═══════════════════════════════════════════════════════════
/*
   Given NxN grid (0 = blocked, 1 = open). Start at (0,0),
   reach (N-1, N-1). Move: Down, Left, Right, Up.
   Print all paths as strings like "DRDDR".

   🧠 Classic grid backtracking:
   - Mark cell as visited
   - Try all 4 directions
   - Unmark (backtrack)
*/
class RatInMaze {
    int n;
    vvec<int> grid;
    vvec<bool> visited;
    vec<string> allPaths;

    // Direction arrays: D, L, R, U (sorted alphabetically for lexicographic order)
    int dr[4] = {1, 0, 0, -1};
    int dc[4] = {0, -1, 1, 0};
    char dir[4] = {'D', 'L', 'R', 'U'};

    void dfs(int r, int c, string& path) {
        if (r == n - 1 && c == n - 1) {
            allPaths.pb(path);
            return;
        }

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
            if (grid[nr][nc] == 0 || visited[nr][nc]) continue;

            visited[nr][nc] = true;     // CHOOSE
            path.pb(dir[d]);
            dfs(nr, nc, path);          // EXPLORE
            path.pop_back();             // UN-CHOOSE
            visited[nr][nc] = false;
        }
    }

public:
    vec<string> solve(vvec<int>& maze) {
        n = sz(maze);
        grid = maze;
        allPaths.clear();

        if (grid[0][0] == 0 || grid[n-1][n-1] == 0) return {};

        visited.assign(n, vec<bool>(n, false));
        visited[0][0] = true;

        string path;
        dfs(0, 0, path);
        return allPaths;
    }
};


// ═══════════════════════════════════════════════════════════
// 2️⃣ M-COLORING PROBLEM (Graph Coloring)
// ═══════════════════════════════════════════════════════════
/*
   Given undirected graph and M colors. Can you color all vertices
   such that no two adjacent vertices have the same color?

   🧠 For each vertex, try each color 1..M:
   - Check if any neighbor has same color
   - If valid: assign, recurse to next vertex
   - Backtrack

   Time: O(M^V) worst case
*/
class MColoring {
    int V, M;
    vvec<int> adj;
    vec<int> color;

    bool isSafe(int node, int c) {
        for (int neighbor : adj[node]) {
            if (color[neighbor] == c) return false;
        }
        return true;
    }

    bool solve(int node) {
        if (node == V) return true;  // All vertices colored!

        for (int c = 1; c <= M; c++) {
            if (isSafe(node, c)) {
                color[node] = c;           // CHOOSE
                if (solve(node + 1)) return true;  // EXPLORE
                color[node] = 0;           // UN-CHOOSE
            }
        }
        return false;  // No valid color for this vertex
    }

public:
    bool canColor(int vertices, int colors, vvec<int>& adjacency) {
        V = vertices;
        M = colors;
        adj = adjacency;
        color.assign(V, 0);
        return solve(0);
    }

    vec<int> getColoring() { return color; }
};


// ═══════════════════════════════════════════════════════════
// 3️⃣ GENERATE VALID PARENTHESES — LC 22
// ═══════════════════════════════════════════════════════════
/*
   Generate all valid combinations of n pairs of parentheses.

   n=3 → ["((()))","(()())","(())()","()(())","()()()"]

   🧠 At each step, we can:
   - Add '(' if open_count < n
   - Add ')' if close_count < open_count

   This is a constrained recursion — not all branches are valid.

   Time: O(4^n / sqrt(n)) — Catalan number
*/
void generateParentheses(int n, int open, int close,
                         string& current, vec<string>& result) {
    if (sz(current) == 2 * n) {
        result.pb(current);
        return;
    }

    if (open < n) {
        current.pb('(');
        generateParentheses(n, open + 1, close, current, result);
        current.pop_back();
    }

    if (close < open) {
        current.pb(')');
        generateParentheses(n, open, close + 1, current, result);
        current.pop_back();
    }
}


// ═══════════════════════════════════════════════════════════
// 4️⃣ KNIGHT'S TOUR
// ═══════════════════════════════════════════════════════════
/*
   Place a knight on NxN board. Visit every cell exactly once.

   Knight moves: 8 possible L-shaped moves

   Time: O(8^(N^2)) worst case — very expensive for large N
*/
class KnightsTour {
    int n;
    vvec<int> board;
    int moveX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int moveY[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    bool solve(int x, int y, int moveNum) {
        if (moveNum == n * n) return true;  // All cells visited!

        for (int i = 0; i < 8; i++) {
            int nx = x + moveX[i], ny = y + moveY[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (board[nx][ny] != -1) continue;

            board[nx][ny] = moveNum;        // CHOOSE
            if (solve(nx, ny, moveNum + 1)) return true;  // EXPLORE
            board[nx][ny] = -1;              // UN-CHOOSE
        }
        return false;
    }

public:
    bool findTour(int size) {
        n = size;
        board.assign(n, vec<int>(n, -1));
        board[0][0] = 0;
        return solve(0, 0, 1);
    }

    void printBoard() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << setw(4) << board[i][j];
            }
            cout << nl;
        }
    }
};


// ═══════════════════════════════════════════════════════════
// 5️⃣ EXPRESSION TARGET — Add +, -, * between digits
// ═══════════════════════════════════════════════════════════
/*
   LC 282: Expression Add Operators
   Given string of digits and target, insert +, -, * to reach target.

   "123", target=6 → ["1+2+3", "1*2*3"]

   This is a GM-level backtracking problem. The tricky part is
   handling multiplication precedence.
*/
void expressionTarget(const string& num, int index, i64 target,
                      i64 currentVal, i64 prevOperand,
                      string& expression, vec<string>& result) {
    if (index == sz(num)) {
        if (currentVal == target) result.pb(expression);
        return;
    }

    for (int len = 1; len + index <= sz(num); len++) {
        string part = num.substr(index, len);
        if (part.size() > 1 && part[0] == '0') break;  // No leading zeros

        i64 val = stoll(part);

        if (index == 0) {
            // First number: no operator
            expression += part;
            expressionTarget(num, index + len, target, val, val, expression, result);
            expression.erase(expression.size() - len);
        } else {
            // Try +
            expression += "+" + part;
            expressionTarget(num, index + len, target,
                           currentVal + val, val, expression, result);
            expression.erase(expression.size() - len - 1);

            // Try -
            expression += "-" + part;
            expressionTarget(num, index + len, target,
                           currentVal - val, -val, expression, result);
            expression.erase(expression.size() - len - 1);

            // Try * (undo previous add/sub, apply multiplication)
            expression += "*" + part;
            expressionTarget(num, index + len, target,
                           currentVal - prevOperand + prevOperand * val,
                           prevOperand * val, expression, result);
            expression.erase(expression.size() - len - 1);
        }
    }
}


// ═══════════════════════════════════════════════════════════
// 🧪 TEST
// ═══════════════════════════════════════════════════════════

void solve() {
    // 1. Rat in Maze
    {
        cout << "=== RAT IN MAZE ===" << nl;
        vvec<int> maze = {
            {1, 0, 0, 0},
            {1, 1, 0, 1},
            {1, 1, 0, 0},
            {0, 1, 1, 1}
        };
        RatInMaze rat;
        auto paths = rat.solve(maze);
        cout << "Paths: ";
        for (auto& p : paths) cout << p << " ";
        cout << nl;
    }

    // 2. Generate Parentheses
    {
        cout << nl << "=== VALID PARENTHESES (n=3) ===" << nl;
        string cur;
        vec<string> res;
        generateParentheses(3, 0, 0, cur, res);
        for (auto& s : res) cout << s << nl;
    }

    // 3. M-Coloring
    {
        cout << nl << "=== M-COLORING ===" << nl;
        // Graph: 0-1, 1-2, 2-3, 3-0, 0-2 (K4 minus one edge)
        vvec<int> adj = {{1, 3, 2}, {0, 2}, {1, 3, 0}, {2, 0}};
        MColoring mc;
        cout << "Can color with 3 colors? " << (mc.canColor(4, 3, adj) ? "YES" : "NO") << nl;
        auto coloring = mc.getColoring();
        for (int i = 0; i < 4; i++) cout << "Vertex " << i << " → Color " << coloring[i] << nl;
    }

    // 4. Expression Target
    {
        cout << nl << "=== EXPRESSION TARGET ===" << nl;
        cout << "num=\"123\", target=6:" << nl;
        string expr;
        vec<string> res;
        expressionTarget("123", 0, 6, 0, 0, expr, res);
        for (auto& s : res) cout << s << " = 6" << nl;
    }

    // 5. Knight's Tour (5x5)
    {
        cout << nl << "=== KNIGHT'S TOUR (5x5) ===" << nl;
        KnightsTour kt;
        if (kt.findTour(5)) {
            kt.printBoard();
        } else {
            cout << "No solution found" << nl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    while (TC--) solve();

    return 0;
}

