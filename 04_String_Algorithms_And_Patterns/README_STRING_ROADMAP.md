# 🔤 String Algorithms & Patterns — Zero to Grandmaster Roadmap

## 📋 Complete Chapter Index

### 🟢 Level 1: Foundation (Newbie → Specialist)
| # | Chapter | Key Topics | Difficulty |
|---|---------|------------|------------|
| 01 | **String Basics & Operations** | I/O, Traversal, Reverse, ASCII, Palindrome, Frequency, Substring | ⭐ |
| 02 | **Classical String Problems** | Anagram, Isomorphic, Valid Parentheses, LCP, Compression | ⭐⭐ |

### 🟡 Level 2: Intermediate (Specialist → Expert)
| # | Chapter | Key Topics | Difficulty |
|---|---------|------------|------------|
| 03 | **Two Pointer & Sliding Window** | Longest Substring, Min Window, K-Distinct, Permutation Check | ⭐⭐⭐ |
| 04 | **String Hashing & Rolling Hash** | Rabin-Karp, Double Hash, Prefix Hash, Collision Avoidance | ⭐⭐⭐ |
| 05 | **Trie & String Data Structures** | Basic Trie, XOR Trie, Binary Trie, Compressed Trie | ⭐⭐⭐ |

### 🔴 Level 3: Advanced (Expert → Master)
| # | Chapter | Key Topics | Difficulty |
|---|---------|------------|------------|
| 06 | **Pattern Matching Algorithms** | KMP, Z-Algo, Manacher, Suffix Array, Aho-Corasick, SAM | ⭐⭐⭐⭐ |
| 07 | **Advanced String Algorithms** | KMP/Z Applications, Suffix Array Queries, Period Analysis | ⭐⭐⭐⭐ |
| 08 | **String DP Problems** | Edit Distance, LCS, Palindromic Subseq, Wildcard, Regex | ⭐⭐⭐⭐ |

### 🟣 Level 4: Grandmaster (Master → Grandmaster)
| # | Chapter | Key Topics | Difficulty |
|---|---------|------------|------------|
| 09 | **Bitmask & Parity Techniques** | Parity Mask, XOR Window, Wonderful Substrings | ⭐⭐⭐⭐⭐ |
| 10 | **Advanced Competitive Tricks** | Contribution Counting, Periodicity, Border Array, Combinatorics | ⭐⭐⭐⭐⭐ |
| 11 | **Advanced Data Structures** | Eertree, Persistent Trie, Suffix Automaton, Rope | ⭐⭐⭐⭐⭐ |

---

## 🎯 How to Study
1. **Read theory comments** in each `.cpp` file top-to-bottom
2. **Understand the code** — every function is self-contained with complexity analysis
3. **Run `main()`** — each file has a demo that tests all concepts
4. **Solve practice problems** listed at the end of each file
5. **Move to next chapter** only when you can code current chapter from memory

## 📊 Time Complexity Cheat Sheet
| Algorithm | Build | Query | Space |
|-----------|-------|-------|-------|
| KMP | O(n+m) | O(n+m) | O(m) |
| Z-Algorithm | O(n) | O(n+m) | O(n) |
| Rabin-Karp | O(n) | O(n+m) avg | O(1) |
| Manacher | O(n) | O(1) | O(n) |
| Suffix Array | O(n log²n) | O(m log n) | O(n) |
| LCP (Kasai) | O(n) | O(1) | O(n) |
| Trie | O(L) insert | O(L) search | O(Σ·N) |
| Aho-Corasick | O(ΣL) | O(n+m+z) | O(ΣL) |
| Suffix Automaton | O(n) | O(m) | O(n) |
| Eertree | O(n) | O(1) | O(n) |

## 🏆 Practice Problem Sources
- **LeetCode**: String tag (Easy → Hard)
- **Codeforces**: Tags: strings, hashing, suffix structures
- **CSES**: String Algorithms section
- **AtCoder**: ABC/ARC string problems
- **SPOJ**: Classical string problems

---
*Created by Sarvan Yaduvanshi — Competitive Programming with Sarvan*

