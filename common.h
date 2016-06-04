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

#define OCTET_STRING 0x04
#define OID 0x06
#define INTEGER 0x02
#define SEQUENCE 0x30
#define NULL_T 0x05
#define PDU_GET_REQ 0xA0

typedef union UINT64_BY_BYTE {
	uint64_t nr;
	uint8_t nr_tab[8];
}UINT64_BY_BYTE_T;

typedef struct VAR_S {
	uint8_t * var;
	uint64_t len_bytes;
}VAR_T;

static inline void free_VAR_T(VAR_T * ptr) {
	free(ptr->var);
	free(ptr);
}

#endif /* COMMON_H_ */
