//
// Created by mimixtop on 02.11.24.
//

#ifndef QT_TEST_CPU_PAGE_H
#define QT_TEST_CPU_PAGE_H

#include "Utils/CpuMonitor.h"

#include <QWidget>
#include <QTableWidget>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>

#include <string>
#include <thread>
#include <fstream>
#include <vector>

class CPU_Page : public QWidget {
    Q_OBJECT

public:
    explicit CPU_Page(QWidget *parent = nullptr);

private:
    QLabel *CpuName;
    QLabel *CpuTemper;
    QTableWidget *Cpuload;
    QLayout *layout;
    std::vector<CPUStats> prevStats;

    std::string getCpuVender();

    unsigned int getCorsCounter();

private slots:
    void updateCpuUsage();
};

#endif //QT_TEST_CPU_PAGE_H
