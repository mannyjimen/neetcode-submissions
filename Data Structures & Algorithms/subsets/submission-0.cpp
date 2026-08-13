/*
no duplicate numebrs in nums,
can return subsets in any order.

brute force:
for every num (including no num (empty)), i either include it or don't include it.

[1,2,3]

first initial "num" is no num in the subset
[]
then, this gets added,
now is my choosing of the nums.
choose to include 1, check [1], choose to include [2], check [1, 2], choose to include [3] ? check, [1, 2, 3]

after including everything individually, i can add these three subsets
[1], [1,2], [1, 2, 3]
now because I have exhausted all my nums (including them all), i can only modify my choices from here and back.
so let me go back to the most recent choice i made which was include 3

choose to include 3? was yes, now no. [1, 2]. I can see I already added this specific subset. So maybe, instead of going back
and to 3 and comitting the choice, maybe its the time when i get to [2] that chooses or doesn't choose which future numbers to add to the subset.

so lets start from the beginning.
[] chooses 1? yes, now we are in a state of subset [1],
    [1] chooses [2]? yes, state = [1, 2]
        [2] chooses [3] ? yes, state = [1, 2, 3]
            [3] cannot choose anything
        [2] chooses [3  ? no, state [1, 2]
        [2] has no further choices
    [1] chooses [2]? no, state [1]
    [1] chooses [3]? yes, state [1, 3]
        [3] has no further choices
    [1] chooses [3]? no, state [1, 3]
    [1] has no further choices
[] chooses 1? no
[] chooses 2? yes, state = [2]
    [2] chooses [3] yes, state [2, 3]...

i am going to stop here.
From what I can see from this trace tree of decisions,
every time we CHOOSE a number ahead of us, we can add it to the subset, add add the subset to the group of all subsets.
Whenever we DONT CHOOSE a number ahead of us, we don't add anything to the subsets, as the state of the subset after not choosing is in a state
    that we already added to the subsets.

So, i guess we can picture this "decision" process as a tree

                []
      /          |    \
    [1]          [2]  [3]
    / \          |    
   [1,2][1,3]   [2,3]
    /
[1, 2, 3]

                  []
            /           \
           [1]             []
        /    \             /   \
    [1,2]       [1]      [2]    [] 
    /    \      / \     /  \    / \
[1,2,3] [1,2] [1,3][1][2,3][2] [3] []

the height of the longest branch is n, where there are n numbers in nums.
how about total nodes for the tree?
each parent has two children (except the leaves, which represent saying yes or no to the last number in nums)
which means that there can be n parents (nums[] -> nums[n-1])
and that means there are 2*n total nodes?

What is looks like is, we should add the subset once we get to the deepest call (no further choices to make).
now building the tree myself, i can see that the total number of nodes is 2 ^ n, where n is the size of nums.
This time complexity is proportional to the number of nodes, which is exponential based on n (not good).




struggling to picture how many calls we are actually doing.
Maybe i am picturing this wrong on the tree.
On the tree, it looks like the calls are not for YES and NO, it looks like YES for every individual possible next number.
(empty has 3 children, when if there was only two, yes for 1 or no for 1, would this make more sense?)

let me try to implement (even though it will most likely be way too long).

starting at empty subset [], choose or dont choose the next number in nums, then let the next number take it from here.
this is going to be recursive.

nextChoice(current_subset, nums, current_index, vector<>& all_subsets)
    if (current_index == nums.size - 1)
        add current subset to all subsets
        return

    //choose or dont choose

    //not choosing
    nextChoice(current_subset, nums, current_index + 1, all_subsets) 
    //choosing
    current_subset.append(nums[current_index])
    nextChoice(current_subset, nums, current_index + 1, all_subsets)

subsets(nums)
    initialize current_subset[]
    nextChoice(current_subset, nums, i, all_subsets)

questoin: there are 2^n / 2 total leaves right?
therefore height of tree is log(2^n/2)

*/
class Solution {
public:
    void nextChoice(vector<int>& current_subset, const vector<int>& nums, int current_index, vector<vector<int>>& all_subsets) {
        if (current_index == nums.size()) {
            all_subsets.push_back(current_subset);
            return;
        }

        nextChoice(current_subset, nums, current_index + 1, all_subsets);
        current_subset.push_back(nums[current_index]);
        nextChoice(current_subset, nums, current_index + 1, all_subsets);
        current_subset.pop_back();
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> all_subsets;
        vector<int> current_subset{};

        nextChoice(current_subset, nums, 0, all_subsets);

        return all_subsets;
    }
};








