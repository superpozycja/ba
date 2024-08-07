#ifndef BA_H
#define BA_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

typedef struct {
	size_t len;
	uint8_t *val;
} ba; 

ba* ba_from_hex(char *hex);
ba* ba_from_hex_n(char *hex, unsigned int n);
void ba_fprint(ba *b, FILE *stream, int prec);
void ba_fprint_ascii(ba *b, FILE *stream, int prec);
void ba_xor(ba *a, ba *b);
int ba_copy(ba *dst, ba *src);
void ba_free(ba *b);

#endif
