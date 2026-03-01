/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — LINKED LIST + STACK, QUEUE, HEAP, MAP                       ║
║           From Zero to Grandmaster — LL with Other Data Structures         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Stack using Linked List
 2. Queue using Linked List
 3. Linked List + Heap (Priority Queue)
 4. Linked List + Map (HashMap)
 5. Linked List in Graph (Adjacency List)
 6. Polynomial Representation using Linked List

STACK USING LL:
──────────────
  Push = Insert at head → O(1)
  Pop  = Delete head    → O(1)
  Top  = head->data     → O(1)

  push(3), push(5), push(7):
  top ──▶ [7] ──▶ [5] ──▶ [3] ──▶ NULL

  pop() returns 7:
  top ──▶ [5] ──▶ [3] ──▶ NULL

QUEUE USING LL:
──────────────
  Enqueue = Insert at tail → O(1) with tail pointer
  Dequeue = Delete head    → O(1)
  Front   = head->data     → O(1)

  enqueue(1), enqueue(2), enqueue(3):
  front ──▶ [1] ──▶ [2] ──▶ [3] ◀── rear

  dequeue() returns 1:
  front ──▶ [2] ──▶ [3] ◀── rear
*/

#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// ═══════════════════════════════════════════════════════════════
// 1. STACK USING LINKED LIST — All operations O(1)
// ═══════════════════════════════════════════════════════════════

class LLStack {
    Node* top_node;
    int sz;
public:
    LLStack() : top_node(nullptr), sz(0) {}
    ~LLStack() { while (top_node) { Node* t = top_node; top_node = top_node->next; delete t; } }

    void push(int val) {
        Node* node = new Node(val);
        node->next = top_node;
        top_node = node;
        sz++;
    }

    int pop() {
        if (!top_node) return -1;
        int val = top_node->data;
        Node* temp = top_node;
        top_node = top_node->next;
        delete temp;
        sz--;
        return val;
    }

    int top() { return top_node ? top_node->data : -1; }
    int size() { return sz; }
    bool empty() { return sz == 0; }
};

// ═══════════════════════════════════════════════════════════════
// 2. QUEUE USING LINKED LIST — All operations O(1)
// ═══════════════════════════════════════════════════════════════

class LLQueue {
    Node* front_node;
    Node* rear_node;
    int sz;
public:
    LLQueue() : front_node(nullptr), rear_node(nullptr), sz(0) {}
    ~LLQueue() { while (front_node) { Node* t = front_node; front_node = front_node->next; delete t; } }

    void enqueue(int val) {
        Node* node = new Node(val);
        if (!rear_node) {
            front_node = rear_node = node;
        } else {
            rear_node->next = node;
            rear_node = node;
        }
        sz++;
    }

    int dequeue() {
        if (!front_node) return -1;
        int val = front_node->data;
        Node* temp = front_node;
        front_node = front_node->next;
        if (!front_node) rear_node = nullptr;
        delete temp;
        sz--;
        return val;
    }

    int front() { return front_node ? front_node->data : -1; }
    int rear() { return rear_node ? rear_node->data : -1; }
    int size() { return sz; }
    bool empty() { return sz == 0; }
};

// ═══════════════════════════════════════════════════════════════
// 3. GRAPH ADJACENCY LIST — Using Linked Lists
// ═══════════════════════════════════════════════════════════════
/*
  Graph:
    0 → 1 → 4
    1 → 0 → 2 → 3 → 4
    2 → 1 → 3
    3 → 1 → 2 → 4
    4 → 0 → 1 → 3

  Adjacency List:
  ┌───┐
  │ 0 │ → [1] → [4] → NULL
  ├───┤
  │ 1 │ → [0] → [2] → [3] → [4] → NULL
  ├───┤
  │ 2 │ → [1] → [3] → NULL
  ├───┤
  │ 3 │ → [1] → [2] → [4] → NULL
  ├───┤
  │ 4 │ → [0] → [1] → [3] → NULL
  └───┘
*/

class Graph {
    int V;
    Node** adjList;

public:
    Graph(int v) : V(v) {
        adjList = new Node*[V];
        for (int i = 0; i < V; i++) adjList[i] = nullptr;
    }

    ~Graph() {
        for (int i = 0; i < V; i++) {
            Node* curr = adjList[i];
            while (curr) { Node* t = curr; curr = curr->next; delete t; }
        }
        delete[] adjList;
    }

    void addEdge(int u, int v) {
        // Insert at head of adjacency list (O(1))
        Node* node = new Node(v);
        node->next = adjList[u];
        adjList[u] = node;

        // Undirected: add reverse edge too
        node = new Node(u);
        node->next = adjList[v];
        adjList[v] = node;
    }

    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "  " << i << " → ";
            Node* curr = adjList[i];
            while (curr) {
                cout << curr->data;
                if (curr->next) cout << " → ";
                curr = curr->next;
            }
            cout << " → NULL\n";
        }
    }
};

// ═══════════════════════════════════════════════════════════════
// 4. POLYNOMIAL REPRESENTATION
// ═══════════════════════════════════════════════════════════════
/*
  Polynomial: 3x^3 + 2x^2 + 5x^1 + 7x^0

  Linked List: [3,3] → [2,2] → [5,1] → [7,0] → NULL
               (coeff, exp)
*/

struct PolyNode {
    int coeff, exp;
    PolyNode* next;
    PolyNode(int c, int e) : coeff(c), exp(e), next(nullptr) {}
};

PolyNode* addPolynomials(PolyNode* p1, PolyNode* p2) {
    PolyNode dummy(0, 0);
    PolyNode* tail = &dummy;

    while (p1 && p2) {
        if (p1->exp > p2->exp) {
            tail->next = new PolyNode(p1->coeff, p1->exp);
            p1 = p1->next;
        } else if (p1->exp < p2->exp) {
            tail->next = new PolyNode(p2->coeff, p2->exp);
            p2 = p2->next;
        } else {
            int sum = p1->coeff + p2->coeff;
            if (sum != 0) tail->next = new PolyNode(sum, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        }
        if (tail->next) tail = tail->next;
    }

    while (p1) { tail->next = new PolyNode(p1->coeff, p1->exp); p1 = p1->next; tail = tail->next; }
    while (p2) { tail->next = new PolyNode(p2->coeff, p2->exp); p2 = p2->next; tail = tail->next; }

    return dummy.next;
}

void printPoly(PolyNode* head) {
    while (head) {
        cout << head->coeff << "x^" << head->exp;
        if (head->next) cout << " + ";
        head = head->next;
    }
    cout << "\n";
}

void freePoly(PolyNode* head) {
    while (head) { PolyNode* t = head; head = head->next; delete t; }
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  LINKED LIST + STACK, QUEUE, GRAPH, POLYNOMIAL         ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Stack
    cout << "═══ STACK USING LINKED LIST ═══\n";
    LLStack stk;
    stk.push(10); stk.push(20); stk.push(30);
    cout << "Push 10, 20, 30 → Top: " << stk.top() << ", Size: " << stk.size() << "\n";
    cout << "Pop: " << stk.pop() << ", Top: " << stk.top() << "\n";

    // Queue
    cout << "\n═══ QUEUE USING LINKED LIST ═══\n";
    LLQueue q;
    q.enqueue(1); q.enqueue(2); q.enqueue(3);
    cout << "Enqueue 1, 2, 3 → Front: " << q.front() << ", Rear: " << q.rear() << "\n";
    cout << "Dequeue: " << q.dequeue() << ", Front: " << q.front() << "\n";

    // Graph
    cout << "\n═══ GRAPH ADJACENCY LIST ═══\n";
    Graph g(5);
    g.addEdge(0, 1); g.addEdge(0, 4);
    g.addEdge(1, 2); g.addEdge(1, 3); g.addEdge(1, 4);
    g.addEdge(2, 3); g.addEdge(3, 4);
    g.printGraph();

    // Polynomial Addition
    cout << "\n═══ POLYNOMIAL ADDITION ═══\n";
    // P1: 3x^3 + 2x^2 + 5x^0
    PolyNode* p1 = new PolyNode(3, 3);
    p1->next = new PolyNode(2, 2);
    p1->next->next = new PolyNode(5, 0);

    // P2: 4x^3 + 1x^1 + 2x^0
    PolyNode* p2 = new PolyNode(4, 3);
    p2->next = new PolyNode(1, 1);
    p2->next->next = new PolyNode(2, 0);

    cout << "P1: "; printPoly(p1);
    cout << "P2: "; printPoly(p2);

    PolyNode* sum = addPolynomials(p1, p2);
    cout << "Sum: "; printPoly(sum);

    freePoly(p1); freePoly(p2); freePoly(sum);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "KEY INSIGHT: Linked Lists are the backbone of many DS!\n";
    cout << "  Hash tables → chaining with LL\n";
    cout << "  Graphs → adjacency list with LL\n";
    cout << "  Stack/Queue → LL implementation\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

