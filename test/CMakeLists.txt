project(x_copilot_test)

add_subdirectory(lib/googletest)

file(GLOB COMMON_SRC
        main.cpp
        CommandRecognizerTest.cpp
        utilsTest.cpp
        integration/CommandsConfigReaderTest.cpp
        integration/CommandsTest.cpp
        CommandsProviderTest.cpp
        util/XPlaneDataRefSDKMock.h)
file(GLOB UNIX_SRC
        UnixRecognizerTest.cpp)

if(WIN32)
    set(SOURCE_FILES ${COMMON_SRC} ${WIN_SRC})
else()
    set(SOURCE_FILES ${COMMON_SRC} ${UNIX_SRC})
endif()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC IBM=1)
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC APL=1)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
        ${gmock_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}/include
        $<TARGET_PROPERTY:x_copilot,INTERFACE_INCLUDE_DIRECTORIES>)

target_link_libraries(${PROJECT_NAME} gmock gmock_main x_copilot)

file(COPY ${POCKETSPHINX_DATA_DIR} DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${CONFIG_DATA_DIR} DESTINATION ${PROJECT_BINARY_DIR})
file(COPY data DESTINATION ${PROJECT_BINARY_DIR})
