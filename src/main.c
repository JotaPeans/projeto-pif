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

void readWalls(const char* filename, Wall walls[], int level) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char line[256];
    int count = 0;
    int i = 0;
    
    while (fgets(line, sizeof(line), file)) {
        if(line[0] == '{' || line[0] == '}')
            continue;

        if(line[4] == '{') {
            if(count != level){
                count++;
                continue;
            }
            else {
                continue;
            }
        };
        
        if(line[8] == '{' && count == level) {
            sscanf(line, "        {%d, %d}", &walls[i].x, &walls[i].y );
            i++;
            continue;
        }

        if(line[4] == '}' && count == level)
            break;
    }

    fclose(file);
}

int main() {
    int level = 2;

    // screenDefaultInit(0);
    // keyboardInit();
    // timerInit(60);

    // keyboardDestroy();
    // screenDestroy();
    // timerDestroy();

    Wall *walls = (Wall *) malloc(100 * sizeof(Wall));
    
    readWalls("levels.txt", walls, level);

    // int i = 0;
    // while (1) {
    //     int x = levels[level - 1][i].x;
    //     if(x) {
    //         walls[i] = levels[level - 1][i];
    //         i++;
    //     }
    //     else break;
    // }

    initGame(walls, 0);

    free(walls);

    return 0;
}