/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — QUEUE USING STACKS + STACK USING QUEUES                       ║
║           From Zero to Grandmaster — Stack & Queue Design Problems          ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

QUEUE USING TWO STACKS (LC 232):
────────────────────────────────
  Two approaches:

  1. COSTLY ENQUEUE: On enqueue, transfer all from s1→s2, push to s1, transfer back.
     Enqueue: O(n), Dequeue: O(1)

  2. COSTLY DEQUEUE (AMORTIZED O(1)): ✅ Better!
     s1 = input stack, s2 = output stack
     Enqueue: push to s1 → O(1)
     Dequeue: if s2 empty, transfer all from s1→s2 (reverses order!)
              pop from s2 → Amortized O(1)

  DRY RUN (Approach 2):
  enqueue(1): s1=[1], s2=[]
  enqueue(2): s1=[1,2], s2=[]
  dequeue():  s2 empty → transfer: s1=[], s2=[2,1] → pop s2 → returns 1
  enqueue(3): s1=[3], s2=[2]
  dequeue():  s2 not empty → pop s2 → returns 2
  dequeue():  s2 empty → transfer: s1=[], s2=[3] → pop s2 → returns 3

  ┌──────────────────────────────────────────────────┐
  │ s1 (input)    s2 (output)                        │
  │ [1,2]    →    []            enqueue(1), enqueue(2)│
  │ []       ←    [2,1]         transfer for dequeue  │
  │ []            [2]           dequeue() → 1         │
  │ [3]           [2]           enqueue(3)            │
  │ [3]           []            dequeue() → 2         │
  │ []            [3]           transfer for dequeue  │
  │ []            []            dequeue() → 3         │
  └──────────────────────────────────────────────────┘

STACK USING TWO QUEUES (LC 225):
────────────────────────────────
  Approach: Make push costly — on push, put new element,
  then transfer all from other queue to make it front.

  push(1): q1=[1]
  push(2): q1=[2], transfer 1 from q2...
  Actually: push to q2, transfer all of q1 to q2, swap q1/q2

  push(1): q1=[1]
  push(2): q2=[2], transfer q1→q2: q2=[2,1], swap → q1=[2,1]
  push(3): q2=[3], transfer q1→q2: q2=[3,2,1], swap → q1=[3,2,1]
  pop():   q1.front()=3, pop → q1=[2,1]
  top():   q1.front()=2
*/

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// QUEUE USING TWO STACKS (LC 232)
// ═══════════════════════════════════════════════════════════════

class MyQueue {
    stack<int> input, output;

    void transfer() {
        while (!input.empty()) {
            output.push(input.top());
            input.pop();
        }
    }

public:
    void push(int x) { input.push(x); }  // O(1)

    int pop() {
        if (output.empty()) transfer();
        int val = output.top();
        output.pop();
        return val;
    }

    int peek() {
        if (output.empty()) transfer();
        return output.top();
    }

    bool empty() { return input.empty() && output.empty(); }
};

// ═══════════════════════════════════════════════════════════════
// STACK USING TWO QUEUES (LC 225)
// ═══════════════════════════════════════════════════════════════

class MyStack {
    queue<int> q1, q2;

public:
    void push(int x) {
        q2.push(x);
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);  // q1 always has elements in stack order
    }

    int pop() {
        int val = q1.front();
        q1.pop();
        return val;
    }

    int top() { return q1.front(); }
    bool empty() { return q1.empty(); }
};

// Single queue approach
class MyStackSingleQ {
    queue<int> q;

public:
    void push(int x) {
        int sz = q.size();
        q.push(x);
        // Rotate all previous elements to after x
        for (int i = 0; i < sz; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() { int v = q.front(); q.pop(); return v; }
    int top() { return q.front(); }
    bool empty() { return q.empty(); }
};

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  QUEUE USING STACKS + STACK USING QUEUES                 ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Queue using stacks
    cout << "═══ QUEUE USING TWO STACKS (LC 232) ═══\n";
    MyQueue q;
    q.push(1); q.push(2); q.push(3);
    cout << "  Push 1,2,3\n";
    cout << "  Peek: " << q.peek() << "\n";        // 1
    cout << "  Pop: " << q.pop() << "\n";           // 1
    cout << "  Pop: " << q.pop() << "\n";           // 2
    q.push(4);
    cout << "  Push 4, Pop: " << q.pop() << "\n";   // 3
    cout << "  Pop: " << q.pop() << "\n\n";          // 4

    // Stack using queues
    cout << "═══ STACK USING TWO QUEUES (LC 225) ═══\n";
    MyStack s;
    s.push(1); s.push(2); s.push(3);
    cout << "  Push 1,2,3\n";
    cout << "  Top: " << s.top() << "\n";           // 3
    cout << "  Pop: " << s.pop() << "\n";           // 3
    cout << "  Pop: " << s.pop() << "\n";           // 2
    cout << "  Pop: " << s.pop() << "\n\n";          // 1

    // Single queue stack
    cout << "═══ STACK USING SINGLE QUEUE ═══\n";
    MyStackSingleQ s2;
    s2.push(10); s2.push(20); s2.push(30);
    cout << "  Push 10,20,30\n";
    cout << "  Pop: " << s2.pop() << "\n";  // 30
    cout << "  Pop: " << s2.pop() << "\n";  // 20

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LC 232, LC 225\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

