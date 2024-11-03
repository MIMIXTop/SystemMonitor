//
// Created by mimixtop on 03.11.24.
//

#ifndef MEMORYMONITOR_HPP
#define MEMORYMONITOR_HPP
#include <array>
#include <fstream>
#include <string>
#include <sstream>
#include <QMessageBox>

enum Memory {
    Total,
    Free,
    Buffers,
    Cached,
    Used// excluding cache and buffers
};

std::array<float,5> MemoryMonitor();


#endif //MEMORYMONITOR_HPP
