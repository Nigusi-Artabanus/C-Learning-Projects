#include "base32.hpp"
#include <bits/time.h>
#include <time.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define SECRET "VXYLMUZAMMRWT5LFWBVDXCLYPJAMPZ5A"

static void debug_binary(uint8_t *buf, size_t len){
    for (int i = 0; i < 20; i++) {
        printf("%02X", buf[i]);
    }
    putchar('\n'); 
}
static time_t unixepoch(){
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
    return tp.tv_sec;
}

static void encode_time_step(uint64_t step, uint8_t *dst){
    for (int i = 0; i < 8; i++) {
    dst[i] = (step >> (7 - i) * 8) & 0xFF;
    }
}
int main() {
    uint8_t key[20];
    base32_decode(SECRET, key, sizeof(key));
    
    uint64_t time_step = unixepoch() / 30;
    printf("%ld\n", time_step);
    
    return 0;
}
