//
// Created by mimixtop on 08.11.24.
//

#include "GPU_Page.hpp"

GPU_Page::GPU_Page(QWidget *parent) {
    std::vector platform = GetPlatforms();
    table = new QTableWidget();

    table->setColumnCount(3);
    table->setRowCount(platform.size());

    table->setColumnWidth(0, 300);

    for (int i = 0; i < platform.size(); ++i) {
        table->setItem(i,0,new QTableWidgetItem(QString(platform[i].name)));
        table->setItem(i,1,new QTableWidgetItem(QString::number(platform[i].memory / 1024 / 1024) + "Mb"));
        table->setItem(i,2,new QTableWidgetItem(QString::number(platform[i].frequency) + "MHz"));
    }

    layout = new QVBoxLayout(this);

    series = new QtCharts::QLineSeries();
    chart = new QtCharts::QChart();
    chart->setTitle("GPU usage");
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axisX()->setRange(0,100);

    chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(chartView);
    layout->addWidget(table);
    setLayout(layout);

    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GPU_Page::UpdateGPULoad);
    timer->start(1000);
}

void GPU_Page::UpdateGPULoad() {
    int GpuLoad = GetLoadGpu();

    series->append(timeIndex++, GpuLoad);

    if (series->count() > 20) {
        series->remove(0);
    }
    chart->axisX()->setRange(timeIndex - 20,timeIndex);
}

