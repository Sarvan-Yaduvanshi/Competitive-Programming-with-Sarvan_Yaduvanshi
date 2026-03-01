/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — STL STACK: COMPLETE API & USAGE                               ║
║           From Zero to Grandmaster — STL Mastery                            ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. std::stack Overview
 2. Internal Implementation
 3. All Member Functions
 4. Common Patterns
 5. Dry Run & Visualization

STD::STACK OVERVIEW:
───────────────────
  #include <stack>
  std::stack<T> is a container adaptor — it wraps another container.
  Default underlying container: std::deque<T>

  Can also use: stack<int, vector<int>> or stack<int, list<int>>

  ┌────────────────────────────────────────┐
  │  stack<int> st;                        │
  │                                        │
  │  Internally uses deque:                │
  │  deque: [10, 20, 30]                   │
  │                  ↑                     │
  │                 TOP (back of deque)    │
  │                                        │
  │  st.push(40) → deque.push_back(40)    │
  │  st.pop()    → deque.pop_back()       │
  │  st.top()    → deque.back()           │
  └────────────────────────────────────────┘

ALL MEMBER FUNCTIONS:
────────────────────
  ┌────────────────┬──────────┬────────────────────────────────┐
  │ Function       │  Time    │ Description                    │
  ├────────────────┼──────────┼────────────────────────────────┤
  │ push(val)      │  O(1)    │ Insert element at top          │
  │ pop()          │  O(1)    │ Remove top element (void!)     │
  │ top()          │  O(1)    │ Reference to top element       │
  │ empty()        │  O(1)    │ Check if stack is empty        │
  │ size()         │  O(1)    │ Number of elements             │
  │ emplace(args)  │  O(1)    │ Construct element in-place     │
  │ swap(other)    │  O(1)    │ Swap contents with other stack │
  └────────────────┴──────────┴────────────────────────────────┘

  ⚠️ IMPORTANT:
  - pop() returns VOID (not the element!)
  - To get and remove: save top() first, then pop()
  - No iterator support! Can't traverse without popping.
  - No clear() function! Pop in loop or swap with empty stack.
*/

#include <iostream>
#include <stack>
#include <vector>
#include <list>
#include <string>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC OPERATIONS
// ═══════════════════════════════════════════════════════════════

void demonstrateBasics() {
    cout << "═══ SECTION 1: STL STACK BASICS ═══\n\n";

    stack<int> st;

    // Push elements
    st.push(10);
    st.push(20);
    st.push(30);
    st.push(40);

    cout << "After push(10, 20, 30, 40):\n";
    cout << "  Top: " << st.top() << "\n";       // 40
    cout << "  Size: " << st.size() << "\n";      // 4
    cout << "  Empty: " << st.empty() << "\n\n";  // 0 (false)

    // Pop (returns void!)
    st.pop();
    cout << "After pop(): Top = " << st.top() << "\n";  // 30

    // Get and remove
    int val = st.top();  // First get the value
    st.pop();            // Then remove
    cout << "Got and removed: " << val << "\n";
    cout << "New top: " << st.top() << "\n\n";  // 20

    // Print all elements (destructive — pops everything)
    cout << "Print all (destructive): ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << "\nStack is now empty: " << st.empty() << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: DIFFERENT UNDERLYING CONTAINERS
// ═══════════════════════════════════════════════════════════════
/*
  stack<T, Container> where Container can be:
    - deque<T>  (default) — Best general performance
    - vector<T>           — Contiguous memory, good cache
    - list<T>             — No reallocation, O(1) push always
*/

void demonstrateContainers() {
    cout << "═══ SECTION 2: DIFFERENT UNDERLYING CONTAINERS ═══\n\n";

    // Default (deque)
    stack<int> st1;
    st1.push(100);
    cout << "stack<int> (deque): " << st1.top() << "\n";

    // Vector-based
    stack<int, vector<int>> st2;
    st2.push(200);
    cout << "stack<int, vector<int>>: " << st2.top() << "\n";

    // List-based
    stack<int, list<int>> st3;
    st3.push(300);
    cout << "stack<int, list<int>>: " << st3.top() << "\n";

    cout << "\nPerformance comparison:\n";
    cout << "  deque:  Good all-around, default choice\n";
    cout << "  vector: Better cache locality, may reallocate\n";
    cout << "  list:   Guaranteed O(1) push, but more memory\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: EMPLACE & SWAP
// ═══════════════════════════════════════════════════════════════

void demonstrateEmplaceSwap() {
    cout << "═══ SECTION 3: EMPLACE & SWAP ═══\n\n";

    // emplace — constructs in-place (avoids copy)
    stack<pair<int, string>> st;
    st.emplace(1, "Hello");     // Constructs pair in-place
    st.emplace(2, "World");
    // vs st.push(make_pair(3, "!")); — creates pair, then copies

    cout << "Emplace: (" << st.top().first << ", " << st.top().second << ")\n";

    // swap — exchange contents in O(1)
    stack<int> a, b;
    a.push(10); a.push(20);
    b.push(100); b.push(200); b.push(300);

    cout << "\nBefore swap:\n";
    cout << "  a.top=" << a.top() << " a.size=" << a.size() << "\n";
    cout << "  b.top=" << b.top() << " b.size=" << b.size() << "\n";

    a.swap(b);

    cout << "After swap:\n";
    cout << "  a.top=" << a.top() << " a.size=" << a.size() << "\n";
    cout << "  b.top=" << b.top() << " b.size=" << b.size() << "\n";

    // Clear a stack (no clear() function!)
    // Method 1: Pop loop
    while (!a.empty()) a.pop();
    // Method 2: Swap with empty
    stack<int>().swap(b);  // b is now empty
    cout << "\nAfter clearing: a.empty=" << a.empty() << " b.empty=" << b.empty() << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: COMMON PATTERNS WITH STL STACK
// ═══════════════════════════════════════════════════════════════

// Pattern 1: Reverse a collection
void reverseUsingStack() {
    cout << "Pattern 1: Reverse a string\n";
    string s = "ALGORITHM";
    stack<char> st;
    for (char c : s) st.push(c);

    string reversed;
    while (!st.empty()) {
        reversed += st.top();
        st.pop();
    }
    cout << "  Original: " << s << "\n";
    cout << "  Reversed: " << reversed << "\n\n";
}

// Pattern 2: Check balanced parentheses
bool isBalanced(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            char top = st.top();
            if ((c == ')' && top == '(') ||
                (c == '}' && top == '{') ||
                (c == ']' && top == '[')) {
                st.pop();
            } else {
                return false;
            }
        }
    }
    return st.empty();
}

// Pattern 3: Copy/Print without destroying
void printStack(stack<int> st) {  // Pass by VALUE (copy)
    cout << "  Stack (top→bottom): ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << "\n";
}

void demonstratePatterns() {
    cout << "═══ SECTION 4: COMMON PATTERNS ═══\n\n";

    reverseUsingStack();

    cout << "Pattern 2: Balanced parentheses\n";
    vector<string> tests = {"(())", "{[()]}", "({[)", "", "(", "([]){}"};
    for (auto& s : tests) {
        cout << "  \"" << s << "\" → " << (isBalanced(s) ? "✅ Balanced" : "❌ Not balanced") << "\n";
    }
    cout << "\n";

    cout << "Pattern 3: Print without destroying (pass by value)\n";
    stack<int> st;
    for (int v : {10, 20, 30, 40, 50}) st.push(v);
    printStack(st);
    cout << "  Original still has " << st.size() << " elements\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  STL STACK: COMPLETE API & USAGE                         ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    demonstrateBasics();
    demonstrateContainers();
    demonstrateEmplaceSwap();
    demonstratePatterns();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "⚠️  COMMON MISTAKES TO AVOID:\n";
    cout << "───────────────────────────────\n";
    cout << "  ❌ int x = st.pop();     — pop() returns VOID!\n";
    cout << "  ✅ int x = st.top(); st.pop();\n\n";
    cout << "  ❌ st.top() on empty stack — UNDEFINED BEHAVIOR!\n";
    cout << "  ✅ if (!st.empty()) st.top();\n\n";
    cout << "  ❌ for (auto x : st)     — NO ITERATOR support!\n";
    cout << "  ✅ while (!st.empty()) { use top(); pop(); }\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

