#include "DashboardWindow.h"
#include <QToolBar>
#include <QLabel>
#include <QPushButton>

DashboardWindow::DashboardWindow(const QString &username, QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    showFullScreen();

    // 1. Create inner view content widget
    m_dashboardWidget = new DashboardWidget(this);
    setCentralWidget(m_dashboardWidget);

    // 2. Add top header toolbar on the Window shell
    QToolBar *topBar = addToolBar("Navigation");
    topBar->setMovable(false);
    
    QLabel *userLabel = new QLabel("Logged in as: " + username + "  ", this);
    userLabel->setStyleSheet("color: #D4AF37; font-weight: bold; margin-right: 12px;");
    topBar->addWidget(userLabel);
}