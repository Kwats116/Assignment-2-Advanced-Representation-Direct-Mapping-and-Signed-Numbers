//Author: Kyle Watson
//Course: CS 3503- Comp Org & Arch
//Assignment: A2 - Data Representation & Mapping
//Language: C Programming
//Topics:Direct mapping, signed representations

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// build a 32-bit binary string from unsigned value
static void to_32bit_binary(uint32_t value, char *out) {
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = ((value >> i) & 1) ? '1' : '0';
    }
    out[32] = '\0';
}

// Direct Mapping Functions

//Octal -> Binary (3 bits each)
void oct_to_bin(const char *oct, char *out) {
    int len = strlen(oct);
    int pos = 0;
    for (int i = 0; i < len; i++) {
        int digit = oct[i] - '0';
        out[pos++] = (digit & 4) ? '1' : '0';
        out[pos++] = (digit & 2) ? '1' : '0';
        out[pos++] = (digit & 1) ? '1' : '0';
    }
    out[pos] = '\0';
}

//Octal -> Binary -> Hex
void oct_to_hex(const char *oct, char *out) {
    char bin[256];
    oct_to_bin(oct, bin);

    //Pad left so length is multiple of 4
    int len = strlen(bin);
    int pad = (4 - (len % 4)) % 4;
    char padded[260];
    for (int i = 0; i < pad; i++) padded[i] = '0';
    strcpy(padded + pad, bin);

    //Convert 4 bits -> hex digit
    char hexmap[] = "0123456789ABCDEF";
    int outpos = 0;
    for (int i =0; i < strlen(padded); i += 4) {
        int val = 0;
        for (int j = 0; j < 4; j++) {
            val = (val << 1) | (padded[i + j] - '0');
        }
        out[outpos++] = hexmap[val];
    }
    out[outpos] = '\0';
}

//Hex -> Binary (4 bits each)
void hex_to_bin(const char *hex, char *out) {
    int len = strlen(hex);
    int pos = 0;
    for (int i = 0; i < len; i++) {
        char c = toupper(hex[i]);
        int val;
        if (c >= '0' && c <= '9') val = c - '0';
        else val = c - 'A' + 10;

        out[pos++] = (val & 8) ? '1' : '0';
        out[pos++] = (val & 4) ? '1' : '0';
        out[pos++] = (val & 2) ? '1' : '0';
        out[pos++] = (val & 1) ? '1' : '0';
    }
    out[pos] = '\0';
}

// Signed Number Representations
void to_sign_magnitude(int32_t n, char *out) {
    if (n >= 0) {
        to_32bit_binary((uint32_t) n, out);
    }else {
        int32_t absval = -n;
        to_32bit_binary((uint32_t) absval, out);
        out[0] = '1';// set sign bit
    }
}

void to_ones_complement(int32_t n, char *out) {
    if (n >= 0) {
        to_32bit_binary((uint32_t) n, out);
    }else {
        uint32_t absval = (uint32_t)(-n);
        char tmp[33];
        to_32bit_binary(absval, tmp);
        for (int i = 0; i < 32; i++) {
            out[i] = (tmp[i] == '0') ? '1' : '0';
        }
        out[32] = '\0';

    }
}
void to_twos_complement(int32_t n, char *out) {
    uint32_t val = (uint32_t) n;// Two's complemt is just the bit pattern
    to_32bit_binary(val, out);
}