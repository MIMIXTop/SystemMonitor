#include "CPU_Page.hpp"

DWORD CPU_Page::GetPhysicalCoreCount() {
    DWORD physicalCoreCount = 0;
    DWORD bufferSize = 0;
    GetLogicalProcessorInformation(nullptr, &bufferSize);
    std::vector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION> buffer(bufferSize / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION));
    GetLogicalProcessorInformation(buffer.data(), &bufferSize);
    for (const auto& info : buffer) {
        if (info.Relationship == RelationProcessorCore) {
            physicalCoreCount++;
        }
    }
    return physicalCoreCount;
}

CPU_Page::CPU_Page(QWidget* parent) : QWidget(parent) {
    CPU_Usege = new QTableWidget(parent);
    CPU_Usege->setObjectName(QString::fromUtf8("CPU_Usege"));
    CPU_Usege->setGeometry(QRect(0, 0, 200, 80));
    CPU_Usege->setColumnCount(2);

    DWORD numPhysicalCores = GetPhysicalCoreCount();
    CPU_Usege->setRowCount(numPhysicalCores);

    QVBoxLayout* layout = new QVBoxLayout(parent);
    layout->addWidget(CPU_Usege);

    CPU_Name = new QLabel(parent);
    CPU_Name->setObjectName(QString::fromUtf8("CPU_Name"));
    CPU_Name->setText(QString::fromStdString(getCPUVender()));
    layout->addWidget(CPU_Name);

    setLayout(layout);

    init();

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CPU_Page::updateCpuUsage);
    timer->start(1000);
}

void CPU_Page::init() {
    PdhOpenQuery(NULL, NULL, &cpuQuery);

    // Получаем количество физических ядер
    DWORD numPhysicalCores = GetPhysicalCoreCount();

    // Добавляем счетчики для каждого физического ядра процессора
    cpuCounters.resize(numPhysicalCores);
    for (DWORD i = 0; i < numPhysicalCores; i++) {
        TCHAR counterPath[50];
        _stprintf_s(counterPath, TEXT("\\Processor(%d)\\%% Processor Time"), i);
        PdhAddEnglishCounter(cpuQuery, counterPath, NULL, &cpuCounters[i]);
    }
    PdhCollectQueryData(cpuQuery);
}

void CPU_Page::updateCpuUsage() {
    PdhCollectQueryData(cpuQuery);
    for (size_t i = 0; i < cpuCounters.size(); i++) {
        PDH_FMT_COUNTERVALUE counterVal;
        PdhGetFormattedCounterValue(cpuCounters[i], PDH_FMT_DOUBLE, NULL, &counterVal);
        CPU_Usege->setItem(i, 0, new QTableWidgetItem(QString("CPU %1").arg(i)));
        CPU_Usege->setItem(i, 1, new QTableWidgetItem(QString::number(counterVal.doubleValue, 'f', 2)));
    }
}

std::vector<double> CPU_Page::getCurrentValues() {
    std::vector<double> values(cpuCounters.size());
    PDH_FMT_COUNTERVALUE counterVal;
    PdhCollectQueryData(cpuQuery);
    for (size_t i = 0; i < cpuCounters.size(); i++) {
        PdhGetFormattedCounterValue(cpuCounters[i], PDH_FMT_DOUBLE, NULL, &counterVal);
        values[i] = counterVal.doubleValue;
    }
    return values;
}

std::string CPU_Page::getCPUVender()
{
    std::string VendorString;
    CPU_REGS Regs{};
    __cpuid(reinterpret_cast<int*>(&Regs), 0x80000000);
    if (Regs.Eax >= 0x80000004)
    {
        VendorString =
            GetCpuVendorSubstring(0x80000002) +
            GetCpuVendorSubstring(0x80000003) +
            GetCpuVendorSubstring(0x80000004);
    }
    return VendorString;
}

std::string CPU_Page::GetCpuVendorSubstring(const DWORD Eax)
{
    CPU_REGS Regs{};
    __cpuid(reinterpret_cast<int*>(&Regs), Eax);
    std::string Str;
    Str += subString(Regs.Eax);
    Str += subString(Regs.Ebx);
    Str += subString(Regs.Ecx);
    Str += subString(Regs.Edx);
    return Str;
}

std::string CPU_Page::subString(DWORD Value)
{
    std::string Str;
    char const* pCursor = (char const*)&Value;
    for (size_t i = 0; i < sizeof(Value); ++i)
    {
        Str += pCursor[i];
    }
    return Str;
}
