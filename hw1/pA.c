#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct queue {
    int *arr;
    int front, rear;
    size_t MAX_QUEUE_SIZE;
}queue;
typedef struct stack {
    int *arr;
    int top;
    size_t MAX_STACK_SIZE;
}stack;

queue* initQueue(size_t size);
void enqueue(queue *q, int value);
void popQueue(queue *q);
int frontQueue(queue *q);
bool isQueueEmpty(const queue *q);
void deleteQueue(queue *q);
queue* queueFull(queue *q);

stack* initStack(size_t size);
void pushStack(stack *s, int value);
void popStack(stack *s);
int topStack(stack *s);
bool isStackEmpty(stack *s);
void deleteStack(stack *s);
void stackFull();

void nearestSmaller(int arr[], int distance[], int size);

int main(void) {
    // setvbuf(stdout, NULL, _IONBF, 0);

    int N;
    while (scanf("%d", &N) != EOF) {
        int arr[N], distance[N];
        for (int i = 0; i < N; i++) {
            scanf("%d", &arr[i]);
        }
        nearestSmaller(arr, distance, N);
        queue *que = initQueue(N);
        for (int i = 0; i< N; i++) {
            printf("%d", distance[i]);
            i != N-1 ? printf(" ") : printf("\n");
            if (distance[i] != -1) {
                enqueue(que, distance[i]);
            }
        }
        if (isQueueEmpty(que)) {
            printf("EMPTY\n");
        } else {
            while (!isQueueEmpty(que)) {
                printf("%d ", frontQueue(que));
                popQueue(que);
            }
            printf("\n");
        }
        deleteQueue(que);
        que = NULL;
    }
    return 0;
}
void nearestSmaller(int arr[], int distance[], const int size) {
    stack *s = initStack(size);
    for (int i = size -1; i >=0; i--) {
        while (!isStackEmpty(s) && arr[topStack(s)] > arr[i]) {
            /*stack is not empty and arr.at(stack.top) is bigger than arr[i]*/
            distance[topStack(s)] = topStack(s) - i;
            popStack(s);
        }
        pushStack(s, i);
    }
    while (!isStackEmpty(s)) {
        distance[topStack(s)] = -1;
        popStack(s);
    }
    deleteStack(s);
    s = NULL;
}

queue* initQueue(const size_t size) {
    queue* newQueue = malloc(sizeof(queue));
    if (newQueue == NULL) {
        perror("malloc queue failed!!");
        exit(1);
    }
    newQueue->arr = malloc(size * sizeof(int));
    if (newQueue->arr == NULL) {
        perror("malloc array failed");
        free(newQueue);
        exit(1);
    }
    newQueue->front = 0;
    newQueue->rear = -1;
    newQueue->MAX_QUEUE_SIZE = size;
    return newQueue;
}
void enqueue(queue *q, const int value) {
    if (q == NULL || q->arr == NULL) {
        perror("queue ptr is null!!\n");
        exit(1);
    }
    if (q->rear == q->MAX_QUEUE_SIZE - 1) {
        printf("Queue full!!\n");
        exit(1);
    }
    ++q->rear;
    q->arr[q->rear] = value;
}
void popQueue(queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty!!\n");
        exit(1);
    }
    ++q->front;
}
int frontQueue(queue *q) {
    if (q == NULL || q->arr == NULL) {
        perror("queue ptr is null!!\n");
        exit(1);
    }
    if (isQueueEmpty(q)) {
        printf("Queue is empty!!\n");
        exit(1);
    }
    return q->arr[q->front];
}
bool isQueueEmpty(const queue *q) {
    if (q == NULL || q->arr == NULL) {
        perror("queue ptr is null!!\n");
        exit(1);
    }
    return q->rear < q->front;
}
void deleteQueue(queue *q) {
    free(q->arr);
    free(q);
}
stack* initStack(const size_t size) {
    stack* newStack = malloc(sizeof(stack));
    if (newStack == NULL) {
        perror("malloc stack failed!!\n");
        exit(1);
    }
    newStack->arr = malloc(size * sizeof(int));
    if (newStack->arr == NULL) {
        perror("malloc array failed");
        free(newStack);
        exit(1);
    }
    newStack->top = -1;
    newStack->MAX_STACK_SIZE = size;
    return newStack;
}
void pushStack(stack *s , const int value) {
    if (s == NULL || s->arr == NULL) {
        perror("stack ptr is null!!");
        exit(1);
    }
    if (s->top == s->MAX_STACK_SIZE - 1) {
        printf("Stack full!!");
        exit(1);
    }
    ++s->top;
    s->arr[s->top] = value;
}
void popStack(stack *s) {
    if (s == NULL || s->arr == NULL) {
        perror("stack ptr is null!!\n");
        exit(1);
    }
    if (s->top == -1) {
        printf("Stack is empty!!\n");
        exit(1);
    }
    --s->top;
}
int topStack(stack *s) {
    if (s == NULL || s->arr == NULL) {
        perror("stack ptr is null!!\n");
        exit(1);
    }
    return s->arr[s->top];
}
bool isStackEmpty(stack *s) {
    if (s == NULL || s->arr == NULL) {
        perror("stack ptr is null!!\n");
        exit(1);
    }
    if (s->top == -1) return true;
    return false;
}
void deleteStack(stack *s) {
    free(s->arr);
    free(s);
}
