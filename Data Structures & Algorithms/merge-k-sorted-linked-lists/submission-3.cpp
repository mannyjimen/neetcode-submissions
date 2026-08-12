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

next approach,
mergesort on every linked list.

context on mergesort, we split up a single array of unordered elements (in half) until the lists are each of size 1, then we merge them in sorted order
combining the lists on every merge.

however, since we are not given an array of elements, we have an array of lists.
these lists, are to our convenience, already sorted.
which means we can just begin the merge sort from these lists themselves instead of having to split first.

thinking about how we can do this....
we should grab pairs of lists.
list 1 and list 2 are going to merge in sorted order.
list 3 and list 4,
list k-1 and list k.
each of these merges should return 1 list.
which means that on every merge of all lists, we get rid of half of the lists.
how long does take to merge an entire layer of lists? the number of elements in all of the lists combined.

therefore, O(nlogk) time complexity.

as for space complexity, we can reuse the space within `lists`, which is given to us, therefore O(1).

Now, let me think about how I actually want this to go.
It has been a year since I `saw` an implementation of divide and conquer mergesort.
I feel like I can do this though.
There is definitely recursion (i think). Actually, i think the recursion part comes from the "dividing" of the algorithm. Given the lists,
we, by default, can skip "dividing".

Now how do i implement the "conquering",
well, since I want to build a single list from two lists,
i can grab every pair of lists (in order), and merge them together.
this does not seem too hard.

however, once I receive the head node for the newly merged list, where should i store it so that it can be iterated through again once the layer of
merging is complete?

i think, since, in the first case, i am grabbing lists 1 and 2, and merging them, the space within lists[0] and lists[1] are free,
therefore, let me use lists[1] for this head node of the merged list, and maybe reserve lists[1] for the merged list that comes from
lists[2] and lists[3].

how can i do this? i can get the index for where the new merged list is supposed to go by dividing the index of the first list of the two that are being merged by 2.

list[0] and list[1] will merge into a list that goes into 0/2 = index 0.
list[2] and list[3] will merge into a list that goes into 2/2 = index 1.

what should i do with the original indices of the linked lists that i have already merged?
lets say i have initially

[list[0], list[1], list[2], list[3]], and these merge into listA and listB, and they go into the vector as:
[listA, listB, list[2], list[3]]. As we can see, list[2] and list[3] still hold on to their original pointers (albeit, there lists are different).
When I finished merging all lists in the first iteration, how do i stop the merge halfway through after the second iteration, and halfway through again
on the third?
One idea is setting the list[i] to nullptr once I have merged it into its larger list that goes into an earlier index,
and then on future iterations, when scanning to get lists to merge, if i hit a nullptr, i go on to the next merge layer iteration.
Another idea is to just resize the vector into the (past size / 2). However, this resize amount differs when looking at an odd number of initial lists.
5 lists should merge into 3, as the last list will not merge into anything, but should still exist.

i can honestly just do (pastsize/2) + (pastsize%2) to get the new size that i use for .resize().

this way, i dont have any conditionals checking if i am at a nullptr list, and the vector shrinks regularly.

now, thinking about my main loop that controls the entire management of lists that merge, the conditional can now keep merging until lists
only has a size of 1.

I think this will work.
Lets try to implement.

*/

class Solution {
public:
    ListNode* merge(ListNode* first, ListNode* second) {
        ListNode* start = new ListNode;
        ListNode* curr = start;

        while (first != nullptr && second != nullptr) {
            if (first->val < second->val) {
                curr->next = first;
                first = first->next;
            } else {
                curr->next = second;
                second = second->next;
            }

            curr = curr->next;
        }

        if (first == nullptr) {
            curr->next = second;
        } else {
            curr->next = first;
        }

        curr = start->next;
        start->next = nullptr;
        delete start;

        return curr;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) return nullptr;

        while (lists.size() > 1) {
            for (int i = 0; i < lists.size(); i += 2) {
                ListNode* first = lists[i];
                ListNode* second;
                
                if (i + 1 == lists.size()) {
                    second = nullptr;
                } else {
                    second = lists[i + 1];
                }

                ListNode* mergedList = merge(first, second);

                int new_index = i/2;
                lists[new_index] = mergedList;
            }

            int new_size = (lists.size() / 2) + (lists.size() % 2);
            lists.resize(new_size);
        }

        return lists[0];
    }
};
