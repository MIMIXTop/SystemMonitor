#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPropertyAnimation>

#include "Page/System_Page.hpp"
#include "Page/Memory_Page.hpp"
#include "Page/CPU_Page.h"
#include "Page/GPU_Page.hpp"
#include "Page/Process_Page.hpp"

class MainWindow : public QWidget {
    Q_OBJECT

private:
    Memory_Page *memory;
    CPU_Page *cpu;
    System_Page *driver;
    GPU_Page *gpu;
    Process_Page *process;

    QStackedWidget *StackWidget;

    QPushButton *CPU_Button;
    QPushButton *Driver_Button;
    QPushButton *Memory_Button;
    QPushButton *GPU_Button;
    QPushButton *Process_Button;

    QHBoxLayout *mainLayout;
    QVBoxLayout *stackLayout;
    QVBoxLayout *buttonLayout;

    void animateTransition(int fromIndex, int toIndex);

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void CPU_Button_clicked();

    void Driver_Button_clicked();

    void Memory_Button_clicked();

    void GPU_Button_clicked();

    void Process_Button_clicked();
};


#endif //MAINWINDOW_HPP
