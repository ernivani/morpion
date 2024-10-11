#ifndef GAME_H
#define GAME_H

#define GRID_SIZE 3

typedef enum { EMPTY, PLAYER_X, PLAYER_O } Cell;
typedef enum { RUNNING, X_WINS, O_WINS, DRAW } GameState;

extern Cell board[GRID_SIZE][GRID_SIZE];
extern GameState game_state;
extern int current_player;

void init_board();
int check_winner();
void handle_click(int x, int y);
void computer_play();

#endif
