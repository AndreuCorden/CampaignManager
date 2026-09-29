#include "CampaignDropZone.h"
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDataStream>

CampaignDropZone::CampaignDropZone(QWidget *parent) : QFrame(parent) {
    setAcceptDrops(true);
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(8, 8, 8, 8);
    m_layout->setSpacing(8);
}

void CampaignDropZone::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("application/x-campaigncard-id")) {
        event->acceptProposedAction();
        setStyleSheet("CampaignDropZone { border: 2px dashed #D4AF37; background-color: rgba(45, 55, 72, 0.4); border-radius: 8px; }");
    }
}

void CampaignDropZone::dragLeaveEvent(QDragLeaveEvent *event) {
    setStyleSheet("");
    Q_UNUSED(event);
}

void CampaignDropZone::dropEvent(QDropEvent *event) {
    setStyleSheet("");
    if (event->mimeData()->hasFormat("application/x-campaigncard-id")) {
        QByteArray itemData = event->mimeData()->data("application/x-campaigncard-id");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        int campaignId;
        dataStream >> campaignId;

        emit campaignDropped(campaignId);
        event->acceptProposedAction();
    }
}