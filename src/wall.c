#include <string.h>
#include <stdlib.h>

#include "screen.h"
#include "player.h"

void pushWall(Node **lista, Wall wall) {
    Node *aux, *new = (Node *) malloc(sizeof(Node));

    new->wall = wall;
    new->next = NULL;
    
    if(*lista == NULL) {
        *lista = new;
        return;
    }
    
    aux = *lista;

    while(aux->next != NULL) {
        aux = aux->next;
    }

    new->next = aux->next;
    aux->next = new;
}

void pushFree(NodeFree **lista, Free free) {
    NodeFree *aux, *new = (NodeFree *) malloc(sizeof(NodeFree));

    new->free = free;
    new->next = NULL;
    
    if(*lista == NULL) {
        *lista = new;
        return;
    }
    
    aux = *lista;

    while(aux->next != NULL) {
        aux = aux->next;
    }

    new->next = aux->next;
    aux->next = new;
}

void buildWall(Node **lista, NodeFree **listaFree, Wall walls[], int wallsSize) {
    Wall wall;
    Free spaceFree;
    int size = strlen("⬜"); // 3

    int iterator = 0;
    
    while(iterator < wallsSize) {
        wall.x = walls[iterator].x;
        wall.y = walls[iterator].y;
        pushWall(lista, wall);
        screenGotoxy(wall.x, wall.y);
        printf("⬜");
        iterator++;
    }

    screenSetColor(BLUE, DARKGRAY);
    for(int x = 2; x < MAXX - 2; x+=2) {
        for(int y = 2; y < MAXY; y+=1) {
            
            if(x == MINX + 1 || x == MAXX - (size + 1) || y == MINY + 1 || y == MAXY - 1) {
                wall.x = x;
                wall.y = y;
                pushWall(lista, wall);
                screenGotoxy(x, y);
                printf("⬜");
            }
            else {
                int searchIterator = 0;
                int founded = 0;

                while(searchIterator < wallsSize) {                    
                    if(x == walls[searchIterator].x && y == walls[searchIterator].y) {
                        founded = 1;
                        break;
                    }

                    searchIterator++;
                }

                if(!founded) {
                    spaceFree.x = x;
                    spaceFree.y = y;
                    spaceFree.touched = 0;
                    pushFree(listaFree, spaceFree);
                }

            }
        }
    }
}