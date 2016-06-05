/*
 * x_string.h
 *
 *  Created on: 1 cze 2016
 *      Author: maly_windows
 */

#ifndef X_STRING_H_
#define X_STRING_H_

#define MAX_UINT8 0xFF

typedef struct VAR_S VAR_T;

void printf_VAR_T(VAR_T * STR);

void x_memcpy_inv(uint8_t * to, uint8_t * from, uint8_t how_many);

uint8_t get_bytes_occupied(uint64_t input);

#endif /* X_STRING_H_ */
