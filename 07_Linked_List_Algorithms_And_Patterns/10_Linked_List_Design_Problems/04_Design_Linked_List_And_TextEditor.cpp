/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           04 — DESIGN LINKED LIST (LeetCode 707)                           ║
║           From Zero to Grandmaster — OOP Design Interview Problem          ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Singly Linked List Design (LeetCode 707)
 2. Doubly Linked List Design (LeetCode 707 — Optimal)
 3. Design Text Editor using DLL

DESIGN LINKED LIST — LeetCode 707:
──────────────────────────────────
  Implement these operations:
  • get(index)           → O(n) — return element at index, or -1
  • addAtHead(val)       → O(1) — insert at beginning
  • addAtTail(val)       → O(n) SLL / O(1) DLL — insert at end
  • addAtIndex(index, val) → O(n) — insert before the index-th node
  • deleteAtIndex(index) → O(n) — delete the index-th node

DRY RUN:
  MyLinkedList obj;
  obj.addAtHead(1);       // [1]
  obj.addAtTail(3);       // [1, 3]
  obj.addAtIndex(1, 2);   // [1, 2, 3]  — insert 2 before index 1
  obj.get(1);             // returns 2
  obj.deleteAtIndex(1);   // [1, 3]
  obj.get(1);             // returns 3
*/

#include <iostream>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// 1. SINGLY LINKED LIST DESIGN — LeetCode 707
// ═══════════════════════════════════════════════════════════════

class MyLinkedListSLL {
    struct Node {
        int val;
        Node* next;
        Node(int v) : val(v), next(nullptr) {}
    };

    Node* head;
    int size;

public:
    MyLinkedListSLL() : head(nullptr), size(0) {}

    ~MyLinkedListSLL() {
        while (head) { Node* t = head; head = head->next; delete t; }
    }

    int get(int index) {
        if (index < 0 || index >= size) return -1;
        Node* curr = head;
        for (int i = 0; i < index; i++) curr = curr->next;
        return curr->val;
    }

    void addAtHead(int val) {
        Node* node = new Node(val);
        node->next = head;
        head = node;
        size++;
    }

    void addAtTail(int val) {
        Node* node = new Node(val);
        if (!head) { head = node; size++; return; }
        Node* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = node;
        size++;
    }

    void addAtIndex(int index, int val) {
        if (index < 0 || index > size) return;
        if (index == 0) { addAtHead(val); return; }

        Node* curr = head;
        for (int i = 0; i < index - 1; i++) curr = curr->next;
        Node* node = new Node(val);
        node->next = curr->next;
        curr->next = node;
        size++;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return;
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return;
        }
        Node* curr = head;
        for (int i = 0; i < index - 1; i++) curr = curr->next;
        Node* temp = curr->next;
        curr->next = temp->next;
        delete temp;
        size--;
    }

    void print() {
        Node* curr = head;
        while (curr) {
            cout << curr->val;
            if (curr->next) cout << " -> ";
            curr = curr->next;
        }
        cout << " -> NULL (size=" << size << ")\n";
    }
};

// ═══════════════════════════════════════════════════════════════
// 2. DOUBLY LINKED LIST DESIGN — Optimal with O(1) head/tail
// ═══════════════════════════════════════════════════════════════
/*
  Uses sentinel head and tail nodes to eliminate edge cases.

  sentinel_head ↔ [node1] ↔ [node2] ↔ ... ↔ sentinel_tail

  addAtHead: Insert after sentinel_head   → O(1)
  addAtTail: Insert before sentinel_tail  → O(1)
  get/add/delete at index:
    If index < size/2 → traverse from head (forward)
    If index >= size/2 → traverse from tail (backward)
    → Average O(n/2) instead of O(n)!
*/

class MyLinkedListDLL {
    struct DNode {
        int val;
        DNode* prev;
        DNode* next;
        DNode(int v) : val(v), prev(nullptr), next(nullptr) {}
    };

    DNode* sentHead;  // Dummy head
    DNode* sentTail;  // Dummy tail
    int size;

    // Helper: get node at index (optimized from both ends)
    DNode* getNode(int index) {
        DNode* curr;
        if (index < size / 2) {
            curr = sentHead->next;
            for (int i = 0; i < index; i++) curr = curr->next;
        } else {
            curr = sentTail->prev;
            for (int i = size - 1; i > index; i--) curr = curr->prev;
        }
        return curr;
    }

    void insertAfter(DNode* node, int val) {
        DNode* newNode = new DNode(val);
        newNode->next = node->next;
        newNode->prev = node;
        node->next->prev = newNode;
        node->next = newNode;
        size++;
    }

    void removeNode(DNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        size--;
    }

public:
    MyLinkedListDLL() : size(0) {
        sentHead = new DNode(0);
        sentTail = new DNode(0);
        sentHead->next = sentTail;
        sentTail->prev = sentHead;
    }

    ~MyLinkedListDLL() {
        DNode* curr = sentHead;
        while (curr) { DNode* t = curr; curr = curr->next; delete t; }
    }

    int get(int index) {
        if (index < 0 || index >= size) return -1;
        return getNode(index)->val;
    }

    void addAtHead(int val) { insertAfter(sentHead, val); }

    void addAtTail(int val) { insertAfter(sentTail->prev, val); }

    void addAtIndex(int index, int val) {
        if (index < 0 || index > size) return;
        if (index == 0) { addAtHead(val); return; }
        if (index == size) { addAtTail(val); return; }
        DNode* node = getNode(index);
        insertAfter(node->prev, val);
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return;
        removeNode(getNode(index));
    }

    void print() {
        DNode* curr = sentHead->next;
        while (curr != sentTail) {
            cout << curr->val;
            if (curr->next != sentTail) cout << " <-> ";
            curr = curr->next;
        }
        cout << " (size=" << size << ")\n";
    }
};

// ═══════════════════════════════════════════════════════════════
// 3. DESIGN TEXT EDITOR using DLL
// ═══════════════════════════════════════════════════════════════
/*
  Simple text editor with cursor:
  • addText(text)   — insert text at cursor position
  • deleteText(k)   — delete k chars left of cursor
  • cursorLeft(k)   — move cursor left k positions
  • cursorRight(k)  — move cursor right k positions

  Uses DLL of characters with cursor between two nodes.
*/

class TextEditor {
    struct CharNode {
        char ch;
        CharNode* prev;
        CharNode* next;
        CharNode(char c) : ch(c), prev(nullptr), next(nullptr) {}
    };

    CharNode* sentHead;
    CharNode* sentTail;
    CharNode* cursor;  // Cursor is AFTER this node

    void insertAfterCursor(char c) {
        CharNode* node = new CharNode(c);
        node->next = cursor->next;
        node->prev = cursor;
        cursor->next->prev = node;
        cursor->next = node;
        cursor = node;
    }

public:
    TextEditor() {
        sentHead = new CharNode('\0');
        sentTail = new CharNode('\0');
        sentHead->next = sentTail;
        sentTail->prev = sentHead;
        cursor = sentHead;
    }

    ~TextEditor() {
        CharNode* curr = sentHead;
        while (curr) { CharNode* t = curr; curr = curr->next; delete t; }
    }

    void addText(string text) {
        for (char c : text) insertAfterCursor(c);
    }

    int deleteText(int k) {
        int deleted = 0;
        while (k > 0 && cursor != sentHead) {
            CharNode* toDelete = cursor;
            cursor = cursor->prev;
            cursor->next = toDelete->next;
            toDelete->next->prev = cursor;
            delete toDelete;
            k--;
            deleted++;
        }
        return deleted;
    }

    string cursorLeft(int k) {
        while (k > 0 && cursor != sentHead) {
            cursor = cursor->prev;
            k--;
        }
        return getLeftContext();
    }

    string cursorRight(int k) {
        while (k > 0 && cursor->next != sentTail) {
            cursor = cursor->next;
            k--;
        }
        return getLeftContext();
    }

    string getLeftContext() {
        string result;
        CharNode* curr = cursor;
        int count = 10;
        while (count > 0 && curr != sentHead) {
            result = curr->ch + result;
            curr = curr->prev;
            count--;
        }
        return result;
    }

    string getText() {
        string result;
        CharNode* curr = sentHead->next;
        while (curr != sentTail) {
            result += curr->ch;
            curr = curr->next;
        }
        return result;
    }
};

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  DESIGN LINKED LIST & TEXT EDITOR                      ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // SLL Design
    cout << "═══ SINGLY LINKED LIST DESIGN (LC 707) ═══\n";
    MyLinkedListSLL sll;
    sll.addAtHead(1);
    sll.addAtTail(3);
    sll.addAtIndex(1, 2);
    cout << "After [addHead(1), addTail(3), addAt(1,2)]: "; sll.print();
    cout << "get(1) = " << sll.get(1) << "\n";
    sll.deleteAtIndex(1);
    cout << "After deleteAt(1): "; sll.print();
    cout << "get(1) = " << sll.get(1) << "\n";

    // DLL Design (optimal)
    cout << "\n═══ DOUBLY LINKED LIST DESIGN (Optimal) ═══\n";
    MyLinkedListDLL dll;
    dll.addAtHead(1);
    dll.addAtTail(3);
    dll.addAtIndex(1, 2);
    cout << "After [addHead(1), addTail(3), addAt(1,2)]: "; dll.print();
    cout << "get(1) = " << dll.get(1) << "\n";
    dll.deleteAtIndex(1);
    cout << "After deleteAt(1): "; dll.print();

    // Text Editor
    cout << "\n═══ TEXT EDITOR DESIGN ═══\n";
    TextEditor editor;
    editor.addText("leetcode");
    cout << "After addText('leetcode'): " << editor.getText() << "\n";
    cout << "deleteText(4) deleted: " << editor.deleteText(4) << " chars\n";
    cout << "Text: " << editor.getText() << "\n";
    editor.addText("practice");
    cout << "After addText('practice'): " << editor.getText() << "\n";
    cout << "cursorLeft(9): '" << editor.cursorLeft(9) << "'\n";
    editor.addText("happy");
    cout << "After addText('happy'): " << editor.getText() << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LeetCode 707, 2296 (Design Text Editor)\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

