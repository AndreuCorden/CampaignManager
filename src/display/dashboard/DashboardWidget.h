#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include <QWidget>

class HubCardWidget;

class DashboardWidget : public QWidget {
    Q_OBJECT

public:
    explicit DashboardWidget(QWidget *parent = nullptr);

    // Updates cards with counts loaded from SQLite
    void updateMetrics(int worldCount, int ideaCount, int charCount);

signals:
    // User clicked card body
    void openWorldsSectionRequested();
    void openIdeasSectionRequested();
    void openCharactersSectionRequested();

private:
    HubCardWidget *m_worldsCard;
    HubCardWidget *m_ideasCard;
    HubCardWidget *m_charactersCard;
};

#endif // DASHBOARDWIDGET_H