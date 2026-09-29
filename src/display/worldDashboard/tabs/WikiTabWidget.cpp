#include "WikiTabWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QLineEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>

WikiTabWidget::WikiTabWidget(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(8, 8, 8, 8);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);

    // --- Left Sidebar: Search + Categorized Tree ---
    QWidget *navWidget = new QWidget(splitter);
    QVBoxLayout *navLayout = new QVBoxLayout(navWidget);
    navLayout->setContentsMargins(0, 0, 8, 0);

    m_searchEdit = new QLineEdit(navWidget);
    m_searchEdit->setPlaceholderText("🔍 Search by title or tag (e.g., war, politics, person)...");
    m_searchEdit->setStyleSheet("QLineEdit { padding: 6px; background: #1A202C; color: #E2E8F0; border: 1px solid #4A5568; border-radius: 4px; }");
    navLayout->addWidget(m_searchEdit);

    m_treeWidget = new QTreeWidget(navWidget);
    m_treeWidget->setHeaderHidden(true);
    m_treeWidget->setStyleSheet(
        "QTreeWidget { background: #1A202C; color: #E2E8F0; border: 1px solid #4A5568; border-radius: 4px; }"
        "QTreeWidget::item:selected { background: #2D3748; color: #D4AF37; }"
    );
    navLayout->addWidget(m_treeWidget);

    QPushButton *addArticleBtn = new QPushButton("+ New Article", navWidget);
    addArticleBtn->setStyleSheet("QPushButton { background-color: #2D3748; color: #D4AF37; padding: 6px; font-weight: bold; border-radius: 4px; }");
    navLayout->addWidget(addArticleBtn);

    // --- Right Pane: Article Content ---
    QWidget *contentWidget = new QWidget(splitter);
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(8, 0, 0, 0);

    m_articleTitleLabel = new QLabel("Select an Article", contentWidget);
    m_articleTitleLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #D4AF37;");
    contentLayout->addWidget(m_articleTitleLabel);

    m_articleContentEdit = new QTextEdit(contentWidget);
    m_articleContentEdit->setStyleSheet("QTextEdit { background: #1A202C; color: #E2E8F0; border: 1px solid #4A5568; border-radius: 4px; }");
    contentLayout->addWidget(m_articleContentEdit);

    splitter->setSizes({280, 720});
    mainLayout->addWidget(splitter);

    populateSampleData();

    connect(m_searchEdit, &QLineEdit::textChanged, this, &WikiTabWidget::filterWikiEntries);
    connect(m_treeWidget, &QTreeWidget::currentItemChanged, this, &WikiTabWidget::onArticleSelected);
}

void WikiTabWidget::populateSampleData() {
    // Top Section 1: World-Wide Lore
    QTreeWidgetItem *worldRoot = new QTreeWidgetItem(m_treeWidget);
    worldRoot->setText(0, "🌐 World-Wide Lore");
    worldRoot->setExpanded(true);

    QTreeWidgetItem *pantheon = new QTreeWidgetItem(worldRoot);
    pantheon->setText(0, "The Old Gods");
    pantheon->setData(0, Qt::UserRole, "religion god pantheon magic person myth");

    QTreeWidgetItem *geography = new QTreeWidgetItem(worldRoot);
    geography->setText(0, "The Dragonbone Peaks");
    geography->setData(0, Qt::UserRole, "geography war mountain border landmark");

    // Top Section 2: Campaign Specific Lore
    QTreeWidgetItem *campaignRoot = new QTreeWidgetItem(m_treeWidget);
    campaignRoot->setText(0, "⚔️ Campaign Subsections");
    campaignRoot->setExpanded(true);

    QTreeWidgetItem *campA = new QTreeWidgetItem(campaignRoot);
    campA->setText(0, "Campaign A: Shadows over Eldoria");
    campA->setExpanded(true);

    QTreeWidgetItem *scandalArticle = new QTreeWidgetItem(campA);
    scandalArticle->setText(0, "The Royal Succession Scandal");
    scandalArticle->setData(0, Qt::UserRole, "scandal politics person noble betrayal treason");

    QTreeWidgetItem *campB = new QTreeWidgetItem(campaignRoot);
    campB->setText(0, "Campaign B: The Sunken Crown");

    QTreeWidgetItem *pirateArticle = new QTreeWidgetItem(campB);
    pirateArticle->setText(0, "The Corsair Alliance");
    pirateArticle->setData(0, Qt::UserRole, "war politics navy scandal person");
}

void WikiTabWidget::filterWikiEntries(const QString &query) {
    QString filter = query.trimmed().toLower();

    auto matchItem = [&filter](QTreeWidgetItem *item) {
        if (filter.isEmpty()) return true;
        QString text = item->text(0).toLower();
        QString tags = item->data(0, Qt::UserRole).toString().toLower();
        return text.contains(filter) || tags.contains(filter);
    };

    for (int i = 0; i < m_treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem *root = m_treeWidget->topLevelItem(i);
        bool rootHasMatch = false;

        for (int j = 0; j < root->childCount(); ++j) {
            QTreeWidgetItem *child = root->child(j);
            
            // Check if sub-campaign level has children
            if (child->childCount() > 0) {
                bool subHasMatch = false;
                for (int k = 0; k < child->childCount(); ++k) {
                    QTreeWidgetItem *leaf = child->child(k);
                    bool match = matchItem(leaf);
                    leaf->setHidden(!match);
                    if (match) subHasMatch = true;
                }
                child->setHidden(!subHasMatch && !matchItem(child));
                if (subHasMatch) rootHasMatch = true;
            } else {
                bool match = matchItem(child);
                child->setHidden(!match);
                if (match) rootHasMatch = true;
            }
        }
        root->setHidden(!rootHasMatch && !matchItem(root));
    }
}

void WikiTabWidget::onArticleSelected(QTreeWidgetItem *current, QTreeWidgetItem *previous) {
    Q_UNUSED(previous);
    if (!current || current->childCount() > 0) return; // Ignore root categories
    m_articleTitleLabel->setText(current->text(0));
    m_articleContentEdit->setPlainText("Displaying article content and descriptors for: " + current->text(0) + 
                                      "\n\nTags: " + current->data(0, Qt::UserRole).toString());
}