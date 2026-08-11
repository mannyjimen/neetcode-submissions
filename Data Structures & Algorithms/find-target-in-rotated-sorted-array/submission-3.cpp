/*

given an array of originally sorted numbers that have been rotated a number of times.

Find target, in O(logn) time (where n = numer of elements in arr).

first of all, what if we just look for the smallest number in the arry?
O(n), too long, can just use this for searching target itself.

Is there any way we CAN find the largest or smallest number in a faster than O(n) way?

[3,4,5,6,1,2]

is there a way we can do a binary search alternative to find
the smallest element in the array?

lets say we have our left and right bounds initally at the start and end of the array

[3,4,5,6,1,2]
 l    m    r

[6, 1, 2, 3, 4, 5]
 l.       m      r

[1, 2, 3, 4, 5]
 l.    m     r

if our middle is less than left and right,
we know our search space has to be now 1 after left, and middle itself.

if our middle element is greater than both element at left and element at right, our search space is now 1 after mid, and right.

if middle element is greater than one of the two, but less than the other, we want to go towards the smaller element.
remember, ANYTHIGN outside bounds is incorrect.

if our smaller element is on the left, we can just return the left element (its the smallest it can be, anything to the left of left pointer is elimnated from search space).

if our smaller element is on the right, our new search space is
[mid + 1][right].

----
try to make this more simple, looks like the conditionals are for EVERY
possible case, when I feel like there are more simple cases that can be used (which will reduce AMOUNT of conditionals). 

firstly, i am seeing that, if element at LEFT is less than right, our left element is the smallest. This is because if there ARE any elements less than left, they would wrap around (if at beginning of array) or be to the left of LEFT, which is already eliminated.
return left

other case, middle and right are smallest.
now, we need to see the relationship between these two.
if middle is smallest, want to eliminate search space from the right.
New search space is [left + 1, middle].
if right is smallest, want to eliminate search space from the left.
New search space is [middle + 1, right].

the search ends when left > right (but this will never happen.)

if left == right, we just return left.

Ok, i think I have the algorithm to find the smallest element in the array.

This is done in O(logn).

Now, the actual binary search from the first element.
Well, because the first index is sort of an offset for the binary search.

We can still use regular left = 0, right = end of array bounds, as well as mid = (size of search space)/ 2 + left,
HOWEVER, when actually indexing into the search space (array), we need to convert our virtual index, into the absolute index, which just means adding the offset, and then finding the remainder.
absolute = (virtual + offset) % size of array.


offset = findStartIndex(nums, n) {
    l = 0, r = n - 1
    
    while (true) {
        mid = (r - l) / 2 + l

        if num at left is < right
            return left
        if mid < right
            left = left + 1
            right = mid
        if right < mid
            left = mid + 1
    }
}

while (l <= r)
    mid = (r - l) / 2 + l
    
    do conditionals, except
    use:
    abs_mid = convToAbs(n, offset)
    abs_left = convToAbs(n, offset)
    abs_right = convToAbs(n, offset)

    ... regular binary search condiationls

*/

class Solution {
public:
/*
nums=[3,4,5,6,1,2]
target=1

left = 0, right = 5, n = 6

nums[0]=3 < nums[5]=2 ? no
mid = (5-0)/2 + 0 = 2
nums[2]=5 < nums[5]=2? no
nums[5]=2 < nums[2]=5? yes
    left = 2 + 1 = 3

left = 3, right = 5
nums[3]=6 < nums[5]=2 ? no
mid =((5 - 3) / 2) + 3 = 4;

nums[4]=1 < nums[5]=2 ? yes
    left = 3 + 1 = 4
    right = 4

left = 4, right = 4
nums[4] = 1 <= nums[4] = 1? yes
    return left (4).
*/
    int findSmallestElementIndex(const vector<int>& nums, int n) {
        int left = 0, right = n - 1;


      //[3,4,5,6,1,2]
      /*

        left = 0, right = 5
        mid = ((5 - 0) / 2) + 0 = 2

        nums[left]=3 < nums[mid] = 5? yes,
        left = 2 + 1 = 3

        left = 3, right = 5
        mid = (5 - 3) / 2  + 3 = 4
        
        nums[left]= 6 < nums[mid]=1? no
        left = 3 + 1 = 4
----
[4,5,6,7,0,1,2]

left = 0, right = 6
mid = ((6 - 0)/2) + 0 = 3
if nums[left(0)=4]<nums[mid(3) = 7] yes,
    left = 3 + 1 = 4

left = 4, right = 6
mid = ((6 - 4)/2) + 4 = 5
if nums[left(4)]=0 < nums[mid(5)]=1, yes


      */

        while (left < right) {
            if (nums[left] < nums[right]) return left;

            int mid = ((right - left) / 2) + left;
            
            if (nums[left] < nums[mid]) {
                left = mid + 1;
            } else {
                left = left + 1;
                right = mid;
            }
        }

        return left;
    }

    int findTargetOfRotatedArr(const vector<int>& nums, int n, int offset, int target) {
        int left = 0, right = n - 1;

        while (left <= right) {
            int mid = ((right - left) / 2) + left;
            int abs_mid = (mid + offset) % n;

            if (nums[abs_mid] == target) {
                return abs_mid;
            } else if (nums[abs_mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    } 

    // int findIndexUsingHalves(const vector<int>& nums, int target, int n) {
    //     int left = 0, right = n - 1;

    //     while (left <= right) {
    //         int mid = ((right - left) / 2) + left;

    //         if (nums[mid] == target) {
    //             return mid;
    //         }

    //         if (nums[left] <= nums[mid]) {
    //             if (nums[left] <= target && nums[mid] >= target) {
    //                 right = mid - 1;
    //             } else {
    //                 left = mid + 1;
    //             }

    //         } else {
    //             if (nums[mid] <= target && nums[right] >= target) {
    //                 left = mid + 1;
    //             } else {
    //                 right = mid - 1;
    //             }
    //         }
    //     }

    //     return -1;
    // }

    int search(vector<int>& nums, int target) {
        int n = nums.size();

        int offset = findSmallestElementIndex(nums, n);

        cout << offset << "\n";

        return findTargetOfRotatedArr(nums, n, offset, target);
    }

/*

when splitting a rotated sorted array in half,
at least one of the halves is completely sorted

how do we figure out which one contains our "target"?
of the two halves, the half that is completely sorted,

we can check whether target exists in between (inclusive) the start and end of this half.
if it doesn't, we only consider the other half.

how do we actually figure out which half is completely sorted?
the first element in the half will be less than the last element in the half.

keep shrinking until we either find the element (maybe something like if left ever lands on the element).


*/
};
