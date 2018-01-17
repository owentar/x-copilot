cmake_minimum_required(VERSION 3.8)
project(x_copilot)

set(CMAKE_CXX_STANDARD 17)
set(POCKETSPHINX_DATA_DIR ${PROJECT_SOURCE_DIR}/pocketsphinx-data)
set(CONFIG_DATA_DIR ${PROJECT_SOURCE_DIR}/config)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(demo)