/*
 * ber.h
 *
 *  Created on: 1 cze 2016
 *      Author: maly_windows
 */

#ifndef BER_H_
#define BER_H_

typedef struct VAR_S VAR_T;

VAR_T * create_field_primary_str(uint8_t type, char * data);

VAR_T * create_field_primary_short(uint8_t type, uint8_t data);

VAR_T * create_field_oid(char * str);

VAR_T * create_parent_field(uint8_t type, VAR_T ** Fields, uint8_t number);


#endif /* BER_H_ */
