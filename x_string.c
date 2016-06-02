#include "common.h"
#include "x_string.h"

static inline void str_inv(VAR_LEN_T * ptr) {
	uint8_t * str = (uint8_t*) malloc (sizeof(uint8_t) * (ptr->bytes_held + 1));
	for(uint8_t i = 0 ; i < ptr->bytes_held ; i ++) {
		str[i] = ptr->var_len[ptr->bytes_held - i - 1];
	}
	str[ptr->bytes_held] = '\0';
	uint8_t * temp = ptr->var_len;
	ptr->var_len = str;
	free(temp);
}

void printf_str_as_hex(uint8_t * str) {
	for(uint8_t * ptr = str; *ptr; ptr++)
		printf("%X ", *ptr);
	printf("\n");
}

void printf_VAR_LEN_T(VAR_LEN_T * ptr) {
	for(uint8_t i = 0; i < ptr->bytes_held; i ++) {
		printf("%X ", ptr->var_len[i]);
	}
	printf("\n");
}


/* 	Long form of header can contain 127 octets and maximum number of bytes representing a number is eight
 	so internal arithmetic should be implemented.
 	Structure STR_LEN_T contains number of length bytes and the length bytes. */
VAR_LEN_T * x_strlen(char * str) {
	uint8_t * len;
	uint8_t bytes_held = 1;
	VAR_LEN_T * RET;

	// Firstly, allocate memory only for one length byte and for \0 character.
	len = (uint8_t *) malloc (sizeof(uint8_t) * 2);
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
					len = (uint8_t *) realloc (len, sizeof(uint8_t) * (bytes_held + 1));
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

	len[bytes_held] = '\0';
	RET = (VAR_LEN_T *) malloc (sizeof( VAR_LEN_T ));
	RET->var_len = len;
	RET->bytes_held = bytes_held;


	// Inversion needed to have MSB at 0 index.
	str_inv(RET);

	return RET;
}
