cmake_minimum_required(VERSION 3.8)
project(x_copilot)

set(SOURCE_FILES
        main.cpp
        Command.cpp
        Command.h
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

target_compile_definitions(${PROJECT_NAME} PUBLIC XPLM200=1 XPLM210=1)

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
            ${PROJECT_SOURCE_DIR}/lib/portaudio/lib/libportaudio.a
            ${PROJECT_SOURCE_DIR}/lib/sphinxbase/lib/libsphinxbase.a
            ${PROJECT_SOURCE_DIR}/lib/pocketsphinx/lib/libpocketsphinx.a
        )

if(APPLE)
    find_library(XPLM_LIBRARY XPLM ${PROJECT_SOURCE_DIR}/lib/XPSDK/Libraries/Mac)
    find_library(XPWIDGETS_LIBRARY XPWidgets ${PROJECT_SOURCE_DIR}/lib/XPSDK/Libraries/Mac)
    find_library(CORESERVICES_LIBRARY CoreServices)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)
    find_library(COREAUDIO_LIBRARY CoreAudio)
    find_library(AUDIOUNIT_LIBRARY AudioUnit)
    find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)

    target_compile_definitions(${PROJECT_NAME} PUBLIC APL=1)

    target_link_libraries(${PROJECT_NAME}
            PUBLIC
                ${CORESERVICES_LIBRARY}
                ${COREFOUNDATION_LIBRARY}
                ${COREAUDIO_LIBRARY}
                ${AUDIOTOOLBOX_LIBRARY}
                ${AUDIOUNIT_LIBRARY}
                ${XPLM_LIBRARY}
                ${PROJECT_SOURCE_DIR}/lib/XPSDK/Libraries/Mac/XPWidgets.framework
            )
elseif(UNIX)
    target_compile_definitions(${PROJECT_NAME} PUBLIC LIN=1)
elseif(WIN32)
    find_library(XPLM_LIBRARY XPLM ${PROJECT_SOURCE_DIR}/lib/XPSDK/Libraries/Win)
    find_library(XPWIDGETS_LIBRARY XPWidgets ${PROJECT_SOURCE_DIR}/lib/XPSDK/Libraries/Win)

    target_compile_definitions(${PROJECT_NAME} PUBLIC IBM=1)

    target_link_libraries(${PROJECT_NAME}
            PUBLIC
                ${XPLM_LIBRARY}
                ${PROJECT_SOURCE_DIR}/lib/XPSDK/Libraries/Win
                #            ${XPWIDGETS_LIBRARY}
                #            ${PROJECT_SOURCE_DIR}/lib/XPSDK/Libraries/Mac/XPLM.framework
                ${PROJECT_SOURCE_DIR}/lib/portaudio/lib/libportaudio.a
                ${PROJECT_SOURCE_DIR}/lib/sphinxbase/lib/libsphinxbase.a
                ${PROJECT_SOURCE_DIR}/lib/pocketsphinx/lib/libpocketsphinx.a
            )
endif()
