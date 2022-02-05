#include "tictactoe.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int max(int num1, int num2) {
    return (num1 > num2) ? num1 : num2;
}

int min(int num1, int num2) {
    return (num1 > num2) ? num2 : num1;
}

int won(char** board, int size, char player, coordinate last_played) {
    int i;

    // check horizontal
    i = 0;
    while (i < size && board[last_played.x][i] == player) {
        i++;
    }
    if (i == size) {
        return 1;
    }

    // check vertical
    i = 0;
    while (i < size && board[i][last_played.y] == player) {
        i++;
    }
    if (i == size) {
        return 1;
    }

    // check diagonal
    if (last_played.x == last_played.y || (last_played.x == size - 1 && last_played.y == 0) || (last_played.x == 0 && last_played.y == size - 1)) {
        i = 0;
        while (i < size && board[i][i] == player) {
            i++;
        }
        if (i == size) {
            return 1;
        }

        i = 0;
        while (i < size && board[i][size - i - 1] == player) {
            i++;
        }
        if (i == size) {
            return 1;
        }
    }
    return 0;
}

int check_winner(char** board, int size) {
    for (int i = 0; i < size; i++) {
        if (won(board, size, PLAYER, (coordinate){i, 0}) || won(board, size, PLAYER, (coordinate){0, i})) {
            return PLAYER_WINS;
        }
        if (won(board, size, AI, (coordinate){i, 0}) || won(board, size, AI, (coordinate){0, i})) {
            return AI_WINS;
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (!board[i][j]) {
                return -1;
            }
        }
    }

    return TIE;
}

int minimax(char** board, int size, int is_maximizing, int alpha, int beta) {
    int winner = check_winner(board, size);
    if (winner != -1) {
        return winner;
    }

    if (is_maximizing) {
        int best_score = INT_MIN;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (!board[i][j]) {
                    board[i][j] = AI;
                    int score = minimax(board, size, 0, alpha, beta);
                    board[i][j] = 0;
                    best_score = max(best_score, score);
                    alpha = max(best_score, alpha);
                    if (beta <= alpha) {
                        return best_score;
                    }
                }
            }
        }
        return best_score;

    } else {
        int best_score = INT_MAX;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (!board[i][j]) {
                    board[i][j] = PLAYER;
                    int score = minimax(board, size, 1, alpha, beta);
                    board[i][j] = 0;
                    best_score = min(best_score, score);
                    beta = min(beta, best_score);
                    if (beta <= alpha) {
                        return best_score;
                    }
                }
            }
        }
        return best_score;
    }
}

coordinate best_move(char** board, int size) {
    int best_score = INT_MIN;
    coordinate optimal_move;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (!board[i][j]) {
                board[i][j] = AI;
                int score = minimax(board, size, 0, INT_MIN, INT_MAX);
                board[i][j] = 0;  // reset
                if (score > best_score) {
                    best_score = score;
                    optimal_move.x = i;
                    optimal_move.y = j;
                }
            }
        }
    }
    board[optimal_move.x][optimal_move.y] = AI;
    return optimal_move;
}

void print_board(char** board, int size) {
    printf("  ");
    for (int i = 0; i < size; i++) {
        printf(" %d", i);
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%d |", i);
        for (int j = 0; j < size; j++) {
            if (!board[i][j]) {
                printf(".|");
            } else {
                printf("%c|", board[i][j]);
            }
        }
        printf("\n");
    }
}