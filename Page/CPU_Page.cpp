#include "CPU_Page.h"

CPU_Page::CPU_Page(QWidget* parent) {
    layout = new QGridLayout();
    //cpuWidget = new CpuWidget();

    setLayout(layout);
    // Создание графика загрузки по ядрам
    mPlot = new QCustomPlot();

    mPlot->yAxis->setLabel("Load (%)");

    for(int i = 0; i < corsCounter; i++) {
        mPlot->addGraph();
        mPlot->graph(i)->setPen(PenColor.at(i));
    }

    layout->addWidget(mPlot,0,0);

    mPlot->xAxis->setRange(0,10);
    mPlot->yAxis->setRange(0,100);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CPU_Page::updateCpuUsage);
    timer->start(1000);

    prevStats = getCPUStats();

    //Создание графика температуры процессора

    tempPlot = new QCustomPlot();

    tempPlot->yAxis->setLabel("Temp (^C)");
    QPen pen(QColor(255,215,0));
    pen.setWidth(2);
    tempPlot->addGraph();
    tempPlot->graph(0)->setPen(pen);

    tempPlot->legend->setVisible(false);

    tempPlot->xAxis->setRange(0,10);
    tempPlot->yAxis->setRange(0,100);

    connect(timer, &QTimer::timeout, this, &CPU_Page::updateCpuTemper);

    layout->addWidget(tempPlot, 1, 0);
    //layout->addWidget(cpuWidget, 0, 1, 2, 1);
}

void CPU_Page::updateCpuUsage() {

    static QVector<double> x;
    static QVector<QVector<double>> yCpu(corsCounter);
    static double startTime = 0;
    static int count = 0;

    std::vector<CPUStats> currStats = getCPUStats();

    if(x.size() > 10) {
        x.remove(0);
        for(auto &y : yCpu) {
            y.remove(0);
        }
    }

    for (int i = 0; i < corsCounter; i++) {
        double cpuUsage = calculateCPUUsage(prevStats[i + 1],currStats[i + 1]);
        yCpu[i].append(cpuUsage);
    }

    double currTime = startTime + count++;
    x.append(currTime);

    mPlot->xAxis->setRange(currTime-10, currTime);

    for(int i = 0; i < corsCounter; i++) {
        mPlot->graph(i)->setData(x,yCpu.at(i));
    }

    mPlot->replot();

    prevStats = currStats;
}

void CPU_Page::updateCpuTemper() {
    static QVector<double> x;
    static QVector<double> yCpu;
    static double startTime = 0;
    static int count = 0;

    double temperature = getCpuTemperature();

    if(x.size() > 10) {
        x.remove(0);
        yCpu.remove(0);
    }

    yCpu.append(temperature);

    double currTime = startTime + count++;
    x.append(currTime);

    tempPlot->xAxis->setRange(currTime-10, currTime);

    tempPlot->graph(0)->setData(x,yCpu);
    tempPlot->replot();
}
