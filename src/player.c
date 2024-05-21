#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "player.h"
#include "screen.h"
#include "commands.h"

int getFreeListSize(NodeFree *listaFree) {
    NodeFree *aux = listaFree;
    int count = 1;

    while(aux->free.x) {
        if(aux->next != NULL) {
            aux = aux->next;
            count++;
        }
        else
            break;
    }

    return count;
}


void movePlayerOnMap(Player player, NodeFree *listaFree, char *color) {
    NodeFree *aux = listaFree;

    screenGotoxy(player.x, player.y);
    printf("%s", player.body);

    if(player.x != player.prevX || player.y != player.prevY) {
        screenGotoxy(player.prevX, player.prevY);
        printf("%s", color);
        
        while(aux->free.x) {
            if(player.x == aux->free.x && player.y == aux->free.y) {
                aux->free.touched = 1;
            }

            if(aux->free.x == 4 && aux->free.y == MAXY-2) {
                aux->free.touched = 1;
            }

            if(aux->next != NULL)
                aux = aux->next;
            else
                break;
        }
    }
}

void moveHunterOnMap(Player hunter, char *color) {
    if(hunter.x && hunter.y) {
        screenGotoxy(hunter.x, hunter.y);
        printf("%s", hunter.body);

        if(hunter.x != hunter.prevX || hunter.y != hunter.prevY) {
            screenGotoxy(hunter.prevX, hunter.prevY);
            printf("%s", color);
        }
    }
}

int playerWon(Player player, NodeFree *listaFree) {
    NodeFree *aux = listaFree;
    int touched = 0;

    while(aux->free.x) {
        if(aux->free.touched == 1) 
            touched++;

        if(aux->next != NULL)
            aux = aux->next;
        else
            break;
    }

    if(touched == getFreeListSize(listaFree))
        return 1;
    else
        return 0;
}


int canMove(Player player, int key, Node *wallList) {
    Node *aux = wallList;

    while(aux->wall.x) {
        if(key == right) {
            if(player.y == aux->wall.y && player.x+2 == aux->wall.x) {
                return 0;
            }
        }

        else if(key == left) {
            if(player.y == aux->wall.y && player.x-2 == aux->wall.x) {
                return 0;
            }
        }

        else if(key == up) {
            if(player.x == aux->wall.x && player.y-1 == aux->wall.y) {
                return 0;
            }
        }

        else if(key == down) {
            if(player.x == aux->wall.x && player.y+1 == aux->wall.y) {
                return 0;
            }
        }

        if(aux->next != NULL)
            aux = aux->next;
        else
            break;
    }

    if(key == right)
        return player.x <= (MAXX - strlen(player.body));

    else if(key == left)
        return player.x >= MINX + 2;

    else if(key == down)
        return player.y <= MAXY - 2;

    else if(key == up)
        return player.y >= MINY + 2;

    return 1;
}

void pushQueue(Queue **queue, int command) {
    Queue *aux, *new = (Queue *) malloc(sizeof(Queue));

    new->command = command;
    new->next = NULL;
    
    if(*queue == NULL) {
        *queue = new;
        return;
    }
    
    aux = *queue;

    while(aux->next != NULL) {
        aux = aux->next;
    }

    new->next = aux->next;
    aux->next = new;
}

int pollQueue(Queue **queue) {
    (*queue) = (*queue)->next;

    int value = (*queue)->command;

    return value;
}

int queueLength(Queue *queue) {
    Queue *aux = (Queue *) malloc(sizeof(Queue));
    aux = queue;
    int count = 0;

    while(aux->next != NULL) {
        aux = aux->next;
        count++;
    }
    return count;
}

void printQueue(Queue *queue) {
    Queue *aux = (Queue *) malloc(sizeof(Queue));
    aux = queue;

    while(aux->next != NULL) {
        aux = aux->next;
        printf("%d\n", aux->command);
    }
}