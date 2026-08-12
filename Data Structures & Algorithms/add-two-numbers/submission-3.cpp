/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

/*
321
654
---
975

----
brute force solution:
traverse each list, store the values of each node (numbers) into a string in the order of the linked list.
reverse both strings, and then convert to integers.
we can add both integers, convert this integer into string,
create a new list from this string.

time complexity:
where n number of nodes in the larger list
O(n) to traverse and store into string
O(n) to reverse each string
O(n) to create new list from string
total: O(n)

space complexity:
excluding the returned list:
we do use 2 strings to store the lists' node digits.
O(n).
store the sum into a string
O(n)
total: O(n)

----

better approach:
traverse each list in unison
add the digits of each lists current node
create a new node out of this sum.
if sum >= 10, we can remember to have to add 1 to the next sum of digits, and create a node using sum - 10 of the sum that was greater than 10.
if there are no further nodes, and we still have to add 1, we just create a new node regardless.

at the end, we can return our head node (assuming we store it before the addition traversal).

time complexity:
O(n)
space complexity, excluding the list we return:
two pointers for each lists traversal, one for the result linked list.
constant space
O(1).

l1, l2
overlflow = 0

head = new ListNode
s1 = head

while (l1 || l2)
    if l1 != nptr 
        l1num = l1.val
        l1 = l1->next
    else 
        l1num = 0
    if l2 != nptr
        l2num = l2.val
        l2 = l2->next
    else
        l2 num = 0

    sum = l1num + l2num + overflow
    overflow = 0

    if sum >= 10
        overflow = 1
        sum -= 10

    s1->next = new listnode(sum)
    s1 = s1->next

//should we remember head->next (as start maybe), disconnect head and delete? not sure.
return head->next
*/

class Solution {
public:
/*

[1,8], [0]
 l1     l2

 x
s1,h



*/

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int l1digit, l2digit;
        int overflow = 0;

        ListNode* head = new ListNode();
        ListNode* s1 = head;

        while ((l1 != nullptr || l2 != nullptr) || overflow > 0) {
            
            if (l1 != nullptr) {
                l1digit = l1->val;
                l1 = l1->next;
            } else {
                l1digit = 0;
            }

            if (l2 != nullptr) {
                l2digit = l2->val;
                l2 = l2->next;
            } else {
                l2digit = 0;
            }

            int sum = l1digit + l2digit + overflow;
            overflow = 0;

            if (sum >= 10) {
                overflow = 1;
                sum -= 10;
            }

            s1->next = new ListNode(sum);
            s1 = s1->next;
        }

        return head->next; 
    }
};
