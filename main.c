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
	VAR_LEN_T * CommStringHead, * CommStringLen, * OidHex, *OidHexHead;

	// Sequence + version
	//char head[] = {0x30, 0x29, 0x02, 0x01, 0x00};


	// Community string
	CommStringLen = x_strlen(CommString);
	printf_VAR_LEN_T(CommStringLen);
	CommStringHead = create_head(OCTET_STRING, CommStringLen);
	free_VAR_LEN(CommStringLen);

	// Convert OID to hex format
	OidHex = oid_chr_to_hex(Oid);
	printf_VAR_LEN_T(OidHex);
	OidHexHead = create_head(OID, OidHex);

	free_VAR_LEN(OidHex);
	free_VAR_LEN(CommStringLen);
	return 0;
}


