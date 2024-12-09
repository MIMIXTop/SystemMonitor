//
// Created by mimixtop on 08.11.24.
//

#include "Gpumonitor.hpp"

#include <iostream>

const std::vector<GPU> GetPlatforms() {
    std::vector<GPU> platforms;
    cl_uint platformCount;
    cl_platform_id *platformsArray = nullptr;

    // Получаем количество платформ
    cl_int err = clGetPlatformIDs(0, nullptr, &platformCount);
    if (err != CL_SUCCESS) {
        std::cerr << "Failed to get number of platforms. Error: " << err << std::endl;
        return {};
    }

    // Выделяем память для платформ
    platformsArray = new cl_platform_id[platformCount];
    err = clGetPlatformIDs(platformCount, platformsArray, nullptr);
    if (err != CL_SUCCESS) {
        std::cerr << "Failed to get platforms. Error: " << err << std::endl;
        delete[] platformsArray;
        return {};
    }

    // Проходим по всем платформам
    for (cl_uint i = 0; i < platformCount; ++i) {
        cl_uint deviceCount;

        // Получаем количество устройств GPU
        err = clGetDeviceIDs(platformsArray[i], CL_DEVICE_TYPE_GPU, 0, nullptr, &deviceCount);
        if (err != CL_SUCCESS) {
            std::cerr << "Failed to get number of GPU devices. Error: " << err << std::endl;
            continue;
        }

        // Если есть устройства, получаем информацию о них
        if (deviceCount > 0) {
            std::vector<cl_device_id> deviceIds(deviceCount);
            err = clGetDeviceIDs(platformsArray[i], CL_DEVICE_TYPE_GPU, deviceCount, deviceIds.data(), nullptr);
            if (err == CL_SUCCESS) {
                for (cl_uint j = 0; j < deviceCount; ++j) {
                    GPU temp;
                    clGetDeviceInfo(deviceIds[j], CL_DEVICE_NAME, sizeof(temp.name), temp.name, nullptr);
                    clGetDeviceInfo(deviceIds[j], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &temp.memory, nullptr);
                    clGetDeviceInfo(deviceIds[j], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_uint), &temp.frequency, nullptr);
                    platforms.push_back(temp);
                }
            }
        }

        // Получаем количество устройств CPU
        err = clGetDeviceIDs(platformsArray[i], CL_DEVICE_TYPE_CPU, 0, nullptr, &deviceCount);
        if (err == CL_SUCCESS && deviceCount > 0) {
            std::vector<cl_device_id> deviceIds(deviceCount);
            err = clGetDeviceIDs(platformsArray[i], CL_DEVICE_TYPE_CPU, deviceCount, deviceIds.data(), nullptr);
            if (err == CL_SUCCESS) {
                for (cl_uint j = 0; j < deviceCount; ++j) {
                    GPU temp;
                    clGetDeviceInfo(deviceIds[j], CL_DEVICE_NAME, sizeof(temp.name), temp.name, nullptr);
                    clGetDeviceInfo(deviceIds[j], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &temp.memory, nullptr);
                    clGetDeviceInfo(deviceIds[j], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_uint), &temp.frequency, nullptr);
                    platforms.push_back(temp);
                }
            }
        }
    }

    delete[] platformsArray;
    return platforms;
}
