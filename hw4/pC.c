#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Position Position;
struct Position {
    int i, j;
};
typedef struct Queue Queue;
struct Queue {
    Position *arr;
    int front, rear;
    int MAX_SIZE, size;
};
Queue* initQueue(int maxQueSize);
void freeQueue(Queue* que);
bool isEmptyQueue(Queue* que);
bool isFullQueue(Queue* que);
void pushQueue(Queue* que, Position newPosition);
void popQueue(Queue* que);
Position frontQueue(Queue* que);

typedef struct ListNode ListNode;
struct ListNode {
    Position position;
    ListNode *next;
};
ListNode* insertList(ListNode *head, Position newPosition);

int leaveTheMaze(char **maze, Position startPos, ListNode *portals[26], int rowSize, int colSize);

int main() {
    while (true) {
        int m, n;
        /*
         * maze[m+2][n+2]
         * visited[m+2][n+2]
         */
        if (scanf("%d %d", &m, &n) == EOF) break;
        getchar();
        char **maze = malloc((m + 2) * sizeof(char *));
        for (int i = 0; i < m + 2; i++) {
            maze[i] = malloc((n + 2) * sizeof(char));
            for (int j = 0; j < n + 2; j++) maze[i][j] = '#';
        }
        Position start = (Position){-1, -1};
        ListNode *portals[26] = {NULL};

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                scanf(" %c", &maze[i][j]);
                if (maze[i][j] == 'B') start = (Position){i, j};
                else if (isupper(maze[i][j]) && maze[i][j] != 'B' && maze[i][j] != 'E') {
                    const int idx = maze[i][j] - 'A';
                    portals[idx] = insertList(portals[idx], (Position){i, j});
                }
            }
        }
        printf("%d\n", leaveTheMaze(maze, start, portals,m+2, n+2));
        for (int i = 0; i < m + 2; i++) free(maze[i]);
        free(maze);
    }
    return 0;
}
Queue* initQueue(const int maxQueSize) {
    Queue *que = malloc(sizeof(Queue));
    que->arr = malloc(maxQueSize * sizeof(Position));
    que->front = 0;   // front points to the first element
    que->rear = 0;    // rear points to the next pos to be placed
    que->size = 0;
    que->MAX_SIZE = maxQueSize;
    return que;
}
void freeQueue(Queue *que) {
    if (!que) return;
    free(que->arr);
    free(que);
}
bool isEmptyQueue(Queue *que) {
    if (!que) {
        perror("Invalid queue pointer\n");
        return true;
    }
    return que->size == 0;
}

bool isFullQueue(Queue *que) {
    if (!que) {
        perror("Invalid queue pointer\n");
        return true;
    }
    return que->size == que->MAX_SIZE;
}
void pushQueue(Queue *que, Position newPosition) {
    if (isFullQueue(que)) return;
    que->arr[que->rear] = newPosition;
    que->rear = (que->rear + 1) % que->MAX_SIZE;
    que->size++;
}
Position frontQueue(Queue *que) {
    if (isEmptyQueue(que)) {
        fprintf(stderr, "frontQueue(): empty queue access\n");
        return (Position){-1, -1};
    }
    return que->arr[que->front];
}
void popQueue(Queue *que) {
    if (isEmptyQueue(que)) return;
    que->front = (que->front + 1) % que->MAX_SIZE;
    que->size--;
}

ListNode* insertList(ListNode *head, Position newPosition) {
    ListNode dummy, *curr = &dummy;
    dummy.next = head;

    ListNode *newNode = malloc(sizeof(struct ListNode));
    newNode->position = newPosition;
    newNode->next = NULL;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newNode;

    return dummy.next;
}
int leaveTheMaze(char **maze, const Position startPos, ListNode *portals[26], const int rowSize, const int colSize) {
    bool **visited = malloc(rowSize * sizeof(bool *));
    for (int i = 0; i < rowSize; i++) {
        visited[i] = malloc(colSize * sizeof(bool));
        for (int j = 0; j < colSize; j++) visited[i][j] = false;
    }
    bool visited_portals[26] = {false};

    Queue *que = initQueue(rowSize*colSize);
    pushQueue(que, startPos);
    visited[startPos.i][startPos.j] = true;
    int step = 0;

    int di[4] = {-1, 0, 1, 0};
    int dj[4] = {0, 1, 0, -1};
    while (!isEmptyQueue(que)) {
        int queSize = que->size;
        while (queSize--) {
            Position curr = frontQueue(que); popQueue(que);
            if (maze[curr.i][curr.j] == 'E') {
                for (int j = 0; j < rowSize; j++) free(visited[j]);
                free(visited);
                freeQueue(que);
                return step;
            }
            char c = maze[curr.i][curr.j];
            if (isupper(c) && c != 'B' && c != 'E') {
                const int idx = maze[curr.i][curr.j] - 'A';
                if (!visited_portals[idx]) {
                    visited_portals[idx] = true;
                    for (ListNode *p = portals[idx]; p != NULL; p = p->next) {
                        if (!visited[p->position.i][p->position.j]) {
                            visited[p->position.i][p->position.j] = true;
                            pushQueue(que, p->position);
                        }
                    }
                }
            }
            for (int k = 0; k<4; k++) {
                int ni = curr.i + di[k];
                int nj = curr.j + dj[k];
                if (maze[ni][nj] != '#' && !visited[ni][nj]) {
                    visited[ni][nj] = true;
                    pushQueue(que, (Position){ni, nj});
                }
            }
        }
        step++;
    }
    // free RAM
    for (int i = 0; i < rowSize; i++)   free(visited[i]);
    free(visited);
    freeQueue(que);

    return -1;
}