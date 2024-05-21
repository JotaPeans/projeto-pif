typedef struct wall {
    int x; // Coordenadas
    int y;
} Wall;


typedef struct free {
    int x; // Coordenadas
    int y;
    int touched;
} Free;


typedef struct node {
    Wall wall;
    struct node *next;
} Node;

typedef struct queue {
    int command;
    struct queue *next;
} Queue;

typedef struct nodeFree {
    Free free;
    struct nodeFree *next;
} NodeFree;


typedef struct player {
    int x; // Coordenadas
    int y;

    char *body;

    int prevX; // Coordenadas anteriores
    int prevY;

    int incX; // Aceleração
    int incY;
} Player;


void pushWall(Node **lista, Wall wall);

void pushFree(NodeFree **lista, Free wall);

void buildWall(Node **lista, NodeFree **listaFree, Wall walls[], int wallsSize);

int getFreeListSize(NodeFree *listaFree);

void movePlayerOnMap(Player player, NodeFree *listaFree, char *color);

void moveHunterOnMap(Player hunter, char *color);

int playerWon(Player player, NodeFree *listaFree);

int canMove(Player player, int key, Node *wallList);

void initGame(Wall walls[], Queue *hunterCommandsQueue, int tam_y);

void pushQueue(Queue **queue, int command);

int pollQueue(Queue **queue);

int queueLength(Queue *queue);

void printQueue(Queue *queue);