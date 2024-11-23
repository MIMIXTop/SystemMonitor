//
// Created by MAXIM on 25.10.2024.
//

#include "Memory_Page.hpp"

Memory_Page::Memory_Page(QWidget* parent)
{
    resize(700,600);
    layout = new QVBoxLayout(this);
    plot = new QCustomPlot();
    layout->addWidget(plot);

    plot->xAxis->setLabel("Load (%)");

    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::black));

    plot->legend->setVisible(false);

    plot->xAxis->setRange(0,10);
    plot->yAxis->setRange(0,100);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Memory_Page::updateMemory);
    timer->start(1000);
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

    yMem.append(memory[Memory::mUsed] / memory[Memory::mTotal] * 100);

    double currentTime = startTime - count++;
    x.append(currentTime);

    plot->xAxis->setRange(currentTime - 10, currentTime);
    plot->graph(0)->setData(x,yMem);
    plot->replot();
}