#include "WorldWidget.h"
#include "tabs/CampaignsTabWidget.h"
#include "tabs/WikiTabWidget.h"
#include "tabs/MapsTabWidget.h"
#include "tabs/TimelineTabWidget.h"
#include <QVBoxLayout>
#include <QTabWidget>

WorldWidget::WorldWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);

    QTabWidget *tabs = new QTabWidget(this);
    tabs->setDocumentMode(true);
    tabs->setStyleSheet(
        "QTabWidget::pane { border: 1px solid #4A5568; background: #1A202C; }"
        "QTabBar::tab { background: #2D3748; color: #A0AEC0; padding: 10px 20px; font-weight: bold; border-top-left-radius: 6px; border-top-right-radius: 6px; }"
        "QTabBar::tab:selected { background: #1A202C; color: #D4AF37; border-top: 2px solid #D4AF37; }"
    );

    // Instantiating isolated tab widgets
    m_campaignsTab = new CampaignsTabWidget(this);
    m_wikiTab = new WikiTabWidget(this);
    m_mapsTab = new MapsTabWidget(this);
    m_timelineTab = new TimelineTabWidget(this);

    // Order: 1. Campaigns, 2. Wiki / Lore, 3. Maps, 4. Timeline
    tabs->addTab(m_campaignsTab, "⚔️ Campaigns");
    tabs->addTab(m_wikiTab, "📖 Wiki / Lore");
    tabs->addTab(m_mapsTab, "🗺️ Maps");
    tabs->addTab(m_timelineTab, "⏳ Timeline");

    mainLayout->addWidget(tabs);
}

void WorldWidget::setWorldDetails(const QString &name, const QString &description) {
    Q_UNUSED(name);
    Q_UNUSED(description);
}