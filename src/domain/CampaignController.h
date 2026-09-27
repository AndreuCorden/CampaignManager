// CampaignController.h
#ifndef CAMPAIGNCONTROLLER_H
#define CAMPAIGNCONTROLLER_H

#include <QObject>
#include "MainWindow.h"

class CampaignController : public QObject {
    Q_OBJECT
public:
    explicit CampaignController(MainWindow *window, QObject *parent = nullptr);

private slots:
    void handleLogin();
    void handleRegister();

private:
    MainWindow *m_window;
};

#endif // CAMPAIGNCONTROLLER_H