/**
 * main.c
 * Created on May, 2024
 * Authors: João Pedro Fontes Ferreira, Larissa Sobrinho, Clara Machado
*/

#include <string.h>
#include <stdlib.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "player.h"
#include "commands.h"


void printString(int x, int y, char *string, int color) {
    screenSetColor(color, DARKGRAY);
    screenGotoxy(x, y);
    printf("%s", string);
}

// Wall walls[] = {
//     {6, 4},
//     {6, 5},
//     {10, 4},
//     {10, 5},
//     {10, 7},
//     {12, 7},
// };
Wall walls[] = {
    {4, 4},
    {6, 4},
    {8, 4},
    {8, 5},
    {12, 7},
};
// Wall walls[] = {
//     {4, 3},
//     {6, 6},
//     {12, 7},
// };
// Wall walls[] = {
//     {6, 4},
//     {6, 5},
//     {6, 6},
//     {8, 4},
//     {8, 5},
//     {8, 6},
//     {10, 4},
//     {10, 5},
//     {10, 6},
// };


int main() {
    int level;

    // screenDefaultInit(0);
    // keyboardInit();
    // timerInit(60);

    // keyboardDestroy();
    // screenDestroy();
    // timerDestroy();

    initGame(walls);

    return 0;
}