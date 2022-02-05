#ifndef TICTACTOE_H
#define TICTACTOE_H

#define AI 'O'
#define PLAYER 'X'

#define PLAYER_WINS -10
#define AI_WINS 10
#define TIE 0

typedef struct {
    int x;
    int y;
} coordinate;

int max(int num1, int num2);

int min(int num1, int num2);

int won(char** board, int size, char player, coordinate last_played);

int check_winner(char** board, int size);

int minimax(char** board, int size, int is_maximizing, int alpha, int beta);

coordinate best_move(char** board, int size);

void print_board(char** board, int size);

#endif