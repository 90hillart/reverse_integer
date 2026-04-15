#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

// Reverse a linked list segment
ListNode* reverse(ListNode* head, ListNode* tail) {
    ListNode* prev = NULL;
    ListNode* curr = head;

    while (curr != tail) {
        ListNode* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    return prev;
}

ListNode* reverseKGroup(ListNode* head, int k) {
    if (!head || k == 1) return head;

    ListNode dummy(0);
    dummy.next = head;

    ListNode* groupPrev = &dummy;

    while (true) {
        ListNode* kth = groupPrev;

        // Find the k-th node
        for (int i = 0; i < k && kth; i++) {
            kth = kth->next;
        }

        if (!kth) break; // not enough nodes

        ListNode* groupNext = kth->next;

        // Reverse group
        ListNode* prev = groupPrev->next;
        ListNode* curr = prev->next;

        for (int i = 1; i < k; i++) {
            ListNode* temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }

        ListNode* first = groupPrev->next;
        groupPrev->next = kth;
        first->next = groupNext;

        groupPrev = first;
    }

    return dummy.next;
}

// Helper functions
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

ListNode* insertEnd(ListNode* head, int val) {
    ListNode* newNode = new ListNode(val);
    if (!head) return newNode;

    ListNode* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    return head;
}

// Driver code
int main() {
    ListNode* head = NULL;

    // Example list: 1->2->3->4->5->6
    for (int i = 1; i <= 6; i++) {
        head = insertEnd(head, i);
    }

    int k = 3;

    cout << "Original List: ";
    printList(head);

    head = reverseKGroup(head, k);

    cout << "Reversed in groups of " << k << ": ";
    printList(head);

    return 0;
}