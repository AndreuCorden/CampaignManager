#ifndef WORLDCARD_H
#define WORLDCARD_H

#include <QFrame>

class WorldCard : public QFrame {
    Q_OBJECT

public:
    explicit WorldCard(int worldId, const QString &name, const QString &description, bool isArchived = false, QWidget *parent = nullptr);
    int worldId() const { return m_worldId; }

signals:
    void cardClicked(int worldId);
    void archiveRequested(int worldId);
    void deleteRequested(int worldId);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    int m_worldId;
    bool m_isArchived;
    QPoint m_dragStartPosition;
};

#endif // WORLDCARD_H