/* ok, output limit exceeded.
for one, mark diagonals takes so much time to do.
O(n) for every queen placed, and another for cleanup.  

there has got to be a way, like for rows and cols, that i can instantly store the diagonal positions that are unusable.

"Q.."
"..."
"..."

can i use a hashmap? 

---
the trick 

if we take a look at 2 diagonal positions on a graph,

"..."
".x."
"z.y"

the coordinates for x are 1,1, y are 2,2, and z are 0, 2.

for all coordinates that go diagonally to the left->bottom, the sum of the two coordinate values are equal.
therefore, when placing a queen, we can calculate the sum of coordinates, store it, and when placing a future queen, checking if the sum of the candidate queen's coordinates already exist within our "diagonal" sum set, if they do, queen cannot be placed in that position.

what about right->bottom diagonals?

ill write a couple of pairs of right->bottom diagonal coordinates

[1, 3], [2, 4], [3, 5], [4, 6]
ok, so both values of the coordinates increment by 1.
what about their sums?
4 - 6 - 8 - 10
ok, this can definitely tell us something.
the sum of every next diagonal coordinate goes up by 2
therefore, if the sum of the queen's coordinates are equal to a past queens coordinate sum + (the amount of rows we have gone down since * 2), then we cannot place the queen there.

still, if we were to use this, we would need to go through every queen sum (in diagonal sums set) and check this condition, this is still O(n) for a diagonal check.

what if we map the sum of the coordinates to ....

trick:
subtracting
lets take a look at these coordinates again:
[1, 3], [2, 4], [3, 5], [4, 6]
i will subtract every row - column
-2, -2, -2, -2
ok, so if a queen candidate's position subtracts (row - col) to a difference existing in.. lets call it diagonal differences.. then we cannot place it there.
every time we place a queen, we have to put its row-col difference in this set too.

ok, makes sense.

check a position for a queen placement,
if row is already in seen_rows
if col is already in seen_cols
if row + col is already in seen_diag_sums,
if row - col is already in seen_diag_diff,

if either of these are true, the position is not suitable for placement of a new queen.

else
we update these 4 sets,
place the queen

if row is tha last row, add current board to solutions,
else
check next n for new queen placements in the next row

remove from 4 sets the current positions corresponding values,
remove the queen

time complexity:
we are going to use every single position in the first row as a starting point, n positions.
for every position, we have n positions to check, but only n - 2 that are valid
so, n-2 valid calls are made to check the next row,
n-4 valid calls to check the next...
n! total calls to check every single VALID possible queen placement
the invalid ones return instantly (if conditions fail due to state of sets)

each valid board must also be copied to the solutions vector,
each copy is n^2,

can't come up with the logic surrounding how many boards can actually be valid from a given n.
i would say n, but don't know.

dont want to just say (n^2 * n!), even though this is definitely an upper bound (every call cannot copy a board, unless its a board of size 1 i guess?, so maybe this is valid?)

space complexity:
dependant on call stack, and size of sets.

for both, the worst case is n calls, and n elements in sets.
therefore, O(n) space complexity
if we count the return vector

dont know.

n^2 * n! + n

---
i can see now that, i don't have to keep a "seen_rows" set, as each call to place queen uses the next row, which implicitly proves that a previous row will never be used.
*/

class Solution {
public:
    vector<string> initializeBoard(int n) {
        vector<string> board;
        string temp = "";
        for (int i = 0; i < n; i++) {
            temp += '.';
        }

        for (int i = 0; i < n; i++) {
            board.push_back(temp);
        }

        return board;
    }

    bool canPlaceQueen(int row, int col, const unordered_set<int>& seen_cols, const unordered_set<int>& seen_diag_sums, const unordered_set<int>& seen_diag_diffs) {
        return !seen_cols.count(col) && !seen_diag_sums.count(row + col) && !seen_diag_diffs.count(row - col);
    }

    void placeQueen(vector<string>& board, int row, int col, unordered_set<int>& seen_cols, unordered_set<int>& seen_diag_sums, unordered_set<int>& seen_diag_diffs, vector<vector<string>>& solutions) {
        if (!canPlaceQueen(row, col, seen_cols, seen_diag_sums, seen_diag_diffs)) {
            return;
        }

        board[row][col] = 'Q';
        seen_cols.insert(col);
        seen_diag_sums.insert(row + col);
        seen_diag_diffs.insert(row - col);

        if (row == board.size() - 1) {
            solutions.push_back(board);
        } else {
            for (int i = 0; i < board.size(); i++) {
                placeQueen(board, row + 1, i, seen_cols, seen_diag_sums, seen_diag_diffs, solutions);
            }
        }

        board[row][col] = '.';
        seen_cols.erase(col);
        seen_diag_sums.erase(row + col);
        seen_diag_diffs.erase(row - col);

        return;
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> solutions;
        vector<string> board = initializeBoard(n);

        unordered_set<int> seen_cols;
        unordered_set<int> seen_diag_sums;
        unordered_set<int> seen_diag_diffs;

        for (int i = 0; i < n; i++) {
            placeQueen(board, 0, i, seen_cols, seen_diag_sums, seen_diag_diffs, solutions);
        }

        return solutions;
    }
};
