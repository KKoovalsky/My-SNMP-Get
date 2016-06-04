#include "common.h"
#include "ber.h"

VAR_T * oid_chr_to_hex(char * str_oid) {

	VAR_T * RET;
	char *ptr = str_oid;
	uint64_t len = 1, len_hex, ind_hex;
	uint64_t * nrs_in_oid;
	uint8_t * hex_form;

	// Count all dots. Basing on the number of dots numbers in OID can be counted.
	while(*ptr) {
		if(*ptr == '.') len++;
		ptr++;
	}
	nrs_in_oid = (uint64_t*) malloc (sizeof(uint64_t) * len);

	// Get numbers in integer form from string.
	ptr = strtok(str_oid, ".");
	for(uint8_t i = 0; i < len ;i++) {
		// Convert number from string format to integer.
		nrs_in_oid[i] = atoi(ptr);
		ptr = strtok(NULL, ".");
	}

	/* Make hex format from integers.
	 * Firstly, allocate predicted memory for hex format. */
	len_hex = len + 2;
	hex_form = (uint8_t *) malloc ( sizeof(uint8_t) * len_hex);

	// First two oid nrs as 40 * x + y
	hex_form[0] = 40 * nrs_in_oid[0] + nrs_in_oid[1];

	// The rest as 7 bit nrs:
	ind_hex = 1;
	for(uint64_t i = 2 ; i < len ; i ++) {
		if(nrs_in_oid[i] > 127) {
			uint64_t temp = nrs_in_oid[i];
			uint8_t hex_sevens[10 + 1]; // ceil(64/7 = 10)
			uint8_t nr_sevens = 0;

			// Get nr of septets and write those in array.
			hex_sevens[10] = '\0';
			while(temp) {
				hex_sevens[nr_sevens] =  temp & 0x7F;
				temp >>= 7;
				nr_sevens ++;
			}

			// If predicted size of hex form array is too small, then enlarge it.
			if(ind_hex + nr_sevens > len_hex - 1) {
				len_hex += nr_sevens;
				hex_form = (uint8_t *) realloc (hex_form, sizeof(uint8_t) * len_hex);
			}

			for(uint8_t i = 0; i < nr_sevens ; i++) {
				hex_form[ind_hex] = hex_sevens[nr_sevens - i - 1] | 0x80;
				ind_hex++;
			}
			hex_form[ind_hex - 1] &= 0x7F;

		} else {
			hex_form[ind_hex] = nrs_in_oid[i];
			ind_hex ++;

			if(ind_hex == len_hex) {
				len_hex += 5;
				hex_form = (uint8_t *) realloc (hex_form, sizeof(uint8_t) * len_hex);
			}
		}
	}

	RET = (VAR_T *) malloc (sizeof ( VAR_T ));
	hex_form = (uint8_t *) realloc(hex_form, sizeof(uint8_t) * ind_hex);
	RET->var = hex_form;
	RET->len_bytes = ind_hex;

	free(nrs_in_oid);
	return RET;
}

VAR_T * create_head(uint8_t type, VAR_T * length) {

	VAR_T * RET;
	uint8_t * content;
	uint8_t bytes_held;

	if(length->len_bytes > 127) {
		printf("Too long octet string (max size 2^(127 * 8))");
		return NULL;
	}

	bytes_held = 1 + (length->len_bytes > 1 ? (length->len_bytes + 1) :
			((length->var[0] > 127) ? 2 : 1 ));

	content = (uint8_t * ) malloc ((bytes_held) * sizeof ( uint8_t ));

	content[0] = type;
	if(bytes_held > 2) {
		content[1] = 0x80 | length->len_bytes;
		memcpy(&content[2], length->var, length->len_bytes);
	} else {
		content[1] = length->var[0];
	}

	RET = (VAR_T *) malloc ( sizeof ( VAR_T ) );
	RET->len_bytes = bytes_held;
	RET->var = content;
	return RET;
}
