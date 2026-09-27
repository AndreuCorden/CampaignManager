#include "WorldsController.h"
#include "display/dashboard/DashboardWindow.h"
#include "domain/DashboardController.h"
#include "database/DatabaseManager.h"
#include <QSqlQuery>

WorldsController::WorldsController(WorldsWindow *window, int userId, const QString &username, QObject *parent)
    : QObject(parent), m_window(window), m_userId(userId), m_username(username)
{
    // Connect Back Button to return handler
    connect(m_window->worldsWidget(), &WorldsWidget::backToDashboardRequested, 
            this, &WorldsController::handleBackToDashboard);

    connect(m_window->worldsWidget(), &WorldsWidget::openWorldRequested, 
            this, &WorldsController::handleOpenWorld);
    connect(m_window->worldsWidget(), &WorldsWidget::openCampaignRequested, 
            this, &WorldsController::handleOpenCampaign);
    connect(m_window->worldsWidget(), &WorldsWidget::reactivateWorldRequested, 
            this, &WorldsController::handleReactivateWorld);

    refreshData();
}

void WorldsController::handleBackToDashboard() {
    // 1. Re-create Dashboard Window
    DashboardWindow *dashWindow = new DashboardWindow(m_username);

    // 2. Re-instantiate Dashboard Controller
    new DashboardController(dashWindow, m_userId, m_username, dashWindow);

    // 3. Show Dashboard
    dashWindow->show();

    // 4. Close Worlds Window
    m_window->close();
}