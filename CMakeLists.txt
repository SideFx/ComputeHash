cmake_minimum_required(VERSION 3.16)

project(ComputeHash VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS LinguistTools)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

qt_add_translations(ComputeHash TS_FILES ComputeHash_en_US.ts)

qt_standard_project_setup(
    I18N_SOURCE_LANGUAGE de         # optional - this is the default
    I18N_TRANSLATED_LANGUAGES en
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ComputeHash
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        libsha512.h
        ComputeHash_en_US.ts
    )

qt_add_translations(ComputeHash TS_FILES ComputeHash_en_US.ts)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ComputeHash APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ComputeHash SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ComputeHash
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ComputeHash PRIVATE Qt${QT_VERSION_MAJOR}::Widgets "${CMAKE_SOURCE_DIR}/libsha512.a")
add_dependencies(ComputeHash update_translations)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ComputeHash)
endif()
set_target_properties(ComputeHash PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ComputeHash
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ComputeHash)
endif()
