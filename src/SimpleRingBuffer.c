//
// Created by Marc Zahno on 28.06.20.
//

#include "SimpleRingBuffer.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 512
#define BUFFER_POOL_SIZE 5

struct RingBuffer_s {
    bool isInUse;
    uint16_t index; // Points to the last char added to the buffer.
    uint8_t data[BUFFER_SIZE];
};

static struct RingBuffer_s BufferPool[BUFFER_POOL_SIZE];

static inline uint16_t DecrementIndexBy(uint16_t index, uint16_t subtrahend){
    return (index + BUFFER_SIZE - subtrahend) % BUFFER_SIZE;
}
static inline uint16_t IncrementIndexBy(uint16_t index, uint16_t addend){
    return (index + addend) % BUFFER_SIZE;
}
static inline uint16_t IncrementIndex(uint16_t index){
    return IncrementIndexBy(index, 1);
}
static inline void PutCharIntoBuffer(RingBuffer instance, uint8_t c){
    instance->data[instance->index] = c;
    instance->index = IncrementIndex(instance->index);
}
inline uint32_t RingBuffer_GetBufferPoolSize(){
    return BUFFER_POOL_SIZE;
}
inline uint32_t RingBuffer_GetBufferSize(){
    return BUFFER_SIZE;
}
static inline void ForEachInstance(void (*f)(RingBuffer buffer)){
    for(uint32_t i=0; i<BUFFER_POOL_SIZE; i++){
        RingBuffer currentBuffer = &BufferPool[i];
        f(currentBuffer);
    }
}
static void ResetData(RingBuffer instance){
    for(uint32_t i=0; i<BUFFER_SIZE; i++){
        instance->data[i] = 0;
    }
}
static RingBuffer FindFreeInstance(){

    // Search for a free buffer in the buffer pool.
    for(uint32_t i=0; i<BUFFER_POOL_SIZE; i++){
        RingBuffer currentBuffer = &BufferPool[i];

        if(currentBuffer->isInUse == false)
            return currentBuffer;
    }

    // No free buffers available, sorry!
    return NULL;
}
void RingBuffer_Destroy(RingBuffer instance){
    if(instance == NULL) return;

    instance->isInUse = false;
    instance->index = 0;
    ResetData(instance);
}
void RingBuffer_DestroyAll(){
    ForEachInstance(RingBuffer_Destroy);
}

RingBuffer RingBuffer_CreateInstance(){
    RingBuffer instance = FindFreeInstance();

    if(instance != NULL) {
        instance->isInUse = true;
        instance->index = 0;
        ResetData(instance);
    }

    return instance;
}

void RingBuffer_Add(RingBuffer instance, uint8_t* data, size_t length){
    if(instance == NULL) return;
    if(instance->isInUse == false) return;

    for(int i=0; i<length; i++){
        PutCharIntoBuffer(instance, data[i]);
    }
}
void RingBuffer_Get(RingBuffer instance, uint8_t *buffer, uint32_t from, uint32_t to){
    if(instance == NULL) return;
    if(instance->isInUse == false) return;

    const auto startIndex = DecrementIndexBy(instance->index, from);
    const auto endIndex = DecrementIndexBy(instance->index, to);

    auto i=0;
    auto currentIndex = startIndex;
    do{
        buffer[i] = instance->data[currentIndex];
        currentIndex = IncrementIndex(currentIndex);
        i++;
    } while (currentIndex != endIndex);
}


