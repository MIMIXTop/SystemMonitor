//
// Created by mimixtop on 10.11.24.
//

#ifndef PROCESSES_HPP
#define PROCESSES_HPP

#include <QString>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <regex>
#include <unistd.h>
#include <pwd.h>

struct Processes {
    QString name;
    QString user;
    int pid;
    float cpu_load;
    float memory_load;
};

std::string GetCurrentUser();

std::vector<Processes> GetProcesses(const std::string& currentUser);

#endif //PROCESSES_HPP
