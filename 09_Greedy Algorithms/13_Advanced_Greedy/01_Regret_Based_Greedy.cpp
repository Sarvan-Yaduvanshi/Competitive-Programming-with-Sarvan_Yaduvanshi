/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Regret-Based Greedy (a.k.a. "Undo Greedy" / "Lazy Greedy")
 *  Level   : Grandmaster
 * ============================================================================
 *
 *  ▶ WHAT IS REGRET-BASED GREEDY?
 *  ──────────────────────────────
 *  Standard greedy makes a choice and never looks back.
 *  Regret-based greedy makes a choice, but stores the option to UNDO it later
 *  if a better choice becomes available.
 *
 *  IMPLEMENTATION: Use a priority queue. When you "undo" a previous choice,
 *  push a "regret token" that represents the cost of undoing.
 *
 *  ▶ CLASSIC EXAMPLE: Buy Low, Sell High (CF 865D)
 *  ────────────────────────────────────────────────
 *  Given stock prices on N days, you can buy/sell at most once per day.
 *  Maximize profit.
 *
 *  GREEDY IDEA: Maintain a min-heap of prices seen.
 *  For each price:
 *    If price > heap.top() → we can "profit" by selling at this price
 *    and buying at heap.top(). Push price TWICE into heap:
 *    - Once to represent "what if we sell here later at an even higher price"
 *    - This effectively allows UNDOING the current sell decision later
 *
 *  TIME: O(N log N)
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ============================================================================
// CF 865D: Buy Low, Sell High — Classic Regret Greedy
// ============================================================================
long long buyLowSellHigh(vector<int>& prices) {
    priority_queue<int, vector<int>, greater<int>> minPQ; // Min-heap
    long long profit = 0;

    for (int price : prices) {
        if (!minPQ.empty() && minPQ.top() < price) {
            // "Sell" at current price, "buy" was at minPQ.top()
            profit += price - minPQ.top();
            minPQ.pop();
            // Push current price as a "regret token"
            // If a higher price comes later, we can undo this sell
            // and sell at the higher price instead
            minPQ.push(price);
        }
        minPQ.push(price);
    }
    return profit;
}

// ============================================================================
// LC 871: Min Refueling Stops — Regret-Based (Already in Module 08)
// When you run out of fuel, retroactively choose to refuel at the
// best station you passed (max fuel). This is regret-based!
// ============================================================================

// ============================================================================
// LC 630: Course Schedule III — Regret-Based
// Take courses greedily by deadline. If a new course doesn't fit,
// swap out the longest course taken so far (regret it).
// ============================================================================

/*
 * WHY REGRET GREEDY WORKS:
 * ─────────────────────────
 * The key insight is that "undoing" a previous decision and making a new one
 * is equivalent to considering all possible decision sequences, but doing it
 * in O(N log N) instead of exponential time.
 *
 * For Buy/Sell: If we buy at price 1, sell at price 5, then see price 10:
 *   Regret undoes "sell at 5" and instead "sells at 10"
 *   Net effect: buy at 1, sell at 10 (profit = 9)
 *   But we computed it as: (5-1) + (10-5) = 4 + 5 = 9 ✓
 *
 * The double-push trick makes this work!
 */

int main() {
    // Buy Low, Sell High
    vector<int> prices = {1, 2, 3, 4, 5};
    cout << "Max profit: " << buyLowSellHigh(prices) << endl; // 4

    vector<int> prices2 = {3, 1, 5, 2, 8};
    cout << "Max profit: " << buyLowSellHigh(prices2) << endl; // 10 (buy@1,sell@5 + buy@2,sell@8)

    vector<int> prices3 = {1, 5, 2, 10};
    cout << "Max profit: " << buyLowSellHigh(prices3) << endl; // 12 (buy@1,sell@5 → regret → sell@10 = 9, plus buy@2,sell@10 → wait, let's trace)
    // Actually: buy@1,sell@10=9 plus buy@2,sell@... hmm, but only 1 stock at a time each day
    // The problem allows multiple buys/sells, just 1 per day

    return 0;
}

