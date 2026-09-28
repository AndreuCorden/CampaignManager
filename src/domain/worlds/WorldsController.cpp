#include "WorldsController.h"
#include "domain/dashboard/DashboardController.h"
#include "display/worldsDashboard/WorldsWindow.h"
#include "display/worldsDashboard/CreateWorldDialog.h"
#include "domain/world/WorldController.h"
#include "database/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
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
    connect(m_window->worldsWidget(), &WorldsWidget::createWorldRequested,
            this, &WorldsController::handleCreateWorld);

    loadWorldsData();
    m_window->show();
}

void WorldsController::handleBackToDashboard()
{
    // Launch DashboardController directly — let it handle its own view!
    new DashboardController(m_userId, m_username);
    m_window->close();
}

void WorldsController::loadWorldsData() {
    // 1. Fetch active and archived worlds from DatabaseManager
    QList<World> activeWorlds = DatabaseManager::instance().getWorldsForUser(m_userId, false);
    QList<World> archivedWorlds = DatabaseManager::instance().getWorldsForUser(m_userId, true);

    // 2. Pass structured records straight to UI
    m_window->worldsWidget()->populateActiveWorlds(activeWorlds);
    m_window->worldsWidget()->populateClosedWorlds(archivedWorlds);
}

void WorldsController::handleOpenWorld(int worldId)
{
    QSqlQuery q;
    q.prepare("UPDATE worlds SET last_opened = CURRENT_TIMESTAMP WHERE id = :id");
    q.bindValue(":id", worldId);
    q.exec();
    qDebug() << "Opening World ID:" << worldId;
}

void WorldsController::handleOpenCampaign(int campaignId)
{
    QSqlQuery q;
    q.prepare("UPDATE campaigns SET last_opened = CURRENT_TIMESTAMP WHERE id = :id");
    q.bindValue(":id", campaignId);
    q.exec();
    qDebug() << "Opening Campaign ID:" << campaignId;
}

void WorldsController::handleReactivateWorld(int worldId)
{
    QSqlQuery q;
    q.prepare("UPDATE worlds SET is_archived = 0, last_opened = CURRENT_TIMESTAMP WHERE id = :id");
    q.bindValue(":id", worldId);
    q.exec();

    loadWorldsData();
}

void WorldsController::handleCreateWorld() {
    CreateWorldDialog dialog(m_window);
    
    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.worldName();
        QString desc = dialog.worldDescription();

        if (name.isEmpty()) return;

        // Delegate insertion to DatabaseManager
        if (DatabaseManager::instance().createWorld(m_userId, name, desc)) {
            loadWorldsData(); // Refresh list on success
        }
    }
}