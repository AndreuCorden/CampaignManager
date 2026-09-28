#ifndef WORLDCARD_H
#define WORLDCARD_H

#include <QFrame>

class WorldCard : public QFrame {
    Q_OBJECT

public:
    explicit WorldCard(int worldId, const QString &name, const QString &description, QWidget *parent = nullptr);
    int worldId() const { return m_worldId; }

signals:
    void cardClicked(int worldId);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    int m_worldId;
};

#endif // WORLDCARD_H