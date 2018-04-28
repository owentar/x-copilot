project(x_copilot_test)

add_subdirectory(lib/googletest)

set(SOURCE_FILES
        main.cpp
        CommandTest.cpp
        RecognizerTest.cpp
        utilsTest.cpp
        XCopilotTest.cpp
        integration/CommandsConfigReaderTest.cpp
        integration/CommandsTest.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
        ${gmock_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}/include
        $<TARGET_PROPERTY:x_copilot,INTERFACE_INCLUDE_DIRECTORIES>)

target_link_libraries(${PROJECT_NAME} gmock gmock_main x_copilot)

file(COPY ${POCKETSPHINX_DATA_DIR} DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${CONFIG_DATA_DIR} DESTINATION ${PROJECT_BINARY_DIR})
file(COPY data DESTINATION ${PROJECT_BINARY_DIR})
