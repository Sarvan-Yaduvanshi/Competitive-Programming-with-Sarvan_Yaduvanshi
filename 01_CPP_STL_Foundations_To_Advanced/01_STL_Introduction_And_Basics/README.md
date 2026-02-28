# 📘 Chapter 01 — STL Introduction & Basics

## Overview
This chapter covers the **absolute foundation** of C++ STL — what every competitive programmer must know before writing a single line of contest code.

## Files in This Chapter

| # | File | Topic | Key Concepts |
|:-:|------|-------|-------------|
| 01 | `01_What_Is_STL.cpp` | What is STL? | Components, history, why STL matters |
| 02 | `02_Containers_Vs_Algorithms.cpp` | Containers vs Algorithms | Taxonomy, separation of concerns |
| 03 | `03_Iterators_Concept.cpp` | Iterators | The glue between containers & algorithms |
| 04 | `04_Time_Complexity_Basics.cpp` | Time Complexity | Big-O for all STL operations |
| 05 | `05_Header_Files.cpp` | Header Files | `bits/stdc++.h`, individual headers, pragmas |
| 06 | `06_Namespaces.cpp` | Namespaces | `using namespace std`, custom namespaces |
| 07 | `07_Auto_Keyword.cpp` | Auto Keyword | Type deduction, `auto&`, `const auto&` |
| 08 | `08_Range_Based_Loops.cpp` | Range-Based Loops | for-each, by-value vs by-ref |
| 09 | `09_Lambda_Basics.cpp` | Lambda Basics | Syntax, capture, simple sort examples |

## 🎯 GM Tips
- Always use `#include <bits/stdc++.h>` in contests — saves time
- `auto` reduces bugs from wrong iterator types
- Range-based loops are cleaner but know when index loops are needed
- Lambdas as comparators is a GM-level pattern you'll use everywhere

## 📚 Practice
- Try rewriting any brute-force solution using STL containers + algorithms
- Time your solutions with and without `ios::sync_with_stdio(false)`

