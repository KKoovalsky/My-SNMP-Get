/*
 * main.c
 *
 *  Created on: 17-05-2016
 *      Author: root
 */
#include  "common.h"

int main(int argc, char * argv[]) {

	char CommString[] = "private";

	char Oid[] = "1.3.6.1.4.1.2680.1.2.7.3.2.0";

	VAR_T * CommStringField = create_field_primary_str(OCTET_STRING, CommString);
	VAR_T * OidField = create_field_oid(Oid);
	VAR_T * GetReqNullField = create_field_primary_str(NULL_T, NULL);
	VAR_T * UniversalIntField = create_field_primary_short(INTEGER, 0);

	VAR_T * VarbindContent[2];
	VarbindContent[0] = OidField;
	VarbindContent[1] = GetReqNullField;

	VAR_T * VarbindField = create_parent_field(SEQUENCE, VarbindContent, 2);
	free_VAR_T(OidField);
	free_VAR_T(GetReqNullField);

	VAR_T * VarbindListField = create_parent_field(SEQUENCE, &VarbindField, 1);
	free_VAR_T(VarbindField);

	VAR_T * PDUContent[4];
	PDUContent[0] = PDUContent[1] = PDUContent[2] = UniversalIntField;
	PDUContent[3] = VarbindListField;

	VAR_T * PDUField = create_parent_field(PDU_GET_REQ, PDUContent, 4);
	free_VAR_T(VarbindListField);

	VAR_T * SNMPContent[3];
	SNMPContent[0] = UniversalIntField;
	SNMPContent[1] = CommStringField;
	SNMPContent[2] = PDUField;

	VAR_T * SNMPField = create_parent_field(SEQUENCE, SNMPContent, 3);
	free_VAR_T(UniversalIntField);
	free_VAR_T(CommStringField);
	free_VAR_T(PDUField);


	printf_VAR_T(SNMPField);

	// UDP packet initialization.
	const char* hostname = 0; /* localhost */
	const char* portname = "daytime";
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));


	# ifndef AI_ADDRCONFIG
	# define AI_ADDRCONFIG 0
	# endif

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_ADDRCONFIG;

	struct addrinfo* res = 0;
	int err = getaddrinfo(hostname, portname , &hints, &res);
	if (err != 0) {
	    printf("failed to resolve remote socket address (err=%d)", err);
	    return 0;
	}




	free_VAR_T(SNMPField);
	return 0;
}


