
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "tictactoe.h"

/*
 ______                ______                     ______                                        ______  ______
/\__  _\__            /\__  _\                   /\__  _\                                      /\  _  \/\__  _\
\/_/\ \/\_\    ___    \/_/\ \/    __      ___    \/_/\ \/   ___      __       __  __    ____   \ \ \L\ \/_/\ \/
   \ \ \/\ \  /'___\     \ \ \  /'__`\   /'___\     \ \ \  / __`\  /'__`\    /\ \/\ \  /',__\   \ \  __ \ \ \ \
    \ \ \ \ \/\ \__/      \ \ \/\ \L\.\_/\ \__/      \ \ \/\ \L\ \/\  __/    \ \ \_/ |/\__, `\   \ \ \/\ \ \_\ \__
     \ \_\ \_\ \____\      \ \_\ \__/.\_\ \____\      \ \_\ \____/\ \____\    \ \___/ \/\____/    \ \_\ \_\/\_____\
      \/_/\/_/\/____/       \/_/\/__/\/_/\/____/       \/_/\/___/  \/____/     \/__/   \/___/      \/_/\/_/\/_____/

*/

int main(void) {
    printf("You are playing Tic Tac Toe.\n");

    int gameloop = 1;

    int moves = 0;
    while (gameloop) {
        int size;
        printf("> Enter a value (integer) to initialize the size of the grid: ");
        scanf("%d", &size);

        while (!(size >= size && size < 100)) {
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
