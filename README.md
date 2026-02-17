<div align="center">

# 🏆 Competitive Programming with Sarvan Yaduvanshi

**A structured, topic-wise DSA & CP mastery repository — built to think faster, code cleaner, and solve harder.**

[![C++](https://img.shields.io/badge/Language-C%2B%2B%2017-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)
[![Problems Solved](https://img.shields.io/badge/Problems%20Solved-100%2B-orange?style=for-the-badge)](.)
[![Platform](https://img.shields.io/badge/Platform-Codeforces%20%7C%20LeetCode%20%7C%20CSES-blue?style=for-the-badge)](.)
[![Stars](https://img.shields.io/github/stars/Sarvan-Yaduvanshi/Competitive-Programming-with-Sarvan_Yaduvanshi?style=for-the-badge&color=yellow)](.)

> *"Competitive Programming is not about memorizing solutions — it's about training your brain to recognize patterns under pressure."*

</div>

---

## 🧠 Why This Repo Exists

Most CP resources are scattered — half-explained blogs, random solutions, or video walkthroughs you can't revisit fast. This repo is different.

Every file here is written with **one goal**: **build the mental model**, not just the solution.

Each topic folder contains:
- **Mastery Guide files** — deep-dive concept walkthroughs with pattern identification
- **LeetCode / Codeforces / CSES solutions** — clean, commented, production-level C++ code
- **Multiple technique variants** — brute → optimized → best approaches in the same file

If you're grinding CP or preparing for FAANG/Google/competitive olympiads, this repo is your structured practice ground.

---

## 📁 Repository Structure

```
Competitive-Programming-with-Sarvan_Yaduvanshi/
│
├── 📂 Array & Subarray Techniques/
│   ├── Classical Array Concept/
│   ├── Classical Array Problems/
│   ├── Hashing & Frequency Problem Solving/
│   │   ├── LC_217_Contains_Duplicate.cpp
│   │   ├── LC_242_Valid_Anagram.cpp
│   │   └── Frequency_Count_Mastery_Guide.cpp   ← START HERE
│   ├── Hashing & Prefix Sum Problem Solving/
│   ├── Hashing Technique/
│   ├── Prefix & Difference Technique Problem Solving/
│   ├── Prefix & Difference Techniques/
│   └── Sliding Window & Two Pointer Technique/
│
├── 📂 Advance Number Theory (Mathematics)/
├── 📂 Advanced Bit Manipulation + DP with Bit-Masking/
├── 📂 Sorting and Searching Technique/
├── 📂 Codeforces Contest/           ← Real contest solutions
├── 📂 Codeforces Problem/           ← Problem-wise practice
├── 📂 CSES Problem Set/             ← Classic CS problems
├── 📂 Company-Specific Problems/    ← Google, etc.
├── 📂 ITMO Academy pilot course/
│
├── 📄 My Competitive Programming Template.cpp  ← Universal CP template
└── 📄 CMakeLists.txt
```

---

## 🗺️ Learning Roadmap

Follow this order if you're starting from scratch or want structured progression:

```
Phase 1 — Foundation
  └── Arrays & Subarrays (Classical Concepts + Problems)
  └── Hashing Techniques & Frequency Count
  └── Prefix Sum & Difference Arrays
  └── Sliding Window & Two Pointers

Phase 2 — Core Algorithms
  └── Sorting & Searching
  └── Advance Number Theory
  └── Bit Manipulation + Bitmask DP

Phase 3 — Competitive Practice
  └── CSES Problem Set (must-solve classics)
  └── ITMO Academy Course
  └── Codeforces Problems (topic-wise)

Phase 4 — Contest Ready
  └── Codeforces Contest Solutions
  └── Company-Specific Problems (Google, etc.)
```

---

## ✨ What Makes This Repo Powerful

### 1. 📖 Mastery Guide Files
Each major topic has a `*_Mastery_Guide.cpp` — a single file that walks through **every variant** of a technique:

```
Frequency_Count_Mastery_Guide.cpp covers:
  TYPE 1 → Basic integer frequency count
  TYPE 2 → Character/string frequency
  TYPE 3 → Boolean frequency (tracking seen elements)
  TYPE 4 → Sorted frequency output (using map)
  TYPE 5 → Pair/Tuple frequency count
  ...and more
```

You don't need to jump between 10 different articles. **One file. Complete mental model.**

### 2. 🔍 Pattern-First Thinking
Every solution is written to teach **why** the approach works, not just **what** the code does. Comments explain the pattern-recognition thought process.

### 3. 🏗️ Real Problems, Real Difficulty
Solutions come from:
| Platform | Usage |
|---|---|
| LeetCode | Concept reinforcement with real interview problems |
| Codeforces | Rating-tagged problems for competitive calibration |
| CSES | Algorithmic classics every serious CP coder must know |
| ITMO Academy | Structured learning with progression tracks |
| Google/Company | Interview-grade problem sets |

### 4. ⚡ Production-Quality C++ Template
The `My Competitive Programming Template.cpp` includes:
- Fast I/O setup
- Common macros and typedefs
- STL shorthands
- Debug utilities

---

## 🚀 Quick Start

### Clone the Repository
```bash
git clone https://github.com/Sarvan-Yaduvanshi/Competitive-Programming-with-Sarvan_Yaduvanshi.git
cd Competitive-Programming-with-Sarvan_Yaduvanshi
```

### Build with CMake (Debug Mode)
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```

### Or Compile Any File Directly
```bash
g++ -std=c++17 -O2 -o solution "Array & Subarray Techniques/Hashing & Frequency Problem Solving/LC_217_Contains_Duplicate.cpp"
./solution
```

---

## 📊 Topics Covered

| Topic | Status | Difficulty Range |
|---|---|---|
| Arrays & Subarrays | ✅ Active | Easy → Hard |
| Hashing & Frequency | ✅ Active | Easy → Hard |
| Prefix Sum & Difference | ✅ Active | Medium → Hard |
| Sliding Window & Two Pointer | ✅ Active | Medium → Hard |
| Sorting & Searching | ✅ Active | Easy → Hard |
| Number Theory | ✅ Active | Medium → Hard |
| Bit Manipulation + Bitmask DP | ✅ Active | Hard |
| CSES Problem Set | 🔄 In Progress | Medium → Hard |
| Codeforces Contests | 🔄 Ongoing | Div 2-3 |
| Company Problems (Google) | 🔄 In Progress | Interview Level |

---

## 💡 How to Use This Repo Effectively

1. **Pick a topic** from the structure above based on your current gap
2. **Read the Mastery Guide** for that topic first — understand every pattern variant
3. **Solve the problems** in the same folder — try yourself before reading the solution
4. **Study the solution comments** — understand *why* the approach was chosen
5. **Replicate from memory** — close the file and rewrite the solution
6. **Move to contest problems** — apply under time pressure in Codeforces section

> 💬 *The best way to use this is not to read solutions — use them as a reference after you've attempted the problem yourself.*

---

## 🤝 Contributing

Found a bug, have a cleaner approach, or want to add a missing problem?

1. Fork this repo
2. Create a branch: `git checkout -b feature/better-solution-lc-123`
3. Commit your changes with clear messages
4. Open a Pull Request

Please maintain the existing code style — clean comments, readable variable names, and approach explanation at the top.

---

## 👤 About the Author

**Sarvan Yaduvanshi** — Competitive Programmer passionate about building strong algorithmic foundations.

- 🌐 GitHub: [@Sarvan-Yaduvanshi](https://github.com/Sarvan-Yaduvanshi)
- 🧩 Focus: DSA mastery, Codeforces rating climb, FAANG prep

---

## ⭐ Support

If this repo helped you think better or solve a hard problem — drop a **⭐ star**. It keeps the motivation going and helps others find this resource.

---

<div align="center">

**Happy Coding. Think in patterns. Code with clarity. Win under pressure. 🚀**

</div>
