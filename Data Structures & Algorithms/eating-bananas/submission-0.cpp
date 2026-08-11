/*

piles[] int array,
h, represents how many hours we have to finish all piles

k (what we return) is the minimum number of bananas per hour to finish all piles before h hours.

the main objective is really,

how can we maximize the number of HOURS to eat, as this will minimize k.
//crutch
what if we sort our piles
piles = [1,4,3,2]
piles = [1,2,3,4], h = 9

let me just introduce a brute force approach.
starting at k = 1, scan and see if we can eat all piles in <= h hours by
dividing piles[i]/k, but getting the ceiling number if theres a decimal.

if we run out of hours, increment the k by 1.
time complexity is O(j * n) where j is the most bananas in a single pile, n is amount of piles.

---
what I wouldnt say on an interview, but what I am saying to myself.
I KNOW this is a binary search question.
How can i manipulate/manage this piles array so that i can get rid of half of the array after every iteration.

well, with this sorted array 
piles = [1,2,3,4], h = 9
I KNOW that the right half will need at LEAST the amount of hours as the left half.
maybe knowing this, can we just eliminate the right half and focus on the left half?
Well, I do want to maximize my hours used, so maybe focusing on the smallest k to finish the right half
in h/2 hours is a possible approach to think about.

[3, 4], h = 9 / 2 = 4

with this, maybe we can just repeat the process,
left side is smaller than right, of course, therefore lets focus on minimum amount of bananas for the right side.

[4], h = 4 / 2 = 2
since we have 2 hours to finish 4 bananas, we can safely say that for each hours, we want to eat 2 bananas.
I guess a way to not just do this in a "oh this makes sense now that we have one pile", is to just
divide the number of bananas in this pile by remaining hours (2) and getting the ceiling. That is the minimum
number of bananas we need to eat per hour, given the alotted (remaining) hours, to finish the pile.

But something doesn't seem right about this.

what if our piles looked like:

[1, 2, 4, 5, 6, 10000], h = 9

then, we would get to our last pile (10000 bananas). Instead of doing the "cut in half, and check largest".
Since we are literally just looking at the largest element, we are dividing h by 2 log(n) times, therefore we can do
(h / 2) ^ log^n = remaining hours for largest pile.

in this case, (9 / 2) ^ log(6)

see, now this is where i am starting to "lose hope" as logging a number is not my "forte".

Well, why dont we just do what we were doing before.

larger half 1:
[5, 6, 10000], h = 9/2=4

larger half 2:
[6, 10000], h = 4/2 = 2

larger half 3:
[10000], h = 2/2=1, 1 hour to eat 10000

i dont know why, but this seems right. Does it?

Should I keep going with this approach (i feel like this is not right, but is leading to SOMETHING).
Let me try to look for another possible approach.

Maybe looking for the pile that has the closest number of bananas to the number of hours given?

What i said before about "the greater half of the sorted piles needs = or > hours than the lesser half".
This mathematically makes sense.
Can I use this somehow?
Should I figure out something about the left side?

Maybe this has something to do with figuring out a proportion for hours between the lesser and greater side.
Can we sum up the bananas in total of the left side, and sum up the amount of piles on the left side, and then get to a
minimum number of hours needed that we can then use for figuring out something with the right side?

[1, 2, 5, 7, 19, 20] h = 9
from this, BECAUSE the h can distribute into each pile only once,
is it right that we commit half of the hours to the lesser half
[1, 2, 5] h = 4
and then the other half to the greater half
[7, 19, 20] h = 4
I think this makes sense. If we end up committing, lets say 3 hours to the left side,
and 6 hours to the right, we can choose a k = 5, but this will go over the amount of hours.

We need to think about the greater bananas rather than the lesser one.
[7, 19, 20] h = 4
we take a look at the greater half (once again, doing this seems kind of pointless, there should be a way to just
use log(n), and then use it alongside the h in an equation to get the number of hours left for a single element (20)).

greater half, there are odd number of elements, don't know how to approach this.
Lets just be "pessimistic" and grab the right half but with the middle element inclusive.

[19, 20] h = 2
greater half is just 20
[20] h = 1,
seeing this, we HAVE to eat 20 bananas in one hour.

But is this optimal?
[1, 2, 5, 7, 19, 20]

No, I can choose myself a k = 10, and see that
we can eat all piles in 8 hours, under our upper bound of 9.

This approach is not logically correct.

What if we were optimistic when splitting the array into two,
[7, 19, 20] h = 4
    ->
[20] h = 2.
We would arrive at our k = 10 but is this just a coincidence?
In an actual interview, do I just go along with it being "right" and start coding???

Already, I can see that if the numbers were different

[18, 19, 20] h = 4, and we were optimistic

[20] h = 2, k = 10.
We CANNOT finish [18, 19, 20] in 4 hours with k = 10.

----

post gemini:
I saw two things.
Gemini pointed out my "brute force" approach.
Moving away from Binary search on an array to Binary search on an ANSWER.

From this, let me start thinking.

Given the array piles, every pile needs to be eaten before the "hours" runs out,
but we want to minimize the amount we eat per hour (our k).

If we set a test k value, how long does it take to check whether this k value satisfies our h hours.
Well, as I said before, we can divide each pile, piles[i], by k, and grab the ceiling of the quotient.
This number represents how many hours we need to finish the pile eating k bananas per hour.

We can do this for every piles[i], decrement from h the amount of hours we need for a single pile (or manage
a counter that increments and compare after processing piles), then it only takes O(n) where there are n piles to
scan through. (Should I even look at time complexity yet, or just go with the solution).

Ok, now that we have that out of the way, how do we get to the optimal k?
Well, firstly, is there a maximum number our k can be? Not in theory, but is there an upper bound that we know if our k = this upper bound,
we can definitely finish the piles in the alotted time?
Yes, once again from before, if the k = the amount of bananas in the largest pile, then we are sure we can finish all the piles in h hours.
(This is assuming that our h >= piles.length, but we can see this is true from the constraints).

So, we know our OPTIMAL k must be between 1 (because every pile has at least 1 banana, once again as seen from constraint), and our max k (largest
bananas pile in piles).
We can refer to this maximum k as largest_pile_number.

so, from 1 -> largest_pile_number, a number in between (inclusive) has to be optimal.
Well, what if we just try to take the number in the middle (an even ground!).

Lets use an example to see this clearly
piles:
[1,4,3,2]
h = 9

so our largest pile consists of 4 bananas.
therefore, a number between and including 1 - 4 is optimal.

grabbing our middle (first middle if even number of elements in search space)
2 is in the middle (first) of 1 and 4: ((4 - 1) / 2) + 1.

So, lets check if 2 as k satisfies h.
We can do this scanning piles, and performing the division -> quotient ceiling, and subtracting from a copy of h.
IF our h is - at the end of processing all of the piles with 2 - >= 0, we know our h is satisfied because we have left over hours.
IF our h is negative, the amount of hours alotted was surpassed, therefore the k is not valid.

[1, 4, 3, 2], h = 9 
hours needed per pile: 1, 2, 2, 1.   h = 9 - 6 hours used = 4 hours left from h.

As we can see here, 2 is a valid k for our h.
In the first, with our starting point at 1, ending point at 4, and middle point at 2, we know that the optimal solution,
BECAUSE 2 is valid, we know that anything after 2 is pointless to check, because 2 will always be more optimal than larger k's.
Now, what we dont know is if 2 is THE optimal solution.
However, because 2 can be seen as our new "upper bound", we can repeat what we just did with 1 -> 2.

The middle of 1 and 2 is 1 (first middle),
lets check if it satisfies the piles.

                        [1, 4, 3, 2], h = 9 
hours needed per pile:   1, 4, 3, 2.  h = 9 - 10 = -1.
Our h is -1.
THEREFORE, the middle value (1) is too small to be our k, we need a larger amount of bananas eaten per hour, which means we can move our
theoretical "lower bound" in front of this 1.

Now, our lower bound is 2, and our upper bound is ALSO 2.
This means that we have shrunk our search space to 1 number, and this number is the optimal k.

----

Time Complexity:

n piles.

O(n) to get largest_pile_number
Binary search using 1 -> largest_pile_number as the initial search space.
Therefore, the amount of iterations this binary search will need is
O(log(largest_pile_number)), lets use j as a variable for this.
O(log(j)).
However, for each iteration of the binary search, we check to see if our midpoint satisfies our h, 
and this, as stated before, involves scanning piles and decrementing from a copy of h on every pile.
In total, this operation takes O(n).

Therefore, our time complexity is O(log(j)*n) for the binary search.
In total, O(log(j)* n + n) which reduces to O(log(j)*n) total time complexity.

Space complexity:
O(1) (not including piles).

*/

class Solution {
public:
    int getLargestPile(const vector<int>& piles) {
        int max_pile_number = 0;
        for (int pile_number: piles) {
            max_pile_number = max(max_pile_number, pile_number);
        }

        return max_pile_number;
    }

    bool satisfiesPiles(const vector<int>& piles, int k, int h) {
        for (int pile_amount: piles) {
            //check google for how to grab ceiling from int division
            //going to review this after (dont know how this gives ceiling) just want to finish implementing
            int hours_needed = (pile_amount + k - 1) / k;
            h -= hours_needed;
        }

        return h >= 0;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int max_pile_number = getLargestPile(piles);
    
        int lower = 1, upper = max_pile_number;
        
        while (lower < upper) {
            int mid = ((upper - lower) / 2) + lower;

            if (satisfiesPiles(piles, mid, h)) {
                upper = mid;
            } else {
                lower = mid + 1;
            }
        }

        return lower;
    }
};








