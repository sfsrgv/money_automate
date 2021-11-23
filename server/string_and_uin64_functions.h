#ifndef BLOWFISH_ALGORITHM_STRING_AND_UIN64_FUNCTIONS_H
#define BLOWFISH_ALGORITHM_STRING_AND_UIN64_FUNCTIONS_H

#include <stdint-gcc.h>
#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "asprintf.h"

// Converts every byte of 8-bytes number to char
char *make_array_of_chars_from_bytes(const uint64_t* buffer);

// Makes 64-bits number from text line
uint64_t convert_string_to_uint64(const char *line);

// Parse 64 bits to first 32 bits and second 32 bits
void split_uint64(const uint64_t* number, uint32_t *left, uint32_t *right);

// Converts code of every char and concatenate them to one 64-bits number
uint64_t make_uint64_from_array_of_chars(const char *array);

#endif //BLOWFISH_ALGORITHM_STRING_AND_UIN64_FUNCTIONS_H
