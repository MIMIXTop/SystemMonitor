//
// Created by MAXIM on 25.10.2024.
//

#include "Memory_Page.hpp"

Memory_Page::Memory_Page(QWidget* parent)
{
    resize(700,600);
    layout = new QVBoxLayout(this);
    table = new QTableWidget(this);
    table->setColumnCount(2);
    table->setRowCount(5);
    layout->addWidget(table);
    setLayout(layout);
    table->setColumnWidth(0,130);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Memory_Page::updateMemory);
    timer->start(1000);
}

void Memory_Page::updateMemory() {
    auto memory = MemoryMonitor();

    table->setItem(0, 0, new QTableWidgetItem("Total Memory:"));
    table->setItem(0, 1, new QTableWidgetItem(QString::number(memory[Memory::Total],'f', 2) + "Gb"));

    table->setItem(1, 0, new QTableWidgetItem("Free Memory:"));
    table->setItem(1, 1, new QTableWidgetItem(QString::number(memory[Memory::Free],'f', 2) + "Gb"));

    table->setItem(2, 0, new QTableWidgetItem("Buffer Memory:"));
    table->setItem(2, 1, new QTableWidgetItem(QString::number(memory[Memory::Buffers],'f', 2) + "Gb"));

    table->setItem(3, 0, new QTableWidgetItem("Cached Memory:"));
    table->setItem(3, 1, new QTableWidgetItem(QString::number(memory[Memory::Cached],'f', 2) + "Gb"));

    table->setItem(4, 0, new QTableWidgetItem("Used Memory:"));
    table->setItem(4, 1, new QTableWidgetItem(QString::number(memory[Memory::Used],'f', 2) + "Gb"));
}