//
// Created by mimixtop on 03.11.24.
//

#ifndef DRIVER_PAGE_HPP
#define DRIVER_PAGE_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QPixmap>
#include <QTreeView>
#include <QStandardItemModel>

#include "Utils/SystemMonitor.hpp"
#include "Utils/Gpumonitor.hpp"

class System_Page : public QWidget {
    Q_OBJECT

public:
    explicit System_Page(QWidget *parent = 0);

private:
    QTreeView *System_Tree;
    QVBoxLayout *layout;
    QStandardItemModel *model;
    QStandardItem *CPU;
    QStandardItem *RAM;
    QStandardItem *GPU;
    QStandardItem *DRIVER;
    QStandardItem *SYSTEM;
    QStandardItem *PARENT_ITEM;
};


#endif //DRIVER_PAGE_HPP
