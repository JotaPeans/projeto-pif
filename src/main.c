/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define up 65
#define down 66
#define left 68
#define right 67

int x = 34, y = 12;
int incX = 2, incY = 1;

typedef struct player {
    double x; // Coordenadas
    double y;

    char *body;

    double prevX; // Coordenadas anteriores
    double prevY;

    double incX; // Aceleração
    double incY;
} Player;

void cleanScreen() {
    int lim = 0;

    for (int i = 2; i < MAXY; i++){ // Começar a apagar a partir da linha 8 (logo abaixo do HIGH SCORE)
        screenGotoxy(MINX+1, i);

        for (int j = 0; j < MAXX - 3; j++){
            printf(" ");
        }
    }
}

void printPlayer(Player player, char *string, int color) {
    screenSetColor(color, DARKGRAY);

    // cleanScreen();

    screenGotoxy(player.x, player.y);
    printf("%s", string);

    if(player.x != player.prevX || player.y != player.prevY) {
        screenGotoxy(player.prevX, player.prevY);
        printf("🟧");
    }
}


void printString(int x, int y, char *string, int color) {
    screenSetColor(color, DARKGRAY);
    screenGotoxy(x, y);
    printf("%s", string);
}


int cantMoveX(Player player, int key) {
    return (key != up && key != down) && (player.x >= (MAXX - strlen(player.body) + 1) || player.x <= MINX);
}

int cantMoveY(Player player, int key) {
    return (key != left && key != right) && (player.y >= MAXY-1 || player.y <= MINY+1);
}

int canMoveX(Player player, int key, int dir) {
    if(dir == 1)
        return player.x <= (MAXX - strlen(player.body));
    else
        return player.x >= MINX + 2;
}

int canMoveY(Player player, int key, int dir) {
    if(dir == 1)
        return player.y <= MAXY - 2;
    else
        return player.y >= MINY + 2;
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
    
    screenInit(1);
    keyboardInit();
    timerInit(60);

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
            printPlayer(player, player.body, 2);

            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}