#include "WorldsWindow.h"
#include <QToolBar>
#include <QLabel>

WorldsWindow::WorldsWindow(const QString &username, QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Campaign Manager - Worlds Shelf");
    resize(1280, 720);

    // Set central view
    m_worldsWidget = new WorldsWidget(this);
    setCentralWidget(m_worldsWidget);

    // Top header bar
    QToolBar *topBar = addToolBar("Navigation");
    topBar->setMovable(false);

    QLabel *userLabel = new QLabel("User: " + username + "  ", this);
    userLabel->setStyleSheet("color: #D4AF37; font-weight: bold; margin-right: 12px;");
    topBar->addWidget(userLabel);
}