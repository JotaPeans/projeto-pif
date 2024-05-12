typedef struct wall {
    double x; // Coordenadas
    double y;
} Wall;


typedef struct free {
    double x; // Coordenadas
    double y;
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
    double x; // Coordenadas
    double y;

    char *body;

    double prevX; // Coordenadas anteriores
    double prevY;

    double incX; // Aceleração
    double incY;
} Player;


void pushWall(Node **lista, Wall wall);

void pushFree(NodeFree **lista, Free wall);

void buildWall(Node **lista, NodeFree **listaFree, Wall walls[], int wallsSize);

int getFreeListSize(NodeFree *listaFree);

void movePlayerOnMap(Player player, NodeFree *listaFree);

int playerWon(Player player, NodeFree *listaFree);

int canMove(Player player, int key, Node *wallList);

void initGame(Wall walls[]);