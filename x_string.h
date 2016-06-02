/*
 * x_string.h
 *
 *  Created on: 1 cze 2016
 *      Author: maly_windows
 */

#ifndef X_STRING_H_
#define X_STRING_H_

#define MAX_UINT8 0xFF

typedef struct VAR_LEN VAR_LEN_T;

void printf_str_as_hex(uint8_t * str);

void printf_VAR_LEN_T(VAR_LEN_T * STR);

VAR_LEN_T * x_strlen(char * str);



#endif /* X_STRING_H_ */
