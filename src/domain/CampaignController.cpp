#include "CampaignController.h"
#include "display/AuthDialog.h"
#include "database/DatabaseManager.h"
#include "display/CustomMessageBox.h"

CampaignController::CampaignController(MainWindow *window, QObject *parent)
    : QObject(parent), m_window(window)
{
    connect(m_window, &MainWindow::logInRequested, this, &CampaignController::handleLogin);
    connect(m_window, &MainWindow::registerRequested, this, &CampaignController::handleRegister);
    connect(m_window, &MainWindow::exitRequested, m_window, &MainWindow::close);
}

void CampaignController::handleLogin()
{
    AuthDialog dialog(AuthDialog::Login, m_window);
    if (dialog.exec() == QDialog::Accepted)
    {
        bool success = DatabaseManager::instance().authenticateUser(dialog.username(), dialog.password());
        if (success)
        {
            CustomMessageBox::information(m_window, "Success", "Welcome back, " + dialog.username() + "!");
        }
        else
        {
            CustomMessageBox::critical(m_window, "Error", "Invalid username or password.");
            handleLogin();
        }
    }
}

void CampaignController::handleRegister()
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

        bool created = DatabaseManager::instance().registerUser(dialog.username(), dialog.password());
        if (created)
        {
            CustomMessageBox::information(m_window, "Success", "Account created successfully! You can now log in.");
        }
        else
        {
            CustomMessageBox::critical(m_window, "Error", "Registration failed. Username may already exist.");
            handleRegister();
        }
    }
}