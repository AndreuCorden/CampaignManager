#include "DashboardWidget.h"
#include "HubCardWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

DashboardWidget::DashboardWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(32, 32, 32, 32);

    // 1. Header Area
    QLabel *welcomeLabel = new QLabel("CAMPAIGN HUB", this);
    welcomeLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: #D4AF37;");
    
    QLabel *recentHeader = new QLabel("Jump Back In", this);
    recentHeader->setStyleSheet("font-size: 16px; font-weight: bold; color: #A0AEC0;");

    // 2. Primary Category Cards Layout (3 Columns)
    QHBoxLayout *cardsLayout = new QHBoxLayout();
    cardsLayout->setSpacing(20);

    // Section 1: Worlds & Campaigns
    m_worldsCard = new HubCardWidget("Worlds & Campaigns", 
                                     "Shelf for campaign setting lore and wikis", 
                                     "+ Create World", this);
    m_worldsCard->setMetricText("4 Worlds");
    m_worldsCard->setRecentSnippet("Last edit: Eldoria • Timeline of the Second Age");

    // Section 2: Miscellaneous Ideas
    m_ideasCard = new HubCardWidget("Scratchpad", 
                                    "Unsorted ideas, plot hooks, and loose concepts", 
                                    "+ New Idea", this);
    m_ideasCard->setMetricText("12 Notes");
    m_ideasCard->setRecentSnippet("Last edit: Underwater Dungeon Puzzle Idea");

    // Section 3: Player Vault
    m_charactersCard = new HubCardWidget("My Characters", 
                                         "Tracker for PCs in external campaigns", 
                                         "+ New Character", this);
    m_charactersCard->setMetricText("3 Characters");
    m_charactersCard->setRecentSnippet("Last edit: Garrick (Lv 6 Paladin) • Curse of Strahd");

    cardsLayout->addWidget(m_worldsCard);
    cardsLayout->addWidget(m_ideasCard);
    cardsLayout->addWidget(m_charactersCard);

    // Combine into main layout
    mainLayout->addWidget(welcomeLabel);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(recentHeader);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(cardsLayout);

    // Signal Routing
    connect(m_worldsCard, &HubCardWidget::cardClicked, this, &DashboardWidget::openWorldsSectionRequested);
    connect(m_ideasCard, &HubCardWidget::cardClicked, this, &DashboardWidget::openIdeasSectionRequested);
    connect(m_charactersCard, &HubCardWidget::cardClicked, this, &DashboardWidget::openCharactersSectionRequested);
}

void DashboardWidget::updateMetrics(int worldCount, int ideaCount, int charCount) {
    if (m_worldsCard) {
        m_worldsCard->setMetricCount(worldCount);
    }
    if (m_ideasCard) {
        m_ideasCard->setMetricCount(ideaCount);
    }
    if (m_charactersCard) {
        m_charactersCard->setMetricCount(charCount);
    }
}