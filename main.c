#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

void drawBoard(char board[3][3]);
bool markLocation(char board[3][3], int chosenRow, int chosenCol);
void computerPlay(char board[3][3]);
bool checkGameEnd(char board[3][3]);

int main() {
    bool gameIsOver = false;
    int chosenRow, chosenCol;
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    drawBoard(board);
    while(!gameIsOver){
        printf("Choose a location to play (4 4 to quit)\n");
        scanf("%d %d", &chosenCol, &chosenRow);
        if(markLocation(board, chosenRow, chosenCol)){
            gameIsOver = checkGameEnd(board);
            if(!gameIsOver) {
                computerPlay(board);
            }
        }
        drawBoard(board);

        if(!gameIsOver)
            gameIsOver = checkGameEnd(board);

        if(chosenRow == 4 && chosenCol == 4) {
            gameIsOver = true;
        }
    }

    return 0;
}

// Marks users chosen location and returns true
// if spot already taken returns false
bool markLocation(char board[3][3], int chosenRow, int chosenCol) {
    if(board[chosenRow-1][chosenCol-1] == ' ') {
        board[chosenRow-1][chosenCol-1] = 'o';
        return true;
    } else {
        return false;
    }
}
void computerPlay(char board[3][3]) {
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++){
            if(board[i][j] != 'o' && board[i][j] != 'x') {
                board[i][j] = 'x';
                return;
            }
        }
    }
}
bool checkGameEnd(char board[3][3]){
    bool xWon = false;
    bool oWon = false;

    int totalHits = 0;
    // Check rows (horizontal win), also check board is full
    for(int i=0; i < 3; i++){
        int xHits = 0;
        int oHits = 0;
        for(int j=0; j<3; j++) {
            if(board[i][j] == 'x'){
                xHits++;
                totalHits++;
            }
            if(board[i][j] == 'o'){
                oHits++;
                totalHits++;
            }
        }
        if(xHits == 3) {
            xWon = true;
            break;
        }
        if(oHits == 3) {
            oWon = true;
            break;
        }
    }
    // Check cols (vertical win)
    for(int i=0; i < 3; i++){
        int xHits = 0;
        int oHits = 0;
        for(int j=0; j<3; j++) {
            if(board[j][i] == 'x'){
                xHits++;
            }
            if(board[j][i] == 'o'){
                oHits++;
            }
        }
        if(xHits == 3) {
            xWon = true;
            break;
        }
        if(oHits == 3) {
            oWon = true;
            break;
        }
    }
    // Check for angle wins
    if(board[0][0] == 'x' && board [1][1] == 'x' && board[2][2] == 'x' ||
        board[2][0] == 'x' && board [1][1] == 'x' && board[0][2] == 'x') {
        xWon = true;
    }
    if(board[0][0] == 'o' && board [1][1] == 'o' && board[2][2] == 'o' ||
        board[2][0] == 'o' && board [1][1] == 'o' && board[0][2] == 'o') {
        oWon = true;
    }
    if(xWon) {
        printf("Computer has won the game.  Better luck next time.\n");
    } else if(oWon) {
        printf("You have won the game!!\n");
    }

    if(totalHits == 9) {
        printf("The game ended in stalemate.\n");
    }
    return xWon || oWon || totalHits == 9;
}

void drawBoard(char board[3][3]) {
    printf(" ");
    for(int headerCol = 0; headerCol < 3; headerCol++){
        printf(" %d", headerCol+1);
    }
    printf("\n");
    for(int row=0; row<3; row++) {
        for(int col=0; col<3; col++){
            if(col==0)printf("%d ", row+1);
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }
}