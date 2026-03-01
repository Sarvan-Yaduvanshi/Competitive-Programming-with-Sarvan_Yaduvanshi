/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           06 — STOCK SPAN PROBLEM                                            ║
║           From Zero to Grandmaster — Classical Stack Problems               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM (LC 901 — Online Stock Span):
─────────────────────────────────────
  The stock span on day i = number of consecutive days (including today)
  where the price was ≤ today's price, going backwards.

  Prices: [100, 80, 60, 70, 60, 75, 85]
  Spans:  [1,   1,  1,  2,  1,  4,  6]

  Day 0: 100 → no previous day ≤ 100 → span = 1
  Day 1: 80  → 80 < 100 → span = 1
  Day 2: 60  → 60 < 80 → span = 1
  Day 3: 70  → 70 ≥ 60 → span = 2 (day 3 and day 2)
  Day 4: 60  → 60 < 70 → span = 1
  Day 5: 75  → 75 ≥ 60, 75 ≥ 70, 75 ≥ 60 → span = 4 (days 5,4,3,2)
  Day 6: 85  → 85 ≥ 75, 85 ≥ 80 → span = 6 (days 6,5,4,3,2,1)

INSIGHT:
───────
  Span[i] = i - index of Previous Greater Element (PGE)

  If PGE doesn't exist, span[i] = i + 1 (all previous days are ≤)

  This is exactly the PGE problem with indices!

DRY RUN:
───────
  Prices: [100, 80, 60, 70, 60, 75, 85]
  Stack stores (price, index) pairs, DECREASING order.

  i=0: price=100, stack=[]       → PGE_idx=-1, span=0-(-1)=1
       push (100,0)              stack=[(100,0)]
  i=1: price=80,  stack=[(100,0)] → 100>80, PGE_idx=0, span=1-0=1
       push (80,1)               stack=[(100,0),(80,1)]
  i=2: price=60,  stack=[...,(80,1)] → 80>60, PGE_idx=1, span=2-1=1
       push (60,2)               stack=[(100,0),(80,1),(60,2)]
  i=3: price=70,  pop (60,2). 80>70 → PGE_idx=1, span=3-1=2
       push (70,3)               stack=[(100,0),(80,1),(70,3)]
  i=4: price=60,  70>60 → PGE_idx=3, span=4-3=1
       push (60,4)               stack=[(100,0),(80,1),(70,3),(60,4)]
  i=5: price=75,  pop (60,4),(70,3). 80>75 → PGE_idx=1, span=5-1=4
       push (75,5)               stack=[(100,0),(80,1),(75,5)]
  i=6: price=85,  pop (75,5),(80,1). 100>85 → PGE_idx=0, span=6-0=6
       push (85,6)               stack=[(100,0),(85,6)]

  Spans: [1, 1, 1, 2, 1, 4, 6] ✅

TIME: O(n) amortized  SPACE: O(n)
*/

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: STOCK SPAN — ARRAY VERSION
// ═══════════════════════════════════════════════════════════════

vector<int> stockSpan(vector<int>& prices) {
    int n = prices.size();
    vector<int> span(n);
    stack<int> st;  // Stores indices, prices are decreasing

    for (int i = 0; i < n; i++) {
        while (!st.empty() && prices[st.top()] <= prices[i]) {
            st.pop();
        }
        span[i] = st.empty() ? (i + 1) : (i - st.top());
        st.push(i);
    }
    return span;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: ONLINE STOCK SPAN (LC 901)
// ═══════════════════════════════════════════════════════════════

class StockSpanner {
    stack<pair<int, int>> st;  // (price, span)
public:
    int next(int price) {
        int span = 1;
        while (!st.empty() && st.top().first <= price) {
            span += st.top().second;
            st.pop();
        }
        st.push({price, span});
        return span;
    }
};

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  STOCK SPAN PROBLEM                                      ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Array version
    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    cout << "Prices: ";
    for (int x : prices) cout << x << " ";
    cout << "\n";

    auto spans = stockSpan(prices);
    cout << "Spans:  ";
    for (int x : spans) cout << x << " ";
    cout << "\n\n";

    // Online version
    cout << "Online Stock Spanner:\n";
    StockSpanner spanner;
    for (int p : prices) {
        cout << "  price=" << p << " → span=" << spanner.next(p) << "\n";
    }

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LC 901 — Online Stock Span\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

