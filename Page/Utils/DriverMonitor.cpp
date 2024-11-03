//
// Created by mimixtop on 03.11.24.
//

#include "DriverMonitor.hpp"

std::vector<float> getDriverStats() {
    const char* path = "/"; // Укажите путь к файловой системе
    struct statvfs stat;

    // Получаем информацию о файловой системе
    if (statvfs(path, &stat) != 0) {
        // Ошибка при вызове statvfs
        QMessageBox::information(nullptr,"Error","Ошибка получения статистики файловой системы" );
        return {};
    }

    // Вычисляем размеры
    float total; // Общий размер
    total = (stat.f_blocks * stat.f_frsize) / 1024.0 / 1024 / 1024;
    float free = (stat.f_bfree * stat.f_frsize) / 1024.0 / 1024 / 1024;   // Свободное место
    float used = total - free;

    return {total,free,used};
}
