#include "AuthController.h"
#include "display/login/AuthDialog.h"
#include "database/DatabaseManager.h"
#include "display/CustomMessageBox.h"

AuthController::AuthController(MainWindow *window, QObject *parent)
    : QObject(parent), m_window(window)
{
    connect(m_window, &MainWindow::logInRequested, this, &AuthController::handleLogin);
    connect(m_window, &MainWindow::registerRequested, this, &AuthController::handleRegister);
    connect(m_window, &MainWindow::exitRequested, m_window, &MainWindow::close);
}

void AuthController::handleLogin()
{
    AuthDialog dialog(AuthDialog::Login, m_window);
    if (dialog.exec() == QDialog::Accepted)
    {
        int userId = DatabaseManager::instance().authenticateUser(dialog.username(), dialog.password());
        
        if (userId != -1)
        {
            CustomMessageBox::information(m_window, "Success", "Welcome back, " + dialog.username() + "!");
            
            // EMIT SIGNAL HERE to trigger transition in main.cpp
            emit authenticated(userId, dialog.username());
        }
        else
        {
            CustomMessageBox::critical(m_window, "Error", "Invalid username or password.");
            handleLogin();
        }
    }
}

void AuthController::handleRegister()
{
    AuthDialog dialog(AuthDialog::Register, m_window);
    if (dialog.exec() == QDialog::Accepted)
    {
        if (dialog.username().isEmpty() || dialog.password().isEmpty())
        {
            CustomMessageBox::warning(m_window, "Warning", "Fields cannot be empty.");
            handleRegister();
            return;
        }

        int newUserId = DatabaseManager::instance().registerUser(dialog.username(), dialog.password());
        if (newUserId != -1)
        {
            CustomMessageBox::information(m_window, "Success", "Account created successfully!");
            
            // Log in automatically and trigger dashboard transition in main.cpp
            emit authenticated(newUserId, dialog.username());
        }
        else
        {
            CustomMessageBox::critical(m_window, "Error", "Registration failed. Username may already exist.");
            handleRegister();
        }
    }
}