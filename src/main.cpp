#include <QApplication>
#include "MainWindow.h"
#include "domain/AuthController.h"
#include "domain/DashboardController.h"
#include "database/DatabaseManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!DatabaseManager::instance().initDatabase("campaign_data.db")) {
        return -1;
    }

    app.setStyleSheet(
        // Main Windows & Splitters
        "QMainWindow {"
        "   background-color: #1A202C;"
        "   border: 4px solid #D4AF37;"
        "}"
        "QSplitter::handle {"
        "   background-color: #4A5568;"
        "}"
        "QSplitter::handle:hover {"
        "   background-color: #D4AF37;"
        "}"

        // --- Core UI Navigation & Tabs ---
        "QTabWidget::pane { border: 2px solid #4A5568; background-color: #1A202C; top: -2px; }"
        "QTabBar::tab {"
        "   background: #2D3748; color: #A0AEC0; padding: 12px 24px;"
        "   font-family: 'Georgia', serif; font-weight: bold;"
        "   border: 1px solid #4A5568; border-bottom: none;"
        "   border-top-left-radius: 4px; border-top-right-radius: 4px;"
        "}"
        "QTabBar::tab:selected { background: #1A202C; color: #D4AF37; border-bottom: 2px solid #1A202C; }"

        // --- Tree View Navigation (Lore Directory) ---
        "QTreeView, QListView {"
        "   background-color: #2D3748;"
        "   color: #E2E8F0;"
        "   border: 1px solid #4A5568;"
        "   font-family: 'Georgia', serif;"
        "}"
        "QTreeView::item:selected, QListView::item:selected {"
        "   background-color: #D4AF37;"
        "   color: #1A202C;"
        "   font-weight: bold;"
        "}"

        // --- Wiki & Text Editors ---
        "QTextEdit, QPlainTextEdit {"
        "   background-color: #2D3748;"
        "   color: #F7FAFC;"
        "   border: 1px solid #4A5568;"
        "   selection-background-color: #D4AF37;"
        "   selection-color: #1A202C;"
        "   font-family: 'Georgia', serif;"
        "   font-size: 14px;"
        "}"

        // --- Inputs & Controls ---
        "QLineEdit, QSpinBox {"
        "   background-color: #2D3748;"
        "   color: white;"
        "   border: 1px solid #4A5568;"
        "   padding: 4px;"
        "   border-radius: 3px;"
        "}"
        "QComboBox { background-color: #2D3748; color: white; padding: 5px; border: 1px solid #4A5568; }"
        "QAbstractItemView { background-color: #2D3748; color: white; selection-background-color: #D4AF37; }"

        // --- Dialogs & Popups ---
        "CampaignDialog, QInputDialog, QMessageBox {"
        "   background-color: #1A202C;"
        "   border: 3px solid #D4AF37;"
        "   border-radius: 8px;"
        "   color: white;"
        "}"

        // --- Buttons ---
        "QPushButton {"
        "   background-color: #2D3748;"
        "   color: #D4AF37;"
        "   font-weight: bold;"
        "   border: 1px solid #D4AF37;"
        "   border-radius: 4px;"
        "   padding: 6px 16px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #D4AF37;"
        "   color: #1A202C;"
        "}"

        // --- Progress & Stat Trackers ---
        "QProgressBar {"
        "   background-color: #2D3748;"
        "   border: 1px solid #4A5568;"
        "   border-radius: 4px;"
        "   text-align: center;"
        "   color: #FFFFFF;"
        "   font-weight: bold;"
        "   height: 24px;"
        "   font-size: 11px;"
        "}"
        "QProgressBar::chunk {"
        "   background-color: #E53E3E;" /* Red chunk for health tracking */
        "}"
    );

    MainWindow loginWindow;
    AuthController authController(&loginWindow);

    QObject::connect(&authController, &AuthController::authenticated, 
    [&](int userId, const QString &username) {
        loginWindow.hide();
        new DashboardController(userId, username);
    });

    loginWindow.show();

    return app.exec();
}