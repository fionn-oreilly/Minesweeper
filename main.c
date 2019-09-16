/* 
 * Author: Fionn O'Reilly
 * Description: Main file for game_functions.c
 */

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

    // call to function in game_functions.c
    startGame(bombs, bombInfo, DIM, knownInfo, numBombs);

    free(bombs);
    return 0;
}
