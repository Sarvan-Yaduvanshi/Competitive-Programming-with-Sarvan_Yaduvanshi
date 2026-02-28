# 📘 Chapter 05 — Container Adaptors

## Overview
Container adaptors provide **restricted interfaces** on top of sequence containers. They enforce specific access patterns (LIFO, FIFO, priority-based).

## Files in This Chapter

| # | File | Topic | Key Concepts |
|:-:|------|-------|-------------|
| 01 | `01_Stack_Complete.cpp` | stack | LIFO, next greater element, valid parentheses, histogram |
| 02 | `02_Queue_Complete.cpp` | queue | FIFO, BFS pattern, circular queue |
| 03 | `03_Priority_Queue_Complete.cpp` | priority_queue | Max/min heap, top-K, merge K sorted |
| 04 | `04_Custom_Comparators.cpp` | Custom Comparators | Functor, lambda, struct, priority_queue custom |
| 05 | `05_Adaptor_Patterns_For_CP.cpp` | CP Patterns | Monotonic stack/queue, lazy deletion PQ, median stream |

## 🎯 GM Tips
- **Min heap**: `priority_queue<int, vector<int>, greater<int>>`
- **Monotonic stack**: O(n) for next greater/smaller element problems
- **Lazy deletion PQ**: Mark deleted instead of actually deleting
- Stack/Queue are wrappers — don't iterate them (no begin/end)

