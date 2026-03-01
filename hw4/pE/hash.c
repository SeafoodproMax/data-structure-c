#include <stdlib.h>

#include "../pD/hash.h"

#define MAX_BUCKET_SIZE 100000


typedef struct ListNode {
    Data data;
    struct ListNode *next;
} ListNode;

// Hash Table buckets
static ListNode *bucket[MAX_BUCKET_SIZE] = {NULL};

// 建立節點
static ListNode *initNode(const Data data) {
    ListNode *node = malloc(sizeof(ListNode));
    if (!node) exit(1); // malloc 失敗直接結束
    node->data = data;
    node->next = NULL;
    return node;
}

// 插入節點 (尾插)
static ListNode *insertNode(ListNode *head, const Data data) {
    if (head == NULL) {
        return initNode(data);
    }
    ListNode *curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = initNode(data);
    return head;
}

// 刪除節點
static ListNode *deleteNode(ListNode *head, const int key) {
    if (head == NULL) return NULL;
    ListNode dummy = {0};
    dummy.next = head;
    ListNode *curr = &dummy;

    while (curr->next != NULL) {
        if (curr->next->data.key == key) {
            ListNode *temp = curr->next;
            curr->next = temp->next;
            free(temp);
            break; // 一定 break，題目保證 key 不重複
        }
        curr = curr->next;
    }
    return dummy.next;
}

// Hash 函數（題目 key ≥ 0）
static int hash(const int key) {
    return key % MAX_BUCKET_SIZE;
}

// 插入資料
void insert(Data *data) {
    const int idx = hash(data->key);
    bucket[idx] = insertNode(bucket[idx], *data);
    free(data); // 題目 main.c 用 malloc 建立 Data，插入後釋放
}

// 刪除資料
void remove(int key) {
    const int idx = hash(key);
    bucket[idx] = deleteNode(bucket[idx], key);
}

// 搜尋資料
int search(int key) {
    const int idx = hash(key);
    const ListNode *ptr = bucket[idx];
    while (ptr != NULL) {
        if (ptr->data.key == key)
            return ptr->data.value;
        ptr = ptr->next;
    }
    return -1;
}