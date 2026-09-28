#include "DashboardController.h"
#include "WorldsController.h" // Only include the Controller!
#include "display/dashboard/DashboardWindow.h"
#include "database/DatabaseManager.h"
#include <QDebug>

DashboardController::DashboardController(int userId, const QString &username, QObject *parent)
    : QObject(parent), m_userId(userId), m_username(username)
{
    // Controller creates and manages its own view window
    m_window = new DashboardWindow(m_username);
    m_window->setAttribute(Qt::WA_DeleteOnClose);

    connect(m_window->dashboardWidget(), &DashboardWidget::openWorldsSectionRequested,
            this, &DashboardController::handleOpenWorlds);

    connect(m_window, &DashboardWindow::logoutRequested, this, &DashboardController::handleLogout);

    loadUserDashboard();
    m_window->show();
}

void DashboardController::loadUserDashboard()
{
    int worldCount = DatabaseManager::instance().getWorldCount(m_userId);
    int ideaCount = DatabaseManager::instance().getIdeaCount(m_userId);
    int charCount = DatabaseManager::instance().getCharacterCount(m_userId);

    m_window->dashboardWidget()->updateMetrics(worldCount, ideaCount, charCount);
}

void DashboardController::handleOpenWorlds()
{
    // Simply delegate execution to WorldsController!
    new WorldsController(m_userId, m_username);
    m_window->close();
}

void DashboardController::handleLogout() {
    // 1. Close current Dashboard Window
    m_window->close();

    // 2. Re-open Login / Auth flow (adjust based on your Auth setup)
    // E.g., relaunching AuthController or showing your MainWindow login window
}