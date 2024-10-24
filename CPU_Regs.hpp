#ifndef CPU_REGS_HPP
#define CPU_REGS_HPP

#include <Windows.h>

struct CPU_REGS{
    DWORD Eax;
    DWORD Ebx;
    DWORD Ecx;
    DWORD Edx;
};

#endif //CPU_REGS_HPP
