#include "game.h"
#include <limits.h>

Cell board[GRID_SIZE][GRID_SIZE];
GameState game_state = RUNNING;
int current_player = PLAYER_X;

void init_board() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

int check_winner() {
    for (int i = 0; i < GRID_SIZE; i++) {
        if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
        if (board[0][i] != EMPTY && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }
    if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }

    int draw = 1;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                draw = 0;
                break;
            }
        }
    }

    if (draw) return DRAW;
    return 0;
}

int minimax(int depth, int isMaximizing) {
    int winner = check_winner();
    
    if (winner == PLAYER_O) return 10 - depth;
    if (winner == PLAYER_X) return depth - 10;
    if (winner == DRAW) return 0;

    if (isMaximizing) {
        int bestScore = INT_MIN;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_O;
                    int score = minimax(depth + 1, 0);
                    board[i][j] = EMPTY;
                    bestScore = score > bestScore ? score : bestScore;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_X;
                    int score = minimax(depth + 1, 1);
                    board[i][j] = EMPTY;
                    bestScore = score < bestScore ? score : bestScore;
                }
            }
        }
        return bestScore;
    }
}

void computer_play() {
    if (game_state != RUNNING || current_player != PLAYER_O) return;

    int bestScore = INT_MIN;
    int moveRow = -1;
    int moveCol = -1;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER_O;
                int score = minimax(0, 0);
                board[i][j] = EMPTY;

                if (score > bestScore) {
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }

    if (moveRow != -1 && moveCol != -1) {
        board[moveRow][moveCol] = PLAYER_O;
        current_player = PLAYER_X;

        int winner = check_winner();
        if (winner == PLAYER_X) {
            game_state = X_WINS;
        } else if (winner == PLAYER_O) {
            game_state = O_WINS;
        } else if (winner == DRAW) {
            game_state = DRAW;
        }
    }
}
