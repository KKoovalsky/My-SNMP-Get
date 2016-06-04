/*
 * ber.h
 *
 *  Created on: 1 cze 2016
 *      Author: maly_windows
 */

#ifndef BER_H_
#define BER_H_

typedef struct VAR_S VAR_T;

VAR_T * oid_chr_to_hex(char * str);

VAR_T * create_head(uint8_t type, VAR_T * var);

#endif /* BER_H_ */
