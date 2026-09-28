#ifndef DASHBOARDCONTROLLER_H
#define DASHBOARDCONTROLLER_H

#include <QObject>
#include <QString>

class DashboardWindow; // Forward declaration only

class DashboardController : public QObject {
    Q_OBJECT

public:
    explicit DashboardController(int userId, const QString &username, QObject *parent = nullptr);

private slots:
    void handleOpenWorlds();
    void handleLogout();

private:
    void loadUserDashboard();

    DashboardWindow *m_window;
    int m_userId;
    QString m_username;
};

#endif // DASHBOARDCONTROLLER_H