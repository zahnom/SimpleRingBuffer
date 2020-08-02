#include <iostream>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

extern "C" {
#include "SimpleRingBuffer.h"
}

int main() {
    RingBuffer instance = RingBuffer_CreateInstance();

    uint8_t data[] = {'C','o','n','a','n','1','2','3'};
    RingBuffer_Add(instance, data, sizeof(data));
    printf("Test passed!\n");
}
