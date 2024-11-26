//
// Created by MAXIM on 25.10.2024.
//

#include "Memory_Page.hpp"

Memory_Page::Memory_Page(QWidget* parent)
{  
    layout = new QVBoxLayout();
    mPlot = new QCustomPlot();

    mPlot->yAxis->setLabel("Load");

    QPen pen(QColor(255,215,0));
    pen.setWidth(2);

    mPlot->addGraph();
    mPlot->graph(0)->setPen(pen);

    mPlot->legend->setVisible(false);

    auto mem = MemoryUsage();

    mPlot->xAxis->setRange(0,10);
    mPlot->yAxis->setRange(0,mem[Memory::mTotal]);

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Memory_Page::updateMemory);
    timer->start(1000);

    layout->addWidget(mPlot);
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
    double usage = memory[Memory::mUsed];
    yMem.append(usage);

    double currentTime = startTime + count++;
    x.append(currentTime);

    mPlot->xAxis->setRange(currentTime - 10, currentTime);

    mPlot->graph(0)->setData(x,yMem);
    mPlot->replot();
}