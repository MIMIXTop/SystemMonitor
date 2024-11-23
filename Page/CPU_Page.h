//
// Created by mimixtop on 02.11.24.
//

#ifndef QT_TEST_CPU_PAGE_H
#define QT_TEST_CPU_PAGE_H

#include "Utils/CpuMonitor.h"

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QGridLayout>
#include "../qcustomplot/qcustomplot.h"

#include <string>
#include <thread>
#include <fstream>
#include <vector>

class CPU_Page : public QWidget {
    Q_OBJECT

public:
    explicit CPU_Page(QWidget *parent = nullptr);

private:
    unsigned int corsCounter = std::thread::hardware_concurrency();
    QCustomPlot *mPlot;
    QCustomPlot *tempPlot;
    QGridLayout *layout;
    std::vector<CPUStats> prevStats;

    int timeIndex = 0;

private slots:
    void updateCpuUsage();
    void updateCpuTemper();
};

inline std::vector PenColor = {
    QPen (Qt::blue),
    QPen (Qt::darkBlue),
    QPen (Qt::green),
    QPen (Qt::darkGreen),
    QPen (Qt::cyan),
    QPen (Qt::darkCyan),
    QPen (Qt::magenta),
    QPen (Qt::darkMagenta),
    QPen (Qt::yellow),
    QPen(Qt::darkYellow),
    QPen(Qt::white),
    QPen(Qt::gray),
    QPen(Qt::darkGray),
    QPen(Qt::darkGray),


};

#endif //QT_TEST_CPU_PAGE_H
