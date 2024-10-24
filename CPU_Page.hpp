#ifndef CPU_PAGE_HPP
#define CPU_PAGE_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QTimer>
#include <pdh.h>
#include <tchar.h>
#include <intrin.h>

#include "CPU_Regs.hpp"

class CPU_Page : public QWidget
{
    Q_OBJECT

public:
    explicit CPU_Page(QWidget* parent);

private:
    QLabel* CPU_Name;
    QTableWidget* CPU_Usege;
    unsigned CpuCoreCounter = 0;
    PDH_HQUERY cpuQuery;
    std::vector<PDH_HCOUNTER> cpuCounters;

    void init();

    std::vector<double> getCurrentValues();

    void updateCpuUsage();

    std::string getCPUVender();

    std::string GetCpuVendorSubstring(const DWORD Eax);

    std::string subString(DWORD Value);

    DWORD GetPhysicalCoreCount();
};


#endif //CPU_PAGE_HPP
