/*
 * common.h
 *
 *  Created on: 1 cze 2016
 *      Author: maly_windows
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
#include <math.h>

#include "x_string.h"
#include "ber.h"

typedef union UINT64_U {
	uint64_t whole_word;
	uint8_t word_by_byte[8];
}UINT64_T_U;

typedef struct STR_LEN {
	uint8_t * str_len;
	uint8_t bytes_held;
}STR_LEN_T;

static inline void free_STR_LEN(STR_LEN_T * pStr) {
	free(pStr->str_len);
	free(pStr);
}

#endif /* COMMON_H_ */
