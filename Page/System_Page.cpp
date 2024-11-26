//
// Created by mimixtop on 03.11.24.
//

#include "System_Page.hpp"

#include "Utils/MemoryMonitor.hpp"

double roundToDecimalPlaces(double num, int decimal_places){
    double factor = std::pow(10, decimal_places);
    return round(num * factor) / factor;
}

System_Page::System_Page(QWidget *parent) {
    auto drive = getDriverStats();

    layout = new QVBoxLayout();

    System_Tree = new QTreeView();
    System_Tree->setHeaderHidden(true);
    System_Tree->setEditTriggers(QAbstractItemView::NoEditTriggers);

    model = new QStandardItemModel();
    PARENT_ITEM = model->invisibleRootItem();
    CPU = new QStandardItem("Процессор");
    GPU = new QStandardItem("Видеокарта");
    RAM = new QStandardItem("Оперативная память");
    DRIVER = new QStandardItem("Файловая система");
    SYSTEM = new QStandardItem("Система");

    QString logo_path = findDistroLogo();
    QPixmap pixmap_logo;

    if(logo_path != "") {
        pixmap_logo = QPixmap(logo_path);
    }else {
        pixmap_logo = QPixmap("../Image/logo_test.png");
    }

    QLabel *label = new QLabel();
    label->setPixmap(pixmap_logo);
    label->setAlignment(Qt::AlignCenter);
    label->setObjectName("SystemLogo");
    layout->addWidget(label);

    PARENT_ITEM->appendRow(SYSTEM);
    PARENT_ITEM->appendRow(CPU);
    PARENT_ITEM->appendRow(GPU);
    PARENT_ITEM->appendRow(RAM);
    PARENT_ITEM->appendRow(DRIVER);

    //System data
    SYSTEM->appendRow(new QStandardItem(printDistroVersion().data()));
    SYSTEM->appendRow(new QStandardItem(printKernelVersion().data()));
    //CPU data
    CPU->appendRow(new QStandardItem(getCpuVender().data()));
    CPU->appendRow(new QStandardItem(QString("Количество ядер: " + QString::number(getCores().physicalCors))));
    CPU->appendRow(new QStandardItem(QString("Количество потоков: " + QString::number(getCores().virtualCors))));
    //RAM data
    auto mem = MemoryUsage();
    RAM->appendRow(new QStandardItem(QString("Общий объем: " + QString::number(roundToDecimalPlaces(mem[Memory::mTotal], 2), 'f',2) + "Gb")));
    //DRIVER data
    auto driver = getDriverStats();
    DRIVER->appendRow(new QStandardItem(QString("Место под систему: " + QString::number(roundToDecimalPlaces(driver[Driver::Total] / 1024 / 1024 / 1024, 2),'f',2) + "Gb")));
    DRIVER->appendRow(new QStandardItem(QString("Свободное место на дис: " + QString::number(roundToDecimalPlaces(driver[Driver::Free] / 1024 / 1024 / 1024, 2),'f',2) + "Gb") ));
    //GPU data
    auto platform = GetPlatforms();
    for(int i = 0; i < platform.size(); i++) {
        GPU->appendRow(new QStandardItem(platform[i].name));
        GPU->appendRow(new QStandardItem(QString("Память: " + QString::number(platform[i].memory / 1024.0 / 1024 / 1024,'f',2) + "Gb")));
        GPU->appendRow(new QStandardItem( QString("Частота: " + QString::number(platform[i].frequency) + "MHz") ));
    }

    System_Tree->setModel(model);
    layout->addWidget(System_Tree);
    setLayout(layout);
}
