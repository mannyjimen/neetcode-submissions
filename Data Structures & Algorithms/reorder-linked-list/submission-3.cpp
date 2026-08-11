/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };

            //i just want to cement the odd vs even cases
        //odd
        //[0, 1]
        // s  f
        //issue, even number of nodes makes slow end 1 ahead of what i wanted
        //odd number makes slow end correctly
        //way to fix, set fast = head->next, so that our slow can reach the node right before the first node of the 2nd half.

 */


class Solution {
public:
    ListNode* splitLinkedList(ListNode* head) {
        ListNode* fast = head->next;
        ListNode* slow = head;

        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }

        ListNode* second_half = slow->next;
        slow->next = nullptr;

        return second_half;
    }

    ListNode* reverseLinkedList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* ahead;
        
        while (curr != nullptr) {
            ahead = curr->next;

            curr->next = prev;
            prev = curr;
            curr = ahead;
        }

        return prev;
    }

    //[1, 2, 3]
    // h1
    //
    //[4, 5, 6]
    /* h2


    */

    void mergeLinkedList(ListNode* head1, ListNode* head2) {
        while (head1 != nullptr && head2 != nullptr) {
            ListNode* next1 = head1->next;
            ListNode* next2 = head2->next;

            head1->next = head2;
            head2->next = next1;

            head1 = next1;
            head2 = next2;
        }
    }

    void reorderList(ListNode* head) {
        if (head->next == nullptr) return;

        ListNode* head2 = splitLinkedList(head);
        head2 = reverseLinkedList(head2);
        mergeLinkedList(head, head2);
    }
};










