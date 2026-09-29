#include "WorldDropZone.h"
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDataStream>

WorldDropZone::WorldDropZone(QWidget *parent) : QFrame(parent) {
    setAcceptDrops(true);
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(8, 8, 8, 8);
    m_layout->setSpacing(8);
}

void WorldDropZone::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("application/x-worldcard-id")) {
        event->acceptProposedAction();
        // Visual gold-dashed border feedback when dragging over
        setStyleSheet("WorldDropZone { border: 2px dashed #D4AF37; background-color: rgba(45, 55, 72, 0.4); border-radius: 8px; }");
    }
}

void WorldDropZone::dragLeaveEvent(QDragLeaveEvent *event) {
    setStyleSheet("");
    Q_UNUSED(event);
}

void WorldDropZone::dropEvent(QDropEvent *event) {
    setStyleSheet("");
    if (event->mimeData()->hasFormat("application/x-worldcard-id")) {
        QByteArray itemData = event->mimeData()->data("application/x-worldcard-id");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        int worldId;
        dataStream >> worldId;

        emit worldDropped(worldId);
        event->acceptProposedAction();
    }
}