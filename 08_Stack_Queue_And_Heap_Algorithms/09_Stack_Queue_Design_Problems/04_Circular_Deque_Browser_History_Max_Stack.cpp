/*
╔══════════════════════════════════════════════════════════════════════════════╗
║       04 — CIRCULAR DEQUE (LC 641) + BROWSER HISTORY (LC 1472)               ║
║           From Zero to Grandmaster — Stack & Queue Design Problems          ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

CIRCULAR DEQUE (LC 641):
───────────────────────
  Design a double-ended circular queue supporting:
    insertFront, insertLast, deleteFront, deleteLast
    getFront, getRear, isEmpty, isFull

  Implementation: Circular array with front & rear pointers.

  Visualization (capacity=4):
    ┌────┬────┬────┬────┐
    │ 10 │ 20 │ 30 │    │   front=0, rear=2, size=3
    └────┴────┴────┴────┘

    insertFront(5):
    ┌────┬────┬────┬────┐
    │ 10 │ 20 │ 30 │  5 │   front=3, rear=2, size=4 (FULL)
    └────┴────┴────┴────┘
    front wraps to (0-1+4)%4 = 3

BROWSER HISTORY (LC 1472):
────────────────────────
  Implement browser with visit, back, forward.

  Approach 1: Two stacks (back_stack, forward_stack)
  Approach 2: Array/vector with current pointer (simpler)

  When visiting a new page, forward history is cleared!
*/

#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// DESIGN CIRCULAR DEQUE (LC 641)
// ═══════════════════════════════════════════════════════════════

class MyCircularDeque {
    vector<int> data;
    int front, rear, size, cap;

public:
    MyCircularDeque(int k) : data(k), front(0), rear(k - 1), size(0), cap(k) {}

    bool insertFront(int value) {
        if (isFull()) return false;
        front = (front - 1 + cap) % cap;
        data[front] = value;
        size++;
        return true;
    }

    bool insertLast(int value) {
        if (isFull()) return false;
        rear = (rear + 1) % cap;
        data[rear] = value;
        size++;
        return true;
    }

    bool deleteFront() {
        if (isEmpty()) return false;
        front = (front + 1) % cap;
        size--;
        return true;
    }

    bool deleteLast() {
        if (isEmpty()) return false;
        rear = (rear - 1 + cap) % cap;
        size--;
        return true;
    }

    int getFront() { return isEmpty() ? -1 : data[front]; }
    int getRear() { return isEmpty() ? -1 : data[rear]; }
    bool isEmpty() { return size == 0; }
    bool isFull() { return size == cap; }
};

// ═══════════════════════════════════════════════════════════════
// BROWSER HISTORY (LC 1472) — Stack Approach
// ═══════════════════════════════════════════════════════════════

class BrowserHistory {
    stack<string> backSt, forwardSt;
    string current;

public:
    BrowserHistory(string homepage) : current(homepage) {}

    void visit(string url) {
        backSt.push(current);
        current = url;
        // Clear forward history
        while (!forwardSt.empty()) forwardSt.pop();
    }

    string back(int steps) {
        while (steps > 0 && !backSt.empty()) {
            forwardSt.push(current);
            current = backSt.top();
            backSt.pop();
            steps--;
        }
        return current;
    }

    string forward(int steps) {
        while (steps > 0 && !forwardSt.empty()) {
            backSt.push(current);
            current = forwardSt.top();
            forwardSt.pop();
            steps--;
        }
        return current;
    }
};

// ═══════════════════════════════════════════════════════════════
// BROWSER HISTORY — Array Approach (faster)
// ═══════════════════════════════════════════════════════════════

class BrowserHistoryArray {
    vector<string> history;
    int cur, end_pos;

public:
    BrowserHistoryArray(string homepage) : cur(0), end_pos(0) {
        history.push_back(homepage);
    }

    void visit(string url) {
        cur++;
        if (cur < (int)history.size())
            history[cur] = url;
        else
            history.push_back(url);
        end_pos = cur;  // Invalidate forward history
    }

    string back(int steps) {
        cur = max(0, cur - steps);
        return history[cur];
    }

    string forward(int steps) {
        cur = min(end_pos, cur + steps);
        return history[cur];
    }
};

// ═══════════════════════════════════════════════════════════════
// MAX STACK (LC 716)
// ═══════════════════════════════════════════════════════════════
/*
  Stack supporting: push, pop, top, peekMax, popMax — all O(log n)

  Use: Doubly Linked List + TreeMap (ordered map)
    DLL: maintains insertion order
    TreeMap: maps value → set of DLL node pointers (for O(log n) max)

  Simplified approach for CP: Two stacks (like Min Stack but track max)
  push: O(1), pop: O(1), top: O(1), peekMax: O(1), popMax: O(n)
*/

class MaxStack {
    stack<int> mainSt;
    stack<int> maxSt;

public:
    void push(int x) {
        mainSt.push(x);
        if (maxSt.empty() || x >= maxSt.top())
            maxSt.push(x);
        else
            maxSt.push(maxSt.top());
    }

    int pop() {
        int val = mainSt.top();
        mainSt.pop();
        maxSt.pop();
        return val;
    }

    int top() { return mainSt.top(); }
    int peekMax() { return maxSt.top(); }

    // popMax is O(n) with this approach
    int popMax() {
        int maxVal = maxSt.top();
        stack<int> temp;
        while (mainSt.top() != maxVal) {
            temp.push(mainSt.top());
            mainSt.pop();
            maxSt.pop();
        }
        mainSt.pop();
        maxSt.pop();
        while (!temp.empty()) {
            push(temp.top());
            temp.pop();
        }
        return maxVal;
    }
};

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  CIRCULAR DEQUE + BROWSER HISTORY + MAX STACK            ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Circular Deque
    cout << "═══ CIRCULAR DEQUE (LC 641) ═══\n";
    MyCircularDeque cd(3);
    cout << "  insertLast(1): " << cd.insertLast(1) << "\n";
    cout << "  insertLast(2): " << cd.insertLast(2) << "\n";
    cout << "  insertFront(3): " << cd.insertFront(3) << "\n";
    cout << "  insertFront(4): " << cd.insertFront(4) << " (full!)\n";
    cout << "  getRear: " << cd.getRear() << "\n";
    cout << "  isFull: " << cd.isFull() << "\n";
    cout << "  deleteLast: " << cd.deleteLast() << "\n";
    cout << "  insertFront(4): " << cd.insertFront(4) << "\n";
    cout << "  getFront: " << cd.getFront() << "\n\n";

    // Browser History
    cout << "═══ BROWSER HISTORY (LC 1472) ═══\n";
    BrowserHistory bh("leetcode.com");
    bh.visit("google.com");
    bh.visit("facebook.com");
    bh.visit("youtube.com");
    cout << "  back(1): " << bh.back(1) << "\n";      // facebook
    cout << "  back(1): " << bh.back(1) << "\n";      // google
    cout << "  forward(1): " << bh.forward(1) << "\n"; // facebook
    bh.visit("linkedin.com");
    cout << "  forward(2): " << bh.forward(2) << "\n"; // linkedin (no forward)
    cout << "  back(2): " << bh.back(2) << "\n";      // google
    cout << "  back(7): " << bh.back(7) << "\n\n";    // leetcode

    // Max Stack
    cout << "═══ MAX STACK (LC 716) ═══\n";
    MaxStack ms;
    ms.push(5); ms.push(1); ms.push(5);
    cout << "  After push(5,1,5):\n";
    cout << "  top: " << ms.top() << "\n";         // 5
    cout << "  peekMax: " << ms.peekMax() << "\n"; // 5
    cout << "  popMax: " << ms.popMax() << "\n";   // 5
    cout << "  top: " << ms.top() << "\n";         // 1
    cout << "  peekMax: " << ms.peekMax() << "\n"; // 5
    cout << "  pop: " << ms.pop() << "\n";         // 1
    cout << "  top: " << ms.top() << "\n";         // 5

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE:\n";
    cout << "  LC 641  — Design Circular Deque\n";
    cout << "  LC 716  — Max Stack\n";
    cout << "  LC 1472 — Design Browser History\n";
    cout << "  LC 355  — Design Twitter (Heap + Design)\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

