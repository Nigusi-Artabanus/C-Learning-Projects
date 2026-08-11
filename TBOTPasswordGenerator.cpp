#include "base32.hpp"
#include <stdio.h>
#include <string.h>

#define SECRET "FRERT5GY76GHVV321DASSC4HB6TH67GH"
int main() {
    uint8_t key[20];
    base32_decode(SECRET, key, sizeof(key));

    for (int i = 0; i < sizeof(key); i++) {
        printf("%02X", key[i]);
    }

    putchar('\n');
    
    return 0;
}
