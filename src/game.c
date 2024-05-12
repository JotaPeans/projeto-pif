#include <string.h>
#include <stdlib.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "player.h"
#include "commands.h"

int incX = 2, incY = 1;

void initGame(Wall walls[]) {
    int wallsSize = 0;
    while (1) {
        int x = (int) walls[wallsSize].x;
        if(x) 
            wallsSize++;
        else break;
    }

    static int key = 0;
    int won;

    screenDefaultInit(0);
    keyboardInit();
    timerInit(60);
    
    Player player;
    player.incX = incX;
    player.incY = incY;
    player.x = 4;
    player.y = MAXY-2;
    player.prevX = player.x;
    player.prevY = player.y;
    player.body = "⬆️";

    Node *wallList = NULL;
    NodeFree *freeList = NULL;
    
    buildWall(&wallList, &freeList, walls, wallsSize);
    
    screenUpdate();

    while (key != 10) {
        if (keyhit() && key == 0) {
            key = readch();
            
            screenUpdate();
        }

        if (timerTimeOver() == 1) {
            player.prevY = player.y;
            player.prevX = player.x;

            if(key == up && canMove(player, key, wallList)) {
                player.body = "⬆️";

                player.y -= player.incY;
            }
            else if(key == down && canMove(player, key, wallList)) {
                player.body = "⬇️";
                
                player.y += player.incY;
            }
            else if(key == left && canMove(player, key, wallList)) {
                player.body = "⬅️";

                player.x -= player.incX;
            }
            else if(key == right && canMove(player, key, wallList)) {
                player.body = "➡️";
                
                player.x += player.incX;
            }
            else {
                key = 0;
            }

            movePlayerOnMap(player, freeList);

            won = playerWon(player, freeList);

            if(won) {
                break;
            }

            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    free(wallList);
    free(freeList);
}