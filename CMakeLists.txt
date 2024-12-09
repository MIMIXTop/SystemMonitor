cmake_minimum_required(VERSION 3.16)

project(QT_test VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск необходимых компонентов Qt
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        PrintSupport
        REQUIRED)

# Указание на директории, где находятся заголовочные файлы
include_directories(${CMAKE_CURRENT_SOURCE_DIR} "/home/mimixtop/CLionProjects/SystemMonitor/qcustomplot")

# Установка переменной для библиотеки OpenCL
set(OpenCL_LIBRARY /usr/lib64/libOpenCL.so.1)

# Список исходных файлов проекта
set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.hpp
        qcustomplot/qcustomplot.h
        Page/Memory_Page.hpp
        Page/Memory_Page.cpp
        Page/CPU_Page.cpp
        Page/CPU_Page.h
        Page/Utils/CpuMonitor.cpp
        Page/Utils/CpuMonitor.h
        Page/Utils/MemoryMonitor.cpp
        Page/Utils/MemoryMonitor.hpp
        Page/Utils/SystemMonitor.cpp
        Page/Utils/SystemMonitor.hpp
        Page/System_Page.cpp
        Page/System_Page.hpp
        Page/Utils/Gpumonitor.cpp
        Page/Utils/Gpumonitor.hpp
        Page/Utils/Processes.cpp
        Page/Utils/Processes.hpp
        Page/Process_Page.cpp
        Page/Process_Page.hpp
)

# Поиск библиотеки OpenCL
find_package(OpenCL REQUIRED)

# Добавление исполняемого файла
add_executable(QT_test ${PROJECT_SOURCES})

# Линковка с библиотеками Qt и OpenCL
target_link_libraries(QT_test
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::PrintSupport
        ${OpenCL_LIBRARY}
)

# Убедитесь, что исходные файлы QCustomPlot также добавлены
set(QCUSTOMPLOT_SRC
        qcustomplot/qcustomplot.cpp
)

# Добавьте файлы QCustomPlot в проект
target_sources(QT_test PRIVATE ${QCUSTOMPLOT_SRC})