#include "MapsTabWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

MapsTabWidget::MapsTabWidget(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(8, 8, 8, 8);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);

    // Sidebar: Maps Index
    QWidget *navWidget = new QWidget(splitter);
    QVBoxLayout *navLayout = new QVBoxLayout(navWidget);

    QLabel *worldLabel = new QLabel("🌐 World Maps", navWidget);
    worldLabel->setStyleSheet("font-weight: bold; color: #D4AF37;");
    navLayout->addWidget(worldLabel);

    m_worldMapsList = new QListWidget(navWidget);
    m_worldMapsList->addItem("World Continent - Global View");
    m_worldMapsList->addItem("Northern Ocean Trade Routes");
    navLayout->addWidget(m_worldMapsList);

    QLabel *campaignLabel = new QLabel("⚔️ Campaign Maps", navWidget);
    campaignLabel->setStyleSheet("font-weight: bold; color: #D4AF37; margin-top: 10px;");
    navLayout->addWidget(campaignLabel);

    m_campaignMapsList = new QListWidget(navWidget);
    m_campaignMapsList->addItem("[Campaign A] City of Eldoria");
    m_campaignMapsList->addItem("[Campaign A] Dungeon Level 1");
    m_campaignMapsList->addItem("[Campaign B] Sunken Archipelago");
    navLayout->addWidget(m_campaignMapsList);

    QPushButton *uploadBtn = new QPushButton("+ Upload Map Image", navWidget);
    uploadBtn->setStyleSheet("QPushButton { background: #2D3748; color: #D4AF37; padding: 6px; font-weight: bold; border-radius: 4px; }");
    navLayout->addWidget(uploadBtn);

    // Viewport
    m_mapViewerPlaceholder = new QLabel("Select a map to view details and markers.", splitter);
    m_mapViewerPlaceholder->setAlignment(Qt::AlignCenter);
    m_mapViewerPlaceholder->setStyleSheet("QLabel { background: #1A202C; border: 1px solid #4A5568; color: #A0AEC0; font-size: 16px; }");

    splitter->setSizes({260, 740});
    mainLayout->addWidget(splitter);
}