#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent): QWidget(parent) {
    mainLayout = new QHBoxLayout(this);
    buttonLayout = new QVBoxLayout();

    this->resize(800, 600);
    CPU_Button = new QPushButton("CPU_Button", this);
    CPU_Button->setGeometry(QRect(5, 50, 95, 60));
    Driver_Button = new QPushButton("Driver_Button", this);
    Driver_Button->setGeometry(QRect(5, 100, 95, 60));
    Memory_Button = new QPushButton("Memory_Button", this);
    Memory_Button->setGeometry(QRect(5, 150, 95, 60));
    GPU_Button = new QPushButton("GPU_Button", this);
    GPU_Button->setGeometry(QRect(5, 200, 95, 60));
    Process_Button = new QPushButton("Process_Button", this);
    Process_Button->setGeometry(QRect(5, 250, 95, 60));

    buttonLayout->addWidget(CPU_Button);
    buttonLayout->addWidget(Driver_Button);
    buttonLayout->addWidget(Memory_Button);
    buttonLayout->addWidget(GPU_Button);
    buttonLayout->addWidget(Process_Button);

    mainLayout->addLayout(buttonLayout);

    connect(CPU_Button, &QPushButton::clicked, this, &MainWindow::CPU_Button_clicked);
    connect(Driver_Button, &QPushButton::clicked, this, &MainWindow::Driver_Button_clicked);
    connect(Memory_Button, &QPushButton::clicked, this, &MainWindow::Memory_Button_clicked);
    connect(GPU_Button, &QPushButton::clicked, this, &MainWindow::GPU_Button_clicked);
    connect(Process_Button, &QPushButton::clicked, this, &MainWindow::Process_Button_clicked);

    StackWidget = new QStackedWidget();
    //StackWidget->resize(700, 600);
    //StackWidget->setGeometry(QRect(100, 0, 700, 600));
    mainLayout->addWidget(StackWidget);

    cpu = new CPU_Page();
    memory = new Memory_Page();
    driver = new Driver_Page();
    gpu = new GPU_Page();
    process = new Process_Page();

    StackWidget->addWidget(cpu);
    StackWidget->addWidget(driver);
    StackWidget->addWidget(memory);
    StackWidget->addWidget(gpu);
    StackWidget->addWidget(process);

    StackWidget->setCurrentIndex(0);
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
}

void MainWindow::Driver_Button_clicked() {
    animateTransition(StackWidget->currentIndex(), 1);
}

void MainWindow::Memory_Button_clicked() {
    animateTransition(StackWidget->currentIndex(), 2);
}

void MainWindow::GPU_Button_clicked() {
    animateTransition(StackWidget->currentIndex(), 3);
}

void MainWindow::Process_Button_clicked() {
    animateTransition(StackWidget->currentIndex(), 4);
}
