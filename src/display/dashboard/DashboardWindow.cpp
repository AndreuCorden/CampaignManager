#include "DashboardWindow.h"
#include <QToolBar>
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>

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

    // User Label on the left
    QLabel *userLabel = new QLabel("Logged in as: " + username, this);
    userLabel->setStyleSheet("color: #D4AF37; font-weight: bold; margin-right: 12px;");
    topBar->addWidget(userLabel);

    // 3. Expanding Spacer — pushes everything after it to the far right
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    topBar->addWidget(spacer);

    // 4. Log Out Button on the right
    QPushButton *logoutBtn = new QPushButton("Log Out", this);
    logoutBtn->setCursor(Qt::PointingHandCursor);
    logoutBtn->setStyleSheet("margin-right: 2px; padding-top: 2px; padding-bottom: 5px;");
    logoutBtn->setCursor(Qt::PointingHandCursor);

    topBar->addWidget(logoutBtn);
    connect(logoutBtn, &QPushButton::clicked, this, &DashboardWindow::logoutRequested);
}