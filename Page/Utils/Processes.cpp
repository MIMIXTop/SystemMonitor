//
// Created by mimixtop on 10.11.24.
//

#include "Processes.hpp"


#include "Processes.hpp"
#include <QVector>
#include <QStringList>
#include <array>
#include <memory>
#include <stdexcept>
#include <cstdio>
#include <qregularexpression.h>

QVector<Processes> GetProcesses() {
    QVector<Processes> processes; // Контейнер для хранения информации о процессах
    Processes process_; // Объект для хранения данных одного процесса
    std::array<char, 128> buffer{}; // Буфер для считывания данных из команды
    QStringList list; // Список для хранения строк, полученных от команды

    // Уникальный указатель для открытия командной строки с помощью popen
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("ps aux", "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!"); // Проверка на ошибки

    // Считывание данных из команды
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        // Добавление считанной строки в список
        list.append(QString::fromStdString(buffer.data()));
    }

    // Обработка каждой строки списка
    for (const auto& process : list) {
        // Разделение строки на поля по пробелам с использованием регулярного выражения
        QVector<QString> fields = QVector<QString>::fromList(process.split(QRegularExpression("\\s+"))); // Разделение по пробелам

        // Проверка, что количество полей соответствует ожиданиям
        if (fields.size() < 11) continue; // Если данных недостаточно, пропускаем строку

        // Здесь можно обработать полученные данные
        process_.user = fields.at(0);
        process_.pid = fields.at(1).toInt(); // Преобразование PID в int
        process_.cpu_load = fields.at(2).toFloat(); // Преобразование CPU нагрузки в float
        process_.memory_load = fields.at(3).toFloat(); // Преобразование памяти в float
        process_.name = fields.at(10); // Обычно имя процесса находится в 11-м поле (индекс 10)

        processes.append(process_); // Добавление информации о процессе в вектор
    }

    // Возврат результата
    return processes;
}
