/*
╔══════════════════════════════════════════════════════════════════════════════╗
║     CHAPTER 05 — TRIE & STRING DATA STRUCTURES                            ║
║     From Zero to Grandmaster — Trie Mastery                                ║
║     Author: Sarvan Yaduvanshi                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Basic Trie (Theory & Structure)
 2. Insert / Search / Delete Operations
 3. Prefix Search (startsWith)
 4. Word Dictionary (Wildcard Search)
 5. Count Words With Prefix
 6. Binary Trie (for integers)
 7. XOR Trie (Maximum XOR pair)
 8. Compressed Trie (Radix Tree / Patricia Trie)

WHAT IS A TRIE?
───────────────
 A TRIE (pronounced "try", from re-TRIE-val) is a tree data structure
 used to store strings. Each edge represents a character.

 STRUCTURE:
   Root → no character
   Each node has up to Σ children (Σ = alphabet size, 26 for lowercase)
   A boolean flag marks "end of word"

   Example: Insert "abc", "abd", "xyz"
   root
   ├── 'a'
   │   └── 'b'
   │       ├── 'c' [end]
   │       └── 'd' [end]
   └── 'x'
       └── 'y'
           └── 'z' [end]

 COMPLEXITY:
   Insert:     O(L) where L = word length
   Search:     O(L)
   Delete:     O(L)
   Prefix:     O(L)
   Space:      O(Σ * N) where N = total characters across all words

 TRIE vs HASH MAP:
   • Trie supports prefix operations (hash map doesn't easily)
   • Trie doesn't need hash function
   • Trie uses more memory but is cache-friendly for prefix ops
   • Hash map: O(L) per query, Trie: O(L) per query

 WHEN TO USE TRIE:
   • Autocomplete / prefix matching
   • Spell checker
   • IP routing (binary trie)
   • XOR problems (binary trie)
   • Word games (Boggle, Scrabble)
   • Counting distinct prefixes
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1 & 2: BASIC TRIE + INSERT / SEARCH / DELETE
// ═══════════════════════════════════════════════════════════════
/*
 IMPLEMENTATION CHOICES:
   (a) Array of pointers: children[26] — fast, more memory
   (b) Map/unordered_map: flexible alphabet — slower, less memory
   (c) Static array (pool): children[MAXN][26] — fastest, competitive programming

 For CP: Use static array (pool-based) for speed.
 For interviews: Use dynamic nodes with new/delete.
*/

// ── Method 1: Dynamic Trie (Interview-friendly) ──

struct TrieNode {
    TrieNode* children[26];
    bool isEnd;
    int prefixCount;  // how many words pass through this node
    int endCount;     // how many words end exactly here

    TrieNode() : isEnd(false), prefixCount(0), endCount(0) {
        for (int i = 0; i < 26; i++) children[i] = nullptr;
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    // INSERT — O(L)
    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
            node->prefixCount++;
        }
        node->isEnd = true;
        node->endCount++;
    }

    // SEARCH (exact match) — O(L)
    bool search(const string& word) {
        TrieNode* node = findNode(word);
        return node != nullptr && node->isEnd;
    }

    // PREFIX SEARCH (startsWith) — O(L)
    bool startsWith(const string& prefix) {
        return findNode(prefix) != nullptr;
    }

    // COUNT WORDS WITH EXACT MATCH
    int countWord(const string& word) {
        TrieNode* node = findNode(word);
        return node ? node->endCount : 0;
    }

    // COUNT WORDS WITH GIVEN PREFIX — O(L)
    int countWordsWithPrefix(const string& prefix) {
        TrieNode* node = findNode(prefix);
        return node ? node->prefixCount : 0;
    }

    // DELETE — O(L), decrements counts
    void erase(const string& word) {
        if (!search(word)) return;
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            node = node->children[idx];
            node->prefixCount--;
        }
        node->endCount--;
        if (node->endCount == 0) node->isEnd = false;
    }

    // GET ALL WORDS IN TRIE (DFS)
    vector<string> getAllWords() {
        vector<string> result;
        string current;
        dfs(root, current, result);
        return result;
    }

    // AUTOCOMPLETE: Get all words starting with prefix
    vector<string> autocomplete(const string& prefix) {
        TrieNode* node = findNode(prefix);
        if (!node) return {};
        vector<string> result;
        string current = prefix;
        dfs(node, current, result);
        return result;
    }

private:
    TrieNode* findNode(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->children[idx]) return nullptr;
            node = node->children[idx];
        }
        return node;
    }

    void dfs(TrieNode* node, string& current, vector<string>& result) {
        if (node->isEnd) result.push_back(current);
        for (int i = 0; i < 26; i++) {
            if (node->children[i]) {
                current += (char)('a' + i);
                dfs(node->children[i], current, result);
                current.pop_back();
            }
        }
    }
};

// ── Method 2: Static Pool Trie (CP-friendly, fastest) ──

struct PoolTrie {
    static const int MAXN = 1000006;  // max total characters
    int children[MAXN][26];
    int endCnt[MAXN];
    int prefCnt[MAXN];
    int sz;

    void init() {
        sz = 1;  // root = node 0
        memset(children[0], 0, sizeof(children[0]));
        endCnt[0] = prefCnt[0] = 0;
    }

    int newNode() {
        memset(children[sz], 0, sizeof(children[sz]));
        endCnt[sz] = prefCnt[sz] = 0;
        return sz++;
    }

    void insert(const string& s) {
        int cur = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (!children[cur][idx]) {
                children[cur][idx] = newNode();
            }
            cur = children[cur][idx];
            prefCnt[cur]++;
        }
        endCnt[cur]++;
    }

    bool search(const string& s) {
        int cur = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (!children[cur][idx]) return false;
            cur = children[cur][idx];
        }
        return endCnt[cur] > 0;
    }

    int countPrefix(const string& s) {
        int cur = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (!children[cur][idx]) return 0;
            cur = children[cur][idx];
        }
        return prefCnt[cur];
    }
};

void demo_basic_trie() {
    cout << "=== SECTIONS 1-3: BASIC TRIE ===" << endl;
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("banana");
    trie.insert("band");
    trie.insert("apple");  // insert duplicate

    cout << "Search 'apple': " << trie.search("apple") << endl;       // 1
    cout << "Search 'app': " << trie.search("app") << endl;           // 1
    cout << "Search 'ap': " << trie.search("ap") << endl;             // 0
    cout << "StartsWith 'app': " << trie.startsWith("app") << endl;   // 1
    cout << "StartsWith 'ban': " << trie.startsWith("ban") << endl;   // 1
    cout << "StartsWith 'xyz': " << trie.startsWith("xyz") << endl;   // 0

    cout << "Count 'apple': " << trie.countWord("apple") << endl;     // 2
    cout << "Words with prefix 'app': " << trie.countWordsWithPrefix("app") << endl;  // 4

    // Delete
    trie.erase("apple");
    cout << "After erase 'apple': count=" << trie.countWord("apple") << endl;  // 1

    // Autocomplete
    auto suggestions = trie.autocomplete("app");
    cout << "Autocomplete 'app': ";
    for (auto& w : suggestions) cout << w << " ";
    cout << endl;

    // All words
    auto allWords = trie.getAllWords();
    cout << "All words: ";
    for (auto& w : allWords) cout << w << " ";
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: WORD DICTIONARY (Wildcard Search with '.')
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: LeetCode 211 — Design Add and Search Words Data Structure
 Support:
   addWord(word)
   search(word) where word may contain '.' that matches any letter

 APPROACH: Trie + DFS for wildcard matching
   When we encounter '.', try ALL 26 children recursively.

 Time: O(26^dots * L) worst case, good average
*/

class WordDictionary {
    TrieNode* root;

public:
    WordDictionary() { root = new TrieNode(); }

    void addWord(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx])
                node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    bool search(const string& word) {
        return searchHelper(root, word, 0);
    }

private:
    bool searchHelper(TrieNode* node, const string& word, int pos) {
        if (!node) return false;
        if (pos == (int)word.size()) return node->isEnd;

        if (word[pos] == '.') {
            // Try all 26 children
            for (int i = 0; i < 26; i++) {
                if (searchHelper(node->children[i], word, pos + 1))
                    return true;
            }
            return false;
        } else {
            return searchHelper(node->children[word[pos] - 'a'], word, pos + 1);
        }
    }
};

void demo_word_dictionary() {
    cout << "\n=== SECTION 4: WORD DICTIONARY (Wildcard) ===" << endl;
    WordDictionary wd;
    wd.addWord("bad");
    wd.addWord("dad");
    wd.addWord("mad");

    cout << "search('pad'): " << wd.search("pad") << endl;  // 0
    cout << "search('bad'): " << wd.search("bad") << endl;  // 1
    cout << "search('.ad'): " << wd.search(".ad") << endl;  // 1
    cout << "search('b..'): " << wd.search("b..") << endl;  // 1
    cout << "search('b.d'): " << wd.search("b.d") << endl;  // 1
    cout << "search('...'): " << wd.search("...") << endl;  // 1
    cout << "search('..'): " << wd.search("..") << endl;    // 0
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: COUNT WORDS WITH PREFIX (Already in Trie above)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Already implemented via prefixCount in our Trie.

 ADDITIONAL PROBLEMS:
   • Count distinct prefixes across all words
   • Longest common prefix using Trie (follow path while only one child)
   • Shortest unique prefix for each word
*/

// Shortest unique prefix for each word
vector<string> shortestUniquePrefixes(vector<string>& words) {
    Trie trie;
    for (auto& w : words) trie.insert(w);

    vector<string> result;
    for (auto& w : words) {
        TrieNode* node = trie.root;
        string prefix;
        for (char c : w) {
            int idx = c - 'a';
            node = node->children[idx];
            prefix += c;
            if (node->prefixCount == 1) break;
        }
        result.push_back(prefix);
    }
    return result;
}

// Longest common prefix using Trie
string lcpUsingTrie(vector<string>& words) {
    Trie trie;
    for (auto& w : words) trie.insert(w);

    string lcp;
    TrieNode* node = trie.root;
    while (true) {
        int childCount = 0, childIdx = -1;
        for (int i = 0; i < 26; i++) {
            if (node->children[i]) {
                childCount++;
                childIdx = i;
            }
        }
        // Stop if: multiple children, or end of word, or no children
        if (childCount != 1 || node->isEnd) break;
        lcp += (char)('a' + childIdx);
        node = node->children[childIdx];
    }
    return lcp;
}

void demo_prefix_counting() {
    cout << "\n=== SECTION 5: COUNT WORDS WITH PREFIX ===" << endl;
    vector<string> words = {"zebra", "dog", "duck", "dove"};
    auto prefixes = shortestUniquePrefixes(words);
    cout << "Shortest unique prefixes: ";
    for (int i = 0; i < (int)words.size(); i++) {
        cout << words[i] << "→" << prefixes[i] << " ";
    }
    cout << endl;

    vector<string> lcpWords = {"flower", "flow", "flight"};
    cout << "LCP using Trie: " << lcpUsingTrie(lcpWords) << endl;  // "fl"
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6 & 7: BINARY TRIE + XOR TRIE
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A BINARY TRIE stores integers in binary representation.
 Each level represents one bit (from MSB to LSB).
 Tree has depth = number of bits (typically 30 for int, 60 for long long).

 XOR TRIE:
   Used to find MAXIMUM XOR of a number with any number in a set.

   KEY INSIGHT: To maximize XOR, at each bit, go OPPOSITE direction.
     If current bit of query is 0, go to child 1 (if exists).
     If current bit of query is 1, go to child 0 (if exists).

 APPLICATIONS:
   • Maximum XOR pair in array — O(n * BITS)
   • Maximum XOR subarray — O(n * BITS) with prefix XOR
   • Queries: insert number, find max XOR with x
   • Persistent XOR trie for range queries

 Complexity: O(BITS) per operation = O(30) or O(60)
*/

class BinaryTrie {
    static const int BITS = 30;  // for values up to ~10^9

    struct Node {
        int children[2];
        int count;  // how many numbers pass through
        Node() : count(0) { children[0] = children[1] = -1; }
    };

    vector<Node> nodes;

    int newNode() {
        nodes.push_back(Node());
        return nodes.size() - 1;
    }

public:
    int root;

    BinaryTrie() {
        nodes.clear();
        root = newNode();
    }

    // Insert a number into the trie
    void insert(int num) {
        int cur = root;
        for (int i = BITS; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (nodes[cur].children[bit] == -1) {
                nodes[cur].children[bit] = newNode();
            }
            cur = nodes[cur].children[bit];
            nodes[cur].count++;
        }
    }

    // Remove a number from the trie
    void erase(int num) {
        int cur = root;
        for (int i = BITS; i >= 0; i--) {
            int bit = (num >> i) & 1;
            cur = nodes[cur].children[bit];
            nodes[cur].count--;
        }
    }

    // Find maximum XOR of num with any number in trie
    int maxXor(int num) {
        int cur = root;
        int result = 0;
        for (int i = BITS; i >= 0; i--) {
            int bit = (num >> i) & 1;
            int want = 1 - bit;  // opposite bit for max XOR

            if (nodes[cur].children[want] != -1 &&
                nodes[nodes[cur].children[want]].count > 0) {
                result |= (1 << i);
                cur = nodes[cur].children[want];
            } else if (nodes[cur].children[bit] != -1) {
                cur = nodes[cur].children[bit];
            } else {
                break;  // no numbers in trie
            }
        }
        return result;
    }

    // Find minimum XOR of num with any number in trie
    int minXor(int num) {
        int cur = root;
        int result = 0;
        for (int i = BITS; i >= 0; i--) {
            int bit = (num >> i) & 1;

            // Try same bit first (to minimize XOR)
            if (nodes[cur].children[bit] != -1 &&
                nodes[nodes[cur].children[bit]].count > 0) {
                cur = nodes[cur].children[bit];
            } else if (nodes[cur].children[1 - bit] != -1) {
                result |= (1 << i);
                cur = nodes[cur].children[1 - bit];
            } else {
                break;
            }
        }
        return result;
    }
};

// Maximum XOR pair in array
int maxXorPair(vector<int>& nums) {
    BinaryTrie bt;
    int maxVal = 0;
    bt.insert(nums[0]);
    for (int i = 1; i < (int)nums.size(); i++) {
        maxVal = max(maxVal, bt.maxXor(nums[i]));
        bt.insert(nums[i]);
    }
    return maxVal;
}

// Maximum XOR subarray (using prefix XOR + binary trie)
int maxXorSubarray(vector<int>& nums) {
    int n = nums.size();
    BinaryTrie bt;
    int prefXor = 0, maxVal = 0;
    bt.insert(0);  // empty prefix

    for (int i = 0; i < n; i++) {
        prefXor ^= nums[i];
        maxVal = max(maxVal, bt.maxXor(prefXor));
        bt.insert(prefXor);
    }
    return maxVal;
}

void demo_binary_trie() {
    cout << "\n=== SECTIONS 6 & 7: BINARY TRIE + XOR TRIE ===" << endl;
    vector<int> nums = {3, 10, 5, 25, 2, 8};
    cout << "Max XOR pair in [3,10,5,25,2,8]: " << maxXorPair(nums) << endl;  // 28 (5^25)

    vector<int> arr = {1, 2, 3, 4};
    cout << "Max XOR subarray in [1,2,3,4]: " << maxXorSubarray(arr) << endl;  // 7

    BinaryTrie bt;
    bt.insert(5);   // 101
    bt.insert(10);  // 1010
    bt.insert(15);  // 1111
    cout << "Max XOR with 7 (0111): " << bt.maxXor(7) << endl;    // 7^10 = 13 or 7^8 = 15
    cout << "Min XOR with 7 (0111): " << bt.minXor(7) << endl;    // 7^5 = 2
}

// ═══════════════════════════════════════════════════════════════
// SECTION 8: COMPRESSED TRIE (Radix Tree / Patricia Trie)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A compressed trie (radix tree) merges chains of single-child nodes.
 Instead of one character per edge, an edge can contain a string.

 Example (Regular Trie):
   r → o → m → a → n → e [end]
                    └── c → e [end]

 Compressed:
   "roman" → e [end]
          └─ ce [end]

 Or better:
   "roma" → "ne" [end]
          → "nce" [end]

 ADVANTAGES:
   • Uses much less memory than regular trie
   • Faster traversal (skip over single-child chains)
   • Same asymptotic complexity

 APPLICATIONS:
   • IP routing tables (CIDR)
   • Compressed suffix tree
   • Memory-efficient dictionary

 IMPLEMENTATION: Each node stores:
   • Edge label (string/substring)
   • Children map
   • isEnd flag
*/

struct CompressedTrieNode {
    string edgeLabel;  // label on the edge from parent to this node
    unordered_map<char, CompressedTrieNode*> children;
    bool isEnd;

    CompressedTrieNode(const string& label = "") : edgeLabel(label), isEnd(false) {}
};

class CompressedTrie {
    CompressedTrieNode* root;

public:
    CompressedTrie() { root = new CompressedTrieNode(); }

    void insert(const string& word) {
        insertHelper(root, word, 0);
    }

    bool search(const string& word) {
        return searchHelper(root, word, 0);
    }

    // Print the trie structure
    void print() {
        printHelper(root, 0);
    }

private:
    void insertHelper(CompressedTrieNode* node, const string& word, int pos) {
        if (pos == (int)word.size()) {
            node->isEnd = true;
            return;
        }

        char firstChar = word[pos];

        if (node->children.count(firstChar)) {
            CompressedTrieNode* child = node->children[firstChar];
            const string& label = child->edgeLabel;

            // Find common prefix length
            int commonLen = 0;
            while (commonLen < (int)label.size() &&
                   pos + commonLen < (int)word.size() &&
                   label[commonLen] == word[pos + commonLen]) {
                commonLen++;
            }

            if (commonLen == (int)label.size()) {
                // Full match with edge label — continue down
                insertHelper(child, word, pos + commonLen);
            } else {
                // Partial match — need to split edge
                CompressedTrieNode* splitNode = new CompressedTrieNode(label.substr(0, commonLen));

                // Existing child becomes child of split node
                child->edgeLabel = label.substr(commonLen);
                splitNode->children[child->edgeLabel[0]] = child;

                // New word becomes another child of split node
                if (pos + commonLen < (int)word.size()) {
                    CompressedTrieNode* newChild = new CompressedTrieNode(word.substr(pos + commonLen));
                    newChild->isEnd = true;
                    splitNode->children[word[pos + commonLen]] = newChild;
                } else {
                    splitNode->isEnd = true;
                }

                node->children[firstChar] = splitNode;
            }
        } else {
            // No matching child — create new edge
            CompressedTrieNode* newChild = new CompressedTrieNode(word.substr(pos));
            newChild->isEnd = true;
            node->children[firstChar] = newChild;
        }
    }

    bool searchHelper(CompressedTrieNode* node, const string& word, int pos) {
        if (pos == (int)word.size()) return node->isEnd;

        char firstChar = word[pos];
        if (!node->children.count(firstChar)) return false;

        CompressedTrieNode* child = node->children[firstChar];
        const string& label = child->edgeLabel;

        // Check if word matches the edge label
        for (int i = 0; i < (int)label.size(); i++) {
            if (pos + i >= (int)word.size() || word[pos + i] != label[i]) {
                return false;
            }
        }

        return searchHelper(child, word, pos + label.size());
    }

    void printHelper(CompressedTrieNode* node, int depth) {
        for (auto& [ch, child] : node->children) {
            for (int i = 0; i < depth; i++) cout << "  ";
            cout << "── \"" << child->edgeLabel << "\"";
            if (child->isEnd) cout << " [END]";
            cout << endl;
            printHelper(child, depth + 1);
        }
    }
};

void demo_compressed_trie() {
    cout << "\n=== SECTION 8: COMPRESSED TRIE ===" << endl;
    CompressedTrie ct;
    ct.insert("romane");
    ct.insert("romanus");
    ct.insert("romulus");
    ct.insert("rubens");
    ct.insert("ruber");
    ct.insert("rubicon");

    cout << "Structure:" << endl;
    ct.print();

    cout << "Search 'romane': " << ct.search("romane") << endl;   // 1
    cout << "Search 'roman': " << ct.search("roman") << endl;     // 0
    cout << "Search 'rubicon': " << ct.search("rubicon") << endl; // 1
    cout << "Search 'xyz': " << ct.search("xyz") << endl;         // 0
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demo_basic_trie();
    demo_word_dictionary();
    demo_prefix_counting();
    demo_binary_trie();
    demo_compressed_trie();

    cout << "\n═══════════════════════════════════════════" << endl;
    cout << "✅ All 8 Trie concepts covered!" << endl;
    cout << "═══════════════════════════════════════════" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════╗
║  PRACTICE PROBLEMS                                              ║
╠══════════════════════════════════════════════════════════════════╣
║  LeetCode 208  — Implement Trie (Prefix Tree)                   ║
║  LeetCode 211  — Design Add and Search Words Data Structure     ║
║  LeetCode 212  — Word Search II                                 ║
║  LeetCode 14   — Longest Common Prefix (Trie approach)          ║
║  LeetCode 421  — Maximum XOR of Two Numbers in an Array         ║
║  LeetCode 1707 — Maximum XOR With an Element From Array         ║
║  LeetCode 1268 — Search Suggestions System                      ║
║  LeetCode 472  — Concatenated Words (Trie + DP)                ║
║  LeetCode 677  — Map Sum Pairs                                  ║
║  CF 706D       — Vasiliy's Multiset (XOR trie)                  ║
║  CF 282E       — Sausage Maximization (prefix XOR + trie)       ║
║  CSES          — Finding Patterns (Aho-Corasick / Trie)         ║
║  SPOJ SUBXOR   — XOR Subarray (binary trie)                     ║
╚══════════════════════════════════════════════════════════════════╝
*/

