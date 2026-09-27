#ifndef WORLDSCONTROLLER_H
#define WORLDSCONTROLLER_H

#include <QObject>
#include <QString>

class WorldsWindow; // Forward declaration only

class WorldsController : public QObject {
    Q_OBJECT

public:
    explicit WorldsController(int userId, const QString &username, QObject *parent = nullptr);

private slots:
    void handleBackToDashboard();
    void handleOpenWorld(int worldId);
    void handleOpenCampaign(int campaignId);
    void handleReactivateWorld(int worldId);

private:
    void refreshData();

    WorldsWindow *m_window;
    int m_userId;
    QString m_username;
};

#endif // WORLDSCONTROLLER_H