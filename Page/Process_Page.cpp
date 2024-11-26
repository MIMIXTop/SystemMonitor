#include "Process_Page.hpp"
#include "CPU_Page.h"
#include <algorithm>

Process_Page::Process_Page(QWidget *parent)
    : QWidget(parent), ascending(true), sortedColumn(0) {

    table = new QTableWidget(this);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setColumnWidth(4, 300); // Устанавливаем ширину для последнего столбца
    layout = new QVBoxLayout(this);
    timer = new QTimer(this);

    layout->addWidget(table);
    setLayout(layout);

    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(QStringList() << "PID" << "User" << "%CPU" << "%Mem" << "Name");

    // Настройка автоподстройки последнего столбца
    table->horizontalHeader()->setStretchLastSection(true);

    // Подключение к сигналу нажатия на заголовок для сортировки
    connect(table->horizontalHeader(), &QHeaderView::sectionClicked, [&](int index) {
        if (sortedColumn == index) {
            ascending = !ascending; // Переключаем порядок сортировки
        } else {
            ascending = true; // Сброс порядка сортировки на восходящий
        }
        sortedColumn = index; // Запоминаем текущую колонку
        update_processes(); // Обновляем данные с учетом новой сортировки
    });

    connect(timer, &QTimer::timeout, this, &Process_Page::update_processes);
    timer->start(1000);
}

void Process_Page::update_processes() {
    auto processes = GetProcesses(GetCurrentUser());

    // Сортировка процессов перед добавлением в таблицу
    switch (sortedColumn) {
        case 0: // PID
            std::sort(processes.begin(), processes.end(), [this](const Processes& a, const Processes& b) {
                return ascending ? (a.pid < b.pid) : (a.pid > b.pid);
            });
            break;
        case 1: // User
            std::sort(processes.begin(), processes.end(), [this](const Processes& a, const Processes& b) {
                return ascending ? (a.user < b.user) : (a.user > b.user);
            });
            break;
        case 2: // %CPU
            std::sort(processes.begin(), processes.end(), [this](const Processes& a, const Processes& b) {
                return ascending ? (a.cpu_load < b.cpu_load) : (a.cpu_load > b.cpu_load);
            });
            break;
        case 3: // %Mem
            std::sort(processes.begin(), processes.end(), [this](const Processes& a, const Processes& b) {
                return ascending ? (a.memory_load < b.memory_load) : (a.memory_load > b.memory_load);
            });
            break;
        case 4: // Name
            std::sort(processes.begin(), processes.end(), [this](const Processes& a, const Processes& b) {
                return ascending ? (a.name < b.name) : (a.name > b.name);
            });
            break;
    }

    table->setRowCount(processes.size());

    for (int i = 0; i < processes.size(); i++) {
        table->setItem(i, 0, new QTableWidgetItem(QString::number(processes.at(i).pid)));
        table->setItem(i, 1, new QTableWidgetItem(processes.at(i).user));

        auto cpuItem = new QTableWidgetItem(QString::number(processes.at(i).cpu_load));
        cpuItem->setData(Qt::UserRole, processes.at(i).cpu_load);
        table->setItem(i, 2, cpuItem);

        auto memItem = new QTableWidgetItem(QString::number(processes.at(i).memory_load));
        memItem->setData(Qt::UserRole, processes.at(i).memory_load);
        table->setItem(i, 3, memItem);

        table->setItem(i, 4, new QTableWidgetItem(processes.at(i).name));
    }
}