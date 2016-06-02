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

typedef struct VAR_LEN {
	uint8_t * var_len;
	uint8_t bytes_held;
}VAR_LEN_T;

static inline void free_VAR_LEN(VAR_LEN_T * ptr) {
	free(ptr->var_len);
	free(ptr);
}

#endif /* COMMON_H_ */
