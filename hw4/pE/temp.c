

#define MAX_BUCKET_SIZE 100000

typedef struct ListNode ListNode;
struct ListNode {
    Data data;
    ListNode *next;
};
ListNode *initNode(const Data data) {
    ListNode *node = malloc(sizeof(ListNode));
    node->data = data;
    node->next = NULL;
    return node;
}
ListNode *insertNode(ListNode *head, const Data data) {
    ListNode dummy, *curr = &dummy;
    dummy.next = head;

    ListNode *node = initNode(data);
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = node;
    return dummy.next;
}
ListNode *deleteNode(ListNode *head, const int key) {
    ListNode dummy, *curr = &dummy;
    dummy.next = head;
    while (curr->next != NULL) {
        if (curr->next->data.key == key) {
            ListNode *temp = curr->next;
            curr->next = temp->next;
            free(temp);
            break;
        }
        curr = curr->next;
    }
    return dummy.next;
}
void freeList(ListNode *head) {
    while (head != NULL) {
        ListNode *temp = head;
        head = head->next;
        free(temp);
    }
}

ListNode *bucket[MAX_BUCKET_SIZE] = {NULL};

int hash(const int key) {
    return key % MAX_BUCKET_SIZE;
}
void insert(Data *data) {
    const int idx = hash(data->key);
    bucket[idx] = insertNode(bucket[idx], *data);
}
void remove(int key) {
    const int idx = hash(key);
    bucket[idx] = deleteNode(bucket[idx], key);
}
int search(int key) {
    ListNode const *ptr = bucket[hash(key)];
    while (ptr != NULL) {
        if (ptr->data.key == key) return ptr->data.value;
        ptr = ptr->next;
    }
    return -1;
}