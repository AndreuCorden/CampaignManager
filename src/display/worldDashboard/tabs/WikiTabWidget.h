#ifndef WIKITABWIDGET_H
#define WIKITABWIDGET_H

#include <QWidget>

class QLineEdit;
class QTreeWidget;
class QTreeWidgetItem;
class QTextEdit;
class QLabel;

class WikiTabWidget : public QWidget {
    Q_OBJECT

public:
    explicit WikiTabWidget(QWidget *parent = nullptr);

private slots:
    void filterWikiEntries(const QString &query);
    void onArticleSelected(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    QLineEdit *m_searchEdit;
    QTreeWidget *m_treeWidget;
    QLabel *m_articleTitleLabel;
    QTextEdit *m_articleContentEdit;

    void populateSampleData();
};

#endif // WIKITABWIDGET_H