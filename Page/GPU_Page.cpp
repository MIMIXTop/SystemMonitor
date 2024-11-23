//
// Created by mimixtop on 08.11.24.
//

#include "GPU_Page.hpp"

#include <iostream>

GPU_Page::GPU_Page(QWidget *parent) {
    std::vector platform = GetPlatforms();
    table = new QTableWidget();
    table->setMinimumSize(100, 50);
    table->setMaximumSize(this->width(), 400);
    table->setColumnCount(3);
    table->setRowCount(platform.size());

    table->setColumnWidth(0, 300);

    for (int i = 0; i < platform.size(); ++i) {
        table->setItem(i,0,new QTableWidgetItem(QString(platform[i].name)));
        table->setItem(i,1,new QTableWidgetItem(QString::number(platform[i].memory / 1024 / 1024) + "Mb"));
        table->setItem(i,2,new QTableWidgetItem(QString::number(platform[i].frequency) + "MHz"));
    }

    layout = new QVBoxLayout(this);


    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table->resizeRowsToContents();
    table->resizeColumnsToContents();

    //график для видеокарты
    gpuPlot = new QCustomPlot();
    layout->addWidget(gpuPlot);

    gpuPlot->yAxis->setLabel("Load");

    gpuPlot->addGraph();
    gpuPlot->graph(0)->setPen(QPen(Qt::black));

    gpuPlot->legend->setVisible(false);

    gpuPlot->xAxis->setRange(0,10);
    gpuPlot->yAxis->setRange(0,100);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GPU_Page::UpdateGPULoad);
    timer->start(1000);
    layout->addWidget(table);

}

void GPU_Page::UpdateGPULoad() {
    QVector<double> x;
    QVector<double> yGpu;
    static double startTime = 0;
    static int count = 0;

    int load = GetLoadGpu();

    if(x.size() > 10) {
        x.remove(0);
        yGpu.remove(0);
    }

    yGpu.append(load);

    double currTime = startTime + count++;
    x.append(currTime);

    gpuPlot->xAxis->setRange(currTime - 10,currTime);

    gpuPlot->graph(0)->setData(x,yGpu);
    gpuPlot->replot();
}

