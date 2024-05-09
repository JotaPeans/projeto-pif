typedef struct wall {
    double x; // Coordenadas
    double y;
} Wall;

typedef struct node {
    Wall wall;
    struct node *next;
} Node;

void pushWall(Node **lista, Wall wall);

void printWall(Node **lista);

void showData(Node *lista);