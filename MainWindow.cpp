#include "MainWindow.hpp"

void MainWindow::CPU_Button_clicked()
{
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
