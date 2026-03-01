/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — STACK: LIFO CONCEPT & ARRAY IMPLEMENTATION                    ║
║           From Zero to Grandmaster — Complete Foundation                     ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What is a Stack?
 2. LIFO (Last In, First Out) Concept
 3. Stack Operations
 4. Array-Based Implementation
 5. Stack Overflow & Underflow
 6. Applications Overview
 7. Dry Run with Visualization
 8. Practice Problems

WHAT IS A STACK?
────────────────
A Stack is a linear data structure that follows the LIFO (Last In, First Out)
principle. Think of it like a stack of plates:
  • You can only ADD (push) a plate on TOP
  • You can only REMOVE (pop) a plate from TOP
  • You can only SEE (peek) the plate on TOP

Real-World Analogies:
  📚 Stack of books     — Take from top, add on top
  🍽️  Stack of plates    — Can't grab the bottom plate
  ↩️  Browser Back button — Goes to LAST visited page
  📝 Undo in text editor — Undoes the LAST action
  🔙 Function call stack — Returns to LAST caller

LIFO VISUALIZATION:
──────────────────
  Push 10, Push 20, Push 30:

        ┌────┐
        │ 30 │  ← TOP (last pushed, first to pop)
        ├────┤
        │ 20 │
        ├────┤
        │ 10 │  ← BOTTOM (first pushed, last to pop)
        └────┘

  Pop() → returns 30 (the LAST element pushed)

        ┌────┐
        │ 20 │  ← new TOP
        ├────┤
        │ 10 │
        └────┘

STACK OPERATIONS & COMPLEXITY:
─────────────────────────────
  ┌────────────────────┬──────────┬──────────────────────┐
  │ Operation          │  Time    │ Description          │
  ├────────────────────┼──────────┼──────────────────────┤
  │ push(x)            │  O(1)    │ Add x on top         │
  │ pop()              │  O(1)    │ Remove top element   │
  │ top() / peek()     │  O(1)    │ View top element     │
  │ isEmpty()          │  O(1)    │ Check if empty       │
  │ isFull()           │  O(1)    │ Check if full        │
  │ size()             │  O(1)    │ Number of elements   │
  └────────────────────┴──────────┴──────────────────────┘
  Space: O(n) where n = max capacity

ARRAY-BASED STACK:
─────────────────
  We use an array and a variable 'topIndex' to track the top.

  Array:    [10] [20] [30] [  ] [  ]
  Index:      0    1    2    3    4
                         ↑
                      topIndex = 2

  push(40): arr[++topIndex] = 40
  Array:    [10] [20] [30] [40] [  ]
  Index:      0    1    2    3    4
                              ↑
                           topIndex = 3

  pop():    return arr[topIndex--]  → returns 40
  Array:    [10] [20] [30] [40] [  ]
  Index:      0    1    2    3    4
                         ↑
                      topIndex = 2
  (arr[3] still has 40 but we won't access it)

OVERFLOW & UNDERFLOW:
────────────────────
  OVERFLOW:  Trying to push when stack is full (topIndex == capacity - 1)
  UNDERFLOW: Trying to pop when stack is empty (topIndex == -1)

  ┌──────────────────────────────────────────────────┐
  │  OVERFLOW: push on full stack                     │
  │  ┌────┐                                           │
  │  │ 50 │ ← topIndex = 4 (capacity = 5)            │
  │  ├────┤   push(60) → ERROR! No space!            │
  │  │ 40 │                                           │
  │  ├────┤                                           │
  │  │ 30 │                                           │
  │  ├────┤                                           │
  │  │ 20 │                                           │
  │  ├────┤                                           │
  │  │ 10 │                                           │
  │  └────┘                                           │
  │                                                    │
  │  UNDERFLOW: pop on empty stack                     │
  │  ┌────┐                                           │
  │  │    │ ← topIndex = -1                           │
  │  └────┘   pop() → ERROR! Nothing to remove!       │
  └──────────────────────────────────────────────────┘

APPLICATIONS OF STACK:
─────────────────────
  1. Function Call Stack (recursion management)
  2. Expression Evaluation (postfix, prefix)
  3. Expression Conversion (infix → postfix)
  4. Parentheses Matching
  5. Undo/Redo operations
  6. Browser Back/Forward
  7. DFS (Depth-First Search)
  8. Backtracking algorithms
  9. Stock Span Problem
  10. Next Greater Element
  11. Histogram problems
  12. String reversal
*/

#include <iostream>
#include <stdexcept>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: STACK USING STATIC ARRAY
// ═══════════════════════════════════════════════════════════════
/*
  Memory Layout:
  ┌──────────────────────────────────────┐
  │  Stack Object                        │
  │  ┌──────────────────────────┐        │
  │  │ arr[0] arr[1] ... arr[N] │ array  │
  │  └──────────────────────────┘        │
  │  topIndex = -1 (empty)               │
  │  capacity = MAX_SIZE                 │
  └──────────────────────────────────────┘
*/

class StackArray {
private:
    static const int MAX_SIZE = 1000;
    int arr[MAX_SIZE];
    int topIndex;

public:
    // Constructor: Initialize empty stack
    StackArray() : topIndex(-1) {}

    // Push: Add element on top
    // Time: O(1)
    void push(int val) {
        if (isFull()) {
            cout << "  ❌ OVERFLOW! Stack is full. Cannot push " << val << "\n";
            return;
        }
        arr[++topIndex] = val;
    }

    // Pop: Remove and return top element
    // Time: O(1)
    int pop() {
        if (isEmpty()) {
            cout << "  ❌ UNDERFLOW! Stack is empty. Cannot pop.\n";
            return -1;
        }
        return arr[topIndex--];
    }

    // Top/Peek: View top element without removing
    // Time: O(1)
    int top() {
        if (isEmpty()) {
            cout << "  ❌ Stack is empty. No top element.\n";
            return -1;
        }
        return arr[topIndex];
    }

    // isEmpty: Check if stack has no elements
    // Time: O(1)
    bool isEmpty() {
        return topIndex == -1;
    }

    // isFull: Check if stack is at capacity
    // Time: O(1)
    bool isFull() {
        return topIndex == MAX_SIZE - 1;
    }

    // Size: Number of elements currently in stack
    // Time: O(1)
    int size() {
        return topIndex + 1;
    }

    // Display: Print stack from top to bottom
    void display() {
        if (isEmpty()) {
            cout << "  Stack is EMPTY\n";
            return;
        }
        cout << "  TOP → ";
        for (int i = topIndex; i >= 0; i--) {
            cout << arr[i];
            if (i > 0) cout << " → ";
        }
        cout << " → BOTTOM\n";
    }
};

// ═══════════════════════════════════════════════════════════════
// SECTION 2: STACK USING DYNAMIC ARRAY
// ═══════════════════════════════════════════════════════════════
/*
  Dynamic stack doubles capacity when full.
  This mimics how std::stack<int> with std::vector works internally.

  Amortized Analysis:
  ─────────────────
  When we double capacity, we copy all elements: O(n)
  But this happens only after n pushes.
  So amortized cost per push = O(n)/n = O(1)

  Capacity Growth:
  push 1: cap=1 → [1]
  push 2: cap=2 → [1,2]          (doubled from 1→2, copy 1 element)
  push 3: cap=4 → [1,2,3, ]      (doubled from 2→4, copy 2 elements)
  push 4: cap=4 → [1,2,3,4]
  push 5: cap=8 → [1,2,3,4,5, , , ]  (doubled from 4→8, copy 4 elements)
*/

class DynamicStack {
private:
    int* arr;
    int topIndex;
    int capacity;

    void resize() {
        int newCapacity = capacity * 2;
        int* newArr = new int[newCapacity];
        for (int i = 0; i <= topIndex; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
        cout << "  📈 Stack resized: " << capacity / 2 << " → " << capacity << "\n";
    }

public:
    DynamicStack(int initCap = 2) : topIndex(-1), capacity(initCap) {
        arr = new int[capacity];
    }

    ~DynamicStack() {
        delete[] arr;
    }

    void push(int val) {
        if (topIndex == capacity - 1) {
            resize();
        }
        arr[++topIndex] = val;
    }

    int pop() {
        if (topIndex == -1) {
            throw runtime_error("Stack underflow!");
        }
        return arr[topIndex--];
    }

    int top() {
        if (topIndex == -1) {
            throw runtime_error("Stack is empty!");
        }
        return arr[topIndex];
    }

    bool isEmpty() { return topIndex == -1; }
    int size() { return topIndex + 1; }
    int getCapacity() { return capacity; }

    void display() {
        cout << "  [size=" << size() << ", cap=" << capacity << "] TOP → ";
        for (int i = topIndex; i >= 0; i--) {
            cout << arr[i];
            if (i > 0) cout << " → ";
        }
        if (isEmpty()) cout << "(empty)";
        cout << "\n";
    }
};

// ═══════════════════════════════════════════════════════════════
// SECTION 3: COMPLETE DRY RUN DEMONSTRATION
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — Operations: push(10), push(20), push(30), top(), pop(), push(40), size()

  Operation    │ Action              │ topIndex │ Stack State      │ Returns
  ─────────────┼─────────────────────┼──────────┼──────────────────┼─────────
  Initial      │ Constructor         │    -1    │ []               │ —
  push(10)     │ arr[0] = 10         │     0    │ [10]             │ —
  push(20)     │ arr[1] = 20         │     1    │ [10, 20]         │ —
  push(30)     │ arr[2] = 30         │     2    │ [10, 20, 30]     │ —
  top()        │ return arr[2]       │     2    │ [10, 20, 30]     │ 30
  pop()        │ return arr[2]; t--  │     1    │ [10, 20]         │ 30
  push(40)     │ arr[2] = 40         │     2    │ [10, 20, 40]     │ —
  size()       │ return topIndex+1   │     2    │ [10, 20, 40]     │ 3
  pop()        │ return arr[2]; t--  │     1    │ [10, 20]         │ 40
  pop()        │ return arr[1]; t--  │     0    │ [10]             │ 20
  pop()        │ return arr[0]; t--  │    -1    │ []               │ 10
  pop()        │ UNDERFLOW!          │    -1    │ []               │ ERROR

  Visual at each step:
  ┌─────────────────────────────────────────┐
  │  After push(10):    │ 10 │              │
  │                     └────┘              │
  │  After push(20):    │ 20 │              │
  │                     │ 10 │              │
  │                     └────┘              │
  │  After push(30):    │ 30 │ ← TOP       │
  │                     │ 20 │              │
  │                     │ 10 │              │
  │                     └────┘              │
  │  After pop():       │ 20 │ ← TOP       │
  │                     │ 10 │              │
  │                     └────┘              │
  │  After push(40):    │ 40 │ ← TOP       │
  │                     │ 20 │              │
  │                     │ 10 │              │
  │                     └────┘              │
  └─────────────────────────────────────────┘
*/

void demonstrateStaticStack() {
    cout << "═══ SECTION 1: STATIC ARRAY STACK ═══\n\n";

    StackArray st;

    cout << "isEmpty: " << (st.isEmpty() ? "true" : "false") << "\n";
    cout << "Pushing 10, 20, 30...\n";
    st.push(10);
    st.push(20);
    st.push(30);
    st.display();

    cout << "Top element: " << st.top() << "\n";
    cout << "Size: " << st.size() << "\n";

    cout << "Pop: " << st.pop() << "\n";
    st.display();

    cout << "Push 40, 50...\n";
    st.push(40);
    st.push(50);
    st.display();

    cout << "Popping all elements: ";
    while (!st.isEmpty()) {
        cout << st.pop() << " ";
    }
    cout << "\n";
    cout << "isEmpty: " << (st.isEmpty() ? "true" : "false") << "\n";

    // Test underflow
    cout << "\nTesting underflow:\n";
    st.pop();

    cout << "\n";
}

void demonstrateDynamicStack() {
    cout << "═══ SECTION 2: DYNAMIC ARRAY STACK ═══\n\n";

    DynamicStack ds(2);  // Start with capacity 2

    cout << "Initial capacity: " << ds.getCapacity() << "\n";

    cout << "Pushing 10, 20 (fills initial capacity)...\n";
    ds.push(10);
    ds.push(20);
    ds.display();

    cout << "Pushing 30 (triggers resize)...\n";
    ds.push(30);
    ds.display();

    cout << "Pushing 40...\n";
    ds.push(40);
    ds.display();

    cout << "Pushing 50 (triggers resize again)...\n";
    ds.push(50);
    ds.display();

    cout << "\nPopping all: ";
    while (!ds.isEmpty()) {
        cout << ds.pop() << " ";
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: REVERSE A STRING USING STACK
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — Reverse "HELLO":

  Push phase:
    push('H') → stack: [H]
    push('E') → stack: [H, E]
    push('L') → stack: [H, E, L]
    push('L') → stack: [H, E, L, L]
    push('O') → stack: [H, E, L, L, O]

  Pop phase:
    pop() → 'O'  result: "O"
    pop() → 'L'  result: "OL"
    pop() → 'L'  result: "OLL"
    pop() → 'E'  result: "OLLE"
    pop() → 'H'  result: "OLLEH"

  Result: "OLLEH" ✅ (reversed!)
*/

void demonstrateStringReverse() {
    cout << "═══ SECTION 4: REVERSE STRING USING STACK ═══\n\n";

    string str = "HELLO";
    StackArray st;

    cout << "Original: " << str << "\n";

    // Push all characters
    for (char c : str) {
        st.push(c);
    }

    // Pop all characters (reversed order)
    string reversed = "";
    while (!st.isEmpty()) {
        reversed += (char)st.pop();
    }

    cout << "Reversed: " << reversed << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  STACK: LIFO CONCEPT & ARRAY IMPLEMENTATION              ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    demonstrateStaticStack();
    demonstrateDynamicStack();
    demonstrateStringReverse();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE PROBLEMS:\n";
    cout << "───────────────────\n";
    cout << "1. Implement a stack that also supports getMin() in O(1)\n";
    cout << "2. Implement two stacks in one array\n";
    cout << "3. Reverse a number using stack\n";
    cout << "4. Check if a string is a palindrome using stack\n";
    cout << "5. Sort a stack using only push and pop operations\n";
    cout << "6. Implement N stacks in a single array\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

