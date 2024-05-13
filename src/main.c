/**
 * main.c
 * Created on May, 2024
 * Authors: João Pedro Fontes Ferreira, Larissa Sobrinho, Clara Machado
*/

#include <string.h>
#include <stdlib.h>

#include "player.h"
#include "screen.h"
#include "keyboard.h"
#include "commands.h"
#include "timer.h"

void printString(int x, int y, char *string, int color);
void readWalls(const char* filename, Wall walls[], int level, int *screenSize);
int getLevelsLength(const char* filename);

int main() {
    char *file = "levels.txt";
    int level = 1;
    int levels = getLevelsLength(file);
    int key = 0;

    screenInit(1, levels + 2);
    keyboardInit();
    timerInit(60);

    for(int i = 1; i <= levels; i++) {
        char str[10];
        if(i < 10)
            sprintf(str, "Nível 0%d", i);
        else
            sprintf(str, "Nível %d", i);

        printString(MINX + 2, MINY + i, str, YELLOW);

    }

    while (key != 32) {
        if (keyhit()) {
            key = readch();
            screenUpdate();
        }

        if (timerTimeOver() == 1) {
            if (key == up && level > 1)
                level--;
            
            else if (key == down && level < levels) 
                level++;

            key = 0;

            for(int i = 1; i <= levels; i++) {
                printString(MAXX - 4, MINY + i, "  ", 0);            
            }
            printString(MAXX - 4, MINY + level, "⬅️", YELLOW);            

            screenUpdate();
        }
    }


    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    Wall *walls = (Wall *) malloc(100 * sizeof(Wall));
    int screenSize = 0;
    
    readWalls(file, walls, level, &screenSize);

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

int getLevelsLength(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return 0;
    }

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';  // Substitui '\n' por '\0'
        }
        
        if(line[0] == '[')
            continue;

        else if(line[4] == '[')
            count++;
    }

    return count;
}