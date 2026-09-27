#ifndef WORLDSCONTROLLER_H
#define WORLDSCONTROLLER_H

#include <QObject>
#include "display/worldsDashboard/WorldsWindow.h"

class WorldsController : public QObject {
    Q_OBJECT

public:
    explicit WorldsController(WorldsWindow *window, int userId, const QString &username, QObject *parent = nullptr);
    void refreshData();

private slots:
    void handleBackToDashboard();
    void handleOpenWorld(int worldId);
    void handleOpenCampaign(int campaignId);
    void handleReactivateWorld(int worldId);

private:
    WorldsWindow *m_window;
    int m_userId;
    QString m_username;
};

#endif // WORLDSCONTROLLER_H