/*
 * main.c
 *
 *  Created on: 17-05-2016
 *      Author: root
 */
#include  "common.h"

#define SIZE 1024

int main(int argc, char * argv[]) {


	char CommString[] = "private";

	char Oid[] = "1.3.6.1.4.1.2680.1.2.7.3.2.0";

	uint64_t RequestId = 127;

	const char* ip_address = "10.0.2.2";

	VAR_T * CommStringField = create_field_primary_str(OCTET_STRING, CommString);
	VAR_T * OidField = create_field_oid(Oid);
	VAR_T * GetReqNullField = create_field_primary_str(NULL_T, NULL);
	VAR_T * UniversalIntField = create_field_primary_short(INTEGER, 0);
	VAR_T * RequestIDField = create_field_int(INTEGER, RequestId);

	VAR_T * VarbindContent[2];
	VarbindContent[0] = OidField;
	VarbindContent[1] = GetReqNullField;

	VAR_T * VarbindField = create_parent_field(SEQUENCE, VarbindContent, 2);
	free_VAR_T(OidField);
	free_VAR_T(GetReqNullField);

	VAR_T * VarbindListField = create_parent_field(SEQUENCE, &VarbindField, 1);
	free_VAR_T(VarbindField);

	VAR_T * PDUContent[4];
	PDUContent[0] = RequestIDField;
	PDUContent[1] = PDUContent[2] = UniversalIntField;
	PDUContent[3] = VarbindListField;

	VAR_T * PDUField = create_parent_field(PDU_GET_REQ, PDUContent, 4);
	free_VAR_T(VarbindListField);
	free_VAR_T(RequestIDField);

	VAR_T * SNMPContent[3];
	SNMPContent[0] = UniversalIntField;
	SNMPContent[1] = CommStringField;
	SNMPContent[2] = PDUField;

	VAR_T * SNMPField = create_parent_field(SEQUENCE, SNMPContent, 3);
	free_VAR_T(UniversalIntField);
	free_VAR_T(CommStringField);
	free_VAR_T(PDUField);


	printf_VAR_T(SNMPField);
	printf("\n");

	// UDP packet initialization.

	const char* portname = "161";
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_ADDRCONFIG;

	struct addrinfo* res = 0;
	int err = getaddrinfo(ip_address, portname , &hints, &res);
	if (err != 0) {
	    printf("failed to resolve remote socket address (err=%d)", err);
	    free_VAR_T(SNMPField);
	    return 0;
	}

	int fd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	if (fd == -1) {
	    printf("%s", strerror(errno));
	    free_VAR_T(SNMPField);
	    freeaddrinfo(res);
	    return 0;
	}

	if (sendto(fd, SNMPField->var, SNMPField->len_bytes, 0, res->ai_addr, res->ai_addrlen)==-1) {
		printf("%s", strerror(errno));
		free_VAR_T(SNMPField);
		freeaddrinfo(res);
		return 0;
	}

	char buffer[SIZE];
	struct sockaddr_storage src_addr;
	socklen_t src_addr_len = sizeof(src_addr);
	ssize_t count = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&src_addr, &src_addr_len);
	if (count == -1) {
		printf("%s", strerror(errno));
		free_VAR_T(SNMPField);
		freeaddrinfo(res);
		return 0;

	} else if (count==sizeof(buffer)) {
	    printf("\ndatagram too large for buffer: truncated\n");
	} else {
		printf("\n%.*s\n", SIZE, buffer);
	}


	free_VAR_T(SNMPField);
	freeaddrinfo(res);
	return 0;
}


