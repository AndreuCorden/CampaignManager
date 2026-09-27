#include "WorldsWidget.h"
#include <QLabel>
#include <QScrollArea>
#include <QFrame>

WorldsWidget::WorldsWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 24, 24, 24);

    // --- Header Bar ---
    QHBoxLayout *headerLayout = new QHBoxLayout();

    QPushButton *backBtn = new QPushButton("← Back to Dashboard", this);
    backBtn->setCursor(Qt::PointingHandCursor);
    backBtn->setStyleSheet(
        "QPushButton {"
        "  padding: 8px 16px;"
        "  background-color: #2D3748;"
        "  color: #D4AF37;"
        "  border-radius: 4px;"
        "  font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "  background-color: #3A4A60;"
        "  color: #F6AD55;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #1A202C;"
        "}"
    );

    QLabel *titleLabel = new QLabel("Worlds & Campaigns Shelf", this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #D4AF37;");

    QPushButton *newWorldBtn = new QPushButton("+ New World", this);
    newWorldBtn->setCursor(Qt::PointingHandCursor);
    newWorldBtn->setStyleSheet(
        "QPushButton {"
        "  padding: 8px 16px;"
        "  background-color: #D4AF37;"
        "  color: #1A202C;"
        "  border-radius: 4px;"
        "  font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "  background-color: #ECC94B;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #B7791F;"
        "}"
    );

    headerLayout->addWidget(backBtn);
    headerLayout->addSpacing(16);
    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(newWorldBtn);

    mainLayout->addLayout(headerLayout);
    mainLayout->addSpacing(16);

    // --- Main Scrollable Container ---
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *scrollContent = new QWidget(scrollArea);
    QVBoxLayout *contentLayout = new QVBoxLayout(scrollContent);
    contentLayout->setSpacing(24);

    // SECTION 1: Active Worlds
    QLabel *activeWorldsHeader = new QLabel("Active Worlds (Most Recently Opened)", scrollContent);
    activeWorldsHeader->setStyleSheet("font-size: 16px; font-weight: bold; color: #E2E8F0;");
    contentLayout->addWidget(activeWorldsHeader);

    m_activeWorldsLayout = new QVBoxLayout();
    contentLayout->addLayout(m_activeWorldsLayout);

    // SECTION 2: Active Campaigns
    QLabel *campaignsHeader = new QLabel("Recent Campaigns (Top 5 Active)", scrollContent);
    campaignsHeader->setStyleSheet("font-size: 16px; font-weight: bold; color: #E2E8F0;");
    contentLayout->addWidget(campaignsHeader);

    m_campaignsLayout = new QHBoxLayout();
    contentLayout->addLayout(m_campaignsLayout);

    // SECTION 3: Closed / Archived Worlds
    QLabel *closedWorldsHeader = new QLabel("Archived Worlds", scrollContent);
    closedWorldsHeader->setStyleSheet("font-size: 16px; font-weight: bold; color: #A0AEC0;");
    contentLayout->addWidget(closedWorldsHeader);

    m_closedWorldsLayout = new QVBoxLayout();
    contentLayout->addLayout(m_closedWorldsLayout);

    scrollArea->setWidget(scrollContent);
    mainLayout->addWidget(scrollArea);

    // Connect Header Signals
    connect(backBtn, &QPushButton::clicked, this, &WorldsWidget::backToDashboardRequested);
    connect(newWorldBtn, &QPushButton::clicked, this, &WorldsWidget::createWorldRequested);
}

void WorldsWidget::populateActiveWorlds(const QList<QPair<int, QString>> &worlds) {
    clearLayout(m_activeWorldsLayout);
    for (const auto &pair : worlds) {
        int worldId = pair.first;
        QPushButton *btn = new QPushButton(pair.second, this);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(
            "QPushButton {"
            "  text-align: left;"
            "  padding: 12px;"
            "  background-color: #2D3748;"
            "  color: white;"
            "  border-radius: 6px;"
            "  border: 1px solid transparent;"
            "}"
            "QPushButton:hover {"
            "  background-color: #3A4A60;"
            "  border: 1px solid #D4AF37;"
            "}"
            "QPushButton:pressed {"
            "  background-color: #1A202C;"
            "}"
        );
        connect(btn, &QPushButton::clicked, this, [this, worldId]() { emit openWorldRequested(worldId); });
        m_activeWorldsLayout->addWidget(btn);
    }
}

void WorldsWidget::populateTopCampaigns(const QList<QPair<int, QString>> &campaigns) {
    clearLayout(m_campaignsLayout);
    for (const auto &pair : campaigns) {
        int campaignId = pair.first;
        QPushButton *btn = new QPushButton(pair.second, this);
        btn->setMinimumHeight(80);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(
            "QPushButton {"
            "  padding: 12px;"
            "  background-color: #1A202C;"
            "  border: 1px solid #D4AF37;"
            "  color: #D4AF37;"
            "  border-radius: 6px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #2D3748;"
            "  color: #ECC94B;"
            "  border-color: #ECC94B;"
            "}"
            "QPushButton:pressed {"
            "  background-color: #0F172A;"
            "}"
        );
        connect(btn, &QPushButton::clicked, this, [this, campaignId]() { emit openCampaignRequested(campaignId); });
        m_campaignsLayout->addWidget(btn);
    }
}

void WorldsWidget::populateClosedWorlds(const QList<QPair<int, QString>> &closedWorlds) {
    clearLayout(m_closedWorldsLayout);
    for (const auto &pair : closedWorlds) {
        int worldId = pair.first;
        QHBoxLayout *row = new QHBoxLayout();

        QLabel *nameLabel = new QLabel(pair.second, this);
        nameLabel->setStyleSheet("color: #A0AEC0; font-size: 14px;");

        QPushButton *reactivateBtn = new QPushButton("Reactivate", this);
        reactivateBtn->setCursor(Qt::PointingHandCursor);
        reactivateBtn->setStyleSheet(
            "QPushButton {"
            "  padding: 4px 12px;"
            "  background-color: #4A5568;"
            "  color: white;"
            "  border-radius: 4px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #2B6CB0;"
            "}"
            "QPushButton:pressed {"
            "  background-color: #1A365D;"
            "}"
        );
        connect(reactivateBtn, &QPushButton::clicked, this, [this, worldId]() { emit reactivateWorldRequested(worldId); });

        row->addWidget(nameLabel);
        row->addStretch();
        row->addWidget(reactivateBtn);
        m_closedWorldsLayout->addLayout(row);
    }
}

void WorldsWidget::clearLayout(QLayout *layout) {
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        if (child->widget()) delete child->widget();
        if (child->layout()) clearLayout(child->layout());
        delete child;
    }
}