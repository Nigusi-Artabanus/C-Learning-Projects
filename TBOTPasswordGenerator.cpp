#include "base32.h"
#include <stdio.h>
#include <string.h>

//#define SECRET "FRERT5GY76GHVV321DASSC4HB6TH67GH"
int main() {
    char src[] = "Hello";
    char dst[80];
    base32_encode((uint8_t *)src, dst, strlen(src));
    printf("Encoded: %s\n", dst);
return 0;
}
