/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Fractional Knapsack
 *  Level   : Beginner
 * ============================================================================
 *
 *  PROBLEM: Given N items with weights and values, and a knapsack of capacity W.
 *           You can take FRACTIONS of items. Maximize total value.
 *
 *  GREEDY: Sort by value/weight ratio (descending). Take items greedily.
 *  TIME:   O(N log N)
 *  SPACE:  O(1) extra
 *
 *  WHY GREEDY WORKS (Exchange Argument):
 *  If optimal doesn't take the highest-ratio item fully, we can swap some
 *  fraction of a lower-ratio item with the higher-ratio item → better or equal value.
 *
 *  NOTE: For 0/1 Knapsack (no fractions), greedy FAILS! Need DP.
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int weight, value;
    double ratio() const { return (double)value / weight; }
};

double fractionalKnapsack(vector<Item>& items, int W) {
    // Sort by value/weight ratio (descending)
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio() > b.ratio();
    });

    double totalValue = 0.0;
    int remaining = W;

    for (auto& item : items) {
        if (remaining <= 0) break;

        if (item.weight <= remaining) {
            // Take entire item
            totalValue += item.value;
            remaining -= item.weight;
        } else {
            // Take fraction
            totalValue += item.ratio() * remaining;
            remaining = 0;
        }
    }

    return totalValue;
}

int main() {
    vector<Item> items = {{10, 60}, {20, 100}, {30, 120}};
    int W = 50;

    cout << "Items:" << endl;
    for (auto& it : items)
        cout << "  w=" << it.weight << " v=" << it.value << " ratio=" << it.ratio() << endl;

    cout << "Capacity: " << W << endl;
    cout << "Max value: " << fractionalKnapsack(items, W) << endl; // 240

    return 0;
}

