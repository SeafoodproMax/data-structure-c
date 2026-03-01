//
// Created by 林勁博 on 2025/11/3.
//

#ifndef HW4_HASH_H
#define HW4_HASH_H
#define remove stdio_remove
#include <stdio.h>
#undef remove

typedef struct Data {
    int key;
    int value;
} Data;
void insert(Data *data);
void remove(int key);
int search(int key);

#endif //HW4_HASH_H