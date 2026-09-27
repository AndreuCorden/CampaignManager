#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QMainWindow>
#include "DashboardWidget.h"

class DashboardWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit DashboardWindow(const QString &username, QWidget *parent = nullptr);
    
    // Accessor so DashboardController can talk directly to the inner widget
    DashboardWidget* dashboardWidget() const { return m_dashboardWidget; }

signals:
    void logoutRequested();

private:
    DashboardWidget *m_dashboardWidget;
};

#endif // DASHBOARDWINDOW_H