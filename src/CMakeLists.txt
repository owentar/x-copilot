cmake_minimum_required(VERSION 3.8)
project(x_copilot)

#include_directories(${PROJECT_SOURCE_DIR}/lib/XPSDK/CHeaders/XPLM")
#include_directories(${PROJECT_SOURCE_DIR}/lib/XPSDK/CHeaders/Widgets")
#include_directories(${PROJECT_SOURCE_DIR}/lib/portaudio/includes")
#include_directories(${PROJECT_SOURCE_DIR}/lib/sphinxbase/includes")
#include_directories(${PROJECT_SOURCE_DIR}/lib/sphinxbase/includes/sphinxbase")
#include_directories(${PROJECT_SOURCE_DIR}/lib/pocketsphinx/includes")
#include_directories(${PROJECT_SOURCE_DIR}/lib/pocketsphinx/includes/pocketsphinx")

#add_library(xpsdk INTERFACE IMPORTED)
#target_include_directories(xpsdk INTERFACE
#        ${PROJECT_SOURCE_DIR}/lib/XPSDK/CHeaders/XPLM"
#        ${PROJECT_SOURCE_DIR}/lib/XPSDK/CHeaders/Widgets")
#set_target_properties(xpsdk INTERFACE
#        IMPORTED_LOCATION )

find_library(XPLM_LIBRARY XPLM ${PROJECT_SOURCE_DIR}/lib/XPSDK/Libraries/Mac)
find_library(XPWIDGETS_LIBRARY XPWidgets ${PROJECT_SOURCE_DIR}/lib/XPSDK/Libraries/Mac)
find_library(CORESERVICES_LIBRARY CoreServices)
find_library(COREFOUNDATION_LIBRARY CoreFoundation)
find_library(COREAUDIO_LIBRARY CoreAudio)
find_library(AUDIOUNIT_LIBRARY AudioUnit)
find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAPL=1 -DXPLM200=1 -DXPLM210=1")

#target_compile_definitions(${PROJECT_NAME} PUBLIC APL=1 XPLM200=1 XPLM210=1)

set(SOURCE_FILES
        main.cpp
        Microphone.cpp
        Microphone.h
        MicrophoneHandler.h
        PocketsphinxWrapper.cpp
        PocketsphinxWrapper.h
        Recognizer.cpp
        Recognizer.h
        StatusWindow.cpp
        StatusWindow.h
        XCopilot.cpp
        XCopilot.h)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_compile_features(${PROJECT_NAME}
        PRIVATE
            cxx_lambdas
            cxx_auto_type
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC
            ${PROJECT_SOURCE_DIR}
            ${PROJECT_SOURCE_DIR}/lib/XPSDK/CHeaders/XPLM
            ${PROJECT_SOURCE_DIR}/lib/XPSDK/CHeaders/Widgets
            ${PROJECT_SOURCE_DIR}/lib/portaudio/includes
            ${PROJECT_SOURCE_DIR}/lib/sphinxbase/includes
            ${PROJECT_SOURCE_DIR}/lib/sphinxbase/includes/sphinxbase
            ${PROJECT_SOURCE_DIR}/lib/pocketsphinx/includes
            ${PROJECT_SOURCE_DIR}/lib/pocketsphinx/includes/pocketsphinx
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
            ${CORESERVICES_LIBRARY}
            ${COREFOUNDATION_LIBRARY}
            ${COREAUDIO_LIBRARY}
            ${AUDIOTOOLBOX_LIBRARY}
            ${AUDIOUNIT_LIBRARY}
            ${XPLM_LIBRARY}
#            ${XPWIDGETS_LIBRARY}
#            ${PROJECT_SOURCE_DIR}/lib/XPSDK/Libraries/Mac/XPLM.framework
            ${PROJECT_SOURCE_DIR}/lib/XPSDK/Libraries/Mac/XPWidgets.framework
            ${PROJECT_SOURCE_DIR}/lib/portaudio/lib/libportaudio.a
            ${PROJECT_SOURCE_DIR}/lib/sphinxbase/lib/libsphinxbase.a
            ${PROJECT_SOURCE_DIR}/lib/pocketsphinx/lib/libpocketsphinx.a
        )
