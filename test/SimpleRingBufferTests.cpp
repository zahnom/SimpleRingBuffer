//
// Created by Marc Zahno on 28.06.20.
//

extern "C" {
#include "SimpleRingBuffer.h"
}

#include <numeric>
#include "gtest/gtest.h"

namespace SimpleRingBuffer {
    using namespace std;

    class BufferInstantiationTests : public ::testing::Test {
    protected:
        void TearDown() override {
            RingBuffer_DestroyAll();
        }
    };
    TEST_F(BufferInstantiationTests, GetOneInstance){
        RingBuffer instance = NULL;
        instance = RingBuffer_CreateInstance();

        ASSERT_NE(nullptr, instance);
    }
    TEST_F(BufferInstantiationTests, GetTwoInstances){
        RingBuffer instance1 = NULL;
        RingBuffer instance2 = NULL;
        instance1 = RingBuffer_CreateInstance();
        instance2 = RingBuffer_CreateInstance();

        ASSERT_NE(nullptr, instance1);
        ASSERT_NE(nullptr, instance2);
        ASSERT_NE(instance1, instance2);
    }
    TEST_F(BufferInstantiationTests, NoFreeInstancesAvailable){
        RingBuffer currentInstance = NULL;
        uint32_t bufferPoolSize = RingBuffer_GetBufferPoolSize();

        // Use all available instances
        for (int i = 0; i < bufferPoolSize; i++) {
            currentInstance = RingBuffer_CreateInstance();
            ASSERT_NE(nullptr, currentInstance);
        }

        // No instances should be free anymore
        currentInstance = RingBuffer_CreateInstance();
        ASSERT_EQ(nullptr, currentInstance);
    }
    TEST_F(BufferInstantiationTests, DestroyInstance){
        RingBuffer currentInstance = NULL;
        uint32_t bufferPoolSize = RingBuffer_GetBufferPoolSize();

        // Use all available instances
        for (int i = 0; i < bufferPoolSize; i++) {
            currentInstance = RingBuffer_CreateInstance();
            ASSERT_NE(nullptr, currentInstance);
        }

        // No instances should be free anymore
        RingBuffer newInstance = RingBuffer_CreateInstance();
        ASSERT_EQ(nullptr, newInstance);

        // Free one instance and check again
        RingBuffer_Destroy(currentInstance);
        currentInstance = NULL;
        newInstance = RingBuffer_CreateInstance();
        ASSERT_NE(nullptr, newInstance);
    }

    class AddDataTests : public ::testing::Test {
    protected:
        void SetUp() override {
            CurrentTestClass = this;
        }
        void TearDown() override {
            RingBuffer_DestroyAll();
        }

    public:
        static AddDataTests *CurrentTestClass;
        RingBuffer BufferUnderTest = RingBuffer_CreateInstance();

    };
    AddDataTests *AddDataTests::CurrentTestClass = NULL;

    TEST_F(AddDataTests, AddData){
        uint8_t dataAddedToBuffer[] = {1, 2, 3, 4, 'a', 'b', 'c'};
        RingBuffer_Add(
                CurrentTestClass->BufferUnderTest,
                dataAddedToBuffer, sizeof(dataAddedToBuffer));

        uint8_t dataRetrievedFromBuffer[sizeof(dataAddedToBuffer)] = {0};
        uint32_t fromBufferStart = sizeof(dataAddedToBuffer);
        uint32_t toBufferHead = 0;
        RingBuffer_Get(
                CurrentTestClass->BufferUnderTest,
                dataRetrievedFromBuffer,
                fromBufferStart, toBufferHead);

        ASSERT_EQ(0, memcmp(dataAddedToBuffer,dataRetrievedFromBuffer,5));
    }
    TEST_F(AddDataTests, AddDataWithCarryover){

        // fill up buffer up until two chars before carryover
        const auto bufferSize = RingBuffer_GetBufferSize();
        uint8_t fillByte[] = {'z'};
        for(auto i=0; i<(bufferSize-2); i++){
            RingBuffer_Add(
                    CurrentTestClass->BufferUnderTest,
                    fillByte, sizeof(fillByte));
        }

        // add test data
        uint8_t dataAddedToBuffer[] = {1, 2, 3, 4, 'a', 'b', 'c'};
        RingBuffer_Add(
                CurrentTestClass->BufferUnderTest,
                dataAddedToBuffer, sizeof(dataAddedToBuffer));

        uint8_t dataRetrievedFromBuffer[sizeof(dataAddedToBuffer)] = {0};
        uint32_t fromBufferStart = sizeof(dataAddedToBuffer);
        uint32_t toBufferHead = 0;
        RingBuffer_Get(
                CurrentTestClass->BufferUnderTest,
                dataRetrievedFromBuffer,
                fromBufferStart, toBufferHead);

        ASSERT_EQ(0, memcmp(dataAddedToBuffer,dataRetrievedFromBuffer,5));
    }
}
