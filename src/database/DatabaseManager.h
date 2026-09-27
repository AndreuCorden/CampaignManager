// DatabaseManager.h
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>

class DatabaseManager {
public:
    static DatabaseManager& instance();
    bool initDatabase(const QString &dbPath = "campaign_data.db");
    
    bool registerUser(const QString &username, const QString &password);
    bool authenticateUser(const QString &username, const QString &password);

    int getWorldCount(int userId);
    int getIdeaCount(int userId);
    int getCharacterCount(int userId);

private:
    DatabaseManager() = default;
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H