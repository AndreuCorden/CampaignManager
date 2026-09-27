// DashboardController.h
#ifndef DASHBOARDCONTROLLER_H
#define DASHBOARDCONTROLLER_H

#include <QObject>
#include "display/dashboard/DashboardWindow.h"

class DashboardController : public QObject {
    Q_OBJECT
public:
    explicit DashboardController(DashboardWindow *window, int userId, const QString &username, QObject *parent = nullptr);

private slots:
    void loadUserDashboard();
    void handleOpenWorlds();
    void handleOpenIdeas();
    void handleOpenCharacters();

private:
    DashboardWindow *m_window;
    int m_userId;
    QString m_username;
};

#endif // DASHBOARDCONTROLLER_H