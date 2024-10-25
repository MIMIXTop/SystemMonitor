#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>

#include "Page/CPU_Page.hpp"
#include "Page/Driver_Page.hpp"
#include "Page/Memory_Page.hpp"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    CPU_Page* cpu;
    Driver_Page* driver;
    Memory_Page* memory;

    QStackedWidget* StackWidget;
    QPushButton* CPU_Button;
    QPushButton* Driver_Button;
    QPushButton* Memory_Button;

public:
    explicit MainWindow(QWidget* parent = nullptr) : QWidget(parent)
    {
        this->resize(800, 600);
        CPU_Button = new QPushButton("CPU_Button",this);
        Driver_Button = new QPushButton("Driver_Button",this);
        CPU_Button->setGeometry(QRect(0, 50, 80, 60));
        Driver_Button->setGeometry(QRect(0, 100, 80, 60));
        Memory_Button = new QPushButton("Memory_Button",this);
        Memory_Button->setGeometry(QRect(0, 150, 80, 60));

        connect(CPU_Button,&QPushButton::clicked,this,&MainWindow::CPU_Button_clicked);
        connect(Driver_Button,&QPushButton::clicked,this,&MainWindow::Driver_Button_clicked);
        connect(Memory_Button,&QPushButton::clicked,this,&MainWindow::Memory_Button_clicked);

        StackWidget = new QStackedWidget(this);
        StackWidget->resize(700, 600);
        StackWidget->setGeometry(QRect(80, 0, 700, 600));
        cpu = new CPU_Page();
        driver = new Driver_Page();
        memory = new Memory_Page();


        StackWidget->addWidget(cpu);
        StackWidget->addWidget(driver);
        StackWidget->addWidget(memory);

        StackWidget->setCurrentIndex(0);
    }

private slots:
    void CPU_Button_clicked();
    void Driver_Button_clicked();
    void Memory_Button_clicked();
};


#endif //MAINWINDOW_HPP
