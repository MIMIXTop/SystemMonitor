#ifndef PROCESS_PAGE_HPP
#define PROCESS_PAGE_HPP

#include "Utils/Processes.hpp"

#include <QWidget>
#include <QTableWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QHeaderView>

class Process_Page : public QWidget {
    Q_OBJECT

public:
    explicit Process_Page(QWidget *parent = nullptr);

    ~Process_Page() override = default;

private:
    QTableWidget *table;
    QVBoxLayout *layout;
    QTimer *timer;
    bool ascending = true;
    int sortedColumn = 0;

private slots:
    void update_processes();
};


#endif //PROCESS_PAGE_HPP
