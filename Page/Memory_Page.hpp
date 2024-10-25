//
// Created by MAXIM on 25.10.2024.
//

#ifndef MEMORY_PAGE_HPP
#define MEMORY_PAGE_HPP

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <windows.h>

class Memory_Page : public QWidget
{
    Q_OBJECT

public:
    explicit Memory_Page(QWidget* parent = nullptr);
    ~Memory_Page() = default;

private:
    QLabel* TotalMemory;
    QLabel* FreeMemory ;
    QVBoxLayout* layout;

    void GetMemory();
private slots:

};



#endif //MEMORY_PAGE_HPP
