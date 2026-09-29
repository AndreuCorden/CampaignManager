#include "CampaignCard.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QDataStream>

CampaignCard::CampaignCard(int campaignId, const QString &name, const QString &description, bool isArchived, QWidget *parent)
    : QFrame(parent), m_campaignId(campaignId), m_isArchived(isArchived)
{
    setCursor(Qt::PointingHandCursor);
    setFrameShape(QFrame::StyledPanel);
    setFixedHeight(90);

    setStyleSheet(
        "CampaignCard {"
        "  background-color: #1A202C;"
        "  border: 1px solid #4A5568;"
        "  border-radius: 8px;"
        "}"
        "CampaignCard:hover {"
        "  background-color: #2D3748;"
        "  border: 1px solid #D4AF37;"
        "}"
    );

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 8, 12, 8);

    QHBoxLayout *topLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel(name, this);
    titleLabel->setStyleSheet("font-size: 15px; font-weight: bold; color: #D4AF37; border: none; background: transparent;");

    QToolButton *optionsBtn = new QToolButton(this);
    optionsBtn->setText("⋮");
    optionsBtn->setCursor(Qt::PointingHandCursor);
    optionsBtn->setStyleSheet(
        "QToolButton { color: #A0AEC0; font-size: 16px; background: transparent; border: none; padding: 2px; }"
        "QToolButton:hover { color: #D4AF37; background: #2D3748; border-radius: 4px; }"
        "QToolButton::menu-indicator { image: none; }"
    );

    QMenu *optionsMenu = new QMenu(optionsBtn);
    optionsMenu->setStyleSheet(
        "QMenu { background-color: #1A202C; border: 1px solid #4A5568; color: #E2E8F0; padding: 4px; border-radius: 6px; }"
        "QMenu::item { padding: 6px 16px; border-radius: 4px; }"
        "QMenu::item:selected { background-color: #2D3748; color: #D4AF37; }"
    );

    QAction *archiveAction = optionsMenu->addAction(m_isArchived ? "Reactivate Campaign" : "Archive Campaign");
    QAction *deleteAction = optionsMenu->addAction("Delete Campaign");

    optionsBtn->setMenu(optionsMenu);
    optionsBtn->setPopupMode(QToolButton::InstantPopup);

    connect(archiveAction, &QAction::triggered, this, [this]() { emit archiveRequested(m_campaignId); });
    connect(deleteAction, &QAction::triggered, this, [this]() { emit deleteRequested(m_campaignId); });

    topLayout->addWidget(titleLabel, 1);
    topLayout->addWidget(optionsBtn);
    layout->addLayout(topLayout);

    QLabel *descLabel = new QLabel(description.isEmpty() ? "No active quest log." : description, this);
    descLabel->setStyleSheet("font-size: 12px; color: #A0AEC0; border: none; background: transparent;");
    descLabel->setWordWrap(true);
    layout->addWidget(descLabel, 1);
}

void CampaignCard::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_dragStartPosition = event->pos();
    }
    QFrame::mousePressEvent(event);
}

void CampaignCard::mouseMoveEvent(QMouseEvent *event) {
    if (!(event->buttons() & Qt::LeftButton)) return;
    if ((event->pos() - m_dragStartPosition).manhattanLength() < QApplication::startDragDistance()) return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << m_campaignId;

    mimeData->setData("application/x-campaigncard-id", itemData);
    drag->setMimeData(mimeData);
    drag->setPixmap(grab());
    drag->setHotSpot(event->pos());

    drag->exec(Qt::MoveAction);
}

void CampaignCard::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if ((event->pos() - m_dragStartPosition).manhattanLength() < QApplication::startDragDistance()) {
            emit cardClicked(m_campaignId);
        }
    }
    QFrame::mouseReleaseEvent(event);
}