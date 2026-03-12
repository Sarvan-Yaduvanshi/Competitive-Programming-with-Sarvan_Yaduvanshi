/*
╔══════════════════════════════════════════════════════════════════╗
║  01 — TRIE (Prefix Tree) — String & XOR Applications           ║
║  Zero to GM Level — Special Trees                                ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 WHAT IS A TRIE?
═══════════════════════════════════════════════════════════════════

 A tree where each edge represents a character.
 Path from root to node = a prefix.
 Used for: fast string prefix queries, autocomplete, XOR problems.

═══════════════════════════════════════════════════════════════════
 VISUALIZATION
═══════════════════════════════════════════════════════════════════

 Insert: "app", "apple", "apt", "bat"

            (root)
           /      \
          a        b
          |        |
          p        a
         / \       |
        p   t*     t*
        |
        l
        |
        e*

 * = end of word

═══════════════════════════════════════════════════════════════════
 DRY RUN — INSERT "apple"
═══════════════════════════════════════════════════════════════════

 Start at root.
 'a': child 'a' exists? If not, create. Move to it.
 'p': child 'p' exists? If not, create. Move to it.
 'p': child 'p' exists? If not, create. Move to it.
 'l': child 'l' exists? If not, create. Move to it.
 'e': child 'e' exists? If not, create. Move to it.
 Mark as end of word.

═══════════════════════════════════════════════════════════════════
 CODE — String Trie + XOR Trie
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
template<class T> using vec = vector<T>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

// ═══════════════════════════════════════════════════════════
// STRING TRIE
// ═══════════════════════════════════════════════════════════
struct Trie {
    int children[26];
    int cnt; // number of strings ending here
    int prefix_cnt; // number of strings passing through here
};

const int MAX_TRIE = 1000005;
Trie trie[MAX_TRIE];
int trieSize;

void trieInit() {
    trieSize = 1;
    memset(trie[0].children, -1, sizeof(trie[0].children));
    trie[0].cnt = 0;
    trie[0].prefix_cnt = 0;
}

void trieInsert(const string& s) {
    int cur = 0;
    for (char c : s) {
        int idx = c - 'a';
        if (trie[cur].children[idx] == -1) {
            trie[cur].children[idx] = trieSize;
            memset(trie[trieSize].children, -1, sizeof(trie[trieSize].children));
            trie[trieSize].cnt = 0;
            trie[trieSize].prefix_cnt = 0;
            trieSize++;
        }
        cur = trie[cur].children[idx];
        trie[cur].prefix_cnt++;
    }
    trie[cur].cnt++;
}

bool trieSearch(const string& s) {
    int cur = 0;
    for (char c : s) {
        int idx = c - 'a';
        if (trie[cur].children[idx] == -1) return false;
        cur = trie[cur].children[idx];
    }
    return trie[cur].cnt > 0;
}

int countWithPrefix(const string& prefix) {
    int cur = 0;
    for (char c : prefix) {
        int idx = c - 'a';
        if (trie[cur].children[idx] == -1) return 0;
        cur = trie[cur].children[idx];
    }
    return trie[cur].prefix_cnt;
}

// ═══════════════════════════════════════════════════════════
// XOR TRIE (find max XOR pair)
// ═══════════════════════════════════════════════════════════
struct XorTrie {
    int ch[2]; // binary: 0 or 1
    int cnt;
};

const int MAX_XOR = 32 * 200005;
XorTrie xtrie[MAX_XOR];
int xtrieSize;

void xtrieInit() {
    xtrieSize = 1;
    xtrie[0] = {{-1, -1}, 0};
}

void xtrieInsert(int num) {
    int cur = 0;
    for (int bit = 29; bit >= 0; bit--) {
        int b = (num >> bit) & 1;
        if (xtrie[cur].ch[b] == -1) {
            xtrie[cur].ch[b] = xtrieSize;
            xtrie[xtrieSize] = {{-1, -1}, 0};
            xtrieSize++;
        }
        cur = xtrie[cur].ch[b];
        xtrie[cur].cnt++;
    }
}

// Find max XOR of num with any inserted number
int xtrieMaxXor(int num) {
    int cur = 0, result = 0;
    for (int bit = 29; bit >= 0; bit--) {
        int b = (num >> bit) & 1;
        int want = 1 - b; // want opposite bit for max XOR
        if (xtrie[cur].ch[want] != -1 && xtrie[xtrie[cur].ch[want]].cnt > 0) {
            result |= (1 << bit);
            cur = xtrie[cur].ch[want];
        } else {
            cur = xtrie[cur].ch[b];
        }
        if (cur == -1) break;
    }
    return result;
}

void solve() {
    // String Trie demo
    trieInit();
    int n; cin >> n;
    vec<string> words(n);
    for (auto& s : words) {
        cin >> s;
        trieInsert(s);
    }

    int q; cin >> q;
    while (q--) {
        int type; string s;
        cin >> type >> s;
        if (type == 1) {
            cout << "Search \"" << s << "\": " << (trieSearch(s) ? "FOUND" : "NOT FOUND") << nl;
        } else {
            cout << "Prefix \"" << s << "\": " << countWithPrefix(s) << " words" << nl;
        }
    }

    // XOR Trie demo
    int m; cin >> m;
    xtrieInit();
    vec<int> nums(m);
    for (auto& x : nums) { cin >> x; xtrieInsert(x); }

    int maxXor = 0;
    for (int x : nums) maxXor = max(maxXor, xtrieMaxXor(x));
    cout << "Max XOR pair: " << maxXor << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1; cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE I/O
═══════════════════════════════════════════════════════════════════

Input:
1
4
apple app apt bat
4
1 apple
1 api
2 ap
2 b
3
3 10 5

Output:
Search "apple": FOUND
Search "api": NOT FOUND
Prefix "ap": 3 words
Prefix "b": 1 words
Max XOR pair: 15

 (3 XOR 10 = 0011 XOR 1010 = 1001 = 9,
  5 XOR 10 = 0101 XOR 1010 = 1111 = 15)

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ String Trie: insert/search O(|s|), prefix count O(|prefix|)
 ✅ XOR Trie: insert/query O(30 bits) = O(log MAX_VAL)
 ✅ Max XOR pair: greedily choose opposite bit at each level
 ✅ Trie nodes: up to 26 children (string) or 2 children (XOR)
═══════════════════════════════════════════════════════════════════
*/

