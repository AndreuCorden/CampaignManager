#include "WorldWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QSplitter>
#include <QTextEdit>

WorldWidget::WorldWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16, 16, 16, 16);

    QTabWidget *tabs = new QTabWidget(this);
    tabs->setDocumentMode(true);

    setupWikiTab(tabs);
    setupTimelineTab(tabs);
    setupMapsTab(tabs);
    setupCampaignsTab(tabs);

    mainLayout->addWidget(tabs);
}

void WorldWidget::setWorldDetails(const QString &name, const QString &description) {
    if (m_worldTitleLabel) {
        m_worldTitleLabel->setText(name);
    }
    if (m_worldDescEdit) {
        m_worldDescEdit->setPlainText(description);
    }
}

void WorldWidget::setupWikiTab(QTabWidget *tabs) {
    QWidget *wikiTab = new QWidget(this);
    QHBoxLayout *wikiLayout = new QHBoxLayout(wikiTab);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, wikiTab);

    // Left sidebar: Article index
    QWidget *navWidget = new QWidget(splitter);
    QVBoxLayout *navLayout = new QVBoxLayout(navWidget);
    navLayout->setContentsMargins(0, 0, 8, 0);

    QLabel *articlesHeader = new QLabel("Lore & Wiki Articles", navWidget);
    articlesHeader->setStyleSheet("font-weight: bold; font-size: 14px;");
    navLayout->addWidget(articlesHeader);

    QListWidget *articleList = new QListWidget(navWidget);
    articleList->addItem("Overview & General Lore");
    articleList->addItem("Factions & Guilds");
    articleList->addItem("Geography & Landmarks");
    articleList->addItem("Pantheon & Magic");
    navLayout->addWidget(articleList);

    QPushButton *addArticleBtn = new QPushButton("+ New Article", navWidget);
    addArticleBtn->setCursor(Qt::PointingHandCursor);
    navLayout->addWidget(addArticleBtn);

    // Right side: Article editor/view
    QWidget *contentWidget = new QWidget(splitter);
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(8, 0, 0, 0);

    m_worldTitleLabel = new QLabel("World Overview", contentWidget);
    m_worldTitleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    contentLayout->addWidget(m_worldTitleLabel);

    m_worldDescEdit = new QTextEdit(contentWidget);
    m_worldDescEdit->setPlaceholderText("Enter world details and lore overview...");
    contentLayout->addWidget(m_worldDescEdit);

    splitter->setSizes({220, 680});
    wikiLayout->addWidget(splitter);

    tabs->addTab(wikiTab, "📖 Wiki / Lore");
}

void WorldWidget::setupTimelineTab(QTabWidget *tabs) {
    QWidget *timelineTab = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(timelineTab);

    QHBoxLayout *header = new QHBoxLayout();
    QLabel *title = new QLabel("Chronological History & Events", timelineTab);
    title->setStyleSheet("font-size: 16px; font-weight: bold;");
    QPushButton *addEventBtn = new QPushButton("+ Add Event", timelineTab);
    addEventBtn->setCursor(Qt::PointingHandCursor);

    header->addWidget(title);
    header->addStretch();
    header->addWidget(addEventBtn);
    layout->addLayout(header);

    QListWidget *eventList = new QListWidget(timelineTab);
    eventList->addItem("Year 0: The First Age Begins");
    eventList->addItem("Year 412: The Sundering War");
    eventList->addItem("Year 1024: Present Era");
    layout->addWidget(eventList);

    tabs->addTab(timelineTab, "⏳ Timeline");
}

void WorldWidget::setupMapsTab(QTabWidget *tabs) {
    QWidget *mapsTab = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(mapsTab);

    QHBoxLayout *header = new QHBoxLayout();
    QLabel *title = new QLabel("World & Regional Maps", mapsTab);
    title->setStyleSheet("font-size: 16px; font-weight: bold;");
    QPushButton *uploadMapBtn = new QPushButton("+ Upload Map", mapsTab);
    uploadMapBtn->setCursor(Qt::PointingHandCursor);

    header->addWidget(title);
    header->addStretch();
    header->addWidget(uploadMapBtn);
    layout->addLayout(header);

    QListWidget *mapList = new QListWidget(mapsTab);
    mapList->addItem("Continental Map - Main Continent");
    mapList->addItem("Regional Map - Northern Reaches");
    layout->addWidget(mapList);

    tabs->addTab(mapsTab, "🗺️ Maps");
}

void WorldWidget::setupCampaignsTab(QTabWidget *tabs) {
    QWidget *campaignsTab = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(campaignsTab);

    QHBoxLayout *header = new QHBoxLayout();
    QLabel *title = new QLabel("Campaigns Set in This World", campaignsTab);
    title->setStyleSheet("font-size: 16px; font-weight: bold;");
    QPushButton *newCampaignBtn = new QPushButton("+ New Campaign", campaignsTab);
    newCampaignBtn->setCursor(Qt::PointingHandCursor);

    header->addWidget(title);
    header->addStretch();
    header->addWidget(newCampaignBtn);
    layout->addLayout(header);

    QListWidget *campaignList = new QListWidget(campaignsTab);
    campaignList->addItem("Campaign 1: Shadows over Eldoria");
    layout->addWidget(campaignList);

    tabs->addTab(campaignsTab, "⚔️ Campaigns");
}