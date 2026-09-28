// AuthController.h
#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <QObject>
#include "MainWindow.h"

class AuthController : public QObject {
    Q_OBJECT
public:
    explicit AuthController(MainWindow *window, QObject *parent = nullptr);

signals:
    // Emitted when authentication succeeds to pass user context to next controller
    void authenticated(int userId, const QString &username);

private slots:
    void handleLogin();
    void handleRegister();

private:
    MainWindow *m_window;
};

#endif // AUTHCONTROLLER_H