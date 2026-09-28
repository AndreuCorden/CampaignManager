// DatabaseManager.cpp
#include "DatabaseManager.h"
#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QCryptographicHash>
#include <QDebug>

#include <iostream>

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

    // 1. Enable Foreign Keys in SQLite
    QSqlQuery fkQuery(m_db);
    fkQuery.exec("PRAGMA foreign_keys = ON;");

    // 2. Open the SQL schema script file (Use ":/..." for Qt Resources)
    QFile sqlFile(":/src/database/campaign_data.db.sql");
    
    if (!sqlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open schema file:" << sqlFile.errorString();
        return false;
    }

    // 3. Read entire file content
    QString sqlContent = QString::fromUtf8(sqlFile.readAll());
    sqlFile.close();

    // 4. Split the file into individual statements separated by semicolons
    QStringList statements = sqlContent.split(';', Qt::SkipEmptyParts);

    // 5. Execute each DDL statement
    QSqlQuery query(m_db);
    for (QString statement : statements) {
        statement = statement.trimmed();
        
        // Skip empty lines or comment-only strings
        if (statement.isEmpty()) {
            continue;
        }

        if (!query.exec(statement)) {
            qDebug() << "Failed to execute SQL statement:" << query.lastError().text();
            qDebug() << "Failed Query:" << statement;
            return false;
        }
    }

    qDebug() << "Database schema initialized successfully from SQL file.";
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

int DatabaseManager::authenticateUser(const QString &username, const QString &password) {
    QSqlQuery query;
    // 1. Select both 'id' and 'password_hash'
    query.prepare("SELECT id, password_hash FROM users WHERE username = :user");
    query.bindValue(":user", username);
    
    if (query.exec() && query.next()) {
        int userId = query.value(0).toInt();
        QString storedHash = query.value(1).toString();
        
        // 2. Validate password, then return the actual database user ID
        if (storedHash == hashPassword(password)) {
            return userId; 
        }
    }
    return -1; // Login failed
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

QList<World> DatabaseManager::getWorldsForUser(int userId, bool isArchived) {
    QList<World> worlds;
    QSqlQuery query;
    
    query.prepare("SELECT id, name, description, is_archived "
                  "FROM worlds "
                  "WHERE user_id = :uid AND COALESCE(is_archived, 0) = :archived "
                  "ORDER BY updated_at DESC");
                  
    query.bindValue(":uid", userId);
    query.bindValue(":archived", isArchived ? 1 : 0);

    if (query.exec()) {
        while (query.next()) {
            worlds.append(World(
                query.value("id").toInt(),
                query.value("name").toString(),
                query.value("description").toString(),
                query.value("is_archived").toBool()
            ));
        }
    } else {
        qDebug() << "Failed to fetch worlds for user:" << query.lastError().text();
    }

    return worlds;
}

bool DatabaseManager::createWorld(int userId, const QString &name, const QString &description) {
    QSqlQuery query;
    query.prepare("INSERT INTO worlds (user_id, name, description) VALUES (:uid, :name, :desc)");
    query.bindValue(":uid", userId);
    query.bindValue(":name", name);
    query.bindValue(":desc", description);

    if (!query.exec()) {
        qDebug() << "Failed to create world:" << query.lastError().text();
        return false;
    }
    return true;
}