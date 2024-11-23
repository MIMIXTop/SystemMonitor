#ifndef DRIVERMONITOR_HPP
#define DRIVERMONITOR_HPP

#include <vector>
#include <sys/statvfs.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sstream>
#include <thread>

#include <QMessageBox>
#include <QDir>

enum Driver {Total, Free, Used};

struct Cors {
    unsigned int physicalCors;
    unsigned int virtualCors;
};

std::string printKernelVersion();
std::string printDistroVersion();
std::vector<unsigned long long> getDriverStats();
std::string getCpuVender();
Cors getCores();
QString findDistroLogo();

#endif //DRIVERMONITOR_HPP
