//
// Created by mimixtop on 17.11.24.
//

#include "CpuWidget.hpp"

CpuWidget::CpuWidget(QWidget *parent) {
    resize(100,100);
    name = new QLabel();
    layout = new QVBoxLayout();
    virtualCors = new QLabel();
    cors = new QLabel();
    layout->addWidget(name);
    layout->addWidget(cors);
    layout->addWidget(virtualCors);
    setLayout(layout);

    Cors tempCors = getCores();

    name->setText(QString::fromStdString(getVender()));
    cors->setText("Cores " + QString::number(tempCors.physicalCors));
    virtualCors->setText("Threads" + QString::number(tempCors.virtualCors));
}

std::string CpuWidget::getVender() {
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    std::string model;

    while (std::getline(cpuinfo, line)) {
        if (line.find("model name") != std::string::npos) {
            model = line;
            break;
        }
    }

    return model.substr(model.find(":") + 2);
}

Cors CpuWidget::getCores() {
    unsigned int eax=11,ebx=0,ecx=1,edx=0;
    asm volatile("cpuid"
        : "=a"(eax),
        "=b"(ebx),
        "=c"(ecx),
        "=d"(edx)
        : "0"(eax), "2"(ecx)
        :);
    return {eax,ebx};
}
