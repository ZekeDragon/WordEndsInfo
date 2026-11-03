cmake_minimum_required(VERSION 3.19)
project(WordEndsInfo
    VERSION 0.1.0
    DESCRIPTION "Word First and Last Letters Application"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()
set(CMAKE_AUTORCC ON)

set(WordEndsInfo_PRIVATE_HEADERS
)

set(WordEndsInfo_SOURCES
    main.cpp

    alphabetselector.cpp
    alphabetselector.hpp

    application.cpp
    application.hpp

    base.hpp

    dictionarylistmodel.cpp
    dictionarylistmodel.hpp

    mainwindow.cpp
    mainwindow.hpp
    mainwindow.ui
)

list(TRANSFORM WordEndsInfo_PRIVATE_HEADERS PREPEND "src/private/")
list(TRANSFORM WordEndsInfo_SOURCES PREPEND "src/")

qt_add_executable(WordEndsInfo
    WIN32 MACOSX_BUNDLE
    ${WordEndsInfo_SOURCES}
    ${WordEndsInfo_PRIVATE_HEADERS}
    data.qrc
)

qt_add_translations(
    TARGETS WordEndsInfo
    TS_FILES WordEndsInfo_en_US.ts
)

target_include_directories(WordEndsInfo
    PUBLIC
        "${PROJECT_SOURCE_DIR}/src"
)

target_link_libraries(WordEndsInfo
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS WordEndsInfo
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET WordEndsInfo
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
