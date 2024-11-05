//
// Created by mimixtop on 03.11.24.
//

#include "Driver_Page.hpp"

Driver_Page::Driver_Page(QWidget *parent) {
    auto drive = getDriverStats();

    layout = new QVBoxLayout();
    Total_Drive = new QLabel();
    Free_Drive = new QLabel();
    Usage_Drive = new QLabel();

    layout->addWidget(Total_Drive);
    layout->addWidget(Free_Drive);
    layout->addWidget(Usage_Drive);
    setLayout(layout);

    Total_Drive->setText("Total Drive: " + QString::number(drive[0],'f',2) + "Gb");
    Free_Drive->setText("Free Drive: " + QString::number(drive[1],'f',2) + "Gb");
    Usage_Drive->setText("Usage Drive: " + QString::number(drive[2],'f',2) + "Gb");
}