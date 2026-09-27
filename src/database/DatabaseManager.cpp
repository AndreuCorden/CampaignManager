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
        qDebug() << "Database Error:" << m_db.lastError().text();
        return false;
    }

    QSqlQuery query;
    return query.exec("CREATE TABLE IF NOT EXISTS users ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "username TEXT UNIQUE NOT NULL, "
                      "password_hash TEXT NOT NULL"
                      ");");
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