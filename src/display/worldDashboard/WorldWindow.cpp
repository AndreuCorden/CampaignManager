#include "WorldWindow.h"
#include "WorldWidget.h"
#include <QToolBar>
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>

WorldWindow::WorldWindow(const QString &username, QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    showFullScreen();

    // Central workspace widget
    m_worldWidget = new WorldWidget(this);
    setCentralWidget(m_worldWidget);

    // Header Toolbar
    QToolBar *topBar = addToolBar("Navigation");
    topBar->setMovable(false);

    // 1. User Label (Matches WorldsWindow positioning & gold styling)
    QLabel *userLabel = new QLabel("User: " + username + "  ", this);
    userLabel->setStyleSheet("color: #D4AF37; font-weight: bold; margin-right: 12px;");
    topBar->addWidget(userLabel);

    // 2. Active World Name Header
    m_titleLabel = new QLabel(" World Workspace", this);
    m_titleLabel->setStyleSheet("font-weight: bold; font-size: 14px; color: #E2E8F0; margin-left: 8px;");
    topBar->addWidget(m_titleLabel);

    // 3. Spacer pushing controls to the far right
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    topBar->addWidget(spacer);

    // 4. Back Navigation Button
    QPushButton *backBtn = new QPushButton("← Back to Worlds", this);
    backBtn->setCursor(Qt::PointingHandCursor);
    topBar->addWidget(backBtn);

    connect(backBtn, &QPushButton::clicked, this, &WorldWindow::backToWorldsRequested);
}

void WorldWindow::setWorldDetails(const QString &name, const QString &description) {
    m_titleLabel->setText(" World: " + name);
    m_worldWidget->setWorldDetails(name, description);
}