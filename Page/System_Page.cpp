//
// Created by mimixtop on 03.11.24.
//

#include "System_Page.hpp"

#include "Utils/MemoryMonitor.hpp"

System_Page::System_Page(QWidget *parent) {
    auto drive = getDriverStats();

    layout = new QVBoxLayout();
    System_Tree = new QTreeView();
    System_Tree->setHeaderHidden(true);
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
        pixmap_logo = QPixmap("../Image/logo.png");
    }

    QLabel *label = new QLabel();
    label->setPixmap(pixmap_logo);
    label->setAlignment(Qt::AlignCenter);
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
    CPU->appendRow(new QStandardItem(std::string("Количество ядер: " + std::to_string(getCores().physicalCors)).c_str()));
    CPU->appendRow(new QStandardItem(std::string("Количество потоков: " + std::to_string(getCores().virtualCors)).c_str()));
    //RAM data
    auto mem = MemoryUsage();
    RAM->appendRow(new QStandardItem(std::string("Общий объем: " + std::to_string(mem[Memory::mTotal]) + "Gb").c_str()));
    //DRIVER data
    auto driver = getDriverStats();
    DRIVER->appendRow(new QStandardItem(std::string("Место под систему: " + std::to_string(driver[Driver::Total] / 1024 / 1024 / 1024) + "Gb").c_str()));
    DRIVER->appendRow(new QStandardItem(std::string("Свободное место на дис: " + std::to_string(driver[Driver::Free] / 1024 / 1024 / 1024) + "Gb").c_str() ));
    //GPU data
    auto platform = GetPlatforms();
    for(int i = 0; i < platform.size(); i++) {
        GPU->appendRow(new QStandardItem(platform[i].name));
        GPU->appendRow(new QStandardItem(std::string("Память: " + std::to_string(platform[i].memory / 1024.0 / 1024 / 1024) + "Mb").c_str()));
        GPU->appendRow(new QStandardItem( std::string("Частота: " + std::to_string(platform[i].frequency) + "MHz").c_str() ));
    }

    System_Tree->setModel(model);
    layout->addWidget(System_Tree);
    setLayout(layout);
}
