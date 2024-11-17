//
// Created by mimixtop on 17.11.24.
//

#ifndef CPUWIDGET_HPP
#define CPUWIDGET_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpacerItem>

#include <thread>
#include <fstream>
#include <string>

struct Cors {
    unsigned int physicalCors;
    unsigned int virtualCors;
};

class CpuWidget : public QWidget {
    Q_OBJECT
    public:
    explicit CpuWidget(QWidget *parent = nullptr);
    ~CpuWidget() = default;
    private:
    std::string getVender();
    Cors getCores();

    QLabel *name;
    QLabel *cors;
    QLabel *virtualCors;
    QVBoxLayout *layout;
    QSpacerItem *spacer;


};



#endif //CPUWIDGET_HPP
