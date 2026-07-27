#include "base32.hpp"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

void base32_encode_char(const uint8_t *src, char *dst, size_t len) {
    // Implementation of base32 encoding
    uint32_t hi = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    uint32_t lo = (hi << 8) | src[4];

    dst[0] = BASE32_ALPHABET[hi >> 27 & 0x1F];
    dst[1] = BASE32_ALPHABET[hi >> 22 & 0x1F];
    dst[2] = BASE32_ALPHABET[hi >> 17 & 0x1F];
    dst[3] = BASE32_ALPHABET[hi >> 12 & 0x1F];
    dst[4] = BASE32_ALPHABET[hi >> 7 & 0x1F];
    dst[5] = BASE32_ALPHABET[hi >> 2 & 0x1F];

    dst[6] = BASE32_ALPHABET[lo >> 5 & 0x1F];
    dst[7] = BASE32_ALPHABET[lo & 0x1F];

}

void base32_encode(const uint8_t *src, char *dst, size_t len){  
    int si = 0, di = 0;

    int fullChars = (len / 5) * 5;

    while (si < fullChars){
        base32_encode_char(&src[si], &dst[di], fullChars - si);
        si += 5;
        di += 8;
    }

    int remaining = len - fullChars;

    if (remaining == 0) {
        dst[di] = '\0';
        return;
    }
    uint32_t val = 0;

    switch(remaining) {
        case 4:
            val |= src[si + 3];
            dst[di + 6] = BASE32_ALPHABET[(val << 3) & 0x1F];
            dst[di + 5] = BASE32_ALPHABET[(val >> 2) & 0x1F];
        case 3:
            val |= src[si + 2] << 8;
            dst[di + 4] = BASE32_ALPHABET[(val >> 7) & 0x1F];
        case 2:
            val |= src[si + 1] << 16;
            dst[di + 3] = BASE32_ALPHABET[(val >> 12) & 0x1F];
            dst[di + 2] = BASE32_ALPHABET[(val >> 17) & 0x1F];
        case 1:
            val |= src[si + 0] << 24;
            dst[di + 1] = BASE32_ALPHABET[(val >> 22) & 0x1F];
            dst[di + 0] = BASE32_ALPHABET[(val >> 27) & 0x1F];
    }
    int npad = (remaining * 8 / 5) + 1;
    for (int i = npad; i < 8; i++) {
        dst[di + i] = '=';
    }
    dst[di + 8] = '\0';
}

static uint8_t base32_decode_char(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    } else if (c >= '2' && c <= '7') {
        return c - '2' + 26;
    } else {
        return 0xFF; // Invalid character
    }
}
int base32_decode(const char *src, char *dst, size_t limit) {
    int n;
    int dsti;
    bool end;

    while (*src != '\0') {
        uint8_t buf[8];
        int dlen = 8;
        for (n = 0; n < 8; ) {
            char c = *src;
            src++;

            if (isspace(c)) {
                continue;
            }

            buf[i] = base32_decode_char(c);
            if (buf[i] == 0xFF) {
                return BASE32_INCORRECT_SYMBOL;
            }
        }
    }

            