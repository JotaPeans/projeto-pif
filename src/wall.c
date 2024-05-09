#include <string.h>
#include <stdlib.h>

#include "screen.h"
#include "wall.h"

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

void printWall(Node **lista) {
    Wall wall;
    int size = strlen("⬜");

    screenSetColor(BLUE, DARKGRAY);
    for(int x = 2; x < MAXX - size; x+=size + 1) {
        for(int y = 2; y < MAXY - 1; y+=size - 1) {
            wall.x = x;
            wall.y = y;
            pushWall(lista, wall);

            screenGotoxy(x, y);
            printf("⬜");
        }
    }
}

void showData(Node *lista) {
    Node *aux = lista;

    while(aux->next != NULL) {
        printf("%f - %f\n", aux->wall.x, aux->wall.y);
        aux = aux->next;
    }
}