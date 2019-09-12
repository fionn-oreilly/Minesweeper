/*Author: Fionn O'Reilly*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_functions.h"

int main()
{
    int numBombs;
    struct locations* bombs = (struct locations*) malloc(sizeof(struct locations)*2);

    int bombInfo[DIM][DIM] = {};

    int knownInfo[DIM][DIM] = {-1,-1,-1,-1,
                               -1,-1,-1,-1,
                               -1,-1,-1,-1,
                               -1,-1,-1,-1};


    startGame(bombs, bombInfo, DIM, knownInfo, numBombs);

    free(bombs);
    return 0;
}
