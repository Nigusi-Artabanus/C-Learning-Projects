#include "base32.hpp"
#include <stdio.h>
#include <string.h>

//#define SECRET "FRERT5GY76GHVV321DASSC4HB6TH67GH"
int main() {
    char src[] = "Hello Base32!";
    char dst[80];
    base32_encode((uint8_t *)src, dst, strlen(src));
    
    printf("%s\n", dst);

    char encoded[] = "JBSWY3DPFQQHO33SNRSCC===";
    int ndecoded = base32_decode(encoded, dst, sizeof(dst));
    printf("%d\n", ndecoded);
    printf("%s\n", dst);
}
