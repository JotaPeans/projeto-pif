#include <string.h>

#include "player.h"
#include "screen.h"
#include "commands.h"


void cleanScreen() {
    int lim = 0;

    for (int i = 2; i < MAXY; i++) {
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