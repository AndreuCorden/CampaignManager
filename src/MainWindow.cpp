#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    showFullScreen();

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 1. Create the UI elements
    m_titleLabel = new QLabel("CAMPAIGN MANAGER", centralWidget);
    m_logInButton = new QPushButton("LOG IN", centralWidget);
    m_registerButton = new QPushButton("REGISTER", centralWidget);
    m_exitButton = new QPushButton("EXIT", centralWidget);

    // 2. Style your text (Using simple web styling CSS syntax)
    m_titleLabel->setStyleSheet("font-size: 32px; font-weight: bold; color: #D4AF37;");
    m_titleLabel->setAlignment(Qt::AlignCenter);

    m_logInButton->setStyleSheet("padding: 10px; font-size: 18px;");
    m_registerButton->setStyleSheet("padding: 10px; font-size: 18px;");
    m_exitButton->setStyleSheet("padding: 10px; font-size: 18px;");

    m_logInButton->setFixedWidth(240);
    m_registerButton->setFixedWidth(240);
    m_exitButton->setFixedWidth(240);

    // 3. Arrange them vertically using a layout manager
    m_mainLayout = new QVBoxLayout(centralWidget);
    m_mainLayout->addStretch(); // Pushes elements down
    m_mainLayout->addWidget(m_titleLabel);
    m_mainLayout->addSpacing(40); // Adds clear blank pixels between items
    m_mainLayout->addWidget(m_logInButton, 0, Qt::AlignCenter);
    m_mainLayout->addWidget(m_registerButton, 0, Qt::AlignCenter);
    m_mainLayout->addWidget(m_exitButton, 0, Qt::AlignCenter);
    m_mainLayout->addStretch(); // Pushes elements up (centering the whole group)

    // 4. Hook up button clicks to trigger our game signals using modern C++ lambdas
    connect(m_logInButton, &QPushButton::clicked, this, &MainWindow::logInRequested);
    connect(m_registerButton, &QPushButton::clicked, this, &MainWindow::registerRequested);
    connect(m_exitButton, &QPushButton::clicked, this, &MainWindow::exitRequested);
}