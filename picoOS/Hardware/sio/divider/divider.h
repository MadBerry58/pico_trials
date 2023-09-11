#ifndef DIVIDERS_H
#define DIVIDERS_H

#include <stdio.h>

/* 
typedef struct{
    boolean coreID;
} dividerConfig;
 */

///TODO: create divider overlay to allow for concurrent use

int32_t  divide_same_divisor(int32_t *divided_numbers,  int32_t  divisor,    int32_t *results,   int32_t *quotents);
uint32_t divide_same_divisor(uint32_t *divided_numbers, uint32_t divisor,   uint32_t *results,  uint32_t *quotents);

int32_t  divide_same_divided(int32_t  divided_number,    int32_t *divisors,  int32_t *results,   int32_t *quotents);
uint32_t divide_same_divided(uint32_t divided_number,   uint32_t *divisors, uint32_t *results,  uint32_t *quotents);

#endif