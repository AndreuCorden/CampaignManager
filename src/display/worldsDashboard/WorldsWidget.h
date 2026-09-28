#ifndef WORLDSWIDGET_H
#define WORLDSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "database/world.h"

class WorldsWidget : public QWidget {
    Q_OBJECT

public:
    explicit WorldsWidget(QWidget *parent = nullptr);

    // Dynamic UI population methods called by WorldsController
    void populateActiveWorlds(const QList<World> &worlds);
    void populateTopCampaigns(const QList<QPair<int, QString>> &campaigns); // <campaignId, "Campaign Name (World Name)">
    void populateClosedWorlds(const QList<World> &worlds);

signals:
    void backToDashboardRequested();
    void openWorldRequested(int worldId);
    void openCampaignRequested(int campaignId);
    void reactivateWorldRequested(int worldId);
    void createWorldRequested();

private:
    QVBoxLayout *m_activeWorldsLayout;
    QHBoxLayout *m_campaignsLayout;
    QVBoxLayout *m_closedWorldsLayout;

    void clearLayout(QLayout *layout);
};

#endif // WORLDSWIDGET_H