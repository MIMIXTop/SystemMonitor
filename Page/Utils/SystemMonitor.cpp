//
// Created by mimixtop on 03.11.24.
//

#include "SystemMonitor.hpp"

std::string printKernelVersion() {
    std::ifstream versionFile("/proc/version");
    std::string result, temp;
    if (versionFile) {
        std::string version;
        std::getline(versionFile, version);
        std::istringstream ss(version);
        for (int i = 0;i < 3;++i){
            ss >> temp;
            result.append(temp);
            if (i == 1) result += ":";
            result += " ";
        }
        return result;
    }
}

std::string printDistroVersion() {
    std::ifstream osReleaseFile("/etc/os-release");
    if (osReleaseFile) {
        std::string line;
        while (std::getline(osReleaseFile, line)) {
            if (line.find("PRETTY_NAME") != std::string::npos) {
                std::string distroName = line.substr(line.find('=') + 1);
                distroName.erase(remove(distroName.begin(), distroName.end(), '\"'), distroName.end());
                return distroName;
            }
        }
    } else {
        throw std::runtime_error("Unable to open /etc/os-release");
    }
}

std::vector<unsigned long long> getDriverStats() {
    const char* path = "/"; // Укажите путь к файловой системе
    struct statvfs stat;

    // Получаем информацию о файловой системе
    if (statvfs(path, &stat) != 0) {
        QMessageBox::information(nullptr,"Error","Ошибка получения статистики файловой системы" );
        return {};
    }

    // Вычисляем размеры
    unsigned long long total;
    total = (stat.f_blocks * stat.f_frsize);
    unsigned long long free = (stat.f_bfree * stat.f_frsize) ;
    unsigned long long used = total - free;

    return {total,free,used};
}

std::string getCpuVender() {
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    std::string model;

    while (std::getline(cpuinfo, line)) {
        if (line.find("model name") != std::string::npos) {
            model = line;
            break;
        }
    }

    return model.substr(model.find(":") + 2);
}

Cors getCores() {
    unsigned int eax=11,ebx=0,ecx=1,edx=0;
    asm volatile("cpuid"
        : "=a"(eax),
        "=b"(ebx),
        "=c"(ecx),
        "=d"(edx)
        : "0"(eax), "2"(ecx)
        :);
    return {eax,ebx};
}

QString findDistroLogo() {
    QDir dir("/usr/share/pixmaps/");
    QStringList possibleLogos = {
        "ubuntu-logo.png",   // Ubuntu
        "fedora-logo.png",   // Fedora
        "debian-logo.png",   // Debian
        "archlinux-logo.png",// Arch Linux
        "opensuse-logo.png", // openSUSE
        "linuxmint-logo.png" // Linux Mint
    };

    for (const QString &logoName : possibleLogos) {
        QFileInfo logoFile(dir, logoName);
        if (logoFile.exists() && logoFile.isFile()) {
            return logoFile.absoluteFilePath();
        }
    }

    return QString();
}
