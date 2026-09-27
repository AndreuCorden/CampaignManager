// DashboardController.cpp
#include "DashboardController.h"
#include "database/DatabaseManager.h"
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
    qDebug() << "Opening Worlds Section for user:" << m_userId;
    // TODO: Transition to World List / Wiki view
}

void DashboardController::handleOpenIdeas() {
    qDebug() << "Opening Scratchpad for user:" << m_userId;
}

void DashboardController::handleOpenCharacters() {
    qDebug() << "Opening Character Vault for user:" << m_userId;
}