/**
 * main.c
 * Created on May, 2024
 * Authors: João Pedro Fontes Ferreira, Larissa Sobrinho, Clara Machado
*/

#include <string.h>
#include <stdlib.h>

#include "player.h"
#include "screen.h"


void printString(int x, int y, char *string, int color) {
    screenSetColor(color, DARKGRAY);
    screenGotoxy(x, y);
    printf("%s", string);
}

Wall levels[][25] = {
    {
        {6, 4},
        {6, 5},
        {10, 4},
        {10, 5},
        {10, 7},
        {12, 7},
    },
    {
        {4, 4},
        {6, 4},
        {8, 4},
        {8, 5},
        {12, 7},
    },
    {
        {4, 3},
        {6, 6},
        {12, 7},
    },
    {
        {6, 4},
        {6, 5},
        {6, 6},
        {8, 4},
        {8, 5},
        {8, 6},
        {10, 4},
        {10, 5},
        {10, 6},
    }
};


int main() {
    int level = 3;

    // screenDefaultInit(0);
    // keyboardInit();
    // timerInit(60);

    // keyboardDestroy();
    // screenDestroy();
    // timerDestroy();

    Wall *walls = (Wall *) malloc(100 * sizeof(Wall));

    int i = 0;
    while (1) {
        int x = levels[level - 1][i].x;
        if(x) {
            walls[i] = levels[level - 1][i];
            i++;
        }
        else break;
    }

    initGame(walls, 0);

    free(walls);

    return 0;
}