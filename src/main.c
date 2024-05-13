/**
 * main.c
 * Created on May, 2024
 * Authors: João Pedro Fontes Ferreira, Larissa Sobrinho, Clara Machado
*/

#include <string.h>
#include <stdlib.h>

#include "player.h"
#include "screen.h"

void printString(int x, int y, char *string, int color);
void readWalls(const char* filename, Wall walls[], int level, int *screenSize);

int main() {
    int level = 7;

    // screenDefaultInit(0);
    // keyboardInit();
    // timerInit(60);

    // keyboardDestroy();
    // screenDestroy();
    // timerDestroy();

    Wall *walls = (Wall *) malloc(100 * sizeof(Wall));
    int screenSize = 0;
    
    readWalls("levels.txt", walls, level, &screenSize);

    initGame(walls, screenSize);

    free(walls);

    return 0;
}


void printString(int x, int y, char *string, int color) {
    screenSetColor(color, DARKGRAY);
    screenGotoxy(x, y);
    printf("%s", string);
}


void readWalls(const char* filename, Wall walls[], int level, int *screenSize) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char line[256];
    int count = 0;
    int i = 0;
    int size;
    
    while (fgets(line, sizeof(line), file)) {

        size_t len = strlen(line);
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';  // Substitui '\n' por '\0'
        }
        
        if(line[0] == '[')
            continue;

        else if(line[4] == '[') {
            if(count != level){
                count++;

                if(count == level) {
                    sscanf(line, "    [ size = %d", &size);
                    printf("s = %d\n", size);
                    *screenSize = size; 
                    continue;
                }

                continue;
            }
        }
        
        else if(strncmp(line, "        {", 9) == 0 && count == level) {
            sscanf(line, "        {%d, %d},", &walls[i].x, &walls[i].y );
            i++;
            continue;
        }

        else if(line[4] == ']' && count == level)
            break;
    }

    fclose(file);
}