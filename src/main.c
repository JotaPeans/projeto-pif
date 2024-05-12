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

int x = 34, y = 12;
int incX = 2, incY = 1;

typedef struct size {
    int x;
    int y;
} Size;


void printString(int x, int y, char *string, int color) {
    screenSetColor(color, DARKGRAY);
    screenGotoxy(x, y);
    printf("%s", string);
}

Size updateScreenSize(int tam_y) {
    Size size;
    size.y = tam_y;
    size.x = tam_y * 2;
    
    return size;
}

void showWallsCoords(Node *lista) {
    Node *aux = lista;

    while(aux->wall.x) {
        printf("%f - %f\n", aux->wall.x, aux->wall.y);

        if(aux->next != NULL)
            aux = aux->next;
        else
            break;
    }
}

void showFreeCoords(NodeFree *lista) {
    NodeFree *aux = lista;

    while(aux->free.x) {
        printf("%f - %f - %d\n", aux->free.x, aux->free.y, aux->free.touched);

        if(aux->next != NULL)
            aux = aux->next;
        else
            break;
    }
}


int main() {
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
    
    buildWall(&wallList, &freeList);
    
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

            movePlayer(player, freeList);

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

    return 0;
}