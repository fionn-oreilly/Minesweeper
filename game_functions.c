/*Author:       Fionn O'Reilly
  Description:  2 stage game. Stage 1 the user has to pick coordinates on a grid
                without landing on a bomb location. Stage 2 the player has to guess
                the locations of the bombs. The user can change the difficulty at the
                beginning of the game.*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game_functions.h"

/*Main game function*/
void startGame(struct locations bombs[], int bombInfo[][DIM], int gridSize, int knownInfo[][DIM], int numBombs) {
    enum gameStatus  {STILL_ALIVE, GAME_OVER};
    enum gameStatus status = STILL_ALIVE;
    int phase = 1, guesses = 0, bombsFound = 0;
    bool found = false, valid = false, search = true;
    char clues;

    while (valid == false) { //Get and validate user input for number of bombs in the grid
        printf("How many bombs would you like on the grid? (2,3,4): ");
        numBombs = getUserChar()-48;
        if (numBombs < 2 || numBombs > 4) {printf("\nNumber of bombs must be 2,3 or 4.\n");}
        else {valid = true;}
    }

    valid = false;
    while (valid == false) { //Get and validate user input for clues to show at game start
        printf("Enter \"Y\" if you would like 2 cells revealed for you, if not, enter \"N\": ");
        char clues = toupper(getUserChar());

        if (clues - 'Y' == 0 || clues - 'N' == 0)  { //If clues = 'Y' or 'N'
            valid = true;
            generateGrid(bombInfo,bombs,numBombs);

            if (clues - 'Y' == 0) {guesses = 2;} //Reduce available guessus if user receives clues
            setClues(knownInfo,bombInfo,numBombs,clues);
            display(knownInfo, (sizeof(knownInfo[0])/sizeof(int)));
            printf("Guesses remaining: %d\n", 5 - guesses);

            if (phase == 1) { //Get hints. Finding bomb in phase 1 is game over.
                while (guesses < 5 && status == STILL_ALIVE) {
                    printf("Enter column: ");
                    int col = toupper(getUserChar()) - 65;
                    printf("Enter row: ");
                    int row = toupper(getUserChar()) - 65;

                    bool check = checkInput(row,col,bombInfo,bombs,numBombs,&found,knownInfo);

                    if (check == true) {
                        bool bombFound = false;
                        int i = 0;

                        //Check found value for each bomb
                        while (bombFound == false && i < numBombs ) {
                            bombFound = bombs[i].found;
                            i++;
                        }

                        if (bombFound == true) {
                            printf("\nGame Over - You found a bomb!\n");
                            printf("Bomb locations were:");
                            for (int i = 0;i<numBombs;i++) { //Print bomb locations
                                printf("[%c,%c],",bombs[i].x+65,bombs[i].y+65);
                            }
                            printf("\n");
                            status = GAME_OVER;
                        } else {
                            phase = 2;
                            guesses++;
                            printf("Guesses remaining: %d\n", 5 - guesses);
                        }
                    } //end if (check == true)
                } //end while (guesses < 5 && status == STILL_ALIVE)
            } //end if (phase == 1)

            if (phase == 2 && status == STILL_ALIVE) { //Phase 2: Find all bombs. Finding a cell that isn't a bomb is game over.
                printf("\n----PHASE 2 ----\nGuess bomb locations\n");
                printf("Bombs remaining: %d\n", numBombs - bombsFound);

                while (status == STILL_ALIVE) {
                    printf("Enter column: ");
                    int col = toupper(getUserChar()) - 65;
                    printf("Enter row: ");
                    int row = toupper(getUserChar()) - 65;

                    bool check = checkInput(row,col,bombInfo,bombs,numBombs,&found,knownInfo);

                    if (check == true) {
                        bool bombFound = false;
                        int i = 0;

                        //Check found value for each bomb
                        while (bombFound == false && i < numBombs ) {
                            bombFound = bombs[i].found;
                            i++;
                        }

                        if (bombInfo[row][col] >= 0) { //If location is not a bomb
                            printf("\nGame Over - There is no bomb at this location.\n");
                            printf("Bomb locations were:");
                            for (int i = 0;i<numBombs;i++) { //Print bomb locations
                                printf("[%c,%c],",bombs[i].x+65,bombs[i].y+65);
                            }
                            printf("\n");
                            status = GAME_OVER;
                        } else if (bombFound == true) {
                            printf("\nYou found a bomb!\n");
                            bombsFound++;
                            printf("Bombs remaining: %d\n", numBombs - bombsFound);
                        }
                    }

                    if (bombsFound == numBombs) {
                        printf("\nCongratulations! - You found all the bombs.\n");
                        status = GAME_OVER;
                    }
                } //end while (status == STILL_ALIVE)
            } //end if (phase == 2 && status == STILL_ALIVE)
        } else {
            printf("Please enter \"Y\" or \"N\"\n");
        }
    }//end while (valid == false)
} /*end startGame*/


/*Get input from user*/
char getUserChar() {
    char res = getchar();
    bool finish = false;
    char dummy_char = ' ';
    while (finish == false) {
        dummy_char = getchar();
        if (dummy_char == '\n')
            finish = true;
    }
    return res;
}


/*Function to generate bomb location grid*/
void generateGrid(int bombInfo[][DIM],struct locations bombs[], int numBombs) {
    int col;
    int row;

    srand(time(0));

    int bombsSet = 0;
    //Set bomb locations
    while (bombsSet < numBombs) {
        col = rand() % DIM;
        row = rand() % DIM;

        if (bombInfo[col][row] > UNKNOWN) {
            bombInfo[col][row] = BOMB;

            bombs[bombsSet].x = row;
            bombs[bombsSet].y  = col;
            bombs[bombsSet].found = false;

            bombsSet++;
        }
    }

    int k;
    int l;
    //Set values for cells surrounding bomb locations
    for (int i=0;i<DIM;i++) { //for each row
        for (int j=0;j<DIM;j++) { //for each column
            if (bombInfo[i][j] < -1) { //if cell contains bomb
                //increase value of surrounding cells by 1
                for (k=i-1;k < i+2;k++) { //for each row around cell
                    if (k < 0) {} else if (k >= DIM) {}
                    else {
                        for(l=j-1;l < j+2;l++) { //for each column around cell
                            if (l < 0) {} else if (l >= DIM) {}
                            else {
                                bombInfo[k][l]++;
                            }
                        }
                    }
                }
            }
        }
    }

    //Print bomb location grid (for testing)
    printf("--------------------\nBomb locations (for testing):\n");
    printf("  A B C D\n");
    char letter = 'A';
    for (int i=0;i<DIM;i++) {
        printf("%c:", letter);
        for (int j=0;j<DIM;j++) {
            if (bombInfo[i][j] < 0) {
                printf("B,");
            } else {
                printf("%d,", bombInfo[i][j]);
            }
        }
        printf("\n");
        letter++;
    }
    printf("-------------------\n\n");
} /*end generateGrid*/


/*Display 2 random clues to player at start of game*/
void setClues(int knownInfo[][DIM],int bombInfo[][DIM], int numBombs,char* clues) {
    if (clues - 'Y' == 0) { //If clues = 'Y'
         int cluesGiven = 0;
         srand(time(0));

         while (cluesGiven < 2) {
            int col = rand() % DIM;
            int row = rand() % DIM;

            //If location isn't a bomb and location hasn't already been given
            if (bombInfo[row][col] > UNKNOWN && knownInfo[row][col] == UNKNOWN) {
                updateKnownInfo(row,col,bombInfo,knownInfo);
                cluesGiven++;
            }
        }
    }
}


/*Function to display game grid to player*/
void display(int knownInfo[][DIM], int size) {
    int i = 0;
    int j = 0;
    char letter = 'A';

    printf("  A B C D\n"); //Column values
    for (i=0;i<size;i++) {
        printf("%c:",letter); //Row values
        for (j=0;j<size;j++) {
            if (knownInfo[i][j] == UNKNOWN) { //If info not known to user
                printf("* ");
            } else {
                if (knownInfo[i][j] < UNKNOWN) { //If info is a bomb
                    printf("B ");
                } else {
                    printf("%d ",knownInfo[i][j]);
                }
            }
        }
        printf("\n");
        letter++;
    }
} /*end display*/


/*Validate player input for grid co-ordinates*/
bool checkInput(int row, int col, int bombInfo[][DIM], struct locations bombs[], int numBombs, bool* found, int knownInfo[][DIM]) {
    if (row < 0 || row > DIM-1 || col < 0 || row > DIM-1) {
        printf("Co-ordinates must be entered as letters A-D, try again.\n");
        return false;
    } else if (knownInfo[row][col] != UNKNOWN) {
        printf("You already entered these coordinates. Enter new ones.\n");
        return false;
    } else {
        checkFound(row, col, bombs, numBombs, found);
        updateKnownInfo(row, col, bombInfo, knownInfo);
        display(knownInfo, (sizeof(knownInfo[0])/sizeof(int)));
        return true;
    }
}


/*Check if position is a bomb. Change found value for bomb in struct*/
void checkFound(int row, int col, struct locations bombs[], int numBombs, bool* found) {
    for (int i =0;i<numBombs;i++) {
        if (row == bombs[i].y && col == bombs[i].x) {
            bombs[i].found = true;
        }
    }
}


/*Update grid info available to player*/
void updateKnownInfo(int row, int col, int bombInfo[][DIM], int knownInfo[][DIM]) {
    int newNum = bombInfo[row][col];
    knownInfo[row][col] = newNum;
}
