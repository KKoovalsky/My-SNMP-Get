/*
 * main.c
 *
 *  Created on: 17-05-2016
 *      Author: root
 */
#include  "common.h"

int main(int argc, char * argv[]) {

	char CommString[] = "public";

	char Oid[] = "1.3.6.1.4.1.2680.1.2.7.3.2.0";
	VAR_T * CommStringHead, * CommStringLen, * CommStringHeadLen, *CommStringWholeLen;
	VAR_T * OidHex, * OidHexLen, *OidHexHead, *OidHexHeadLen;
	VAR_T * VarbindLen, * VarbindHead, * VarbindHeadLen, * VarbindListLen, * VarbindListHead, * VarbindListHeadLen;
	VAR_T * PDULen, * PDUHead, * PDUHeadLen, * PDUWholeLen;
	VAR_T * PacketLen, * PacketHead;

	// Sequence + version
	//char head[] = {0x30, 0x29, 0x02, 0x01, 0x00};

	// Community string
	CommStringLen = x_strlen(CommString);
	printf_VAR_T(CommStringLen);
	CommStringHead = create_head(OCTET_STRING, CommStringLen);
	CommStringHeadLen = x_strlen_VAR_T(CommStringHead);
	CommStringWholeLen = sum_VAR_T(CommStringHeadLen, CommStringLen);

	// Convert OID to hex format
	OidHex = oid_chr_to_hex(Oid);
	printf_VAR_T(OidHex);
	OidHexLen = x_strlen_VAR_T(OidHex);
	OidHexHead = create_head(OID, OidHexLen);
	OidHexHeadLen = x_strlen_VAR_T(OidHexHead);

	// Varbind
	VarbindLen = sum_VAR_T(OidHexHeadLen, OidHexLen);
	update_len_VAR_T(VarbindLen, 2);
	VarbindHead = create_head(SEQUENCE, VarbindLen);
	VarbindHeadLen = x_strlen_VAR_T(VarbindHead);

	// Varbind list
	VarbindListLen = sum_VAR_T(VarbindHeadLen, VarbindLen);
	VarbindListHead = create_head(SEQUENCE, VarbindListLen);
	VarbindListHeadLen = x_strlen_VAR_T(VarbindHead);

	// PDU
	PDULen = sum_VAR_T(VarbindListHeadLen, VarbindListLen);
	update_len_VAR_T(PDULen, 9);
	PDUHead = create_head(PDU_GET_REQ, PDULen);
	PDUHeadLen = x_strlen_VAR_T(PDUHead);
	PDUWholeLen = sum_VAR_T(PDUHeadLen, PDULen);

	// SNMP packet
	PacketLen = sum_VAR_T(PDUWholeLen, CommStringWholeLen);
	update_len_VAR_T(PacketLen, 3);
	PacketHead = create_head(SEQUENCE, PacketLen);


	//--------------------------------------------------------
	//	Create SNMP packet
	//--------------------------------------------------------



	free_VAR_T(CommStringLen);
	free_VAR_T(CommStringHead);
	free_VAR_T(CommStringHeadLen);
	free_VAR_T(CommStringWholeLen);

	free_VAR_T(OidHex);
	free_VAR_T(OidHexLen);
	free_VAR_T(OidHexHead);
	free_VAR_T(OidHexHeadLen);

	free_VAR_T(VarbindLen);
	free_VAR_T(VarbindHead);
	free_VAR_T(VarbindHeadLen);

	free_VAR_T(VarbindListLen);
	free_VAR_T(VarbindListHead);
	free_VAR_T(VarbindListHeadLen);

	free_VAR_T(PDULen);
	free_VAR_T(PDUHead);
	free_VAR_T(PDUHeadLen);
	free_VAR_T(PDUWholeLen);

	free_VAR_T(PacketLen);
	free_VAR_T(PacketHead);

	return 0;
}


