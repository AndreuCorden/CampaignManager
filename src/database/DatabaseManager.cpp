// DatabaseManager.cpp
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QCryptographicHash>
#include <QDebug>

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::initDatabase(const QString &dbPath) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);

    if (!m_db.open()) {
        qDebug() << "Database connection failed:" << m_db.lastError().text();
        return false;
    }

    QSqlQuery query;

    // Enable foreign keys in SQLite (disabled by default in SQLite)
    query.exec("PRAGMA foreign_keys = ON;");

    // 1. Users Table
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "username TEXT UNIQUE NOT NULL, "
               "password_hash TEXT NOT NULL"
               ");");

    // 2. Worlds & Campaigns Shelf Table
    query.exec("CREATE TABLE IF NOT EXISTS worlds ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "user_id INTEGER NOT NULL, "
               "name TEXT NOT NULL, "
               "description TEXT, "
               "updated_at DATETIME DEFAULT CURRENT_TIMESTAMP, "
               "FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE"
               ");");

    // 3. Scratchpad / Loose Ideas Table
    query.exec("CREATE TABLE IF NOT EXISTS loose_ideas ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "user_id INTEGER NOT NULL, "
               "title TEXT NOT NULL, "
               "content TEXT, "
               "updated_at DATETIME DEFAULT CURRENT_TIMESTAMP, "
               "FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE"
               ");");

    // 4. External Player Characters Vault
    query.exec("CREATE TABLE IF NOT EXISTS external_characters ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "user_id INTEGER NOT NULL, "
               "character_name TEXT NOT NULL, "
               "campaign_name TEXT, "
               "updated_at DATETIME DEFAULT CURRENT_TIMESTAMP, "
               "FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE"
               ");");

    return true;
}

static QString hashPassword(const QString &password) {
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

bool DatabaseManager::registerUser(const QString &username, const QString &password) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password_hash) VALUES (:user, :pass)");
    query.bindValue(":user", username);
    query.bindValue(":pass", hashPassword(password));
    return query.exec();
}

bool DatabaseManager::authenticateUser(const QString &username, const QString &password) {
    QSqlQuery query;
    query.prepare("SELECT password_hash FROM users WHERE username = :user");
    query.bindValue(":user", username);
    
    if (query.exec() && query.next()) {
        QString storedHash = query.value(0).toString();
        return storedHash == hashPassword(password);
    }
    return false;
}

int DatabaseManager::getWorldCount(int userId) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM worlds WHERE user_id = :uid");
    query.bindValue(":uid", userId);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int DatabaseManager::getIdeaCount(int userId) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM loose_ideas WHERE user_id = :uid");
    query.bindValue(":uid", userId);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int DatabaseManager::getCharacterCount(int userId) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM external_characters WHERE user_id = :uid");
    query.bindValue(":uid", userId);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}