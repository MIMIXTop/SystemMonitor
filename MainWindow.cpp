#include "MainWindow.hpp"

void MainWindow::CPU_Button_clicked() {
    if(StackWidget->currentIndex() != 0)
    {
        StackWidget->setCurrentIndex(0);
    }
}
void MainWindow::Driver_Button_clicked()
{
    if(StackWidget->currentIndex() != 1)
    {
        StackWidget->setCurrentIndex(1);
    }

}

void MainWindow::Memory_Button_clicked()
{
    if(StackWidget->currentIndex() != 2)
    {
        StackWidget->setCurrentIndex(2);
    }
}
