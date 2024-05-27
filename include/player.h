typedef struct wall {
    int x; // Define a coordenada/localização das paredes
    int y;
} Wall;


typedef struct free {
    int x; // Coordenadas de espaços livres a serem preenchidos
    int y;
    int touched; // espaço vazio preenchido
} Free;


typedef struct node {
    Wall wall; // lista que junta todas as paredes
    struct node *next;
} Node;

typedef struct queue { //lista de comandos do player (como movimentação: cima, baixo, lado)
    int command; // comandos que ele já fez
    struct queue *next;
} Queue;

typedef struct nodeFree { // lista de espaços livres
    Free free;
    struct nodeFree *next;
} NodeFree;


typedef struct player {
    int x; // Coordenadas de localização do player (atual)
    int y;

    char *body; // Corpo do player

    int prevX; // Coordenadas anteriores (onde o player já passou)
    int prevY;

    int incX; // Aceleração do jogador (iniciativa de movimento)
    int incY;
} Player;


void pushWall(Node **lista, Wall wall); //colocar uma parede numa lista de paredes

void pushFree(NodeFree **lista, Free wall); // colocar um espaço vazio numa lista de espaço vazio

void buildWall(Node **lista, NodeFree **listaFree, Wall walls[], int wallsSize); // construção das paredes

int getFreeListSize(NodeFree *listaFree); // tamanho da lista de espaços livres

void movePlayerOnMap(Player player, NodeFree *listaFree, char *color); // função para mover o player

void moveHunterOnMap(Player hunter, char *color); // função pra mover o hunter

int playerWon(Player player, NodeFree *listaFree); // verifica se o player ganhou

int canMove(Player player, int key, Node *wallList); //chegar se o player pode se mover

void initGame(Wall walls[], Queue *hunterCommandsQueue, int tam_y); // função principal = abre a tela, mapa do jogo, roda o jogo

void pushQueue(Queue **queue, int command); // colocar um comando na fila de comandos do hunter

int pollQueue(Queue **queue); // pegar um elemento que está na ordem na fila

int queueLength(Queue *queue); // tamanho da fila (quantos elementos/comandos na fila)

void printQueue(Queue *queue); // função para o tamanho da lista de paredes

void endGameMessage(char *string, int color); // printa na tela "you win" ou "you lose"