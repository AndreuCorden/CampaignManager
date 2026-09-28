#ifndef WORLDWIDGET_H
#define WORLDWIDGET_H

#include <QWidget>

class QTabWidget;
class QLabel;
class QTextEdit;

class WorldWidget : public QWidget {
    Q_OBJECT

public:
    explicit WorldWidget(QWidget *parent = nullptr);

    void setWorldDetails(const QString &name, const QString &description);

private:
    void setupWikiTab(QTabWidget *tabs);
    void setupTimelineTab(QTabWidget *tabs);
    void setupMapsTab(QTabWidget *tabs);
    void setupCampaignsTab(QTabWidget *tabs);

    QLabel *m_worldTitleLabel = nullptr;
    QTextEdit *m_worldDescEdit = nullptr;
};

#endif // WORLDWIDGET_H