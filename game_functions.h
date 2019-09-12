/*Author: Fionn O'Reilly*/
#define GAME_FUNCTIONS_H_INCLUDED
#include <stdbool.h>

#define DIM 4
#define UNKNOWN -1
#define BOMB -5

struct locations {
    int x;
    int y;
    bool found;
};

char* getName();

void startGame(struct locations* bombs, int bombInfo[][DIM], int gridSize, int knownInfo[][DIM], int numBombs);

void generateGrid(int bombInfo[][DIM],struct locations bombs[], int numBombs);

char getUserChar();

void displayClues(int knownInfo[][DIM],int bombInfo[][DIM],int numBombs,char* clues);

void display(int knownInfo[][DIM], int size);

bool checkInput(int row, int col, int bombInfo[][DIM], struct locations bombs[], int numBombs, bool* found, int knownInfo[][DIM]);

void checkFound(int row, int col, struct locations bombs[], int numBombs, bool* found);

void updateKnownInfo(int row, int col, int bombInfo[][DIM], int known[][DIM]);


#endif // GAME_FUNCTIONS_H_INCLUDED
