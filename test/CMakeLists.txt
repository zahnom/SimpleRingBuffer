add_executable(GoogleTestsRun main.cpp SimpleRingBufferTests.cpp)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(GoogleTestsRun SimpleRingBuffer gtest gtest_main)