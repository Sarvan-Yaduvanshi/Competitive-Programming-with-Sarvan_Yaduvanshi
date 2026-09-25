/*
Author: Sarvan Yaduvanshi
Created : 2026-09-23 23:38:00
*/

#include <iostream>
using namespace std;

/*
                <------------------------------------------------------>
                        SECTION 1: BUILDING A LIST FROM ARRAY
                <------------------------------------------------------>
  Problem: Given an array of integers, build a singly linked list where each node contains one integer from the array.
  Example: Input: arr = [5, 10, 15, 20], Output: Linked List: 5->10->15->20->NULL

  DRY RUN — Building list from array [5, 10, 15, 20]:

  Step 1: head = new Node(5)
          head ──▶ [5 | NULL]
          tail = head

  Step 2: tail->next = new Node(10), tail = tail->next
          head ──▶ [5 | ──]──▶ [10 | NULL]
                                  ↑ tail

  Step 3: tail->next = new Node(15), tail = tail->next
          head ──▶ [5 | ──]──▶ [10 | ──]──▶ [15 | NULL]
                                               ↑ tail

  Step 4: tail->next = new Node(20), tail = tail->next
          head ──▶ [5 | ──]──▶ [10 | ──]──▶ [15 | ──]──▶ [20 | NULL]
                                                            ↑ tail

  Time: O(n)  Space: O(n) for n nodes
*/
struct Node{
    int data;
    Node* next;

    // Constructor initializes node(value) and sets next to nullptr
    Node(int val) : data(val), next(nullptr) {}
};

/*
    Build Linked List from Array
    Approach:
        - First element becomes head.
        - Maintain tail to append each new node in O(1).
        - Return head as the entry point of the list.
    Time  : O(n)
    Space : O(n)
*/
static Node* buildList(const int arr[], const int n){
    // Edge case: If the array is empty, return nullptr
    if (n == 0)
        return nullptr;

    // Step 1: Create new nodes with first value
    Node* head = new Node(arr[0]);
    // Step 2: // First node is both head and tail
    Node* tail = head;

    // Step 3: Append remaining elements using tail
    for (int i = 1; i < n; i++){
        tail->next = new Node(arr[i]);
        tail = tail->next;
    }

    // Step 4: return head of the linked list
    return head;
}

// Traverse and print the linked list
// Time Complexity: O(n), Space Complexity: O(1)
static void printList(const Node* head){
    // Used a temporary pointer to traverse the list without modifying head
    const Node* temp = head;

    // Traverse the list and print each node's data
    while (temp != nullptr){
        cout << temp->data;
        if (temp->next != nullptr)
            cout << "->";

        // Move to the next node
        temp = temp->next;
    }
    cout << "->NULL\n";
}

/*
    Delete the complete linked list.
        Important:
            We pass head by reference because the caller's head
            must also become nullptr after deletion.
    Time  : O(n)
    Space : O(1)
*/
static void deleteList(Node*& head){
    while (head != nullptr){
        Node* temp = head->next; // Store the current head
        delete head;              // Delete the current head
        head = temp;              // Move head to the next node
    }
}

constexpr int MAX_SIZE = 1e5; // Maximum size of the array
static int arr[MAX_SIZE];          // Array to hold input values
void solve() {
    int n; cin >> n;

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "Array print : ";
    cout << "[";
    for (int i = 0; i < n; i++)
        cout << arr[i] << (i == n - 1? "" : ", ");
    cout << "]\n";

    Node* head = buildList(arr, n);
    cout << "Linked List print : ";
    printList(head);

    // Clean up memory to avoid leaks
    deleteList(head);
}

int main() {
    solve();
    return 0;
}

