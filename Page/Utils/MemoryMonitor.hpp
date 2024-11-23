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
    mTotal,
    mUsed
};

std::array<float,2> MemoryUsage();

std::vector<long long> stringConvertToInt(std::vector<std::string> data);
std::vector<std::string> readFile();


#endif //MEMORYMONITOR_HPP
