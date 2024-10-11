#include "game.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define EPSILON 0.2
NeuralNetwork ai_x;
NeuralNetwork ai_o;

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

void init_ai() {
    init_network(&ai_x);
    init_network(&ai_o);
}

void handle_click(int x, int y) {
    if (game_state != RUNNING) return;

    int row = y / (600 / GRID_SIZE);
    int col = x / (600 / GRID_SIZE);

    if (board[row][col] == EMPTY && current_player == PLAYER_X) {
        board[row][col] = PLAYER_X;
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


void ai_play(NeuralNetwork *nn, Cell player) {
    double input[INPUT_NODES];
    double output[OUTPUT_NODES];

    for (int i = 0; i < GRID_SIZE * GRID_SIZE; i++) {
        int row = i / GRID_SIZE;
        int col = i % GRID_SIZE;
        if (board[row][col] == EMPTY)
            input[i] = 0;
        else if (board[row][col] == player)
            input[i] = 1;
        else
            input[i] = -1;
    }

    feedforward(nn, input, output);

    int move = -1;

    double r = ((double)rand() / RAND_MAX);

    if (r < EPSILON) {
        int valid_moves[GRID_SIZE * GRID_SIZE];
        int num_valid_moves = 0;
        for (int i = 0; i < OUTPUT_NODES; i++) {
            int row = i / GRID_SIZE;
            int col = i % GRID_SIZE;
            if (board[row][col] == EMPTY) {
                valid_moves[num_valid_moves++] = i;
            }
        }
        if (num_valid_moves > 0) {
            int random_index = rand() % num_valid_moves;
            move = valid_moves[random_index];
        }
    } else {
        double bestValue = -INFINITY;
        for (int i = 0; i < OUTPUT_NODES; i++) {
            int row = i / GRID_SIZE;
            int col = i % GRID_SIZE;
            if (board[row][col] == EMPTY && output[i] > bestValue) {
                bestValue = output[i];
                move = i;
            }
        }
    }

    if (move != -1) {
        int row = move / GRID_SIZE;
        int col = move % GRID_SIZE;
        board[row][col] = player;
    }
}
void computer_play() {
    if (game_state != RUNNING) return;

    if (current_player == PLAYER_X) {
        ai_play(&ai_x, PLAYER_X);
        current_player = PLAYER_O;
    } else if (current_player == PLAYER_O) {
        ai_play(&ai_o, PLAYER_O);
        current_player = PLAYER_X;
    }

    int winner = check_winner();
    if (winner == PLAYER_X) {
        game_state = X_WINS;
    } else if (winner == PLAYER_O) {
        game_state = O_WINS;
    } else if (winner == DRAW) {
        game_state = DRAW;
    }
}
