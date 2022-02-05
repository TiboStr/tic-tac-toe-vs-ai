#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define AI 'O'
#define PLAYER 'X'

/*
 ______                ______                     ______                                        ______  ______
/\__  _\__            /\__  _\                   /\__  _\                                      /\  _  \/\__  _\
\/_/\ \/\_\    ___    \/_/\ \/    __      ___    \/_/\ \/   ___      __       __  __    ____   \ \ \L\ \/_/\ \/
   \ \ \/\ \  /'___\     \ \ \  /'__`\   /'___\     \ \ \  / __`\  /'__`\    /\ \/\ \  /',__\   \ \  __ \ \ \ \
    \ \ \ \ \/\ \__/      \ \ \/\ \L\.\_/\ \__/      \ \ \/\ \L\ \/\  __/    \ \ \_/ |/\__, `\   \ \ \/\ \ \_\ \__
     \ \_\ \_\ \____\      \ \_\ \__/.\_\ \____\      \ \_\ \____/\ \____\    \ \___/ \/\____/    \ \_\ \_\/\_____\
      \/_/\/_/\/____/       \/_/\/__/\/_/\/____/       \/_/\/___/  \/____/     \/__/   \/___/      \/_/\/_/\/_____/

*/

typedef struct {
    int x;
    int y;
} coordinate;

int minimax(char** board) {
    return 1;
}

coordinate best_move(char** board) {
    int best_score = INT_MIN;
    coordinate optimal_move;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!board[i][j]) {
                board[i][j] = AI;
                int score = minimax(board);
                board[i][j] = 0;  // reset
                best_score = score > best_score ? score : best_score;
                optimal_move.x = i;
                optimal_move.y = j;
            }
        }
    }
    board[optimal_move.x][optimal_move.y] = AI;
    return optimal_move;
}

void print_board(char** board, int size) {
    for (int i = 0; i < size; i++) {
        printf("|");
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

int won(char** board, int size, char player, int x, int y) {
    int i;

    // check horizontal
    i = 0;
    while (i < size && board[x][i] == player) {
        i++;
    }
    if (i == size) {
        return 1;
    }

    // check vertical
    i = 0;
    while (i < size && board[i][y] == player) {
        i++;
    }
    if (i == size) {
        return 1;
    }

    // check diagonal
    if (x == y || (x == size - 1 && y == 0) || (x == 0 && y == size - 1)) {
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

int main(void) {
    printf("You are playing Tic Tac Toe.\n");

    //  int** board = (int**)calloc(3, sizeof(int*));
    char** board = (char**)malloc(3 * sizeof(char*));
    for (int i = 0; i < 3; i++) {
        board[i] = (char*)calloc(3, sizeof(char));
    }

    int gameloop = 1;
    int size = 3;

    int moves = 0;
    while (gameloop) {
        //  printf("Enter a value (integer) to initialize the size of the grid: ");
        // size = 3;

        print_board(board, 3);

        while (1) {
            int x, y;

            // PLAYER MAKES MOVE
            printf("> Enter x and y: ");
            scanf("%d%d", &x, &y);

            while (!(0 <= x && x < 3 && 0 <= y && y < 3) || board[x][y]) {
                printf("The values of x and y must be greater than 0 and smaller than 3\n");
                printf("> Enter x and y: ");

                while (getchar() != '\n')
                    ;  // https://stackoverflow.com/a/68471839

                scanf("%d%d", &x, &y);
            }
            printf("You entered %d and %d\n", x, y);

            board[x][y] = PLAYER;

            moves++;
            print_board(board, 3);
            if (won(board, 3, PLAYER, x, y)) {
                printf("Congratiolations, you won!\n");
                break;
            }

            if (moves >= 3 * 3) {
                printf("Tie.\n");
                break;
            }

            // AI MAKES MOVE
            printf("AI's turn:\n");
            coordinate coord = best_move(board);
            moves++;
            print_board(board, 3);
            if (won(board, 3, AI, coord.x, coord.y)) {
                printf("You lose.\n");
                break;
            }
        }
        moves = 0;
        gameloop = 0;
    }

    printf("Thank you for playing.\n");
    return 1;
}
