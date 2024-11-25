//
// Created by mimixtop on 02.11.24.
//

#ifndef QT_TEST_CPUMONITOR_H
#define QT_TEST_CPUMONITOR_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

struct CPUStats {
    std::string name;
    unsigned long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
};

std::vector<CPUStats> getCPUStats();
double calculateCPUUsage(const CPUStats& prev, const CPUStats& curr);
double getCpuTemperature();

#endif //QT_TEST_CPUMONITOR_H