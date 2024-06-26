cmake_minimum_required(VERSION 3.5)

project(GAMES-Renderer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

set(TS_FILES GAMES-Renderer_zh_CN.ts)

set(PROJECT_SOURCES
        mainwindow.ui
        mainwindow.cpp
        mainwindow.h
        main.cpp
        ${TS_FILES}
)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)
link_directories(${PROJECT_SOURCE_DIR}/dlls)
file(GLOB_RECURSE srcs CONFIGURE_DEPENDS
    src/*.cpp
    src/*.vs
    src/*.fs
    include/*.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GAMES-Renderer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${srcs}
        src/shaders/PhoneVertex.vsh
        src/shaders/PhoneFragment.fsh
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET GAMES-Renderer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(GAMES-Renderer SHARED
            ${PROJECT_SOURCES}
            ${srcs}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(GAMES-Renderer
            ${PROJECT_SOURCES}
            ${srcs}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()


target_link_libraries(GAMES-Renderer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(GAMES-Renderer PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(GAMES-Renderer PRIVATE ASSIMP)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GAMES-Renderer)
endif()
set_target_properties(GAMES-Renderer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS GAMES-Renderer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GAMES-Renderer)
endif()
