#include <ctype.h>
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

coordinate best_move(char** board, int size) {
    int best_score = INT_MIN;
    coordinate optimal_move;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
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

int main(void) {
    printf("You are playing Tic Tac Toe.\n");

    int gameloop = 1;

    int moves = 0;
    while (gameloop) {
        int size;
        printf("> Enter a value (integer) to initialize the size of the grid: ");
        scanf("%d", &size);

        while (!(size >= 3 && size < 100)) {
            printf("Please enter a valid size.\n");
            printf("> Enter a value (integer) to initialize the size of the grid: ");
            while (getchar() != '\n')
                ;  // https://stackoverflow.com/a/68471839
            scanf("%d", &size);
        }
        printf("You are playing on a %dx%d grid\n", size, size);

        char** board = (char**)calloc(size, sizeof(char*));
        for (int i = 0; i < size; i++) {
            board[i] = (char*)calloc(size, sizeof(char));
        }

        print_board(board, size);

        while (1) {
            int row, col;

            // PLAYER MAKES MOVE
            printf("> Enter row and col: ");
            scanf("%d%d", &row, &col);

            while (!(0 <= row && row < size && 0 <= col && col < size) || board[row][col]) {
                printf("The values for row and col must be greater than 0 and smaller than %d, make sure you select an empty spot.\n", size);
                printf("> Enter row and col: ");

                while (getchar() != '\n')
                    ;  // https://stackoverflow.com/a/68471839

                scanf("%d%d", &row, &col);
            }
            printf("You entered %d and %d\n", row, col);

            board[row][col] = PLAYER;

            moves++;
            print_board(board, size);

            if (won(board, size, PLAYER, (coordinate){row, col})) {
                printf("Congratiolations, you won!\n");
                break;
            }

            if (moves >= size * size) {
                printf("Tie.\n");
                break;
            }

            // AI MAKES MOVE
            printf("AI's turn:\n");
            coordinate coord = best_move(board, size);
            moves++;
            print_board(board, size);
            if (won(board, size, AI, coord)) {
                printf("You lose.\n");
                break;
            }
        }
        moves = 0;

        for (int i = 0; i < size; i++) {
            free(board[i]);
            board[i] = NULL;
        }
        free(board);
        board = NULL;

        printf("Do you want to play again? (y/n): ");
        char c;
        scanf(" %c", &c);
        gameloop = tolower(c) == 'y';
    }

    printf("Thank you for playing.\n");

    return 1;
}
