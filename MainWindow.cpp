#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    mainLayout = new QHBoxLayout(this);
    StackWidget = new QStackedWidget();
    buttonLayout = new QVBoxLayout();
    backgroundWidget = new QWidget();
    stackLayout = new QVBoxLayout(backgroundWidget);
    NamePage = new QLabel();

    backgroundWidget->setObjectName("BackGround");
    setObjectName("mainWindow");

    NamePage->setFixedHeight(30);
    NamePage->setAlignment(Qt::AlignCenter);
    NamePage->setObjectName("NamePage");

    this->resize(800, 600);

    // Создание кнопок
    CPU_Button = new QPushButton();
    CPU_Button->setIcon(QIcon("../Image/IconButton/cpu_yellow.png"));
    CPU_Button->setIconSize(QSize(75, 75));
    CPU_Button->setMinimumSize(75, 75);
    CPU_Button->setMaximumSize(95, 95);
    CPU_Button->setStyleSheet("background-color: #3CB371;");

    Memory_Button = new QPushButton();
    Memory_Button->setIcon(QIcon("../Image/IconButton/ram_yellow.png"));
    Memory_Button->setIconSize(QSize(75, 75));
    Memory_Button->setMinimumSize(75, 75);
    Memory_Button->setMaximumSize(95, 95);

    Process_Button = new QPushButton();
    Process_Button->setIcon(QIcon("../Image/IconButton/process_yellow.png"));
    Process_Button->setIconSize(QSize(75, 75));
    Process_Button->setMinimumSize(75, 75);
    Process_Button->setMaximumSize(95, 95);

    Driver_Button = new QPushButton();
    Driver_Button->setIcon(QIcon("../Image/IconButton/linux_logo_yellow.png"));
    Driver_Button->setIconSize(QSize(75, 75));
    Driver_Button->setMinimumSize(75, 75);
    Driver_Button->setMaximumSize(95, 95);

    // Добавление кнопок в layout
    buttonLayout->addWidget(CPU_Button);
    buttonLayout->addWidget(Memory_Button);
    buttonLayout->addWidget(Process_Button);
    buttonLayout->addWidget(Driver_Button);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(CPU_Button, &QPushButton::clicked, this, &MainWindow::CPU_Button_clicked);
    connect(Driver_Button, &QPushButton::clicked, this, &MainWindow::Driver_Button_clicked);
    connect(Memory_Button, &QPushButton::clicked, this, &MainWindow::Memory_Button_clicked);
    connect(Process_Button, &QPushButton::clicked, this, &MainWindow::Process_Button_clicked);

    // Создание QStackedWidget и страниц
    stackLayout->addWidget(NamePage);
    stackLayout->addWidget(StackWidget);
    StackWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(backgroundWidget);

    cpu = new CPU_Page();
    memory = new Memory_Page();
    driver = new System_Page();
    process = new Process_Page();

    StackWidget->addWidget(cpu);
    StackWidget->addWidget(memory);
    StackWidget->addWidget(process);
    StackWidget->addWidget(driver);

    StackWidget->setCurrentIndex(0);
    NamePage->setText("Процессор");
}

void MainWindow::animateTransition(int fromIndex, int toIndex) {
    if (fromIndex == toIndex || animationInProgress) return;

    animationInProgress = true;

    QWidget *currentWidget = StackWidget->widget(fromIndex);
    QWidget *nextWidget = StackWidget->widget(toIndex);

    nextWidget->setGeometry(currentWidget->geometry());
    nextWidget->setVisible(true);

    QPropertyAnimation *flipOutAnimation = new QPropertyAnimation(currentWidget, "geometry");
    flipOutAnimation->setDuration(500);
    flipOutAnimation->setStartValue(currentWidget->geometry());

    if (fromIndex > toIndex) {
        flipOutAnimation->setEndValue(QRect(currentWidget->x() + currentWidget->width(), currentWidget->y(), currentWidget->width(), currentWidget->height()));
    } else {
        flipOutAnimation->setEndValue(QRect(currentWidget->x() - currentWidget->width(), currentWidget->y(), currentWidget->width(), currentWidget->height()));
    }

    QPropertyAnimation *flipInAnimation = new QPropertyAnimation(nextWidget, "geometry");
    flipInAnimation->setDuration(500);

    if (fromIndex > toIndex) {
        flipInAnimation->setStartValue(QRect(currentWidget->x() - currentWidget->width(), currentWidget->y(), currentWidget->width(), currentWidget->height()));
    } else {
        flipInAnimation->setStartValue(QRect(currentWidget->x() + currentWidget->width(), currentWidget->y(), currentWidget->width(), currentWidget->height()));
    }
    flipInAnimation->setEndValue(currentWidget->geometry());

    QParallelAnimationGroup *animationGroup = new QParallelAnimationGroup(this);
    animationGroup->addAnimation(flipOutAnimation);
    animationGroup->addAnimation(flipInAnimation);

    connect(animationGroup, &QParallelAnimationGroup::finished, [=]() {
        StackWidget->setCurrentIndex(toIndex);
        currentWidget->setVisible(false);
        animationInProgress = false;
    });

    animationGroup->start();
}

void MainWindow::settingButtons(QPushButton *clickedButton) {
    for (QPushButton *button : findChildren<QPushButton *>()) {
        button->setStyleSheet("");
    }

    clickedButton->setStyleSheet("background-color: #3CB371;");
}

void MainWindow::CPU_Button_clicked() {
    animateTransition(StackWidget->currentIndex(), 0);
    NamePage->setText("Процессор");
    settingButtons(CPU_Button);
}

void MainWindow::Driver_Button_clicked() {
    animateTransition(StackWidget->currentIndex(), 3);
    NamePage->setText("Система");
    settingButtons(Driver_Button);
}

void MainWindow::Memory_Button_clicked() {
    animateTransition(StackWidget->currentIndex(), 1);
    NamePage->setText("Оперативная память");
    settingButtons(Memory_Button);
}

void MainWindow::Process_Button_clicked() {
    animateTransition(StackWidget->currentIndex(), 2);
    NamePage->setText("Процессы");
    settingButtons(Process_Button);
}