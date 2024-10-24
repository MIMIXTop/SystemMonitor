#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QStackedWidget>

#include "CPU_Page.hpp"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    CPU_Page* cpu;

    QStackedWidget* StackWidget;

public:
    explicit MainWindow(QWidget* parent = nullptr) : QWidget(parent)
    {
        this->resize(800, 600);
        StackWidget = new QStackedWidget(this);
        StackWidget->resize(400, 200);
        cpu = new CPU_Page(this);

        StackWidget->addWidget(cpu);

        StackWidget->setCurrentIndex(0);
    }

private slots:


};


#endif //MAINWINDOW_HPP
