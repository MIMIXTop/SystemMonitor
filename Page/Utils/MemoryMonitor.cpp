//
// Created by mimixtop on 03.11.24.
//

#include "MemoryMonitor.hpp"

std::array<float, 5> MemoryMonitor() {
    std::array<float, 5> result;
    std::ifstream memInf("/proc/meminfo");
    if (!memInf.is_open()) {
        QMessageBox::information(nullptr,"Error","File not found");
    }

    std::string line;

    long totalMem = 0;
    long usedMem = 0;
    long freeMem = 0;
    long cached = 0;
    long buffer = 0;

    while (std::getline(memInf, line)) {
        if (line.find("MemTotal:") == 0) {
            totalMem = std::stol(line.substr(line.find_first_of("0123456789")));
        } else if (line.find("MemFree:") == 0) {
            freeMem = std::stol(line.substr(line.find_first_of("0123456789")));
        } else if (line.find("Buffers:") == 0) {
            buffer = std::stol(line.substr(line.find_first_of("0123456789")));
        } else if (line.find("Cached:") == 0) {
            cached = std::stol(line.substr(line.find_first_of("0123456789")));
        }
    }

    memInf.close();

    usedMem = totalMem - cached - freeMem - buffer;

    result[Memory::Total] = static_cast<float>(totalMem) / 1024 / 1024;
    result[Memory::Used] = static_cast<float>(usedMem) / 1024 / 1024; ;
    result[Memory::Cached] = static_cast<float>(cached) / 1024 / 1024; ;
    result[Memory::Free] = static_cast<float>(freeMem) / 1024 / 1024; ;
    result[Memory::Buffers] = static_cast<float>(buffer) / 1024 / 1024; ;
    return result;
}
