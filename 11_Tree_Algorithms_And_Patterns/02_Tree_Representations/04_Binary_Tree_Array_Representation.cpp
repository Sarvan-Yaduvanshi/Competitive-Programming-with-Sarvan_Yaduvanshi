/*
╔══════════════════════════════════════════════════════════════════╗
║       04 — BINARY TREE ARRAY REPRESENTATION                     ║
║       Zero to GM Level — Tree Representations                    ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CONCEPT
═══════════════════════════════════════════════════════════════════

 Store a COMPLETE binary tree in an array using INDEX MATH:
   - Root at index 1
   - Left child of i  → 2*i
   - Right child of i → 2*i + 1
   - Parent of i      → i/2

 This is used in:
   ✅ Binary Heaps (priority queues)
   ✅ Segment Trees
   ✅ Tournament Trees

═══════════════════════════════════════════════════════════════════
 VISUALIZATION
═══════════════════════════════════════════════════════════════════

 Tree:
              1
            /   \
           2     3
          / \   / \
         4   5 6   7

 Array (1-indexed):
 Index:  1  2  3  4  5  6  7
 Value: [1][2][3][4][5][6][7]

 Relationship:
   node 1: left=2*1=2, right=2*1+1=3, parent=none
   node 2: left=2*2=4, right=2*2+1=5, parent=2/2=1
   node 3: left=2*3=6, right=2*3+1=7, parent=3/2=1
   node 4: left=2*4=8(nil), right=9(nil), parent=4/2=2
   node 5: parent=5/2=2
   node 6: parent=6/2=3
   node 7: parent=7/2=3

 MEMORY LAYOUT:
  ┌───┬───┬───┬───┬───┬───┬───┬───┐
  │ _ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │
  └───┴───┴───┴───┴───┴───┴───┴───┘
   [0] [1] [2] [3] [4] [5] [6] [7]
         │
    index 0 unused (1-indexed)

═══════════════════════════════════════════════════════════════════
 INCOMPLETE TREE EXAMPLE
═══════════════════════════════════════════════════════════════════

 Tree:
              A
            /   \
           B     C
          /       \
         D         G

 Array: [_, A, B, C, D, _, _, G]
          0  1  2  3  4  5  6  7

 Node B (index 2): left=4 (D), right=5 (empty)
 Node C (index 3): left=6 (empty), right=7 (G)

 ⚠️ Problem: Gaps waste memory!
 For a DEGENERATE tree of height h:
   Array needs 2^h entries, but only h+1 are filled!
   → Extremely wasteful for unbalanced trees

═══════════════════════════════════════════════════════════════════
 SEGMENT TREE LAYOUT (MOST IMPORTANT IN CP!)
═══════════════════════════════════════════════════════════════════

 Segment tree for array [3, 1, 4, 1, 5] (sum queries):

 Index 1 stores sum of entire range [0..4]
 Index 2 stores sum of [0..2], Index 3 stores sum of [3..4]
 And so on...

                  14 [1]           ← sum(0..4) = 14
                /       \
           8 [2]         6 [3]     ← sum(0..2)=8, sum(3..4)=6
          /    \        /    \
       4 [4]  4 [5]  1 [6]  5 [7] ← sum(0..1)=4, sum(2..2)=4, ...
      /   \     |
   3 [8] 1 [9] 4 [10]             ← individual elements

 Array: [_, 14, 8, 6, 4, 4, 1, 5, 3, 1, 4]
              1  2  3  4  5  6  7  8  9  10

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────┬────────────┬────────────────────┐
 │ Operation                │ Time       │ Space              │
 ├──────────────────────────┼────────────┼────────────────────┤
 │ Access node i            │ O(1)       │ —                  │
 │ Find parent              │ O(1) i/2   │ —                  │
 │ Find left child          │ O(1) 2*i   │ —                  │
 │ Find right child         │ O(1) 2*i+1 │ —                  │
 │ Space (complete tree)    │ —          │ O(N) exact         │
 │ Space (degenerate tree)  │ —          │ O(2^N) ❌ terrible │
 │ Space (segment tree)     │ —          │ O(4*N) safe        │
 └──────────────────────────┴────────────┴────────────────────┘

═══════════════════════════════════════════════════════════════════
 CODE
═══════════════════════════════════════════════════════════════════
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
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

// ═══════════════════════════════════════════════════════════════
// Binary Heap using array representation (MIN HEAP)
// ═══════════════════════════════════════════════════════════════
struct MinHeap {
    vec<int> heap; // 1-indexed

    MinHeap() { heap.pb(0); } // placeholder for index 0

    int parent(int i) { return i / 2; }
    int left(int i) { return 2 * i; }
    int right(int i) { return 2 * i + 1; }

    void push(int val) {
        heap.pb(val);
        // Bubble up
        int i = sz(heap) - 1;
        while (i > 1 && heap[i] < heap[parent(i)]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    int top() { return heap[1]; }

    void pop() {
        heap[1] = heap.back();
        heap.pop_back();
        // Bubble down
        int i = 1, n = sz(heap) - 1;
        while (left(i) <= n) {
            int smallest = i;
            if (left(i) <= n && heap[left(i)] < heap[smallest])
                smallest = left(i);
            if (right(i) <= n && heap[right(i)] < heap[smallest])
                smallest = right(i);
            if (smallest == i) break;
            swap(heap[i], heap[smallest]);
            i = smallest;
        }
    }

    bool empty() { return sz(heap) <= 1; }

    void print() {
        cout << "Heap array: [";
        for (int i = 1; i < sz(heap); i++) {
            if (i > 1) cout << ", ";
            cout << heap[i];
        }
        cout << "]" << nl;

        // Print as tree
        if (sz(heap) <= 1) return;
        cout << "As tree:" << nl;
        int level = 0, count = 1, idx = 1;
        while (idx < sz(heap)) {
            int spaces = (1 << (3 - level)) - 1;
            for (int i = 0; i < count && idx < sz(heap); i++, idx++) {
                cout << string(i == 0 ? spaces : 2*spaces+1, ' ') << heap[idx];
            }
            cout << nl;
            level++;
            count *= 2;
        }
    }
};

void solve() {
    int n;
    cin >> n;

    MinHeap heap;

    cout << "Building min-heap by inserting elements:" << nl;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        heap.push(x);
        cout << "  Insert " << x << ": ";
        heap.print();
    }

    cout << nl << "Extracting elements (sorted order):" << nl;
    while (!heap.empty()) {
        cout << "  Min = " << heap.top();
        heap.pop();
        cout << ", after pop: ";
        heap.print();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    cin >> TC;
    while (TC--) solve();

    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE INPUT / OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
5
5 3 8 1 4

Output shows heap building and extraction process.

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Array index math: left=2i, right=2i+1, parent=i/2
 ✅ Perfect for COMPLETE binary trees (no wasted space)
 ✅ Used in: Binary Heaps, Segment Trees, Tournament Trees
 ✅ DON'T use for general/unbalanced trees (wastes space)
 ✅ For segment tree: allocate 4*N to be safe
═══════════════════════════════════════════════════════════════════
*/

