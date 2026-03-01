#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

// --- 設定與常數 ---
#define MAX_KEY 10005
#define MAX_DEGREE 100
#define MAX_NODES 500       // 稍微大一點以防萬一
#define SAFETY_LIMIT 1000   // 防止無窮迴圈的強制中斷點

// --- 資料結構 ---
typedef struct Node {
    int key;
    int degree;
    struct Node *parent;

    // 子節點串列 (線性雙向: Head -> ... -> Tail -> NULL)
    struct Node *childHead;
    struct Node *childTail;

    // 兄弟節點 (線性雙向: Prev <-> Next)
    struct Node *next;
    struct Node *prev;

    bool mark;
} Node;

// --- 全域變數 ---
Node *rootHead = NULL;
Node *rootTail = NULL;
Node *minNode = NULL;
Node *key_map[MAX_KEY]; // 用於 O(1) 查找

// --- 輔助函式 ---

// 安全取得 Map
Node* get_node(int key) {
    if (key >= 0 && key < MAX_KEY) return key_map[key];
    return NULL;
}

// 安全更新 Map
void update_map(int key, Node* node) {
    if (key >= 0 && key < MAX_KEY) key_map[key] = node;
}

Node* create_node(int key) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->degree = 0;
    node->parent = NULL;
    node->childHead = NULL;
    node->childTail = NULL;
    node->next = NULL;
    node->prev = NULL;
    node->mark = false;
    return node;
}

// 嚴格的線性 Append (加入 Root List 尾端)
void append_to_root(Node *node) {
    if (node == NULL) return;

    // 清理節點狀態，確保它看起來是獨立的
    node->parent = NULL;
    node->next = NULL;
    node->prev = rootTail;
    node->mark = false; // 移回 Root 後 mark 重置

    if (rootHead == NULL) {
        rootHead = node;
        rootTail = node;
    } else {
        rootTail->next = node;
        rootTail = node;
    }

    // 更新 Min
    if (minNode == NULL || node->key < minNode->key) {
        minNode = node;
    }
}

// 將 child 加入 parent 的子列表 "尾端"
void add_child(Node *parent, Node *child) {
    if (parent == NULL || child == NULL) return;

    child->parent = parent;
    child->mark = false;
    child->next = NULL;
    child->prev = parent->childTail;

    if (parent->childHead == NULL) {
        parent->childHead = child;
        parent->childTail = child;
    } else {
        parent->childTail->next = child;
        parent->childTail = child;
    }
    parent->degree++;
}

// 從線性列表移除節點 (通用)
void remove_node_linear(Node *node, Node **head, Node **tail) {
    if (node == NULL) return;

    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        *head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        *tail = node->prev;
    }

    node->prev = NULL;
    node->next = NULL;
}

// 重新掃描 Root List 找出最小值
void refresh_min() {
    minNode = NULL;
    Node *curr = rootHead;
    int guard = 0;
    while (curr != NULL) {
        if (minNode == NULL || curr->key < minNode->key) {
            minNode = curr;
        }
        curr = curr->next;

        if (++guard > SAFETY_LIMIT) break; // 防黑屏
    }
}

// --- 比較函式 (用於 qsort) ---
int compare_nodes_by_key(const void *a, const void *b) {
    Node *n1 = *(Node**)a;
    Node *n2 = *(Node**)b;
    return n1->key - n2->key;
}

// --- 核心邏輯 ---

// Consolidate: 解決作業要求的特殊合併規則
void consolidate() {
    // 1. 先把所有 Root 拿出來放到暫存陣列，清空全域 Root List
    // 這樣做最安全，不會因為邊遍歷邊修改指針導致無窮迴圈
    Node *roots[MAX_NODES];
    int count = 0;
    Node *curr = rootHead;
    int guard = 0;

    while (curr != NULL) {
        roots[count++] = curr;
        curr = curr->next;
        if (++guard > SAFETY_LIMIT) break;
    }

    // 清空
    rootHead = NULL;
    rootTail = NULL;
    minNode = NULL;

    // 2. 建立 Bucket (使用動態陣列模擬)
    // buckets[d] 存放度數為 d 的所有節點
    Node* buckets[MAX_DEGREE][MAX_NODES];
    int bucket_sizes[MAX_DEGREE] = {0};

    for (int i = 0; i < count; i++) {
        Node *n = roots[i];
        // 斷開舊連結，視為獨立樹
        n->next = NULL; n->prev = NULL; n->parent = NULL;

        int d = n->degree;
        if (d < MAX_DEGREE) {
            buckets[d][bucket_sizes[d]++] = n;
        }
    }

    // 3. 執行合併：由度數小到大處理
    // 作業規定：如果有 3 個以上相同度數，優先合併 Key 小的
    for (int d = 0; d < MAX_DEGREE - 1; d++) {
        // 當此度數還有 2 個以上節點時，持續合併
        int loop_guard = 0;
        while (bucket_sizes[d] >= 2) {
            // 排序：找出 Key 最小的兩個
            qsort(buckets[d], bucket_sizes[d], sizeof(Node*), compare_nodes_by_key);

            Node *n1 = buckets[d][0]; // 最小 (當父)
            Node *n2 = buckets[d][1]; // 次小 (當子)

            // 從 bucket[d] 移除這兩個 (將後面的往前移)
            for(int k=2; k<bucket_sizes[d]; k++) {
                buckets[d][k-2] = buckets[d][k];
            }
            bucket_sizes[d] -= 2;

            // 合併動作
            add_child(n1, n2);

            // n1 度數增加，放入下一層 bucket[d+1]
            int new_d = n1->degree;
            if (new_d < MAX_DEGREE) {
                buckets[new_d][bucket_sizes[new_d]++] = n1;
            }

            if (++loop_guard > SAFETY_LIMIT) break; // 防黑屏
        }
    }

    // 4. 重建 Root List
    // 依照 Bucket 順序 (度數小到大) 加回 Root List
    for (int d = 0; d < MAX_DEGREE; d++) {
        // 同度數內，依照原本順序(或 Key 順序，這裡 qsort 過是 key 順序)加回
        // 這樣輸出時就會自然排序好
        for (int i = 0; i < bucket_sizes[d]; i++) {
            append_to_root(buckets[d][i]);
        }
    }

    refresh_min();
}

void insert_op(int key) {
    Node *node = create_node(key);
    update_map(key, node);
    append_to_root(node);
}

void extract_min() {
    Node *z = minNode;
    if (z != NULL) {
        // 1. 將 z 的子節點 "依序" 移至 Root List 尾端
        // 先收集到陣列，避免邊遍歷邊修改導致指針亂掉
        Node *children[MAX_NODES];
        int child_cnt = 0;
        Node *curr = z->childHead;
        int guard = 0;

        while (curr != NULL) {
            children[child_cnt++] = curr;
            curr = curr->next;
            if (++guard > SAFETY_LIMIT) break;
        }

        for(int i=0; i<child_cnt; i++) {
            append_to_root(children[i]);
        }

        // 2. 從 Root List 移除 z
        remove_node_linear(z, &rootHead, &rootTail);
        update_map(z->key, NULL);

        // 3. Consolidate
        if (rootHead != NULL) {
            consolidate();
        } else {
            minNode = NULL;
        }

        free(z);
    }
}

void cut(Node *x, Node *y) {
    remove_node_linear(x, &y->childHead, &y->childTail);
    y->degree--;
    append_to_root(x);
    x->mark = false;
}

void cascading_cut(Node *y) {
    Node *z = y->parent;
    if (z != NULL) {
        if (y->mark == false) {
            y->mark = true;
        } else {
            cut(y, z);
            cascading_cut(z);
        }
    }
}

void decrease_key(int key, int val) {
    Node *x = get_node(key);
    if (x == NULL) return;

    // 先把舊的 key 從 map 移除
    update_map(x->key, NULL);

    // 更新 key
    x->key -= val;

    // 如果 key 還是正數 (不是 delete 造成的)，更新 map
    // 注意：Delete 操作時 key 會變負數，這時不要放入 map，避免之後操作錯誤
    if (x->key > -100000) {
        update_map(x->key, x);
    }

    Node *y = x->parent;
    if (y != NULL && x->key < y->key) {
        cut(x, y);
        cascading_cut(y);
    }

    if (minNode != NULL && x->key < minNode->key) {
        minNode = x;
    }
}

void delete_op(int key) {
    Node *x = get_node(key);
    if (x == NULL) return;

    // 降到極小值 (Input 最小為 1)
    // 讓它變成 -20 億左右
    int drop = x->key - (-2000000000);
    decrease_key(key, drop);
    extract_min();
}

// --- 輸出 ---

// Root 排序: Degree ASC -> Key ASC
int compare_roots(const void *a, const void *b) {
    Node *n1 = *(Node**)a;
    Node *n2 = *(Node**)b;
    if (n1->degree != n2->degree) {
        return n1->degree - n2->degree;
    }
    return n1->key - n2->key;
}

void print_heap() {
    if (rootHead == NULL) return;

    // 1. 收集所有 Root
    Node *roots[MAX_NODES];
    int count = 0;
    Node *curr = rootHead;
    int guard = 0;
    while (curr != NULL) {
        roots[count++] = curr;
        curr = curr->next;
        if (++guard > SAFETY_LIMIT) break;
    }

    // 2. 排序 Roots
    qsort(roots, count, sizeof(Node*), compare_roots);

    // 3. 輸出每一棵樹 (Level-order)
    for (int i = 0; i < count; i++) {
        Node *level_nodes[MAX_NODES];
        int level_cnt = 0;

        level_nodes[level_cnt++] = roots[i];

        int first_in_tree = 1;

        while (level_cnt > 0) {
            // 對當前層排序 (Key ASC)
            qsort(level_nodes, level_cnt, sizeof(Node*), compare_nodes_by_key);

            // 輸出並收集下一層
            Node *next_level[MAX_NODES];
            int next_cnt = 0;

            for (int j = 0; j < level_cnt; j++) {
                if (!first_in_tree) printf(" ");
                printf("%d", level_nodes[j]->key);
                first_in_tree = 0;

                // 收集子節點 (收集到陣列再放，確保安全)
                Node *child = level_nodes[j]->childHead;
                int child_guard = 0;
                while (child != NULL) {
                    next_level[next_cnt++] = child;
                    child = child->next;
                    if (++child_guard > SAFETY_LIMIT) break;
                }
            }

            // 更新 level
            for(int j=0; j<next_cnt; j++) level_nodes[j] = next_level[j];
            level_cnt = next_cnt;

            int loop_guard = 0;
            if (++loop_guard > SAFETY_LIMIT) break;
        }
        printf("\n");
    }
}

int main() {
    char cmd[20];

    // 初始化 map
    for(int i=0; i<MAX_KEY; i++) key_map[i] = NULL;

    while (scanf("%s", cmd) && strcmp(cmd, "exit") != 0) {
        if (strcmp(cmd, "insert") == 0) {
            int key;
            scanf("%d", &key);
            insert_op(key);
        } else if (strcmp(cmd, "extract-min") == 0) {
            extract_min();
        } else if (strcmp(cmd, "delete") == 0) {
            int key;
            scanf("%d", &key);
            delete_op(key);
        } else if (strcmp(cmd, "decrease") == 0) {
            int key, val;
            scanf("%d %d", &key, &val);
            decrease_key(key, val);
        }
    }

    print_heap();

    return 0;
}