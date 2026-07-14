#include "base32.h"
#include <stdint.h>

void base32_encode(const uint8_t *src, char *dst, size_t len) {
    // Implementation of base32 encoding
    uint32_t hi = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    uint32_t lo = (hi << 8) | src[4];

    dst[0] = BASE32_ALPHABET[hi >> 27 & 0x1F];
    dst[1] = BASE32_ALPHABET[hi >> 22 & 0x1F];
    dst[2] = BASE32_ALPHABET[hi >> 17 & 0x1F];
    dst[3] = BASE32_ALPHABET[hi >> 12 & 0x1F];
    dst[4] = BASE32_ALPHABET[hi >> 7 & 0x1F];
    dst[5] = BASE32_ALPHABET[hi >> 2 & 0x1F];

    dst[6] = 0;
}
