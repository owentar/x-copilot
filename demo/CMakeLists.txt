cmake_minimum_required(VERSION 3.8)
project(x_copilot_demo)

set(SOURCE_FILES
        portaudio-demo.cpp
        XPlaneDataRefSDKStub.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} x_copilot)