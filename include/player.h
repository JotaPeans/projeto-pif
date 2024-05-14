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

int playerWon(Player player, NodeFree *listaFree);

int canMove(Player player, int key, Node *wallList);

void initGame(Wall walls[], int tam_y);