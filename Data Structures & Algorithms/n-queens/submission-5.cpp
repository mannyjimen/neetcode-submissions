class Solution {
public:
    void placeQueen(vector<string>& board, int row, vector<bool>& seen_cols, vector<bool>& seen_pos_diags, vector<bool>& seen_neg_diags, vector<vector<string>>& solutions) {
        if (row == board.size()) {
            solutions.push_back(board);
            return;
        }

        for (int col = 0; col < board.size(); col++) {
            if (seen_cols[col] || seen_pos_diags[row - col + board.size()] || seen_neg_diags[row + col]) {
                continue;
            }

            seen_cols[col] = true;
            seen_pos_diags[row - col + board.size()] = true;
            seen_neg_diags[row + col] = true;
            board[row][col] = 'Q';

            placeQueen(board, row + 1, seen_cols, seen_pos_diags, seen_neg_diags, solutions);

            seen_cols[col] = false;
            seen_pos_diags[row - col + board.size()] = false;
            seen_neg_diags[row + col] = false;
            board[row][col] = '.';
        }
    }

    vector<string> initBoard(int n) {
        string row = "";

        for (int i = 0; i < n; i++) row += '.';

        vector<string> board(n, row);

        return board;
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> solutions;
        vector<string> board = initBoard(n);

        vector<bool> seen_cols(n, false);
        vector<bool> seen_pos_diags(n * 2, false);
        vector<bool> seen_neg_diags(n * 2, false); //offset for diff = +n


        placeQueen(board, 0, seen_cols, seen_pos_diags, seen_neg_diags, solutions);
    
        return solutions;
    }
};
