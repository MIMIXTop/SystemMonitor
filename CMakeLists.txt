cmake_minimum_required(VERSION 3.16)

project(QT_test VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.hpp
        CPU_Regs.hpp
        Page/Memory_Page.hpp
        Page/Memory_Page.cpp
        Page/CPU_Page.cpp
        Page/CPU_Page.h
        Page/Utils/CpuMonitor.cpp
        Page/Utils/CpuMonitor.h
        Page/Utils/MemoryMonitor.cpp
        Page/Utils/MemoryMonitor.hpp
)

add_executable(QT_test ${PROJECT_SOURCES})  # Исправлено на PROJECT_SOURCES
target_link_libraries(QT_test
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)