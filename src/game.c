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

void initGame(Wall walls[], Queue *hunterCommandsQueue, int tam_y) {
    srand(time(NULL));
    
    int wallsSize = 0, playerMoves = 0, minPlayerMovesToHunter = 4;

    int key = 0, hunterKey = 0, ticksCount = 0;
    int won;

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

    Player hunter;
    hunter.incX = incX;
    hunter.incY = incY;

    Node *wallList = NULL;
    NodeFree *freeList = NULL;
    
    buildWall(&wallList, &freeList, walls, wallsSize);
    
    screenUpdate();

    while (key != 10) {
        if (keyhit() && key == 0) {
            key = readch();

            if((key == up || key == down || key == left || key == right) && canMove(player, key, wallList)) {
                pushQueue(&hunterCommandsQueue, key);
                playerMoves++;
            }

            if(playerMoves == minPlayerMovesToHunter) {
                hunter.body = "🗡️";
                hunter.x = 4;
                hunter.y = MAXY-2;
            }
            
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

            if(
                ticksCount % 10 == 0 && 
                hunterKey == 0 && 
                playerMoves >= minPlayerMovesToHunter && 
                queueLength(hunterCommandsQueue) > 0
            ) {
                hunterKey = pollQueue(&hunterCommandsQueue);
            }

            if(hunter.x && hunter.y) {
                hunter.prevY = hunter.y;
                hunter.prevX = hunter.x;
            }

            if(hunterKey == up && canMove(hunter, hunterKey, wallList)) {
                hunter.y -= hunter.incY;
            }
            else if(hunterKey == down && canMove(hunter, hunterKey, wallList)) {
                hunter.y += hunter.incY;
            }
            else if(hunterKey == left && canMove(hunter, hunterKey, wallList)) {
                hunter.x -= hunter.incX;
            }
            else if(hunterKey == right && canMove(hunter, hunterKey, wallList)) {
                hunter.x += hunter.incX;
            }
            else {
                hunterKey = 0;
            }

            movePlayerOnMap(player, freeList, colors[randomColorIndex]);
            moveHunterOnMap(hunter, colors[randomColorIndex]);

            won = playerWon(player, freeList);
            
            if(hunter.x && hunter.y) {
                if(player.x == hunter.x && player.y == hunter.y) {
                    break;
                }
            }

            screenUpdate();

            if(won) {
                usleep(300 * 1000);
                break;
            }
        }

        ticksCount++;
    }


    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    free(wallList);
    free(freeList);
}