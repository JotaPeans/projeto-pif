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


int main() { // jogador escolhe o nível
    char *file = "levels.txt";
    int level = 1;
    int levels = getLevelsLength(file);
    int key = 0;

    screenInit(1, levels + 2, 18); // inicia a tela bonitinha
    keyboardInit(); // inicia o teclado
    timerInit(60); // padrão


    while (key != 10) { // seletor de nível

        for(int i = 1; i <= levels; i++) { // printa os níveis na tela
            char str[10];
            if(i < 10)
                sprintf(str, "Nível 0%d", i);
            else
                sprintf(str, "Nível %d", i);

            printString(MINX + 2, MINY + i, str, YELLOW); // chama a função e printa

        }

        if (keyhit()) { //verifica a tecla clicada
            key = readch();
            screenUpdate();
        }

        if (timerTimeOver() == 1) {
            if (key == up && level > 1) // movimentação do jogador na seleção de níveis
                level--; // level atual selecionado
            
            else if (key == down && level < levels) 
                level++;


            for(int i = 1; i <= levels; i++) { // quando mudar a setinha de selecionar, apagar a passada
                printString(MAXX - 4, MINY + i, "  ", 0);   // miny = 1           
            }
            printString(MAXX - 4, MINY + level, "⬅️", YELLOW);         

            key = 0; // enter

            screenUpdate(); // atualiza a tela
        }
    }

    screenDestroy(); //ao pressionar o enter, inciia o jogo e apaga as telas inciais
    keyboardDestroy();
    timerDestroy();

    Wall *walls = (Wall *) malloc(100 * sizeof(Wall)); // alocando memória para as paredes
    Queue *hunterCommandsQueue = (Queue *) malloc(100 * sizeof(Queue)); // queue = lista que insere no final e tira do começo

    int screenSize = 0; // tamanho padrão do jogo
    
    readWalls(file, walls, level, &screenSize); //abre o arquivo 

    initGame(walls, hunterCommandsQueue, screenSize);

    free(walls);

    return 0;
}

void printString(int x, int y, char *string, int color) {
    screenSetColor(color, DARKGRAY);
    screenGotoxy(x, y);
    printf("%s", string);
}


void readWalls(const char* filename, Wall walls[], int level, int *screenSize) { // transforma os niveis em uma lista
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

        int len = strlen(line);
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

int getLevelsLength(const char* filename) { // checar a quantidade de níveis
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