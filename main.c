/*
 * main.c
 *
 *  Created on: 17-05-2016
 *      Author: root
 */
#include  "common.h"

int main(int argc, char * argv[]) {

	char CommString[] = "public"; //argv[2]
	//char id[] = "1";
	//char ver[] = "-v1"; //argv[3]
	char Oid[] = "1.3.6.1.4.1.2680.1.2.7.3.2.0";
	char CommStringHead[3];
	STR_LEN_T * CommStringLen, * OidHex;

	// Sequence + version
	//char head[] = {0x30, 0x29, 0x02, 0x01, 0x00};


	// Community string
	CommStringLen = x_strlen(CommString);
	printf_STR_LEN_T(CommStringLen);
	if(CommStringLen->bytes_held > 127) {
		printf("Too long community string (max 2^127 length)");
		free_STR_LEN(CommStringLen);
		return 0;
	}
	CommStringHead[0] = 0x04;
	CommStringHead[1] = CommStringLen->str_len[0];
	CommStringHead[2] = '\0';
	if(CommStringLen->bytes_held > 1 || CommStringLen->str_len[0] > 127) {
		CommStringHead[1] = CommStringLen->bytes_held | 0x80; // Long form
	}


	// Convert OID to hex format
	OidHex = oid_chr_to_hex(Oid);
	printf_STR_LEN_T(OidHex);

	free_STR_LEN(OidHex);
	free_STR_LEN(CommStringLen);
	return 0;
}


