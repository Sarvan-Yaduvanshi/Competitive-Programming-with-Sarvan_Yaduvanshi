# Module 13: Advanced Greedy

> **Level:** ⭐⭐⭐⭐⭐ Grandmaster  
> **Prerequisites:** All previous modules

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_Regret_Based_Greedy.cpp` | Lazy choices with rollback via PQ | GM |
| 2 | `02_Greedy_with_Rollback.cpp` | Undo-able greedy (DSU rollback) | GM |
| 3 | `03_Online_Greedy_Algorithms.cpp` | Secretary problem, online matching | GM |
| 4 | `04_Greedy_Future_Simulation.cpp` | Belady's algorithm, page replacement | GM |
| 5 | `05_Scheduling_Multiprocessor_Greedy.cpp` | LPT, SPT, load balancing | GM |

## Key Insight
Advanced greedy = standard greedy + a **twist**:
- **Regret**: Make a choice, but undo it later if a better option appears (PQ trick)
- **Rollback**: Use DSU with rollback for undoable union operations
- **Online**: Make irrevocable decisions with incomplete information
- **Future Simulation**: Optimal offline algorithms that look ahead

