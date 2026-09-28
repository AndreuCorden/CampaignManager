#ifndef WORLD_H
#define WORLD_H

#include <QString>

class World {
public:
    World(int id, const QString &name, const QString &description = "", bool isArchived = false)
        : m_id(id), m_name(name), m_description(description), m_isArchived(isArchived) {}

    int id() const { return m_id; }
    QString name() const { return m_name; }
    QString description() const { return m_description; }
    bool isArchived() const { return m_isArchived; }

private:
    int m_id;
    QString m_name;
    QString m_description;
    bool m_isArchived;
};

#endif // WORLD_H