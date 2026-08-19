/*

reclarify the question:

board = [
  ["A","B","C","D"],
  ["S","A","A","T"],
  ["A","C","A","E"]
],

word = "CAT"

----

use every letter in the board as a starting point, and then try to look for the next letter in the word in one of the adjacent cells.
continue until the entire word has been formed, or every cell has been used as a starting point, with no success.

"CAT"
    i

  ["A","B","xC","D"],
  ["S","A","xA","xT"],
  ["A","C","A","E"]

return true

complexity:
n*m grid, k chars in word 

time complexity:
O(nm * (3 ^ nm)) ? check later.
O(3^(nm))

space complexity:
O(k)

-----

processChar
    check if character matches
    increment counters if does
    if not, return false

    if processChar( all adjacent in bounds characters, excluding past coords)
        return true

    return false
----

after initial implementation, i didn't realize one very important note.
i am only implementing the check on whether i JUST came from the cell, but not whether it was used in my path at all.



*/

class Solution {
public:
    bool isValidCoords(int new_i, int new_j, const vector<vector<char>>& board) {
        int n = board.size(); int m = board[0].size();

        if (new_i >= n || new_i < 0) {
            return false;
        }

        if (new_j >= m || new_j < 0) {
            return false;
        }

        if (board[new_i][new_j] == '0') {
            return false;
        }

        return true;
    }

    bool processChar(vector<vector<char>>& board, const string& word, int word_pos, int curr_i, int curr_j) {
        if (word[word_pos] != board[curr_i][curr_j]) {
            return false;
        }

        char original = board[curr_i][curr_j];
        board[curr_i][curr_j] = '0';

        if (word_pos == word.size() - 1) {
            return true;
        }

        vector<int> mods{0, 1, 0, -1, 0};

        for (int k = 0; k < 4; k++) {
            
            int new_i = curr_i + mods[k];
            int new_j = curr_j + mods[k + 1];
            
            if (isValidCoords(new_i, new_j, board)) {
                if (processChar(board, word, word_pos + 1, new_i, new_j)) {
                    return true;
                }
            }
        }

        //reverting state
        board[curr_i][curr_j] = original;        
        return false;
    }

/*

instead of passing around coordinates symbolizing the 'past' cell, we need a way to know a certain cell was used already in a path.

how about we just modify the cell itself to a "illegal" character right after using it, and we turn it back into its original character after we 
find no successful outcomes from using that cell.

*/

    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size(); int m = board[0].size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (processChar(board, word, 0, i, j)) {
                    return true;
                }
            }
        }

        return false;
    }
};
