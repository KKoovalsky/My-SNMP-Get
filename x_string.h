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

void printf_str_as_hex(char * str);

void printf_VAR_T(VAR_T * STR);

VAR_T * x_strlen(char * str);

VAR_T * x_strlen_VAR_T(VAR_T * str);

VAR_T * sum_VAR_T(VAR_T * L, VAR_T * R);

void update_len_VAR_T(VAR_T * VAR, uint8_t len);

#endif /* X_STRING_H_ */
