//
// Created by mimixtop on 10.11.24.
//

#ifndef PROCESSES_HPP
#define PROCESSES_HPP

#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <QVector>
#include <QStringList>
#include <QRegExp>

struct Processes {
    QString name;
    QString user;
    int pid;
    float cpu_load;
    float memory_load;
};

QVector<Processes> GetProcesses();

#endif //PROCESSES_HPP
