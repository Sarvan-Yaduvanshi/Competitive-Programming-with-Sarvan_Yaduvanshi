/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Huffman Coding — Greedy Optimal Prefix Code
 *  Level   : Intermediate
 * ============================================================================
 *
 *  PROBLEM: Given characters with frequencies, build a binary tree such that
 *           the total encoding length (Σ freq[i] * depth[i]) is minimized.
 *
 *  GREEDY: Always merge the two nodes with LOWEST frequency.
 *  DATA STRUCTURE: Min-Heap (Priority Queue)
 *
 *  TIME:  O(N log N)
 *  SPACE: O(N)
 *
 *  WHY GREEDY WORKS:
 *  The two least-frequent characters should be at the deepest level.
 *  By merging them first, they share the longest path but have lowest frequency.
 *  Exchange argument: If a higher-freq char is deeper, swapping improves the cost.
 *
 *  APPLICATIONS:
 *  - Data compression (ZIP, GZIP)
 *  - File encoding
 *  - Optimal merge pattern (merging sorted files)
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq; // Min-heap by frequency
    }
};

// Build Huffman Tree
HuffmanNode* buildHuffmanTree(vector<pair<char,int>>& charFreq) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    // Create leaf nodes
    for (auto& [ch, freq] : charFreq)
        pq.push(new HuffmanNode(ch, freq));

    // Merge until one node remains
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        // Create internal node with combined frequency
        HuffmanNode* merged = new HuffmanNode('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    return pq.top();
}

// Generate codes by traversing the tree
void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[root->ch] = code.empty() ? "0" : code; // Handle single character
        return;
    }
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

// Clean up tree memory
void deleteTree(HuffmanNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    vector<pair<char,int>> charFreq = {{'a',5}, {'b',9}, {'c',12}, {'d',13}, {'e',16}, {'f',45}};

    HuffmanNode* root = buildHuffmanTree(charFreq);

    unordered_map<char, string> codes;
    generateCodes(root, "", codes);

    cout << "Huffman Codes:" << endl;
    int totalBits = 0;
    for (auto& [ch, freq] : charFreq) {
        cout << "  " << ch << " (freq=" << freq << "): " << codes[ch] << endl;
        totalBits += freq * codes[ch].size();
    }
    cout << "Total encoding bits: " << totalBits << endl;

    deleteTree(root);
    return 0;
}

