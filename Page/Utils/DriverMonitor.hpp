#ifndef DRIVERMONITOR_HPP
#define DRIVERMONITOR_HPP

#include <vector>
#include <sys/statvfs.h>

#include <QMessageBox>

std::vector<float> getDriverStats();

#endif //DRIVERMONITOR_HPP
