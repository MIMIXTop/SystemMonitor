#ifndef GPU_PAGE_HPP
#define GPU_PAGE_HPP

#include <QTableWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

#include "Utils/Gpumonitor.hpp"

class GPU_Page : public QWidget {
    Q_OBJECT

public:
    explicit GPU_Page(QWidget *parent = nullptr);

private slots:
    void UpdateGPULoad();

private:
    QtCharts::QLineSeries *series;
    QtCharts::QChart *chart;
    QtCharts::QChartView *chartView;
    QTimer *timer;
    QVBoxLayout *layout;

    QTableWidget *table;
    int timeIndex = 0;
};


#endif //GPU_PAGE_HPP
