#include "common.h"
#include "x_string.h"

static inline void inv_VAR_T(VAR_T * ptr) {
	uint8_t * str = (uint8_t*) malloc (sizeof(uint8_t) * (ptr->len_bytes));
	for(uint8_t i = 0 ; i < ptr->len_bytes ; i ++) {
		str[i] = ptr->var[ptr->len_bytes - i - 1];
	}
	uint8_t * temp = ptr->var;
	ptr->var = str;
	free(temp);
}

void printf_str_as_hex(char * str) {
	for(char * ptr = str; *ptr; ptr++)
		printf("%X ", *ptr);
	printf("\n");
}

void printf_VAR_T(VAR_T * ptr) {
	for(uint64_t i = 0; i < ptr->len_bytes; i ++) {
		printf("%X ", ptr->var[i]);
	}
	printf("\n");
}


/* 	Long form of header can contain 127 octets and maximum number of bytes representing a number is eight
 	so internal arithmetic should be implemented.
 	Structure STR_LEN_T contains number of length bytes and the length bytes. */
VAR_T * x_strlen(char * str) {
	uint8_t * len;
	uint64_t bytes_held = 1;
	VAR_T * RET;

	// Firstly, allocate memory only for one length byte
	len = (uint8_t *) malloc (sizeof(uint8_t));
	len[0] = 0;

	for(char * ptr = str; *ptr; ptr ++) {

		// When length of string reaches multiplicity of 256 next bytes should be incremented.
		if(len[0] == MAX_UINT8) {
			uint8_t i = 0;
			while(len[i] == MAX_UINT8) {
				i ++;

				// If string length reaches 2^8, 2^16, 2^32...
				if(i == bytes_held) {
					bytes_held ++;
					len = (uint8_t *) realloc (len, sizeof(uint8_t) * (bytes_held));
					len[i] = 0x00;
					break;
				}
			}

			// Clear bytes with 0xFF
			len[i] ++;
			while (i) {
				i--;
				len[i] = 0x00;
			}

			continue;
		}
		len[0] ++;
	}

	RET = (VAR_T *) malloc (sizeof( VAR_T ));
	RET->var = len;
	RET->len_bytes = bytes_held;

	return RET;
}

VAR_T * x_strlen_VAR_T(VAR_T * str) {
	VAR_T * RET;
	UINT64_BY_BYTE_T LEN;
	LEN.nr = str->len_bytes;

	RET = (VAR_T *) malloc ( sizeof( VAR_T ) );
	RET->len_bytes = 0;
	uint64_t temp = LEN.nr;
	while(temp) {
		RET->len_bytes ++;
		temp >>= 8;
	}

	RET->var = (uint8_t *) malloc (sizeof ( uint8_t ) * RET->len_bytes );
	memcpy(RET->var, LEN.nr_tab, RET->len_bytes);

	return RET;
}

VAR_T * sum_VAR_T(VAR_T * L, VAR_T * R) {

	uint64_t sum_num = (L->len_bytes > R->len_bytes ? R->len_bytes : L->len_bytes);
	VAR_T * Greater = (L->len_bytes > R->len_bytes ? L : R );
	if(L->len_bytes == R->len_bytes) Greater = NULL;

	VAR_T * RET = (VAR_T *) malloc (sizeof ( VAR_T ) );
	RET->len_bytes = (Greater ? Greater->len_bytes : sum_num);
	RET->var = (uint8_t *) malloc (sizeof ( uint8_t ) * RET->len_bytes);

	uint8_t ovf = 0;
	for(uint64_t i = 0 ; i < sum_num; i ++) {
		uint16_t sum = L->var[i] + R->var[i] + ovf;
		ovf = (0xFF00 & sum) >> 8;
		RET->var[i] = (uint8_t)sum;
	}

	if(Greater) {
		for(uint64_t i = 0 ; i < Greater->len_bytes - sum_num ; i ++) {
			uint16_t sum = Greater->var[sum_num + i] + ovf;
			ovf = (0xFF00 & sum) >> 8;
			RET->var[sum_num + i] = (uint8_t)sum;
		}
	}

	if(ovf) {
		RET->len_bytes ++;
		RET->var = (uint8_t *) realloc (RET->var, sizeof(uint8_t) * RET->len_bytes);
		RET->var[RET->len_bytes - 1] = ovf;
	}

	return RET;
}

void update_len_VAR_T(VAR_T * VAR, uint8_t len) {
	uint16_t sum = VAR->var[0] + len;
	uint8_t ovf = (0xFF00 & sum) >> 8;

	for(uint64_t i = 1 ; i < VAR->len_bytes && ovf ; i ++) {
		uint16_t sum = VAR->var[i] + ovf;
		ovf = (0xFF00 & sum) >> 8;
		VAR->var[i] = (uint8_t)sum;
	}

	if(ovf) {
		VAR->len_bytes ++;
		VAR->var = (uint8_t *) realloc (VAR->var, sizeof(uint8_t) * VAR->len_bytes);
		VAR->var[VAR->len_bytes - 1] = ovf;
	}
}
