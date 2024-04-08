#include "sudoku.h"

Sudoku * createSudoku(Square *** squares, Box ** boxes) {
    Sudoku * sudoku;
    sudoku = malloc(sizeof(Sudoku));
    
    sudoku -> squares = squares;
    sudoku -> boxes = boxes;

    return sudoku;
}

Sudoku * setUpPuzzle(int ** puzzle) {
    Square *** sudoku;
    Box ** boxes;
    int currentBox = 0;

    sudoku = (Square***) malloc(sizeof(Square**) * 9);
    boxes = createBoxes();

    //loop through rows
    for(int i = 0; i < SIZE_ROWS; i++) {
        //malloc space for each row
        sudoku[i] = (Square**) malloc(sizeof(Square*) * 9);

        //loop through columns
        for(int j = 0; j < SIZE_COLUMNS; j++) {
            //malloc space for each square
            sudoku[i][j] = (Square*) malloc(sizeof(Square) * 9);

            //assign number to sudoku adt
            sudoku[i][j] -> number = puzzle[i][j];

            //assign row and column numbers to each square
            sudoku[i][j] -> row = i;
            sudoku[i][j] -> column = j;
            sudoku[i][j] -> solvable = 9;

            boxes[currentBox] -> squares[boxes[currentBox] -> numbers] = sudoku[i][j]; 
            sudoku[i][j] -> box = boxes[currentBox];
            boxes[currentBox] -> numbers++;

            for(int k = 0; k < SIZE_ROWS; k++) {
                sudoku[i][j] -> possible[k] = 0;
            }

            if(j == 2) {
                currentBox++;
            }

            if(j == 5) {
                currentBox++;
            }
        }
        currentBox -= 2;

        if(i == 2) {
            currentBox = 3;
        }

        if(i == 5) {
            currentBox = 6;
        }
    }

    //loop through rows
    for(int i = 0; i < SIZE_ROWS; i++) {
        //loop through columns
        for(int j = 0; j < SIZE_COLUMNS; j++) {

            if(sudoku[i][j] -> number != 0) {
                sudoku[i][j] -> solvable = 0;
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }

    return createSudoku(sudoku, boxes);
}

int updateSudoku(Square *** sudoku, int row, int col) {
    int number = sudoku[row][col] -> number;

    //loops through the columns
    for(int i = 0; i < SIZE_ROWS; i++) {
        if(sudoku[i][col] -> possible[number - 1] == 0) {
            sudoku[i][col] -> solvable--;
        }
        sudoku[i][col] -> possible[number - 1] = 1;
    }

    //loops through the rows
    for(int i = 0; i < SIZE_COLUMNS; i++) {
        if(sudoku[row][i] -> possible[number - 1] == 0) {
            sudoku[row][i] -> solvable--;
        }
        sudoku[row][i] -> possible[number - 1] = 1;
    }

    return 1;
}

int checkPuzzle(Square *** sudoku, Box ** boxes) {
    //loop through rows
    for(int i = 0; i < SIZE_ROWS; i++) {
        //loop through columns
        for(int j = 0; j < SIZE_COLUMNS; j++) {
            if(sudoku[i][j] -> solvable == 1) {
                solveSquare(sudoku[i][j]);
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);

                return 1;
            }
        }
    }

    return boxSingles(sudoku, boxes);
}

int ** createPuzzle() {
    int ** puzzle;
    int array[9][9] = {0, 1, 9,    0, 0, 2,    0, 0, 0,
                       4, 7, 0,    6, 9, 0,    0, 0, 1,
                       0, 0, 0,    4, 0, 0,    0, 9, 0,
                       
                       8, 9, 4,    5, 0, 7,    0, 0, 0,
                       0, 0, 0,    0, 0, 0,    0, 0, 0,
                       0, 0, 0,    2, 0, 1,    9, 5, 8,
                       
                       0, 5, 0,    0, 0, 6,    0, 0, 0,
                       6, 0, 0,    0, 2, 8,    0, 7, 9,
                       0, 0, 0,    1, 0, 0,    8, 6, 0};
    
    puzzle = (int**) malloc(sizeof(int*) * 9);

    for(int i = 0; i < 9; i++) {
        puzzle[i] = (int*) malloc(sizeof(int) * 9);

        for(int j = 0; j < 9; j++) {
            puzzle[i][j] = array[i][j];
        }
    }

    return puzzle;
}

void printPuzzle(Square *** puzzle) {
    printf("-------------------------------\n");

    for(int i = 0; i < SIZE_ROWS; i++) {
        printf("|");
        //print each row
        for(int j = 0; j < SIZE_COLUMNS; j++) {
            printf(" %d ", puzzle[i][j] -> number);

            if(((j + 1) % 3) == 0) {
                printf("|");
            }
        }
        printf("\n");
        if(((i + 1) % 3) == 0) {
            printf("-------------------------------\n");
        }
    }
}