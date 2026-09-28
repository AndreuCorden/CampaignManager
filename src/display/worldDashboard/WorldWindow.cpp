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

    // Central workspace
    m_worldWidget = new WorldWidget(this);
    setCentralWidget(m_worldWidget);

    // Header Toolbar
    QToolBar *topBar = addToolBar("Navigation");
    topBar->setMovable(false);

    QPushButton *backBtn = new QPushButton("← Back to Worlds", this);
    backBtn->setCursor(Qt::PointingHandCursor);
    backBtn->setStyleSheet("margin-left: 8px; padding: 4px 12px;");
    topBar->addWidget(backBtn);

    m_titleLabel = new QLabel(" World Workspace", this);
    m_titleLabel->setStyleSheet("font-weight: bold; margin-left: 16px; font-size: 14px;");
    topBar->addWidget(m_titleLabel);

    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    topBar->addWidget(spacer);

    QLabel *userLabel = new QLabel("Logged in as: " + username, this);
    userLabel->setStyleSheet("margin-right: 12px;");
    topBar->addWidget(userLabel);

    connect(backBtn, &QPushButton::clicked, this, &WorldWindow::backToWorldsRequested);
}

void WorldWindow::setWorldDetails(const QString &name, const QString &description) {
    m_titleLabel->setText(" World: " + name);
    m_worldWidget->setWorldDetails(name, description);
}