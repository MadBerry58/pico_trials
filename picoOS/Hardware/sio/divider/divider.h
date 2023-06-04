#ifndef DIVIDERS_H
#define DIVIDERS_H

#include <stdio.h>

int32_t divide_same_divisor_signed      (int32_t *divided_numbers,  int32_t divisor,    int32_t *results,   int32_t *quotents);
uint32_t divide_same_divisor_unsigned   (uint32_t *divided_numbers, uint32_t divisor,   uint32_t *results,  uint32_t *quotents);

int32_t divide_same_divided_signed      (int32_t divided_number,    int32_t *divisors,  int32_t *results,   int32_t *quotents);
uint32_t divide_same_divided_unsigned   (uint32_t divided_number,   uint32_t *divisors, uint32_t *results,  uint32_t *quotents);

#endif