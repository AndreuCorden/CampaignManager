// DashboardController.cpp
#include "DashboardController.h"
#include "database/DatabaseManager.h"
#include "domain/WorldsController.h"
#include <QDebug>

DashboardController::DashboardController(DashboardWindow *window, int userId, const QString &username, QObject *parent)
    : QObject(parent), m_window(window), m_userId(userId), m_username(username)
{
    // Connect Dashboard view signals to controller slots
    connect(m_window->dashboardWidget(), &DashboardWidget::openWorldsSectionRequested, 
            this, &DashboardController::handleOpenWorlds);
    connect(m_window->dashboardWidget(), &DashboardWidget::openIdeasSectionRequested, 
            this, &DashboardController::handleOpenIdeas);
    connect(m_window->dashboardWidget(), &DashboardWidget::openCharactersSectionRequested, 
            this, &DashboardController::handleOpenCharacters);

    loadUserDashboard();
}

void DashboardController::loadUserDashboard() {
    // 1. Fetch counts from database layer for this user ID
    int worldCount = DatabaseManager::instance().getWorldCount(m_userId);
    int ideaCount = DatabaseManager::instance().getIdeaCount(m_userId);
    int charCount = DatabaseManager::instance().getCharacterCount(m_userId);

    // 2. Populate UI
    m_window->dashboardWidget()->updateMetrics(worldCount, ideaCount, charCount);
}

void DashboardController::handleOpenWorlds() {
    // 1. Create the new Worlds Window
    WorldsWindow *worldsWindow = new WorldsWindow(m_username);

    // 2. Pass ownership to the new WorldsController
    new WorldsController(worldsWindow, m_userId, m_username, worldsWindow);

    // 3. Display the new window
    worldsWindow->show();

    // 4. Close and destroy the current Dashboard window
    m_window->close();
}

void DashboardController::handleOpenIdeas() {
    qDebug() << "Opening Scratchpad for user:" << m_userId;
}

void DashboardController::handleOpenCharacters() {
    qDebug() << "Opening Character Vault for user:" << m_userId;
}