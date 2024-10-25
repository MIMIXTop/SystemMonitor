//
// Created by MAXIM on 25.10.2024.
//

#include "Memory_Page.hpp"

Memory_Page::Memory_Page(QWidget* parent)
{
    resize(700,600);
    layout = new QVBoxLayout(this);
    TotalMemory = new QLabel(this);
    TotalMemory->setAlignment(Qt::AlignCenter);
    TotalMemory->setGeometry(QRect(10, 10, 300, 300));
    FreeMemory = new QLabel(this);
    FreeMemory->setAlignment(Qt::AlignCenter);
    FreeMemory->setGeometry(QRect(10, 10, 300, 300));
    layout->addWidget(TotalMemory);
    layout->addWidget(FreeMemory);
    setLayout(layout);
}

void Memory_Page::GetMemory()
{
    MEMORYSTATUS ms;
    GlobalMemoryStatus(&ms);
    TotalMemory->setText("Total Memory:" + QString::number(static_cast<int>(ms.dwTotalPhys)/1024/1024/1024));
    FreeMemory->setText("Free mmemory: " + QString::number(static_cast<int>(ms.dwAvailPhys)/1024/1024/1024));
}
