//
// Created by mimixtop on 08.11.24.
//

#ifndef GPUMONITOR_HPP
#define GPUMONITOR_HPP

#include <CL/cl.h>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <regex>

struct GPU {
    char name[128];
    cl_ulong memory;
    cl_uint frequency;
};

const std::vector<GPU> GetPlatforms();

#endif //GPUMONITOR_HPP
