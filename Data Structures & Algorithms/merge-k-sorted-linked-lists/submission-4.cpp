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

optimized heap approach.

isntead of checking all k lists for the node that has the lowest value,
we can maintain a heap that contains the k current nodes for the lists.
This way, whenever we want to "figure out" the smallest valued node, 
we can do so in O(1) by checking top, and then we also have to pop it, and insert the next node
that comes in the list of the node we just popped.
This is O(logk), as we have to insert it into the heap.
if the next node is a nullptr, we don't add anything.

initializing the heap with the first k nodes = O(klogk)

creating the list
popping the heap top n times,
each pop results in O(logk), but then we have to insert the node ahead of the one we just popped,
which is also O(logk).

so in total, time complexity is O(nlogk).

I didnt bring up anything regarding creating the list (how we actually do this), but its going to end up being O(1) per new node
we have to add, as we just add the popped node to the front of the list, and then move our building node* to that node (the new front)
for future nodes.

initialize heap of ListNode*,
heap will be of type ListNode*, and we can write our custom comparator (or just make it so the heap is of pair<int, ListNode*>, and set
the int value to the value of the ListNode*), but, it seems more nicely packed if we just create a custom comparator.

create start node,
set curr = start

while heap is not empty
    set curr->next = top
    set new_node = top.next,
    heap.pop

    if new node is not nullptr
        add new node to heap

    curr = curr->next

return start->next (do memory cleanup if i want).

*/

class Solution {
public:
    struct ListNodeCompare {
        bool operator() (const ListNode* a, const ListNode* b) const {
            return a->val > b->val;
        }
    };

    priority_queue<ListNode*, vector<ListNode*>, ListNodeCompare> initializeHeap(const vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, ListNodeCompare> nodes;

        for (ListNode* node: lists) {
            nodes.push(node);
        }

        //might be able to do nodes.push_range(lists);
        return nodes;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, ListNodeCompare> nodes = initializeHeap(lists);

        ListNode* start = new ListNode;
        ListNode* curr = start;

        while (!nodes.empty()) {
            curr->next = nodes.top();
            ListNode* next_node = nodes.top()->next;

            nodes.pop();

            if (next_node != nullptr) {
                nodes.push(next_node);
            }

            curr = curr->next;
        }

        return start->next;
    }
};









