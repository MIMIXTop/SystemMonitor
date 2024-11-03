#include "CPU_Page.h"

CPU_Page::CPU_Page(QWidget* parent) {
    layout = new QVBoxLayout;
    Cpuload = new QTableWidget(this);
    CpuName = new QLabel(QString::fromStdString(getCpuVender()),this);
    CpuTemper = new QLabel("Temperature: " + QString::number(getCpuTemperature()) + "^C");
    layout->addWidget(CpuName);
    layout->addWidget(Cpuload);
    layout->addWidget(CpuTemper);

    Cpuload->setRowCount(getCorsCounter() + 1);
    Cpuload->setColumnCount(2);

    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CPU_Page::updateCpuUsage);
    timer->start(1000);

}

void CPU_Page::updateCpuUsage() {

    auto currStats = getCPUStats();
    if (!prevStats.empty()) {
        for (size_t i = 0; i < currStats.size(); ++i) {
            double usage = calculateCPUUsage(prevStats[i], currStats[i]);
            Cpuload->setItem(i, 0, new QTableWidgetItem(QString("CPU %1").arg(i)));
            Cpuload->setItem(i,1,new QTableWidgetItem(QString::number(usage,'f',2)));
        }
    }
    prevStats = currStats;
    CpuTemper->setText("Temperature: " + QString::number(getCpuTemperature()) + "^C");
}

std::string CPU_Page::getCpuVender() {

    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    std::string model;

    while (std::getline(cpuinfo,line)){
        if(line.find("model name") != std::string::npos){
            model = line;
            break;
        }
    }

    return model.substr(model.find(":") + 2);
}

unsigned int CPU_Page::getCorsCounter() {
    return std::thread::hardware_concurrency();
}
