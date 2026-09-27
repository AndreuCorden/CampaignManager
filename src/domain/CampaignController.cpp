// CampaignController.cpp
#include "CampaignController.h"
#include "AuthDialog.h"
#include "DatabaseManager.h"
#include <QMessageBox>

CampaignController::CampaignController(MainWindow *window, QObject *parent)
    : QObject(parent), m_window(window) 
{
    connect(m_window, &MainWindow::logInRequested, this, &CampaignController::handleLogin);
    connect(m_window, &MainWindow::registerRequested, this, &CampaignController::handleRegister);
    connect(m_window, &MainWindow::exitRequested, m_window, &MainWindow::close);
}

void CampaignController::handleLogin() {
    AuthDialog dialog(AuthDialog::Login, m_window);
    if (dialog.exec() == QDialog::Accepted) {
        bool success = DatabaseManager::instance().authenticateUser(dialog.username(), dialog.password());
        if (success) {
            QMessageBox::information(m_window, "Success", "Welcome back, " + dialog.username() + "!");
            // TODO: Load workspace dashboard
        } else {
            QMessageBox::critical(m_window, "Error", "Invalid username or password.");
        }
    }
}

void CampaignController::handleRegister() {
    AuthDialog dialog(AuthDialog::Register, m_window);
    if (dialog.exec() == QDialog::Accepted) {
        if (dialog.username().isEmpty() || dialog.password().isEmpty()) {
            QMessageBox::warning(m_window, "Warning", "Fields cannot be empty.");
            return;
        }

        bool created = DatabaseManager::instance().registerUser(dialog.username(), dialog.password());
        if (created) {
            QMessageBox::information(m_window, "Success", "Account created successfully! You can now log in.");
        } else {
            QMessageBox::critical(m_window, "Error", "Username already exists.");
        }
    }
}