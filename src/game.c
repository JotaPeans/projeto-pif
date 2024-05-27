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

void initGame(Wall walls[], Queue *hunterCommandsQueue, int tam_y) { // tam_y= paredes (são quadrados)
    srand(time(NULL)); //semente da funções que aleatoriza os números (padrão)
    
    int wallsSize = 0, playerMoves = 0, minPlayerMovesToHunter = 4;

    int key = 0, hunterKey = 0, ticksCount = 0; //ticks= atraso na jogada do hunter
    int won; // 1 ou 0 = ganhou ou não

    char *colors[] = {
        "🟫", "🟪", "🟦", "🟩", "🟨", "🟥" //forma aleatoria pra colorirr
    };

    int randomColorIndex = rand() % 5; //randomizador de cores
    
    while (1) { //  pega o tamanho da lista de paredes
        int x = walls[wallsSize].x; // wallssize = conta quantos {  , }
        if(x) // enquanto x tiver alguma coisa, soma a quant de elementos para a parede
            wallsSize++;
        else break;
    }


    if(tam_y == 0|| tam_y < 0)
        screenDefaultInit(0);
    else
        screenInit(0, tam_y + 4, (tam_y + 4) * 2); // inicializa a tela 

    keyboardInit(); // inicializa o teclado
    timerInit(60); // timer = padrão
    
    Player player; // dados do player
    player.incX = incX;
    player.incY = incY;
    player.x = 4;
    player.y = MAXY-2;
    player.prevX = player.x;
    player.prevY = player.y;
    player.body = "⬆️";

    Player hunter; // dados do hunter
    hunter.incX = incX;
    hunter.incY = incY;

    Node *wallList = NULL;
    NodeFree *freeList = NULL;
    
    buildWall(&wallList, &freeList, walls, wallsSize);
    
    screenUpdate(); // atualiza a tela

    while (key != 10) {
        if (keyhit() && key == 0) {
            key = readch();

            if((key == up || key == down || key == left || key == right) && canMove(player, key, wallList)) {
                pushQueue(&hunterCommandsQueue, key);
                playerMoves++;
            }

            if(playerMoves == minPlayerMovesToHunter) {
                playerMoves++;
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
                ticksCount % 8 == 0 && 
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

    if(tam_y == 0|| tam_y < 0)
        screenDefaultInit(1);
    else
        screenInit(1, tam_y + 4, (tam_y + 4) * 2);

    keyboardInit();
    timerInit(60);

    if(won) {
        endGameMessage("YOU WIN!!", GREEN);
    }
    else {
        endGameMessage("YOU LOSE!!", RED);
    }

    while (key != 10) {
        if (keyhit()) 
            key = readch();
    }


    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    free(wallList);
    free(freeList);
}

void endGameMessage(char *string, int color) {
    screenSetColor(color, DARKGRAY);
    screenGotoxy((MAXX / 2) - (strlen(string) / 2), MAXY / 2 + 1);
    printf("%s", string);
    screenUpdate();
}