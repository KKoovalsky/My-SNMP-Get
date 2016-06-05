#include "common.h"
#include "x_string.h"

void printf_VAR_T(VAR_T * ptr) {
	for(uint64_t i = 0; i < ptr->len_bytes; i ++) {
		printf("%X ", ptr->var[i]);
	}
	printf("\n");
}

void x_memcpy_inv(uint8_t * to, uint8_t * from, uint8_t how_many) {
	for(uint8_t i = 0 ; i < how_many; i ++) {
		to[i] = from[how_many - i - 1];
	}
}

uint8_t get_bytes_occupied(uint64_t input) {
	uint8_t bytes_occupied = 0;
	while(input) {
		bytes_occupied ++;
		input >>= 8;
	}

	if(!bytes_occupied) return 1;
	return bytes_occupied;
}
