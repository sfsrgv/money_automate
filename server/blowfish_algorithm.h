#ifndef BLOWFISH_ALGORITHM_BLOWFISH_ALGORITHM_H
#define BLOWFISH_ALGORITHM_BLOWFISH_ALGORITHM_H

#include <stdint-gcc.h>

#include "string_and_uin64_functions.h"

#define CODE 0
#define DECODE 1

// Function to swap two 32-bytes numbers
void swap(uint32_t *left, uint32_t *right);

// Function used in round of blowfish algorithm
uint32_t blowfish_function(const uint32_t* number);

// One round of algorithm
void round_function(uint32_t *left, uint32_t *right, const uint32_t* key);

// Coding or decoding 64 bits using blowfish algorithm
uint64_t blowfish(uint64_t *number, int operation);

int blowfish_for_database(int operation, char* database);


#endif //BLOWFISH_ALGORITHM_BLOWFISH_ALGORITHM_H
