#include "WorldsWidget.h"
#include "WorldCard.h"
#include "WorldDropZone.h"
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

WorldsWidget::WorldsWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 24, 24, 24);

    // --- Header Bar ---
    QHBoxLayout *headerLayout = new QHBoxLayout();

    QPushButton *backBtn = new QPushButton("← Back to Dashboard", this);
    backBtn->setCursor(Qt::PointingHandCursor);
    backBtn->setStyleSheet(
        "QPushButton { padding: 8px 16px; background-color: #2D3748; color: #D4AF37; border-radius: 4px; font-weight: bold; }"
        "QPushButton:hover { background-color: #3A4A60; color: #F6AD55; }"
    );

    QLabel *titleLabel = new QLabel("Worlds & Campaigns Shelf", this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #D4AF37;");

    QPushButton *newWorldBtn = new QPushButton("+ New World", this);
    newWorldBtn->setCursor(Qt::PointingHandCursor);
    newWorldBtn->setStyleSheet(
        "QPushButton { padding: 8px 16px; background-color: #D4AF37; color: #1A202C; border-radius: 4px; font-weight: bold; }"
        "QPushButton:hover { background-color: #ECC94B; }"
    );

    headerLayout->addWidget(backBtn);
    headerLayout->addSpacing(16);
    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(newWorldBtn);

    mainLayout->addLayout(headerLayout);
    mainLayout->addSpacing(16);

    // --- Main Scroll Area ---
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("background: transparent;");

    QWidget *scrollContent = new QWidget(scrollArea);
    scrollContent->setStyleSheet("background: transparent;");
    
    QVBoxLayout *contentLayout = new QVBoxLayout(scrollContent);
    contentLayout->setContentsMargins(0, 0, 16, 0);
    contentLayout->setSpacing(24);

    // SECTION 1: Active Worlds (Drop Zone -> Reactivates/Unarchives dropped world)
    QLabel *activeWorldsHeader = new QLabel("Active Worlds (Drag here to unarchive)", scrollContent);
    activeWorldsHeader->setStyleSheet("font-size: 16px; font-weight: bold; color: #E2E8F0;");
    contentLayout->addWidget(activeWorldsHeader);

    WorldDropZone *activeDropZone = new WorldDropZone(scrollContent);
    m_activeWorldsLayout = activeDropZone->contentLayout();
    contentLayout->addWidget(activeDropZone);

    connect(activeDropZone, &WorldDropZone::worldDropped, this, &WorldsWidget::reactivateWorldRequested);

    // SECTION 2: Active Campaigns
    QLabel *campaignsHeader = new QLabel("Recent Campaigns (Top 5 Active)", scrollContent);
    campaignsHeader->setStyleSheet("font-size: 16px; font-weight: bold; color: #E2E8F0;");
    contentLayout->addWidget(campaignsHeader);

    m_campaignsLayout = new QHBoxLayout();
    m_campaignsLayout->setSpacing(12);
    contentLayout->addLayout(m_campaignsLayout);

    // SECTION 3: Closed / Archived Worlds (Drop Zone -> Archives dropped world)
    QLabel *closedWorldsHeader = new QLabel("Archived Worlds (Drag here to archive)", scrollContent);
    closedWorldsHeader->setStyleSheet("font-size: 16px; font-weight: bold; color: #A0AEC0;");
    contentLayout->addWidget(closedWorldsHeader);

    WorldDropZone *archivedDropZone = new WorldDropZone(scrollContent);
    m_closedWorldsLayout = archivedDropZone->contentLayout();
    contentLayout->addWidget(archivedDropZone);

    connect(archivedDropZone, &WorldDropZone::worldDropped, this, &WorldsWidget::archiveWorldRequested);

    contentLayout->addStretch();

    scrollArea->setWidget(scrollContent);
    mainLayout->addWidget(scrollArea);

    connect(backBtn, &QPushButton::clicked, this, &WorldsWidget::backToDashboardRequested);
    connect(newWorldBtn, &QPushButton::clicked, this, &WorldsWidget::createWorldRequested);
}

void WorldsWidget::populateActiveWorlds(const QList<World> &worlds) {
    clearLayout(m_activeWorldsLayout);

    if (worlds.isEmpty()) {
        QLabel *emptyLabel = new QLabel("No active worlds found. Click '+ New World' to create one!", this);
        emptyLabel->setStyleSheet("color: #718096; font-style: italic; font-size: 14px; margin: 8px 0;");
        m_activeWorldsLayout->addWidget(emptyLabel);
        return;
    }

    for (const World &world : worlds) {
        WorldCard *card = new WorldCard(world.id(), world.name(), world.description(), false, this);

        connect(card, &WorldCard::cardClicked, this, &WorldsWidget::openWorldRequested);
        connect(card, &WorldCard::archiveRequested, this, &WorldsWidget::archiveWorldRequested);
        connect(card, &WorldCard::deleteRequested, this, &WorldsWidget::deleteWorldRequested);

        m_activeWorldsLayout->addWidget(card);
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
            "QPushButton { padding: 12px; background-color: #1A202C; border: 1px solid #D4AF37; color: #D4AF37; border-radius: 6px; }"
            "QPushButton:hover { background-color: #2D3748; color: #ECC94B; border-color: #ECC94B; }"
            "QPushButton:pressed { background-color: #0F172A; }"
        );
        connect(btn, &QPushButton::clicked, this, [this, campaignId]() { emit openCampaignRequested(campaignId); });
        m_campaignsLayout->addWidget(btn);
    }
}

void WorldsWidget::populateClosedWorlds(const QList<World> &worlds) {
    clearLayout(m_closedWorldsLayout);
    if (worlds.isEmpty()) {
        QLabel *emptyLabel = new QLabel("No closed worlds found.", this);
        emptyLabel->setStyleSheet("color: #718096; font-style: italic; font-size: 14px; margin: 8px 0;");
        m_closedWorldsLayout->addWidget(emptyLabel);
        return;
    }

    for (const World &world : worlds) {
        WorldCard *card = new WorldCard(world.id(), world.name(), world.description(), true, this);

        connect(card, &WorldCard::cardClicked, this, &WorldsWidget::openWorldRequested);
        connect(card, &WorldCard::archiveRequested, this, &WorldsWidget::reactivateWorldRequested);
        connect(card, &WorldCard::deleteRequested, this, &WorldsWidget::deleteWorldRequested);

        m_closedWorldsLayout->addWidget(card);
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