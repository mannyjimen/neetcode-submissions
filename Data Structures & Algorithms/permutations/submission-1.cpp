/*

nums = [1,2,3]

Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

a permutation is an ordering of all the elements, every element is in the permutation.

clarifying...

for every number in a certain position, we want to use this number for every position in an array of the same size as nums.

[1,2,3]

[x, x, x]
---
[1, choose all possible permutations of the rest of the numbers]
[1, 2, ....]

for each number in nums, we use it in the first position, and then process the rest of the array (figuring out all perms) with the remaining numbers, 
in n -1 possible spots.

in each call for the next permutation array, we have n-1 spots, and n-1 numbers, and choose 1 of the n-1 numbers to go into the next spot, and so on...


current position = 0

for every number in nums
    use it in current position
    process rest of permutations
    pass in current permutation, and current position += 1.     

for the next call, every number except the one in the current position will be considered when figuring out a new permutation for the remaining spots in the array.

time complexity:
n = len(nums)

n choices * n-1 choices * n-2 choices

n^n time complexity

space complexity:
total amount of permutations = n * n-1 * n-2 ...also equal to n^n

O(n^n) space complexity,
O(n) space complexity if we only count EXTRA storage.

---

dry run:

nums        [1, 2, 3]
perms       {[1, 2, 3], [1, 3, 2], [2, 1, 3]}
curr_perm   {2, 1, 3}
position    3
used_pos    [false, true, false]

*/

class Solution {
public:
    void nextPermutationPosition(vector<vector<int>>& permutations, vector<int>& current_permutation, const vector<int>& nums, vector<bool>& used_positions, int current_position) {
        if (current_position == nums.size()) {
            permutations.push_back(current_permutation);
        }

        for (int i = 0; i < nums.size(); i++) {
            if (used_positions[i] == true) {
                continue;
            }

            used_positions[i] = true;
            current_permutation[current_position] = nums[i];

            nextPermutationPosition(permutations, current_permutation, nums, used_positions, current_position + 1);

            used_positions[i] = false;
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> permutations;
        vector<int> current_permutation(nums.size(), 0);

        vector<bool> used_positions(nums.size(), false);

        nextPermutationPosition(permutations, current_permutation, nums, used_positions, 0);

        return permutations;
    }
};
