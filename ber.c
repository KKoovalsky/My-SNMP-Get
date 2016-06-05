#include "common.h"
#include "ber.h"

static inline uint8_t create_head(VAR_T * Field, uint8_t type, uint64_t ContentLen) {

	uint8_t len_bytes_occu;
	UINT64_BY_BYTE_T ContentLenU;
	ContentLenU.nr = ContentLen;
	len_bytes_occu = get_bytes_occupied(ContentLenU.nr);

	if(ContentLenU.nr > 127) {
		Field->len_bytes = 1 + 1 + len_bytes_occu + ContentLenU.nr;
		Field->var = (uint8_t *) malloc (sizeof(uint8_t) * Field->len_bytes );
		Field->var[0] = type;
		Field->var[1] = 0x80 | len_bytes_occu;

		x_memcpy_inv(&Field->var[2], ContentLenU.nr_tab, len_bytes_occu);

		return 2 + len_bytes_occu;
	}

	Field->len_bytes = 1 + 1 + ContentLenU.nr;
	Field->var = (uint8_t *) malloc (sizeof(uint8_t) * Field->len_bytes );
	Field->var[0] = type;
	Field->var[1] = ContentLenU.nr_tab[0];
	return 2;
}
VAR_T * create_field_oid(char * str_oid){

	VAR_T * Field;
	char *ptr = str_oid;
	uint64_t len = 1, len_hex, ind_hex, ind;
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

	if(len_hex != ind_hex) hex_form = (uint8_t *) realloc(hex_form, sizeof(uint8_t) * ind_hex);

	Field = (VAR_T *) malloc (sizeof(VAR_T));
	ind = create_head(Field, OID, ind_hex);
	memcpy(&Field->var[ind], hex_form, ind_hex);

	free(hex_form);
	free(nrs_in_oid);
	return Field;
}


VAR_T * create_field_primary_str(uint8_t type, char * data) {

	VAR_T * Field;
	uint64_t ind;

	if(!data) {
		Field = (VAR_T *) malloc (sizeof(VAR_T));
		Field->len_bytes = 2;
		Field->var = (uint8_t*) malloc (sizeof(uint8_t) * Field->len_bytes );
		Field->var[0] = type;
		Field->var[1] = 0;
		return Field;
	}

	Field = (VAR_T *) malloc (sizeof(VAR_T));
	ind = create_head(Field, type, strlen(data));
	memcpy(&Field->var[ind], data, strlen(data));

	return Field;
}

VAR_T * create_field_primary_short(uint8_t type, uint8_t data) {
	VAR_T * Field = (VAR_T *) malloc (sizeof(VAR_T));
	Field->len_bytes = 3;
	Field->var = (uint8_t *) malloc (sizeof (uint8_t) * Field->len_bytes);
	Field->var[0] = type;
	Field->var[1] = 1;
	Field->var[2] = data;
	return Field;
}

VAR_T * create_parent_field(uint8_t type, VAR_T ** Fields, uint8_t number) {
	VAR_T * ParentField;

	uint64_t content_len = 0;
	uint64_t ind;

	for(uint8_t i = 0 ; i < number ; i ++) {
		content_len += Fields[i]->len_bytes;
	}

	ParentField = (VAR_T *) malloc (sizeof(VAR_T));
	ind = create_head(ParentField, type, content_len);

	for(uint8_t i = 0 ; i < number; i ++) {
		memcpy(&ParentField->var[ind], Fields[i]->var, Fields[i]->len_bytes);
		ind += Fields[i]->len_bytes;
	}

	return ParentField;

}
