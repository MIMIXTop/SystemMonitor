//
// Created by mimixtop on 10.11.24.
//

#include "Process_Page.hpp"

#include "CPU_Page.h"

Process_Page::Process_Page(QWidget *parent) {
    table = new QTableWidget;
    layout = new QVBoxLayout;
    timer = new QTimer(this);

    layout->addWidget(table);
    setLayout(layout);

    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(QStringList() << "PID" << "User" << "%CPU" << "%Mem" << "Name");

    connect(table->horizontalHeader(),&QHeaderView::sectionClicked,[&](int index) {
        ascending = !ascending;
        table->sortItems(index,ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
    });

    connect(timer,&QTimer::timeout,this,&Process_Page::update_processes);
    timer->start(1000);

}

void Process_Page::update_processes() {
    auto processes = GetProcesses();
    table->setRowCount(processes.size());
    for(int i = 0; i < processes.size(); i++) {
        table->setItem(i,0,new QTableWidgetItem(QString::number(processes.at(i).pid)));
        table->setItem(i,1,new QTableWidgetItem(processes.at(i).user));
        table->setItem(i,2,new QTableWidgetItem(QString::number(processes.at(i).cpu_load) + " %"));
        table->setItem(i,3,new QTableWidgetItem(QString::number(processes.at(i).memory_load) + " %"));
        table->setItem(i,4,new QTableWidgetItem(processes.at(i).name));
    }
}
