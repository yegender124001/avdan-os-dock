cmake_minimum_required(VERSION 3.14)

project(avdan-os-dock VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)
find_package(KF5WindowSystem)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        dockwindow.h dockwindow.cpp
        appmodel.h appmodel.cpp
        applicationitem.h
        utils.h utils.cpp
        systemappmonitor.h systemappmonitor.cpp
        systemappitem.h systemappitem.cpp
        processprovider.h processprovider.cpp
        xwindowinterface.h xwindowinterface.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(avdan-os-dock
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET avdan-os-dock APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(avdan-os-dock SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(avdan-os-dock
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(avdan-os-dock
  PRIVATE KF5::WindowSystem Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick xcb Qt5X11Extras)

install(TARGETS avdan-os-dock
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(avdan-os-dock)
    qt_finalize_executable(avdan-os-dock)
endif()
