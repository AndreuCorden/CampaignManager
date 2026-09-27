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

private:
    DatabaseManager() = default;
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H