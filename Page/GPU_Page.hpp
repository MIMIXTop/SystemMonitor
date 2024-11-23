#ifndef GPU_PAGE_HPP
#define GPU_PAGE_HPP

#include <QTableWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>
#include <qcustomplot/qcustomplot.h>
#include <QVector>

#include <vector>

#include "Utils/Gpumonitor.hpp"

class GPU_Page : public QWidget {
    Q_OBJECT

public:
    explicit GPU_Page(QWidget *parent = nullptr);

private slots:
    void UpdateGPULoad();

private:
    QCustomPlot *gpuPlot;
    QTimer *timer;
    QVBoxLayout *layout;

    QTableWidget *table;
    int timeIndex = 0;
};


#endif //GPU_PAGE_HPP
