cmake_minimum_required(VERSION 3.8)
project(x_copilot_demo)

set(SOURCE_FILES
        demo.cpp
        XPlaneDataRefSDKStub.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC IBM=1)
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC APL=1)
endif()

target_link_libraries(${PROJECT_NAME} x_copilot)

file(COPY ${POCKETSPHINX_DATA_DIR} DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${CONFIG_DATA_DIR} DESTINATION ${PROJECT_BINARY_DIR})