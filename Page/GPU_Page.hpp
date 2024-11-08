//
// Created by mimixtop on 08.11.24.
//

#ifndef GPU_PAGE_HPP
#define GPU_PAGE_HPP

#include <QWidget>

#include "Utils/Gpumonitor.hpp"

class GPU_Page : public QWidget {
    Q_OBJECT
    public:
    explicit GPU_Page(QWidget *parent = nullptr);
    private slots:
    private:
    void UpdateGPULoad();
};



#endif //GPU_PAGE_HPP
