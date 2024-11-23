//
// Created by MAXIM on 25.10.2024.
//

#include "Memory_Page.hpp"

#include <iostream>

Memory_Page::Memory_Page(QWidget* parent)
{  
    layout = new QVBoxLayout();
    tempPlot = new QCustomPlot();

    tempPlot->yAxis->setLabel("Temp (^C)");

    tempPlot->addGraph();
    tempPlot->graph(0)->setPen(QPen (Qt::blue));

    tempPlot->legend->setVisible(false);

    tempPlot->xAxis->setRange(0,10);
    tempPlot->yAxis->setRange(0,100);

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Memory_Page::updateMemory);
    timer->start(1000);

    layout->addWidget(tempPlot);
    setLayout(layout);
}

void Memory_Page::updateMemory() {
    static QVector<double> x;
    static QVector<double> yMem;
    static double startTime = 0;
    static int count = 0;

    auto memory = MemoryUsage();

    if (x.size() > 10) {
        x.remove(0);
        yMem.remove(0);
    }
    double usage = memory[Memory::mUsed] / memory[Memory::mTotal] * 100;
    yMem.append(usage);

    double currentTime = startTime + count++;
    x.append(currentTime);

    tempPlot->xAxis->setRange(currentTime - 10, currentTime);

    tempPlot->graph(0)->setData(x,yMem);
    tempPlot->replot();
}