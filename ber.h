/*
 * ber.h
 *
 *  Created on: 1 cze 2016
 *      Author: maly_windows
 */

#ifndef BER_H_
#define BER_H_

typedef struct VAR_LEN VAR_LEN_T;

VAR_LEN_T * oid_chr_to_hex(char * str);

VAR_LEN_T * create_head(uint8_t type, VAR_LEN_T * var);

#endif /* BER_H_ */
