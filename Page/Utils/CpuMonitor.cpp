//
// Created by mimixtop on 02.11.24.
//

#include "CpuMonitor.h"

std::vector<CPUStats> getCPUStats() {
    std::ifstream file("/proc/stat");
    std::string line;
    std::vector<CPUStats> stats;

    while (std::getline(file, line)) {
        if (line.substr(0, 3) == "cpu") {
            std::istringstream ss(line);
            CPUStats stat;
            ss >> stat.name >> stat.user >> stat.nice >> stat.system >> stat.idle >> stat.iowait
               >> stat.irq >> stat.softirq >> stat.steal >> stat.guest >> stat.guest_nice;
            stats.push_back(stat);
        }
    }
    return stats;
}

double calculateCPUUsage(const CPUStats& prev, const CPUStats& curr) {
    unsigned long prevIdle = prev.idle + prev.iowait;
    unsigned long currIdle = curr.idle + curr.iowait;

    unsigned long prevNonIdle = prev.user + prev.nice + prev.system + prev.irq + prev.softirq + prev.steal;
    unsigned long currNonIdle = curr.user + curr.nice + curr.system + curr.irq + curr.softirq + curr.steal;

    unsigned long prevTotal = prevIdle + prevNonIdle;
    unsigned long currTotal = currIdle + currNonIdle;

    unsigned long totalDiff = currTotal - prevTotal;
    unsigned long idleDiff = currIdle - prevIdle;

    return (double)(totalDiff - idleDiff) / totalDiff * 100;
}
