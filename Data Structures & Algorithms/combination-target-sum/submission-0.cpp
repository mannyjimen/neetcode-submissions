/*

just to be clear of the question
we want to return all distinct combinations,
we can reuse the same number as many times as we want
distinct combinations have different frequencies of numbers.

nums = [2,5,6,9]
target = 9

[9], [2, 2, 5].

---
inner thoughts
use number, use it again, use it again, keep using until it goes over target,
if it goes over target, stop using the same number, and use the next number repeat the process.
---

we want all possible combinations (even those using the same number as many times needed).

choices

"using" a number means its added to our sum, and our current combination

for each number we either
use it, dont use it.

if we dont use it, we move on to making a choice for the next number
if we do use it, we have another two choices to make
use it, dont use it.

the only time we will get to the next number is if we don't choose the current number.

how do we know when we should stop using the current number?

process:

if the current sum > target, return and dont process any future numbers from this "branch" of choices
if the current sum becomes equal to target, we can remember the current combination.

if neither of these are true, then that means the current sum is less than target, and we can make choices on this current number we are processing.
use it
    add number to sum,
    add number to current combination array,
    recursively process the currnet number
dont use it
    subtract the number from sum,
    remove the number from the combination array (popback)
    recursively process the next number.

----
as we can see,
we stop processing a branch when the sum either becomes equal to target (which means we found a combination, any future additions to the combination will
surely make the sum > target), or when the sum > target (branch leads to non-correct combination).
---

time complexity:
since we can use the same number an infinite amount of times,
it almost feels like the time complexity is infinity (if the target is so large, and the number we reuse over and over again is so small).

we can't just think of each number in nums to be used or not used, because it CAN be reused, which means there aren't only 2 decisions coming from one number, there are many.

not sure at all how to go about this.

looking at the constraints, every num in nums is between and including 2 and 30,
the target as well.

knowing this, worst case is the number we reuse many times is 2, which means our longest branch of reusage will be 20, that is our space complexity (constant).
for time complexity, how many calls do we make?
if the array has 20 numbers, we can, at max, reuse one number (2) 15 times... 20 ^ (15 + 1) - 1 total nodes of decisions,
constant number of decisions. constant time complexity (only because of the constraints).

*/

class Solution {
public:
    void combinationChoice(vector<int>& current_combination, int current_sum, int target, int current_index, vector<vector<int>>& combinations, const vector<int>& nums) {
        if (current_index >= nums.size()) return;

        if (current_sum == target) {
            combinations.push_back(current_combination);
            return;
        } else if (current_sum > target) {
            return;
        }

        //choose current number
        current_combination.push_back(nums[current_index]);
        current_sum += nums[current_index];
        combinationChoice(current_combination, current_sum, target, current_index, combinations, nums);
        current_combination.pop_back();
        current_sum -= nums[current_index];


        combinationChoice(current_combination, current_sum, target, current_index + 1, combinations, nums);
    }

    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        vector<vector<int>> combinations;

        vector<int> current_combination = {};
        int current_sum = 0;

        combinationChoice(current_combination, current_sum, target, 0, combinations, nums);

        return combinations;
    }
};









