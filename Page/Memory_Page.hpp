//
// Created by MAXIM on 25.10.2024.
//

#ifndef MEMORY_PAGE_HPP
#define MEMORY_PAGE_HPP

#include <QWidget>
#include <QString>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QTimer>

#include <array>

#include "Utils/MemoryMonitor.hpp"

class Memory_Page : public QWidget
{
    Q_OBJECT

public:
    explicit Memory_Page(QWidget* parent = nullptr);
    ~Memory_Page() = default;

private:
    QVBoxLayout* layout;
    QTableWidget* table;
private slots:
    void updateMemory();
};



#endif //MEMORY_PAGE_HPP
