#include "game.h"
#include "render.h"

void draw_board(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int i = 1; i < GRID_SIZE; i++) {
        SDL_RenderDrawLine(renderer, i * (600 / GRID_SIZE), 0, i * (600 / GRID_SIZE), 600);
        SDL_RenderDrawLine(renderer, 0, i * (600 / GRID_SIZE), 600, i * (600 / GRID_SIZE));
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] == PLAYER_X) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawLine(renderer, j * (600 / GRID_SIZE), i * (600 / GRID_SIZE),
                                   (j + 1) * (600 / GRID_SIZE), (i + 1) * (600 / GRID_SIZE));
                SDL_RenderDrawLine(renderer, (j + 1) * (600 / GRID_SIZE), i * (600 / GRID_SIZE),
                                   j * (600 / GRID_SIZE), (i + 1) * (600 / GRID_SIZE));
            } else if (board[i][j] == PLAYER_O) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_Rect rect = { j * (600 / GRID_SIZE) + 10, i * (600 / GRID_SIZE) + 10,
                                  (600 / GRID_SIZE) - 20, (600 / GRID_SIZE) - 20 };
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}

void display_winner(SDL_Renderer *renderer) {
    if (game_state == X_WINS) {
        printf("Le joueur X a gagné !\n");
    } else if (game_state == O_WINS) {
        printf("Le joueur O a gagné !\n");
    } else if (game_state == DRAW) {
        printf("Match nul !\n");
    }
}
