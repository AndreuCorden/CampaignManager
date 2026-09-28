#include "WorldController.h"
#include "domain/worlds/WorldsController.h"
#include "display/worldDashboard/WorldWindow.h"
#include "database/DatabaseManager.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

WorldController::WorldController(int worldId, int userId, const QString &username, QObject *parent)
    : QObject(parent), m_worldId(worldId), m_userId(userId), m_username(username)
{
    m_window = new WorldWindow(m_username);
    m_window->setAttribute(Qt::WA_DeleteOnClose);

    connect(m_window, &WorldWindow::backToWorldsRequested, this, &WorldController::handleBackToWorlds);

    loadWorldData();
    m_window->show();
}

void WorldController::loadWorldData() {
    QSqlQuery q;
    q.prepare("SELECT name, description FROM worlds WHERE id = :id");
    q.bindValue(":id", m_worldId);
    if (q.exec() && q.next()) {
        QString name = q.value(0).toString();
        QString desc = q.value(1).toString();
        m_window->setWorldDetails(name, desc);
    }
}

void WorldController::handleBackToWorlds() {
    new WorldsController(m_userId, m_username);
    m_window->close();
}