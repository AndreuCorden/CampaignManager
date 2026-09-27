#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // 1. Frameless Window setup
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    showFullScreen();

    // 2. Global Dark Medieval Styling
    setStyleSheet(R"(
        QMainWindow {
            background-color: #1a1a1a;
            border: 2px solid #4a3b2c;
        }
        QLabel {
            color: #dcdcdc;
            font-family: 'Segoe UI', sans-serif;
        }
        QPushButton {
            background-color: #2b2b2b;
            color: #e0e0e0;
            border: 1px solid #5a4b3c;
            border-radius: 4px;
            padding: 10px 20px;
            font-size: 16px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #3d3126;
            border: 1px solid #8c6d46;
            color: #ffffff;
        }
        QPushButton:pressed {
            background-color: #1f1812;
        }
    )");

    // 3. Controller & Navigation Setup
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    stackedWidget->setCurrentIndex(0);
}