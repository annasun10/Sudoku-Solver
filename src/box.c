#include "sudoku.h"

int boxSingles(Square *** sudoku, Box ** boxes) {
    int count;
    int temp;

    //loop through boxes
    for(int i = 0; i < 9; i++) {
        //loop through possible array
        for(int j = 0; j < 9; j++) {
            count = 0;

            //loop through squares
            for(int k = 0; k < 9; k++) {
                if(boxes[i] -> squares[k] -> number != 0) {
                    continue;
                }
                if(boxes[i] -> squares[k] -> possible[j] == 0) {
                    count++;
                    temp = k;
                }
                if(count == 2) {
                    break;
                }
            }

            if(count == 1) {
                boxes[i] -> squares[temp] -> number =  j + 1;
                UNSOLVED--;
                boxes[i] -> squares[temp] -> solvable = 0;

                updateSudoku(sudoku, boxes[i] -> squares[temp] -> row, boxes[i] -> squares[temp] -> column);

                return 1;
            }
       }
    }

    return 0;
}

Box ** createBoxes() {
    Box ** boxes;
    boxes = malloc(sizeof(Box*) * 9);

    for(int i = 0; i < 9; i++) {
        boxes[i] = malloc(sizeof(Box));
        boxes[i] -> squares = malloc(sizeof(Square*) * 9);
        boxes[i] -> numbers = 0;
        boxes[i] -> solvable = 9;

        for(int j = 0; j < 9; j++) {
            boxes[i] -> possible[j] = 0;
        }
    }
    
    return boxes;
}

int updateBoxes(Square *** sudoku, int row, int col) {
    int number = sudoku[row][col] -> number;
    Box * box;
    box = sudoku[row][col] -> box;

    for(int i = 0; i < 9; i++) {
        if(box -> squares[i] -> possible[number - 1] == 0) {
            box -> squares[i] -> solvable--;
            box -> squares[i] -> possible[number - 1] = 1;
        }
    }
}