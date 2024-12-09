#include <QApplication>
#include <QFile>
#include "MainWindow.hpp"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QFile styleFile("../style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = styleFile.readAll();
        styleFile.close();
        a.setStyleSheet(style);
    } else {
        throw std::runtime_error("Style file could not be opened");
    }
    MainWindow w;
    w.setWindowTitle("AIDA");
    w.show();
    return QApplication::exec();
}
