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
#include "wall.h"
#include "player.h"
#include "commands.h"

int x = 34, y = 12;
int incX = 2, incY = 1;


void printString(int x, int y, char *string, int color) {
    screenSetColor(color, DARKGRAY);
    screenGotoxy(x, y);
    printf("%s", string);
}


int main() {
    static int key = 0;

    Player player;
    player.incX = incX;
    player.incY = incY;
    player.x = 2;
    player.y = MAXY-1;
    player.prevX = player.x;
    player.prevY = player.y;
    player.body = "⬆️";

    Node *wallList = NULL;
    
    screenInit(1);
    keyboardInit();
    timerInit(60);
    
    printWall(&wallList);
    
    screenUpdate();

    while (key != 10) { //enter
        // Handle user input
        if (keyhit()) {
            key = readch();
            screenUpdate();
        }

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1) {
            player.prevY = player.y;
            player.prevX = player.x;

            if(key == up && canMoveY(player, key, -1)) {
                player.body = "⬆️";

                player.y -= player.incY;
            }
            if(key == down && canMoveY(player, key, 1)) {
                player.body = "⬇️";
                
                player.y += player.incY;
            }
            if(key == left && canMoveX(player, key, -1)) {
                player.body = "⬅️";

                player.x -= player.incX;
            }
            if(key == right && canMoveX(player, key, 1)) {
                player.body = "➡️";
                
                player.x += player.incX;
            }

            if (cantMoveX(player, key)) key = 0;

            if (cantMoveY(player, key)) key = 0;

            char str[3];
            sprintf(str, "%d", key);

            printString(MAXX / 2, MAXY, str, YELLOW);
            printPlayer(player, 2);

            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    showData(wallList);

    free(wallList);

    return 0;
}