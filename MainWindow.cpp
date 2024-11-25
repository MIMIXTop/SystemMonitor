#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent): QWidget(parent) {
    mainLayout = new QHBoxLayout(this);
    buttonLayout = new QVBoxLayout();
    stackLayout = new QVBoxLayout();
    NamePage = new QLabel();

    NamePage->setFixedHeight(30);

    NamePage->setObjectName("NamePage");
    buttonLayout->setObjectName("myLabel");

    this->resize(800, 600);

    CPU_Button = new QPushButton();
    CPU_Button->setIcon(QIcon("../Image/IconButton/cpu_yellow.png"));
    CPU_Button->setIconSize(QSize(75, 75));
    CPU_Button->setCheckable(true);

    Memory_Button = new QPushButton();
    Memory_Button->setIcon(QIcon("../Image/IconButton/ram_yellow.png"));
    Memory_Button->setIconSize(QSize(75, 75));

    Process_Button = new QPushButton();
    Process_Button->setIcon(QIcon("../Image/IconButton/process_yellow.png"));
    Process_Button->setIconSize(QSize(75, 75));

    Driver_Button = new QPushButton();
    Driver_Button->setIcon(QIcon("../Image/IconButton/linux_logo_yellow.png"));
    Driver_Button->setIconSize(QSize(75, 75));

    buttonLayout->addWidget(CPU_Button);
    buttonLayout->addWidget(Memory_Button);
    buttonLayout->addWidget(Process_Button);
    buttonLayout->addWidget(Driver_Button);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);

    connect(CPU_Button, &QPushButton::clicked, this, &MainWindow::CPU_Button_clicked);
    connect(Driver_Button, &QPushButton::clicked, this, &MainWindow::Driver_Button_clicked);
    connect(Memory_Button, &QPushButton::clicked, this, &MainWindow::Memory_Button_clicked);
    connect(Process_Button, &QPushButton::clicked, this, &MainWindow::Process_Button_clicked);

    StackWidget = new QStackedWidget();
    stackLayout->addWidget(NamePage);
    stackLayout->addWidget(StackWidget);

    mainLayout->addLayout(stackLayout);

    cpu = new CPU_Page();
    cpu->setObjectName("CPU_Page");
    memory = new Memory_Page();
    driver = new System_Page();
    process = new Process_Page();

    StackWidget->addWidget(cpu);
    StackWidget->addWidget(memory);
    StackWidget->addWidget(process);
    StackWidget->addWidget(driver);

    StackWidget->setCurrentIndex(0);
    NamePage->setText("Процессор");
    NamePage->setAlignment(Qt::AlignHCenter);
    setLayout(mainLayout);
}


void MainWindow::animateTransition(int fromIndex, int toIndex) {
    if (fromIndex == toIndex) return;

    QWidget *currentWidget = StackWidget->widget(fromIndex);
    QWidget *nextWidget = StackWidget->widget(toIndex);

    nextWidget->setGeometry(currentWidget->geometry());
    nextWidget->setVisible(true);

    QPropertyAnimation *flipOutAnimation = new QPropertyAnimation(currentWidget,"geometry");
    flipOutAnimation->setDuration(500);
    flipOutAnimation->setStartValue(currentWidget->geometry());
    flipOutAnimation->setEndValue(QRect(currentWidget->x() + currentWidget->width(), currentWidget->y(), currentWidget->width(), currentWidget->height()));

    QPropertyAnimation *flipInAnimation = new QPropertyAnimation(nextWidget,"geometry");
    flipInAnimation->setDuration(500);
    flipInAnimation->setStartValue(QRect(currentWidget->x() - currentWidget->width(), currentWidget->y(), currentWidget->width(), currentWidget->height()));
    flipInAnimation->setEndValue(currentWidget->geometry());

    connect(flipOutAnimation, &QPropertyAnimation::finished,[=]() {
        StackWidget->setCurrentIndex(toIndex);
        currentWidget->setVisible(false);
    });

    flipOutAnimation->start();
    flipInAnimation->start();
}

void MainWindow::CPU_Button_clicked() {
    animateTransition(StackWidget->currentIndex(), 0);
    NamePage->setText("Процессор");

}

void MainWindow::Driver_Button_clicked() {
    animateTransition(StackWidget->currentIndex(), 3);
    NamePage->setText("Система");
}

void MainWindow::Memory_Button_clicked() {
    animateTransition(StackWidget->currentIndex(), 1);
    NamePage->setText("Оперативная память");
}

void MainWindow::Process_Button_clicked() {
    animateTransition(StackWidget->currentIndex(), 2);
    NamePage->setText("Процессы");
}
