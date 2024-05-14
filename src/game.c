#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "player.h"
#include "commands.h"

int incX = 2, incY = 1;

void initGame(Wall walls[], int tam_y) {
    srand(time(NULL));
    
    int wallsSize = 0;

    char *colors[] = {
        "🟫", "🟪", "🟦", "🟩", "🟨", "🟥"
    };

    int randomColorIndex = rand() % 5;
    
    while (1) {
        int x = walls[wallsSize].x;
        if(x) 
            wallsSize++;
        else break;
    }

    int key = 0;
    int won;

    if(tam_y == 0|| tam_y < 0)
        screenDefaultInit(0);
    else
        screenInit(0, tam_y + 4, (tam_y + 4) * 2);

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

            movePlayerOnMap(player, freeList, colors[randomColorIndex]);

            won = playerWon(player, freeList);

            screenUpdate();

            if(won) {
                usleep(300 * 1000);
                break;
            }
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    free(wallList);
    free(freeList);
}