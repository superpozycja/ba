#include "ba.h"

ba* ba_from_hex(char* hex) 
{
	size_t b_len = strlen(hex);

	if (b_len%2 != 0) {
		fprintf(stderr, "can't create ba from string %.10s", hex);
		if (b_len > 10)
			fprintf(stderr, "...");
		fprintf(stderr, " - odd number of hex digits\n");
		return NULL;
	}
	b_len /= 2;

	uint8_t* b_val = (uint8_t*) malloc(sizeof(uint8_t)*b_len);
	ba* b = (ba*) malloc(sizeof(ba));

	if (b_val == NULL || b == NULL) {
		fprintf(stderr, "can't create ba from string %.10s", hex);
		if(b_len > 10)
			fprintf(stderr, "...");
		fprintf(stderr, " - malloc() error\n");
	}

	for (int i = 0; i < b_len; i++) {
		char tmp[3];
		strncpy(tmp, hex+2*i, 2);
		tmp[2] = '\0';
		b_val[i] = strtol(tmp, NULL, 16);
	}

	b->len = b_len;
	b->val = b_val;
	return b;
}

ba* ba_from_hex_n(char* hex, unsigned int n) 
{
	size_t b_len = strlen(hex)*n;
	size_t offset = strlen(hex);

	if (b_len%2 != 0) {
		fprintf(stderr, "can't create ba from string %.10s", hex);
		if (b_len > 10)
			fprintf(stderr, "...");
		fprintf(stderr, " - odd number of hex digits\n");
		return NULL;
	}
	b_len /= 2;

	uint8_t* b_val = (uint8_t*) malloc(sizeof(uint8_t)*b_len);
	ba* b = (ba*) malloc(sizeof(ba));

	if (b_val == NULL || b == NULL) {
		fprintf(stderr, "can't create ba from string %.10s", hex);
		if(b_len > 10)
			fprintf(stderr, "...");
		fprintf(stderr, " - malloc() error\n");
	}

	for (int o = 0; o < b_len*2; o+=offset) {
		for (int i = 0; i < offset; i++) {
			char tmp[3];
			strncpy(tmp, hex+2*i, 2);
			tmp[2] = '\0';
			b_val[i+o/2] = strtol(tmp, NULL, 16);
		}
	}

	b->len = b_len;
	b->val = b_val;
	return b;
}

void ba_fprint(ba* b, FILE* stream, int prec) 
{
	int len = (prec > b->len) || prec == 0 ? b->len : prec;
	for (int i = 0; i < len; i++)
		fprintf(stream, "%02x", (b->val)[i]);
}

void ba_fprint_ascii(ba* b, FILE* stream, int prec) 
{
	int len = (prec > b->len) || prec == 0 ? b->len : prec;
	for (int i = 0; i < len; i++)
		if (isprint((b->val)[i])) 
			fprintf(stream, "%c", (b->val)[i]);
		else
			fprintf(stream, "\\b%02x", (b->val)[i]);
}

void ba_xor(ba* a, ba* b) 
{
	int len = a->len < b->len ? a->len : b->len;
	for (int i = 0; i < len; i++)
		(a->val)[i] = (a->val)[i] ^ (b->val)[i];
}

int ba_copy(ba *dst, ba *src)
{
	if (!dst)
		return -1;

	if (dst->val)
		free(dst->val);
	dst->len = src->len;
	dst->val = (uint8_t*) malloc(sizeof(uint8_t)*src->len);
	memcpy(dst->val, src->val, src->len);
	return 0;

}

void ba_free(ba* b) 
{
	free(b->val);
	free(b);
}
