/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — STACK: LINKED LIST IMPLEMENTATION                             ║
║           From Zero to Grandmaster — Complete Foundation                     ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Why Linked List for Stack?
 2. Node Structure
 3. Push Operation (Insert at Head)
 4. Pop Operation (Delete from Head)
 5. Top / Peek Operation
 6. Complete Implementation
 7. Array vs Linked List Stack Comparison
 8. Dry Run with Memory Visualization

WHY LINKED LIST FOR STACK?
──────────────────────────
  Array Stack:
    ✅ Cache-friendly (contiguous memory)
    ✅ Simple implementation
    ❌ Fixed size (or expensive resizing)
    ❌ Wastes memory if under-utilized

  Linked List Stack:
    ✅ Dynamic size (no overflow unless system memory full)
    ✅ No wasted memory
    ✅ No resizing needed
    ❌ Extra memory per element (pointer overhead)
    ❌ Not cache-friendly (scattered memory)

  Key Insight: Push = Insert at Head, Pop = Delete from Head
  Both are O(1) with a singly linked list!

LINKED LIST STACK VISUALIZATION:
───────────────────────────────
  Push 10, Push 20, Push 30:

  top ──▶ [30 | ──]──▶ [20 | ──]──▶ [10 | NULL]
           ↑ TOP

  Pop() → returns 30:

  top ──▶ [20 | ──]──▶ [10 | NULL]
           ↑ TOP

  The 'top' pointer is the HEAD of the linked list.
  Push = insert at head (O(1))
  Pop  = delete from head (O(1))

MEMORY COMPARISON:
─────────────────
  Array Stack (capacity 5, size 3):
  ┌────┬────┬────┬────┬────┐
  │ 10 │ 20 │ 30 │    │    │   2 slots wasted
  └────┴────┴────┴────┴────┘
  Memory: 5 × sizeof(int) = 20 bytes

  Linked List Stack (size 3):
  [30|ptr] → [20|ptr] → [10|NULL]
  Memory: 3 × (sizeof(int) + sizeof(ptr)) = 3 × 12 = 36 bytes
  (No wasted slots, but pointer overhead per node)
*/

#include <iostream>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: NODE STRUCTURE
// ═══════════════════════════════════════════════════════════════
/*
  ┌───────┬──────────┐
  │ data  │  next ───┼──▶ (points to node below in stack)
  └───────┴──────────┘
*/

struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
    Node(int val, Node* nxt) : data(val), next(nxt) {}
};

// ═══════════════════════════════════════════════════════════════
// SECTION 2: STACK USING LINKED LIST
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — push(10), push(20), push(30), pop(), top():

  push(10):
    Create node [10|NULL]
    topNode ──▶ [10 | NULL]
    size = 1

  push(20):
    Create node [20|NULL]
    Set new->next = topNode (which points to [10|NULL])
    topNode ──▶ [20 | ──]──▶ [10 | NULL]
    size = 2

  push(30):
    Create node [30|NULL]
    Set new->next = topNode (which points to [20|...])
    topNode ──▶ [30 | ──]──▶ [20 | ──]──▶ [10 | NULL]
    size = 3

  pop():
    Save topNode->data = 30
    Save temp = topNode
    topNode = topNode->next
    Delete temp
    topNode ──▶ [20 | ──]──▶ [10 | NULL]
    size = 2, returns 30

  top():
    Return topNode->data = 20 (without removing)
*/

class StackLL {
private:
    Node* topNode;
    int count;

public:
    // Constructor: Empty stack
    StackLL() : topNode(nullptr), count(0) {}

    // Destructor: Free all nodes
    ~StackLL() {
        while (topNode != nullptr) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    // Push: Insert at head — O(1)
    /*
      Before: top → [B] → [A] → NULL
      After:  top → [NEW] → [B] → [A] → NULL

      Steps:
        1. Create new node with value
        2. Point new node's next to current top
        3. Update top to new node
        4. Increment size
    */
    void push(int val) {
        Node* newNode = new Node(val, topNode);
        topNode = newNode;
        count++;
    }

    // Pop: Delete from head — O(1)
    /*
      Before: top → [C] → [B] → [A] → NULL
      After:  top → [B] → [A] → NULL  (C is deleted, returns C's data)

      Steps:
        1. Check underflow (empty stack)
        2. Save top's data
        3. Save temp pointer to top
        4. Move top to next node
        5. Delete old top
        6. Decrement size
    */
    int pop() {
        if (isEmpty()) {
            cout << "  ❌ UNDERFLOW! Stack is empty.\n";
            return -1;
        }
        int val = topNode->data;
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        count--;
        return val;
    }

    // Top: View top element — O(1)
    int top() {
        if (isEmpty()) {
            cout << "  ❌ Stack is empty.\n";
            return -1;
        }
        return topNode->data;
    }

    bool isEmpty() { return topNode == nullptr; }
    int size() { return count; }

    // Display: Print from top to bottom
    void display() {
        if (isEmpty()) {
            cout << "  Stack: (empty)\n";
            return;
        }
        cout << "  TOP → ";
        Node* curr = topNode;
        while (curr != nullptr) {
            cout << "[" << curr->data << "]";
            if (curr->next) cout << " → ";
            curr = curr->next;
        }
        cout << " → NULL\n";
    }

    // Display with memory addresses
    void displayDetailed() {
        if (isEmpty()) {
            cout << "  Stack: (empty)\n";
            return;
        }
        cout << "  Stack (top to bottom):\n";
        Node* curr = topNode;
        int pos = 0;
        while (curr != nullptr) {
            cout << "    [" << pos << "] data=" << curr->data
                 << " @" << curr << " next→" << curr->next << "\n";
            curr = curr->next;
            pos++;
        }
    }
};

// ═══════════════════════════════════════════════════════════════
// SECTION 3: DEMONSTRATION
// ═══════════════════════════════════════════════════════════════

void demonstrateLinkedListStack() {
    cout << "═══ LINKED LIST STACK DEMONSTRATION ═══\n\n";

    StackLL st;

    cout << "isEmpty: " << (st.isEmpty() ? "true" : "false") << "\n\n";

    // Push operations
    cout << "Push 10:\n";
    st.push(10);
    st.display();

    cout << "Push 20:\n";
    st.push(20);
    st.display();

    cout << "Push 30:\n";
    st.push(30);
    st.display();

    cout << "\nDetailed view:\n";
    st.displayDetailed();

    // Top and Pop
    cout << "\nTop: " << st.top() << "\n";
    cout << "Pop: " << st.pop() << "\n";
    st.display();

    cout << "Pop: " << st.pop() << "\n";
    st.display();

    cout << "Pop: " << st.pop() << "\n";
    st.display();

    // Underflow test
    cout << "\nTesting underflow:\n";
    st.pop();

    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: GENERIC TEMPLATE STACK
// ═══════════════════════════════════════════════════════════════

template <typename T>
class GenericStack {
private:
    struct GNode {
        T data;
        GNode* next;
        GNode(T val, GNode* nxt = nullptr) : data(val), next(nxt) {}
    };

    GNode* topNode;
    int count;

public:
    GenericStack() : topNode(nullptr), count(0) {}

    ~GenericStack() {
        while (topNode) {
            GNode* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    void push(T val) {
        topNode = new GNode(val, topNode);
        count++;
    }

    T pop() {
        if (!topNode) throw runtime_error("Stack underflow!");
        T val = topNode->data;
        GNode* temp = topNode;
        topNode = topNode->next;
        delete temp;
        count--;
        return val;
    }

    T top() {
        if (!topNode) throw runtime_error("Stack empty!");
        return topNode->data;
    }

    bool isEmpty() { return topNode == nullptr; }
    int size() { return count; }
};

void demonstrateGenericStack() {
    cout << "═══ GENERIC TEMPLATE STACK ═══\n\n";

    // Integer stack
    GenericStack<int> intStack;
    intStack.push(100);
    intStack.push(200);
    intStack.push(300);
    cout << "Int stack top: " << intStack.top() << "\n";
    cout << "Int stack pop: " << intStack.pop() << "\n";

    // String stack
    GenericStack<string> strStack;
    strStack.push("Hello");
    strStack.push("World");
    strStack.push("Stack");
    cout << "String stack top: " << strStack.top() << "\n";
    cout << "String stack pop: " << strStack.pop() << "\n";

    // Double stack
    GenericStack<double> dblStack;
    dblStack.push(3.14);
    dblStack.push(2.72);
    cout << "Double stack top: " << dblStack.top() << "\n";

    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  STACK: LINKED LIST IMPLEMENTATION                       ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    demonstrateLinkedListStack();
    demonstrateGenericStack();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "COMPARISON: ARRAY vs LINKED LIST STACK:\n";
    cout << "───────────────────────────────────────────────────────────\n";
    cout << "┌──────────────────┬─────────────┬────────────────┐\n";
    cout << "│ Feature          │ Array Stack │ LL Stack       │\n";
    cout << "├──────────────────┼─────────────┼────────────────┤\n";
    cout << "│ Push             │ O(1) amort. │ O(1)           │\n";
    cout << "│ Pop              │ O(1)        │ O(1)           │\n";
    cout << "│ Memory           │ Pre-alloc   │ On-demand      │\n";
    cout << "│ Cache            │ Friendly    │ Unfriendly     │\n";
    cout << "│ Overflow         │ Possible    │ Only sys limit │\n";
    cout << "│ Extra per elem   │ 0 bytes     │ 8 bytes (ptr)  │\n";
    cout << "└──────────────────┴─────────────┴────────────────┘\n";
    cout << "\n";
    cout << "PRACTICE PROBLEMS:\n";
    cout << "───────────────────\n";
    cout << "1. Implement a stack with getMax() in O(1) using LL\n";
    cout << "2. Merge two stacks into one sorted stack\n";
    cout << "3. Implement a stack iterator (traverse without pop)\n";
    cout << "4. Clone a stack (deep copy)\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

