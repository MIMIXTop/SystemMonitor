#include "Driver_Page.hpp"

Driver_Page::Driver_Page(QWidget* parent)
{
    resize(300,400);
    layout = new QVBoxLayout(this);
    GetDiskInfo();

    for (auto&& driver : DriversInfo)
    {
        QLabel* label;
        label = new QLabel(QString(R"(Name: %1, Type: %2, Totale Size: %3, Free Size: %4, Volum Name: %5)")
                           .arg(driver.Name_)
                           .arg(driver.Type_)
                           .arg(driver.TotalSpace_)
                           .arg(driver.FreeSpace_)
                           .arg(driver.VolumeName_));
        layout->addWidget(label);
    }
    layout->setAlignment(Qt::AlignRight|Qt::AlignTop);
    setLayout(layout);
}

void Driver_Page::GetDiskInfo()
{
    Driver driver;
    char driveLetter[4] = "A:\\";
    DWORD drives = GetLogicalDrives();

    while (drives) {
        if (drives & 1) {
             driver.Name_ = driveLetter;

            // Get the drive type
            UINT driveType = GetDriveTypeA(driveLetter);
            switch (driveType) {
            case DRIVE_REMOVABLE: driver.Type_ = "Removable"; break;
            case DRIVE_FIXED: driver.Type_ = "Fixed"; break;
            case DRIVE_REMOTE: driver.Type_ = "Remote"; break;
            case DRIVE_CDROM: driver.Type_ = "CD-ROM"; break;
            case DRIVE_RAMDISK: driver.Type_ = "RAM Disk"; break;
            default: driver.Type_ = "Unknown"; break;
            }

            // Get free and total space
            ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;
            if (GetDiskFreeSpaceExA(driveLetter, &freeBytesAvailable, &totalBytes, &totalFreeBytes)) {
                driver.TotalSpace_ = totalBytes.QuadPart / (1024 * 1024 * 1024) ;// GB
                driver.TotalSpace_ = totalFreeBytes.QuadPart / (1024 * 1024 * 1024) ;//GB
            } else {
                MessageBox(NULL,
                        L"Error getting free space info.",
                        L"Error",
                        MB_OK);
            }

            // Get volume name
            char volumeName[MAX_PATH] = {0};
            if (GetVolumeInformationA(driveLetter, volumeName, MAX_PATH, NULL, NULL, NULL, NULL, 0)) {
                driver.VolumeName_ = volumeName;
            } else {
                MessageBoxW(NULL,
                    L"Error getting volume name.",
                    L"Error",
                    MB_OK);
            }

            DriversInfo.push_back(driver);
            driver = {};
        }
        drives >>= 1;
        ++driveLetter[0];
    }
}
