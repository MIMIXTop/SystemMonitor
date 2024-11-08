#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Page/Driver_Page.hpp"
#include "Page/Memory_Page.hpp"
#include "Page/CPU_Page.h"
#include "Page/GPU_Page.hpp"

class MainWindow : public QWidget {
    Q_OBJECT

private:
    Memory_Page *memory;
    CPU_Page *cpu;
    Driver_Page *driver;
    GPU_Page *gpu;

    QStackedWidget *StackWidget;
    QPushButton *CPU_Button;
    QPushButton *Driver_Button;
    QPushButton *Memory_Button;
    QPushButton *GPU_Button;
    QHBoxLayout *mainLayout;
    QVBoxLayout *stackLayout;
    QVBoxLayout *buttonLayout;

public:
    explicit MainWindow(QWidget *parent = nullptr) : QWidget(parent) {
        mainLayout = new QHBoxLayout(this);
        buttonLayout = new QVBoxLayout();

        this->resize(800, 600);
        CPU_Button = new QPushButton("CPU_Button", this);
        Driver_Button = new QPushButton("Driver_Button", this);
        CPU_Button->setGeometry(QRect(5, 50, 95, 60));
        Driver_Button->setGeometry(QRect(5, 100, 95, 60));
        Memory_Button = new QPushButton("Memory_Button", this);
        Memory_Button->setGeometry(QRect(5, 150, 95, 60));
        GPU_Button = new QPushButton("GPU_Button", this);
        GPU_Button->setGeometry(QRect(5, 200, 95, 60));

        buttonLayout->addWidget(CPU_Button);
        buttonLayout->addWidget(Driver_Button);
        buttonLayout->addWidget(Memory_Button);
        buttonLayout->addWidget(GPU_Button);

        mainLayout->addLayout(buttonLayout);

        connect(CPU_Button, &QPushButton::clicked, this, &MainWindow::CPU_Button_clicked);
        connect(Driver_Button, &QPushButton::clicked, this, &MainWindow::Driver_Button_clicked);
        connect(Memory_Button, &QPushButton::clicked, this, &MainWindow::Memory_Button_clicked);
        connect(GPU_Button,&QPushButton::clicked,this,&MainWindow::GPU_Button_clicked);

        StackWidget = new QStackedWidget();
        //StackWidget->resize(700, 600);
        //StackWidget->setGeometry(QRect(100, 0, 700, 600));
        mainLayout->addWidget(StackWidget);

        cpu = new CPU_Page();
        memory = new Memory_Page();
        driver = new Driver_Page();
        gpu = new GPU_Page();

        StackWidget->addWidget(cpu);
        StackWidget->addWidget(driver);
        StackWidget->addWidget(memory);
        StackWidget->addWidget(gpu);

        StackWidget->setCurrentIndex(0);
        setLayout(mainLayout);
    }

private slots:
    void CPU_Button_clicked();

    void Driver_Button_clicked();

    void Memory_Button_clicked();

    void GPU_Button_clicked();
};


#endif //MAINWINDOW_HPP
