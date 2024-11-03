//
// Created by mimixtop on 03.11.24.
//

#ifndef DRIVER_PAGE_HPP
#define DRIVER_PAGE_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "Utils/DriverMonitor.hpp"

class Driver_Page : public QWidget {
    Q_OBJECT

public:
    explicit Driver_Page(QWidget *parent = 0);

private:
    QLabel *Free_Drive;
    QLabel *Total_Drive;
    QLabel *Usage_Drive;
    QVBoxLayout *layout;
};


#endif //DRIVER_PAGE_HPP
