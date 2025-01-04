#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int evaluate(const vector<vector<char>>& board) {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == 'X') return 10;
            if (board[row][0] == 'O') return -10;
        }
    }
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == 'X') return 10;
            if (board[0][col] == 'O') return -10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'X') return 10;
        if (board[0][0] == 'O') return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'X') return 10;
        if (board[0][2] == 'O') return -10;
    }
    return 0;
}

bool isMovesLeft(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == '_') return true;
        }
    }
    return false;
}

int alphaBeta(vector<vector<char>>& board, int depth, bool isMaximizingPlayer, int alpha, int beta) {
    int score = evaluate(board);
    if (score == 10 || score == -10) return score;
    if (!isMovesLeft(board)) return 0;
    if (isMaximizingPlayer) {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = 'X';
                    best = max(best, alphaBeta(board, depth + 1, false, alpha, beta));
                    board[i][j] = '_';
                    alpha = max(alpha, best);
                    if (beta <= alpha) break;
                }
            }
        }
        return best;
    }
    else {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = 'O';
                    best = min(best, alphaBeta(board, depth + 1, true, alpha, beta));
                    board[i][j] = '_';
                    beta = min(beta, best);
                    if (beta <= alpha) break;
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestValue = INT_MIN;
    pair<int, int> bestMove = {-1, -1};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = 'X';
                int moveValue = alphaBeta(board, 0, false, INT_MIN, INT_MAX);
                board[i][j] = '_';
                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }
    return bestMove;
}

int main() {
    vector<vector<char>> board = {
            {'X', 'O', 'X'},
            {'O', 'O', '_'},
            {'_', '_', '_'}
    };
    pair<int, int> bestMove = findBestMove(board);
    cout << "The best move is: Row = " << bestMove.first << ", Col = " << bestMove.second << endl;
    return 0;
}
