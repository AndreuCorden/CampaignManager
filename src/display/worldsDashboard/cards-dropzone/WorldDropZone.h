#ifndef WORLDDROPZONE_H
#define WORLDDROPZONE_H

#include <QFrame>

class QVBoxLayout;

class WorldDropZone : public QFrame {
    Q_OBJECT

public:
    explicit WorldDropZone(QWidget *parent = nullptr);
    QVBoxLayout* contentLayout() const { return m_layout; }

signals:
    void worldDropped(int worldId);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    QVBoxLayout *m_layout;
};

#endif // WORLDDROPZONE_H