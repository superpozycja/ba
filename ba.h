/* copyright 2024 anna@superpozycja.net all right reserved  */

#ifndef BA_H
#define BA_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    size_t len;
    uint8_t* val;
} ba; 

ba* ba_from_hex(char* hex);
void ba_fprint(ba* b, FILE* stream, int prec);
void ba_xor(ba* a, ba* b);
void ba_free(ba* b);

/* this is really janky but fuck it */
#include "ba.c"
#endif
