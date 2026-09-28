#include "WorldsController.h"
#include "DashboardController.h"
#include "display/worldsDashboard/WorldsWindow.h"
#include "database/DatabaseManager.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

WorldsController::WorldsController(int userId, const QString &username, QObject *parent)
    : QObject(parent), m_userId(userId), m_username(username)
{
    // Controller creates and manages its own view window
    m_window = new WorldsWindow(m_username);
    m_window->setAttribute(Qt::WA_DeleteOnClose);

    connect(m_window->worldsWidget(), &WorldsWidget::backToDashboardRequested,
            this, &WorldsController::handleBackToDashboard);
    connect(m_window->worldsWidget(), &WorldsWidget::openWorldRequested,
            this, &WorldsController::handleOpenWorld);
    connect(m_window->worldsWidget(), &WorldsWidget::openCampaignRequested,
            this, &WorldsController::handleOpenCampaign);
    connect(m_window->worldsWidget(), &WorldsWidget::reactivateWorldRequested,
            this, &WorldsController::handleReactivateWorld);

    refreshData();
    m_window->show();
}

void WorldsController::handleBackToDashboard() {
    // Launch DashboardController directly — let it handle its own view!
    new DashboardController(m_userId, m_username);
    m_window->close();
}

void WorldsController::refreshData() {
    // 1. Fetch Active Worlds
    QList<QPair<int, QString>> activeWorlds;
    QSqlQuery q1;
    q1.prepare("SELECT id, name FROM worlds WHERE user_id = :uid AND is_archived = 0 ORDER BY last_opened DESC");
    q1.bindValue(":uid", m_userId);
    if (q1.exec()) {
        while (q1.next()) {
            activeWorlds.append({q1.value(0).toInt(), q1.value(1).toString()});
        }
    }
    m_window->worldsWidget()->populateActiveWorlds(activeWorlds);

    // 2. Fetch Top 5 Active Campaigns Across Worlds
    QList<QPair<int, QString>> topCampaigns;
    QSqlQuery q2;
    q2.prepare("SELECT c.id, c.name || ' (' || w.name || ')' FROM campaigns c "
               "JOIN worlds w ON c.world_id = w.id "
               "WHERE w.user_id = :uid AND w.is_archived = 0 "
               "ORDER BY c.last_opened DESC LIMIT 5");
    q2.bindValue(":uid", m_userId);
    if (q2.exec()) {
        while (q2.next()) {
            topCampaigns.append({q2.value(0).toInt(), q2.value(1).toString()});
        }
    }
    m_window->worldsWidget()->populateTopCampaigns(topCampaigns);

    // 3. Fetch Closed/Archived Worlds
    QList<QPair<int, QString>> closedWorlds;
    QSqlQuery q3;
    q3.prepare("SELECT id, name FROM worlds WHERE user_id = :uid AND is_archived = 1 ORDER BY last_opened DESC");
    q3.bindValue(":uid", m_userId);
    if (q3.exec()) {
        while (q3.next()) {
            closedWorlds.append({q3.value(0).toInt(), q3.value(1).toString()});
        }
    }
    m_window->worldsWidget()->populateClosedWorlds(closedWorlds);
}

void WorldsController::handleOpenWorld(int worldId) {
    QSqlQuery q;
    q.prepare("UPDATE worlds SET last_opened = CURRENT_TIMESTAMP WHERE id = :id");
    q.bindValue(":id", worldId);
    q.exec();
    qDebug() << "Opening World ID:" << worldId;
}

void WorldsController::handleOpenCampaign(int campaignId) {
    QSqlQuery q;
    q.prepare("UPDATE campaigns SET last_opened = CURRENT_TIMESTAMP WHERE id = :id");
    q.bindValue(":id", campaignId);
    q.exec();
    qDebug() << "Opening Campaign ID:" << campaignId;
}

void WorldsController::handleReactivateWorld(int worldId) {
    QSqlQuery q;
    q.prepare("UPDATE worlds SET is_archived = 0, last_opened = CURRENT_TIMESTAMP WHERE id = :id");
    q.bindValue(":id", worldId);
    q.exec();
    
    refreshData();
}