//
// Created by mimixtop on 03.11.24.
//

#include "MemoryMonitor.hpp"

std::vector<std::string> readFile(){
    std::ifstream file;
    std::string line;
    std::vector<std::string> result;

    file.open("/proc/meminfo");

    if(file.is_open()){
        while (std::getline(file,line))
        {
            result.push_back(line);
        }
    }else{
        throw std::runtime_error("Unable to open /proc/meminfo");
    }

    return result;
}

std::vector<long long> stringConvertToInt(std::vector<std::string> data){
    std::vector<long long > result;

    for (auto &&line : data){
        result.push_back(std::stoll(line.substr(line.find_first_of("0123456789"))));
    }

    return result;
}

std::array<float,2> MemoryUsage(){
    std::vector data = stringConvertToInt(readFile());

    auto memTotal = data.at(0);
    auto memFree = data.at(1);
    auto buffer = data.at(3);
    auto cached = data.at(4);
    auto swapTotal = data.at(14);
    auto swapFree = data.at(15);
    auto sreclaimable = data.at(23);
    auto shmem = data.at(22);

    cached = (cached + sreclaimable - shmem);
    auto memUsed = (memTotal - (memFree + buffer + cached));
    auto swapUsed = (swapTotal - swapFree);

    return {static_cast<float>(memTotal / 1024.0 / 1024),static_cast<float>(memUsed / 1024.0 / 1024)};
}

