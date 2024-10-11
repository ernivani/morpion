#include "game.h"
#include <stdlib.h>
#include <time.h>

Cell board[GRID_SIZE][GRID_SIZE];
GameState game_state = RUNNING;
int current_player = PLAYER_X;

void init_board() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
    srand(time(NULL));  // Initialisation pour les mouvements aléatoires
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

void handle_click(int x, int y) {
    if (game_state != RUNNING) return;

    int row = y / (600 / GRID_SIZE);
    int col = x / (600 / GRID_SIZE);

    if (board[row][col] == EMPTY && current_player == PLAYER_X) {
        board[row][col] = current_player;
        current_player = PLAYER_O;

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

void computer_play() {
    if (game_state != RUNNING || current_player != PLAYER_O) return;

    int row, col;
    do {
        row = rand() % GRID_SIZE;
        col = rand() % GRID_SIZE;
    } while (board[row][col] != EMPTY);

    board[row][col] = PLAYER_O;
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
