typedef struct player {
    double x; // Coordenadas
    double y;

    char *body;

    double prevX; // Coordenadas anteriores
    double prevY;

    double incX; // Aceleração
    double incY;
} Player;

void cleanScreen();

void printPlayer(Player player, int color);

int cantMoveX(Player player, int key);

int cantMoveY(Player player, int key);

int canMoveX(Player player, int key, int dir);

int canMoveY(Player player, int key, int dir);