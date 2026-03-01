#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// this place is temporarily used to implement linear probing of an easy hash table
void linear_probing(int hash[], int arr[], int size, int index) {
    for (int i = 0; i < size; i++) {
        int key = arr[i];
        for (int j = 0; j < size; j++) {
            int idx = key%size+j;
            if (hash[idx] == INT_MIN) {
                hash[idx] = key;
                break;
            }
        }
    }
}
void delete_key(int hash[], int key, int size) {
    int idx = key%size;
    for (int i = 0; i < size; i++) {

    }
}

int main() {
    while(true) {
        char buffer[100];
        int n;
        if (fgets(buffer, 100, stdin) == NULL) break;
        sscanf(buffer, "%d", &n);
        int arr[n], hash[n];
        fgets(buffer, 100, stdin);
        for (int i = 0; i < n; i++) {
            sscanf(buffer, "%d", &arr[i]);
        }
        for (int i = 0; i < n; i++) {
            hash[i] = INT_MIN;
        }


    }
    return 0;
}