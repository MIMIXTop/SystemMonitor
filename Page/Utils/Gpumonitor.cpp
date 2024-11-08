//
// Created by mimixtop on 08.11.24.
//


#include "Gpumonitor.hpp"

#include <iostream>

const std::vector<GPU> GetPlatforms() {
    std::vector<GPU> platforms;
    GPU temp;
    unsigned counter = 0;

    cl_uint platformCount;
    cl_platform_id *platform = nullptr;

    cl_int err = clGetPlatformIDs(0, nullptr, &platformCount);

    if (err != CL_SUCCESS) {
        std::cerr << "Failed to get number of platforms. Error: " << err << std::endl;
        return {};
    }

    platform = new cl_platform_id[platformCount];

    err = clGetPlatformIDs(platformCount, platform, nullptr);
    if (err != CL_SUCCESS) {
        std::cerr << "Failed to get platforms. Error: " << err << std::endl;
        return {};
    }

    for (cl_uint i = 0; i < platformCount; ++i) {
        cl_uint deviceCount;
        err = clGetDeviceIDs(platform[i], CL_DEVICE_TYPE_GPU, 0, nullptr, &deviceCount);
        if (err != CL_SUCCESS && deviceCount > 0) {
            cl_device_id *deviceIds = new cl_device_id[deviceCount];
            err = clGetDeviceIDs(platform[i], CL_DEVICE_TYPE_GPU, 0, deviceIds, nullptr);
            if (err == CL_SUCCESS) {
                clGetDeviceInfo(deviceIds[0], CL_DEVICE_NAME, sizeof(temp.name),temp.name, nullptr);
                clGetDeviceInfo(deviceIds[0],CL_DEVICE_GLOBAL_MEM_SIZE,sizeof(cl_ulong) , &temp.memory,nullptr);
                clGetDeviceInfo(deviceIds[0],CL_DEVICE_MAX_CLOCK_FREQUENCY,sizeof(cl_uint) ,&temp.frequency,nullptr);
                platforms.push_back(temp);
            }
            delete[] deviceIds;
        }

        err = clGetDeviceIDs(platform[i], CL_DEVICE_TYPE_CPU, 0, nullptr, &platformCount);
        if (err == CL_SUCCESS && deviceCount > 0) {
            cl_device_id *deviceIds = new cl_device_id[deviceCount];
            err = clGetDeviceIDs(platform[i], CL_DEVICE_TYPE_CPU, 0, deviceIds, nullptr);
            if (err == CL_SUCCESS) {
                clGetDeviceInfo(deviceIds[0], CL_DEVICE_NAME, sizeof(temp.name),temp.name, nullptr);
                clGetDeviceInfo(deviceIds[0],CL_DEVICE_GLOBAL_MEM_SIZE,sizeof(cl_ulong) , &temp.memory,nullptr);
                clGetDeviceInfo(deviceIds[0],CL_DEVICE_MAX_CLOCK_FREQUENCY,sizeof(cl_uint) ,&temp.frequency,nullptr);
                platforms.push_back(temp);
            }
        }

        if (deviceCount == 0) {
            std::cout << "No devices found for this platform." << std::endl;
            return {};
        }
    }

    delete[] platform;
    return platforms;
}

const int GetFrequency() {
    std::array<char,128> buffer;
    std::string load;

    std::unique_ptr<FILE,decltype(&pclose)> pipe(popen("nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader", "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("Failed to open pipe stream.");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        load.append(buffer.data());
    }
    int result ;

    std::regex regex(R"(/d+)");

    std::smatch match;
    std::regex_search(load, match, regex);
    result = std::stoi(match.str(0));
    return result;
}

