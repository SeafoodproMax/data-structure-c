#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX_QUEUE_SIZE 3000

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
typedef struct TreeNode *TreeNode;

TreeNode CreateNode(int val);
TreeNode insertNode(TreeNode root, int val);
TreeNode deleteNode(TreeNode root, int val);
TreeNode searchNode(TreeNode root, int val);
TreeNode findMin(TreeNode node);
TreeNode deleteTree(TreeNode root);
void printTree(TreeNode root);

struct Queue {
    TreeNode *arr;
    int front;
    int rear;
    size_t MAX_SIZE;
};
typedef struct Queue *Queue;

Queue initQueue(size_t maxQueSize);
void freeQueue(Queue queue);
void enqueue(Queue queue, TreeNode node);
TreeNode dequeue(Queue queue);
TreeNode frontQueue(Queue queue);
bool isEmptyQueue(Queue queue);

int main() {
    TreeNode root = NULL;
    while (true) {
        char buffer[100];
        if (fgets(buffer, 99, stdin) == NULL) {
            if (feof(stdin)) break;
            perror("Error reading input\n");
            return -1;
        }
        char option[20];
        sscanf(buffer, "%s", &option);
        if (!strncmp(option, "insert", 6)) {
            int x;
            sscanf(buffer, "%*[^ ]%d", &x);
            root = insertNode(root, x);
        }
        else if (!strncmp(option, "delete", 6)) {
            int x;
            sscanf(buffer, "%*[^ ]%d", &x);
            root = deleteNode(root, x);
        }
        else if (!strncmp(option, "exit", 6)) {
            printTree(root);
            deleteTree(root);
            root = NULL;
        }
        else perror("Invalid option\n");
    }

    return 0;
}

TreeNode CreateNode(int const val) {
    TreeNode newNode = malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
TreeNode insertNode(TreeNode root, int val) {
    if (root == NULL) return CreateNode(val);
    if (val < root->val) {
        root->left = insertNode(root->left, val);
    } else {
        root->right = insertNode(root->right, val);
    }
    return root;
}
TreeNode findMin(TreeNode node) {
    while (node!= NULL && node->left != NULL) {
        node = node->left;
    }
    return node;
}
TreeNode deleteNode(TreeNode root, int val) {
    if (root == NULL) return NULL;

    if (val < root->val) {
        root->left = deleteNode(root->left, val);
    } else if (val > root->val) {
        root->right = deleteNode(root->right, val);
    } else {
        if (root->left == NULL && root->right == NULL) {    // deg0
            free(root);
            return NULL;
        }
        else if (root-> right == NULL) {     // deg 1 with left
            TreeNode child = root->left;
            free(root);
            return child;
        }
        else if (root->left == NULL) {     // deg 1 with right
            TreeNode child = root->right;
            free(root);
            return child;
        }
        else {  // deg 2
            TreeNode successor = findMin(root->right);
            root->val = successor->val;
            root->right = deleteNode(root->right, successor->val);
        }
    }
    return root;
}
TreeNode searchNode(TreeNode root, int val) {
    if (!root)  return NULL;
    if (root->val == val)   return root;
    if (val < root->val)    return searchNode(root->left, val);
    if (val > root->val)    return searchNode(root->right, val);
}
TreeNode deleteTree(TreeNode root) {
    if (root == NULL) return NULL;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
    return NULL;
}
void printTree(TreeNode root) {
    if (root == NULL) return;
    Queue que = initQueue(MAX_QUEUE_SIZE);
    enqueue(que, root);
    while (!isEmptyQueue(que)) {
        TreeNode curr = frontQueue(que); dequeue(que);
        if (curr->left != NULL) enqueue(que, curr->left);
        if (curr->right != NULL) enqueue(que, curr->right);
        printf("%d ", curr->val);
    }
    printf("\n");
    freeQueue(que);
}
Queue initQueue(size_t const maxQueSize) {
    Queue que = malloc(sizeof(struct Queue));
    que->arr = malloc(sizeof(struct TreeNode)*maxQueSize);
    que->front = 0;
    que->rear = -1;
    que->MAX_SIZE = (size_t)maxQueSize;
    return que;
}
void freeQueue(Queue queue) {
    free(queue->arr);
    free(queue);
}
void enqueue(Queue queue, TreeNode node) {
    if (queue->rear == queue->MAX_SIZE-1) {
        perror("Queue is full\n");
        return;
    }
    queue->arr[++queue->rear] = node;
}
TreeNode dequeue(Queue queue) {
    if (isEmptyQueue(queue)) {
        perror("Queue is empty\n");
        return NULL;
    }
    return queue->arr[queue->front++];
}
TreeNode frontQueue(Queue queue) {
    if (isEmptyQueue(queue)) {
        perror("Queue is empty\n");
        return NULL;
    }
    return queue->arr[queue->front];
}
bool isEmptyQueue(Queue queue) {
    return queue->front > queue->rear;
}

