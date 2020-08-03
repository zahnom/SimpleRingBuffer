//
// Created by Marc Zahno on 28.06.20.
//

#ifndef SIMPLE_RING_BUFFER_SIMPLERINGBUFFER_H
#define SIMPLE_RING_BUFFER_SIMPLERINGBUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define SimpleRingBuffer_BUFFER_SIZE 512
#define SimpleRingBuffer_BUFFER_POOL_SIZE 5

typedef struct RingBuffer_s *RingBuffer;

uint32_t RingBuffer_GetBufferPoolSize();
uint32_t RingBuffer_GetBufferSize();

RingBuffer RingBuffer_CreateInstance();
void RingBuffer_Destroy(RingBuffer instance);
void RingBuffer_DestroyAll();
void RingBuffer_Add(RingBuffer instance, uint8_t *data, size_t length);
void RingBuffer_Get(RingBuffer instance, uint8_t *buffer, uint32_t from, uint32_t to);

#endif //SIMPLE_RING_BUFFER_SIMPLERINGBUFFER_H
