cmake_minimum_required(VERSION 3.8)
project(x_copilot_demo)

set(SOURCE_FILES
        demo.cpp
        XPlaneDataRefSDKStub.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} x_copilot)

file(COPY ${POCKETSPHINX_DATA_DIR} DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${CONFIG_DATA_DIR} DESTINATION ${PROJECT_BINARY_DIR})