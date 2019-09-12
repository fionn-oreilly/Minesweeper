/*Fionn O'Reilly C Programming Assignment 2*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_functions.h"

int main()
{
    /*static int i = 1;
    i = i+2;
    printf("%d", i);
     i = 1;
    i = i+2;
    printf("%d", i);
    /*char b[8] = "Bonjour";
    char a[8] = "Hello"; //changed size from 6 to 8
    strcpy(a, b);
    printf("%s\n", a);*/

    /*char name[50] = "cat";
    printf("%c",name[0]);
    printf("\n%c\n",name[strlen(name)-1]);
    /*char* pName = getName();
    printf("%s",pName);
    /*int list[] = {1,2,3};
    printf("%d",list);
    printf("\n%d\n",list[sizeof(list)/sizeof(list[0])-1]);

    int i= 0;
    while (i<sizeof(list)/sizeof(list[0])) {
        printf("%d",list[i]);
        i++;
    }*/
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

/*char* getName() {
    char *str = (char *) malloc(sizeof(char) * 6);
    return str;
}*/
