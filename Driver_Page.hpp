//
// Created by MAXIM on 24.10.2024.
//

#ifndef DRIVER_PAGE_HPP
#define DRIVER_PAGE_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <list>
#include <windows.h>

struct Driver
{
    QString Name_;
    QString Type_;
    int TotalSpace_;
    int FreeSpace_;
    QString VolumeName_;
};


class Driver_Page : public QWidget
{
    Q_OBJECT

public:
    explicit Driver_Page(QWidget* parent = nullptr);
    ~Driver_Page() = default;
private slots:

    void GetDiskInfo();
private:
    QVBoxLayout* layout;
    std::list<Driver> DriversInfo;
};


#endif //DRIVER_PAGE_HPP
