/*
Author: Sarvan Yaduvanshi
Created : 2026-10-10 18:23:20
*/

/*
* Problem: Insertion before the value X in Linked List
* Given the head of a singly linked list and two integers X and val.
* Insert a node with value val before the node with value X in the linked list and return the head of the modified list.
*
* Example 1:
* Input: head = [1,2,3,4], X = 3, val = 5
* Output: 1->2->5->3->4
*
* Example 2:
* Input: head = [1,2,3,4], X = 1, val = 5
* Output: 5->1->2->3->4
*
* Example 3:
* Input: head = [1,2,3,4], X = 5, val = 6
* Output: 1->2->3->4 (X not found in the list, no insertion)
*
* Constraints:
* n == number of nodes in the Linked List
* 1 <= n <= 1000
* 0 <= ListNode.val <= 100
* 0 <= X <= 100
* 0 <= val <= 100
* Number of nodes with value X is 0 or 1
*/

#include <iostream>
using namespace std;

class myLinkedList{
private:
    struct ListNode{
        int val;
        ListNode* next;
        explicit ListNode(int x) : val(x), next(nullptr) {}
    };

    ListNode* head;

public:
    myLinkedList() : head(nullptr) {}

    static ListNode* insertBeforeX(ListNode* &head, int X, int val){
        if (head == nullptr)
            return nullptr;

        // Case 1: Insert before head
        if (head->val == X){
            ListNode* newNode = new ListNode(val);
            newNode->next = head;
            head = newNode;
            return head;
        }

        // Case 2: Insert before any other node
        ListNode* curr = head;
        while (curr->next != nullptr){
            // Case 1: Found the node with value X
            if (curr->next->val == X){
                // Create a new node with value val
                ListNode* newNode = new ListNode(val);
                newNode->next = curr->next; // link new node to curr next
                curr->next = newNode; // link curr to new node
                return head; // return head after insertion

            } else{ // Case 2: Move to next node
                curr = curr->next;
            }
        }

        return head; // X not found, return head without insertion
    }

    // Function to print the linked list
    void printList() const{
        ListNode* curr = head;
        while (curr != nullptr){
            cout << curr->val << " -> ";
            curr = curr->next;
        }
        cout << "nullptr" << endl;
    }

    // Function to build linked list from an array
    ListNode* buildList(const int arr[], const int n){
        if (n <= 0)
            return nullptr;

        head = new ListNode(arr[0]);
        ListNode* curr = head;
        for (int i = 1; i < n; ++i){
            curr->next = new ListNode(arr[i]);
            curr = curr->next;
        }
        return head;
    }
};

constexpr int MAX_NODES = 1000;
static int arr[MAX_NODES];
static void solve() {
    int n, X, val;
    cout << "Enter the number of nodes in the linked list: ";
    cin >> n;
    cout << "Enter " << n << " values for the linked list: ";
    for (int i = 0; i < n; ++i){
        cin >> arr[i];
    }

    cout << "Enter the value X to insert before: ";
    cin >> X;
    cout << "Enter the value val to insert: ";
    cin >> val;

    auto ll = myLinkedList();
    auto head = ll.buildList(arr, n);

    cout << "Original linked list: ";
    ll.printList();

    head = myLinkedList::insertBeforeX(head, X, val);
    cout << "Modified linked list after inserting " << val << " before " << X << ": ";
    ll.printList();
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}

