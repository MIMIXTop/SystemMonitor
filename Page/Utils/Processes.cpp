#include "Processes.hpp"

std::string GetCurrentUser() {
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    return pw ? pw->pw_name : "unknown";
}

// Функция для разделения строки на слова
std::vector<std::string> SplitString(const std::string& str) {
    std::vector<std::string> words;
    std::regex wordReg(R"(\s+)"); // Разделитель: один или несколько пробелов

    std::sregex_token_iterator it(str.begin(), str.end(), wordReg, -1);
    std::sregex_token_iterator end;

    for (; it != end; ++it) {
        if (!it->str().empty()) { // Игнорируем пустые строки
            words.push_back(it->str());
        }
    }

    return words;
}

std::vector<Processes> GetProcesses(const std::string& currentUser) {
    std::vector<Processes> processes;

    // Выполняем команду ps aux
    std::array<char, 128> buffer;
    std::string result;

    std::shared_ptr<FILE> pipe(popen("ps aux --sort=-%cpu", "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("Ошибка при выполнении команды ps");
    }

    // Читаем вывод команды
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Разделяем строки
    std::istringstream iss(result);
    std::string line;

    // Пропускаем заголовок
    std::getline(iss, line);

    // Читаем каждую строку
    while (std::getline(iss, line)) {
        std::vector<std::string> tokens = SplitString(line);

        if (tokens.size() >= 11) { // Убедимся, что есть достаточно токенов
            Processes info;
            info.user = QString::fromStdString(tokens[0]); // Имя пользователя
            info.cpu_load = std::stof(tokens[2]); // Загрузка CPU
            info.memory_load = std::stof(tokens[3]); // Использование памяти
            info.pid = std::stoi(tokens[1]); // PID

            // Составляем имя процесса из оставшихся токенов
            QString name;
            for (size_t i = 10; i < tokens.size(); ++i) {
                name += QString::fromStdString(tokens[i]) + " "; // Добавляем пробел между словами
            }
            info.name = name.trimmed(); // Удаляем лишние пробелы

            // Сокращаем имя до 150 символов, если необходимо
            if (info.name.length() > 150) {
                info.name = info.name.left(150) + "..."; // Добавляем многоточие
            }

            // Фильтруем по имени пользователя
            if (info.user == QString::fromStdString(currentUser)) {
                processes.push_back(info);
            }
        }
    }

    return processes;
}