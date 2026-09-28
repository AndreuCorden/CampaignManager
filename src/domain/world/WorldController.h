#ifndef WORLDCONTROLLER_H
#define WORLDCONTROLLER_H

#include <QObject>
#include <QString>

class WorldWindow;

class WorldController : public QObject {
    Q_OBJECT

public:
    explicit WorldController(int worldId, int userId, const QString &username, QObject *parent = nullptr);

private slots:
    void handleBackToWorlds();

private:
    void loadWorldData();

    WorldWindow *m_window;
    int m_worldId;
    int m_userId;
    QString m_username;
};

#endif // WORLDCONTROLLER_H