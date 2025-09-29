cmake_minimum_required(VERSION 3.16)
project(ClientStudio_Clean LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt5/Qt6 compatible
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(ClientStudio_Clean
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
)

target_link_libraries(ClientStudio_Clean PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
