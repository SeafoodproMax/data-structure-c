//
// Created by 林勁博 on 2025/12/4.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h> // Included for potential advanced use, though not strictly needed for basic operations

// --- 1. Define Bloom Filter Constants and Structure ---
#define M 11        // Size of the bit array (m) in bits (from slide example)
#define H 2         // Number of hash functions (h) (from slide example)

// Macro to calculate the required size of the char array (in bytes) to store M bits.
#define BIT_ARRAY_SIZE ((M + 7) / 8)

typedef struct {
    unsigned char bit_array[BIT_ARRAY_SIZE]; // Array of bytes to simulate the bit array
    int m; // Array size (number of bits)
    int h; // Number of hash functions
} BloomFilter;

// --- 2. Hash Functions Framework ---

/**
 * @brief The i-th hash function.
 * * In a real-world Bloom Filter, independent and uniform hash functions
 * (like MurmurHash or Jenkins Hash) are preferred. For this template,
 * we use simple modulo arithmetic based on the slide example for demonstration.
 * * @param key The input key (k)
 * @param i The index of the hash function (0 to H-1)
 * @param m The size of the bit array
 * @return The hash result, an index between [0, m-1]
 */
int hash_func(int key, int i, int m) {
    switch (i) {
        case 0:
            // Example f1(k) = k mod m (from slide)
            return key % m;
        case 1:
            // Example f2(k) = (2k) mod m (from slide)
            return (2 * key) % m;
        case 2:
            // An additional example: f3(k) = (3k) mod m
            return (3 * key) % m;
        default:
            // A generic, non-independent form for placeholders
            return ((i + 1) * key) % m;
    }
}

// --- 3. Bit Array Utility Functions ---

/**
 * @brief Sets the bit at the specified index to 1.
 * @param bf Pointer to the BloomFilter structure
 * @param index The bit index to set (0 to M-1)
 */
void set_bit(BloomFilter *bf, int index) {
    if (index >= 0 && index < bf->m) {
        int byte_index = index / 8;
        int bit_offset = index % 8;
        // Use bitwise OR to set the specific bit
        bf->bit_array[byte_index] |= (1 << bit_offset);
    }
}

/**
 * @brief Checks if the bit at the specified index is 1.
 * @param bf Pointer to the BloomFilter structure
 * @param index The bit index to check (0 to M-1)
 * @return true if the bit is 1, false if the bit is 0
 */
bool check_bit(BloomFilter *bf, int index) {
    if (index >= 0 && index < bf->m) {
        int byte_index = index / 8;
        int bit_offset = index % 8;
        // Use bitwise AND to check the specific bit
        return (bf->bit_array[byte_index] & (1 << bit_offset)) != 0;
    }
    return false; // Invalid index
}

// --- 4. Main Bloom Filter Operations ---

/**
 * @brief Initializes the Bloom Filter structure.
 * @param bf Pointer to the BloomFilter structure
 * @param m Bit array size
 * @param h Number of hash functions
 */
void bf_init(BloomFilter *bf, int m, int h) {
    bf->m = m;
    bf->h = h;
    // Initialize all bits to 0
    memset(bf->bit_array, 0, (m + 7) / 8);
}

/**
 * @brief Inserts an element (key k) into the set.
 * * [cite_start]For each of the h hash functions, the corresponding bit in the array is set to 1[cite: 26].
 * * @param bf Pointer to the BloomFilter structure
 * @param key The key to insert (k)
 */
void bf_insert(BloomFilter *bf, int key) {
    // Iterate through all h hash functions
    for (int i = 0; i < bf->h; i++) {
        // Calculate the index in the bit array
        int index = hash_func(key, i, bf->m);

        // Set the corresponding bit to 1
        set_bit(bf, index);
    }
}

/**
 * @brief Checks if an element (key k) is a member of the set.
 * * If any of the h bits checked are 0, the key is definitely NOT in the set ("No").
 * [cite_start]If all h bits are 1, the key MAY be in the set ("Maybe")[cite: 49].
 * * @param bf Pointer to the BloomFilter structure
 * @param key The key to check (k)
 * @return true ("Maybe") if all h bits are 1, false ("No") if any bit is 0
 */
bool bf_member(BloomFilter *bf, int key) {
    // Iterate through all h hash functions
    for (int i = 0; i < bf->h; i++) {
        // Calculate the index in the bit array
        int index = hash_func(key, i, bf->m);

        // If any bit is 0, the element is definitely not in the set
        if (!check_bit(bf, index)) {
            return false;// Always accurate rejection [cite: 6]
        }
    }

    // If all bits are 1, the element MAY be in the set.
    // This result is subject to False Positives (filter error)[cite: 5].
    return true;// Returns "Maybe" [cite: 7]
}

/**
 * @brief Prints the contents of the Bloom Filter's bit array (M bits).
 * @param bf Pointer to the BloomFilter structure
 */
void print_bf(BloomFilter *bf) {
    printf("Bit Array (%d bits): ", bf->m);
    for (int i = 0; i < bf->m; i++) {
        printf("%d", check_bit(bf, i));
    }
    printf("\n");
}