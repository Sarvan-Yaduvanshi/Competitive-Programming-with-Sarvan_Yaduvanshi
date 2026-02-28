/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Happy Number (LC 202) + Middle/Reorder List (LC 876, 143, 19)
 *  Level   : Easy → Medium
 * ============================================================================
 *
 *  LC 202  — Happy Number  https://leetcode.com/problems/happy-number/
 *  LC 876  — Middle of LL  https://leetcode.com/problems/middle-of-the-linked-list/
 *  LC 19   — Remove Nth from End  https://leetcode.com/problems/remove-nth-node-from-end-of-list/
 *  LC 143  — Reorder List  https://leetcode.com/problems/reorder-list/
 *  LC 2095 — Delete Middle  https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
using namespace std;

// ============================================================================
// LC 202: Happy Number — Floyd's on digit-square sequence
// ============================================================================
int digitSquareSum(int n) {
    int sum = 0;
    while (n > 0) {
        int d = n % 10;
        sum += d * d;
        n /= 10;
    }
    return sum;
}

bool isHappy(int n) {
    int slow = n, fast = n;
    do {
        slow = digitSquareSum(slow);
        fast = digitSquareSum(digitSquareSum(fast));
    } while (slow != fast);
    return slow == 1;
}

// ============================================================================
// LC 876: Middle of Linked List
// ============================================================================
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* middleNode(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow; // For even length, returns second middle
}

// ============================================================================
// LC 19: Remove Nth Node From End — Two pointer with gap = N
// ============================================================================
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode *fast = &dummy, *slow = &dummy;

    // Move fast N+1 steps ahead
    for (int i = 0; i <= n; i++) fast = fast->next;

    // Move both until fast reaches end
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }

    // slow->next is the Nth from end
    ListNode* toDelete = slow->next;
    slow->next = slow->next->next;
    delete toDelete;

    return dummy.next;
}

int main() {
    cout << "Is 19 happy? " << isHappy(19) << "\n"; // 1
    cout << "Is 2 happy? " << isHappy(2) << "\n";   // 0

    // Middle
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    cout << "Middle: " << middleNode(head)->val << "\n"; // 3

    return 0;
}

