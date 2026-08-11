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

[2,10,4,6,8]
    j x i 


[2,8,4,6]

we want to be able to grab the last node, and move it to front, then the second to last node, and move it up a little further from the front (+2).

brute force approach.
we can store every node into an array
use two pointers, one starting at each end of the array.
and set the first pointers node->next to the last pointers node.
increase the first pointer.
set the last pointers node to the first pointer
decrement last pointer
repeat UNTIL first pointer == last pointer.

storing every node involves scanning entire linked list, O(n) if there are n nodes.
doing the pointer manipulation is constant, O(1).

O(n) time complexity,
O(n) space complexity, because we do create an array for all the nodes.
----
improving space complexity?

knowing which node to modify the next value of is easy when we think of the nodes from left to right,
however, since we want to order the last node and its predecessors from left to right as well, grabbing them in this order
is not easy, because this is a singly linked list, and doesn't let us check which node we just came from.


[0, 1, 2, 3, 4, 5, 6]

can we use 1 pointer for this? no, we need to keep track of both ends.
what about two? no, with our second pointer, we cannot go backwards.
what about 3?
i can have one pointer at the current front of the list, one at the end, but where will the third one go?
Can we have it go one before the end, so that I know what the previous node is for the next iterations node modification? Sure, but then
what will we do for further iterations, we dont have ANOTHER node right behind it as well.

after looking at second hint from neetcode ("For example, consider the list [1, 2, 3, 4, 5]. To reorder the list, we connect the first and last nodes, then continue with the second and second-to-last nodes, and so on. Essentially, the list is split into two halves: the first half remains as is, and the second half is reversed and merged with the first half. For instance, [1, 2] will merge with the reversed [5, 4, 3]. Can you figure out a way to implement this reordering process? Maybe dividing the list into two halves could help.")

if we look at this "final" linked list a litte differently, it looks as if
we are splitting the linked list into two halves (first one being the larger if odd number of nodes),
and then merging them together. HOWEVER

this list
[0, 1, 2, 3, 4, 5, 6]
can turn into
[0, 1, 2, 3] [4, 5, 6]

merging them together would not give us our desired list, as we want our second half to go into the first, but in reverse order.
Therefore, we need to reverse the second half and then do the merge.

[0, 1, 2, 3] [6, 5, 4].
This looks right, then merging (starting at the first half), would look like
[0, 6, 1, 5, 2, 4, 3].
And this is our desired list.

So, there are three parts to this solution:
first, finding the halfway mark,
second, reversing the second half of the list
third, merging both lists together.

lets think about finding the halfway mark
well, we can just traverse through the list once, see how many times we hopped, and that will be the number of elements in the list.
Then, we can half this number (ceiling if odd number of hops).
Then, starting from the front, we hop this many times, and end up at the halfway mark.

Nice, now we have the first and second half of the list split into two (still connected, but we can disconnect if we want, not sure if needed).

Now, lets think about reversing a linked list.
For this, we need two pointers, one remaining at the previous node (we can call this prev), and one that is one ahead of the previous (we can call this curr), able to change its curr->next to prev.
However, after performing this assignment, we lose track of what came after curr since we just changed where curr->next pointed to. Therefore, we need one more pointer managing the node AFTER the one we currently are modifying (lets call this ahead).
Then, after the modification, we can set curr = ahead, and increment curr.
When curr = nullptr, that is when we can finally stop iterating/traversing, and return prev as the new head of the reverse linked list.

Now, merging.
Since we have two lists (their heads),
and we know the list we want to start merging with (has = or 1 more node than the other reversed list), we can simply
merge by
having two pointers on each list,
lets call the first lists curr and ahead, and the second lists, curr2 and ahead2 (i dont like these names).

[3] nptr
c   a
. nptr
  c2a2

[0 -> 6 -> 1 -> 5 -> 2 -> 4 -> 3]

set curr->next = curr2
set curr = ahead
increment ahead
set curr2->next = curr
set curr2 = ahead2
increment ahead2
repeat.

[0, 1, 2, 3, 4, 5, 6]
             c
halfway = 0


once curr2 becomes nullptr, we stop right there.
we can set 3->next to nullptr (if we havent done so from splitting, which we should most definitely do),
and then return our head
(we have to remember our first node from the first list)


time complexity:
halfway/splitting list:
scanning list twice, once to get number of elements, another time to the halfway mark.
O(2n) = O(n)
reversing the list
managing three pointers,
all three pointers move in unison until middle one finishes traversing the entire list (->next ressaignments are O(1))
O(3n) = O(n)
merging the list
managing two pointers per list (4 pointers total)
each pair of pointers move in unison with eachother until the first lists' (n/2 + 1 elements at most) nodes are done being traversed.
O(n)

therefore, O(n) overall time complexity.
space complexity: O(1), as we hold data in a constant number of node pointer variables.

[0, 1, 2]
          c  a 
[5, 4, 3]
       c2  a2

0->5->1->4->2->3

---
trace
[2,4,6,8,10]
head

splitLinkedList
length = 5
curr = head

[2->4->6->8->10]
                c

length = 5
halfway = ((5 + 2 - 1) / 2) = 3

curr = head
[2->4->6  8->10]
       t  c
halfway = 0
    
ret curr (correct)
*/

class Solution {
public:
    ListNode* splitLinkedList(ListNode* head) {
        int length = 0;
        ListNode* curr = head;
        while (curr != nullptr) {
            curr = curr->next;
            length++;
        }

        //ceiling
        int halfway = (length + 2 - 1) / 2;

        curr = head;
        while (halfway > 0) {

            if (halfway == 1) {
                ListNode* temp = curr;
                curr = curr->next;
                temp->next = nullptr;
            } else {
                curr = curr->next;
            }

            halfway--;
        }
        return curr;
    }


/*

reverseLinkedList
head2 = 8 [8 -> 10]

prev = nullptr
curr = 8
ahead;

[nptr<-8<-10]    
           p 
prev is returned, correct

[2->4->6->] [10->8->]

*/
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

/*

[2->4->6->] [10->8->]
 h           h2

[2->10->4->8->6->]  
              c   a   c2a2
*/

    void mergeLinkedList(ListNode* head, ListNode* head2) {
        
        ListNode* curr = head;
        ListNode* curr2 = head2;
        ListNode* ahead = curr->next;
        ListNode* ahead2 = curr2->next;

        while (curr != nullptr) {
            curr->next = curr2;

            curr = ahead;
            if (curr == nullptr) {
                break;
            }

            ahead = ahead->next;

            curr2->next = curr;
            curr2 = ahead2;
            if (curr2 == nullptr) {
                break;
            }

            ahead2 = ahead2->next;
        }
    }

    void reorderList(ListNode* head) {
        if (head->next == nullptr) return;

        ListNode* head2 = splitLinkedList(head);
        head2 = reverseLinkedList(head2);
        mergeLinkedList(head, head2);
    }
};










