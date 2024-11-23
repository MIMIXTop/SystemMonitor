#include <QApplication>
#include "MainWindow.hpp"
//#include "Style/myStyle.hpp"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    //myStyle style;
    //QApplication::setStyle(&style);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
