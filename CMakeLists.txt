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
        Charts
        REQUIRED)

include_directories(/usr/include)

set(OpenCL_LIBRARY /usr/lib64/libOpenCL.so.1)

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
        Page/Utils/DriverMonitor.cpp
        Page/Utils/DriverMonitor.hpp
        Page/Driver_Page.cpp
        Page/Driver_Page.hpp
        Page/Utils/Gpumonitor.cpp
        Page/Utils/Gpumonitor.hpp
        Page/GPU_Page.cpp
        Page/GPU_Page.hpp
)

find_package(OpenCL REQUIRED)

add_executable(QT_test ${PROJECT_SOURCES})  # Исправлено на PROJECT_SOURCES
target_link_libraries(QT_test
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
)

target_link_libraries(QT_test ${OpenCL_LIBRARY})